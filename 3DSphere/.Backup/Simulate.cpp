#include "mfem.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Simulate.h"

using namespace std;
using namespace mfem;


void PerformExp(flowParameters &FP,int myid,ParMesh *pmesh,int order,
                int num_iterations,double tol){
   FP.order = order;
   FP.num_iterations = num_iterations;
   FP.tol = tol;


// Parse command-line options.
   const char *mesh_file = "mesh.msh";
   bool static_cond = true;
   bool pa = false;
   const char *device_config = "cpu";
   bool visualization = false;
   bool algebraic_ceed = false;


   //int dparser = DefaultParser(FP.args,myid,mesh_file,order,static_cond,pa,device_config,
   //            visualization,algebraic_ceed);

   Device device(device_config);
   if (myid == 0) { device.Print(); }
   //Read the mesh from the given mesh file
   int dim = pmesh->Dimension();

   FiniteElementCollection *fec;
   bool delete_fec = true;
   fec = new H1_FECollection(order, dim);

   ParFiniteElementSpace fespace(pmesh, fec);
   HYPRE_BigInt size = fespace.GlobalTrueVSize();
   if (myid == 0)
   {
      cout << "Number of finite element unknowns: " << size << endl;
   }

   //Set the ess_bdr attributes
   Array<int> ess_tdof_list;

   Array<int> ess_bdr(pmesh->bdr_attributes.Max());
   ess_bdr = 1; //ess_bdr[4] = 0;
   fespace.GetEssentialTrueDofs(ess_bdr, ess_tdof_list);
   //Array<int> nbdr(pmesh->bdr_attributes.Max());
   //nbdr = 0; nbdr[4] = 1;

   double hmin,hmax,kappamin,kappamax;
   pmesh->GetCharacteristics(hmin,hmax,kappamin,kappamax);
   FP.hmin = hmin; FP.hmax = hmax;
   FP.kappamin = kappamin; FP.kappamax = kappamax;

   //Define and set the linear form
   ParLinearForm b(&fespace);
   ConstantCoefficient one(1.0);
   ConstantCoefficient zero(0.0);
   //b.AddDomainIntegrator(new DomainLFIntegrator(zero));
   //b.AddBoundaryIntegrator(new BoundaryLFIntegrator(zero),nbdr);
   b.Assemble();

   // 8. Define the solution vector x as a finite element grid function
   //    corresponding to fespace. Initialize x with initial guess of zero,
   //    which satisfies the boundary conditions.

   ParGridFunction x(&fespace);
   ParGridFunction exact_sol(&fespace);
   x = 0.0;
   FunctionCoefficient f_sol(f_exact);
   x.ProjectBdrCoefficient(f_sol,ess_bdr);
   exact_sol.ProjectCoefficient(f_sol);
   //x.ProjectCoefficient(f_sol);

   // 9. Set up the bilinear form a(.,.)
   ParBilinearForm a(&fespace);
   if (pa) { a.SetAssemblyLevel(AssemblyLevel::PARTIAL); }
   a.AddDomainIntegrator(new DiffusionIntegrator(one));

   // Solve the linear system and recover the solution
   if (static_cond) { a.EnableStaticCondensation(); }
   a.Assemble();

   OperatorPtr A;
   Vector B, X;
   a.FormLinearSystem(ess_tdof_list, x, b, A, X, B);

   // 13. Solve the linear system A X = B.
   //     * With full assembly, use the BoomerAMG preconditioner from hypre.
   //     * With partial assembly, use Jacobi smoothing, for now.
   Solver *prec = NULL;
   if (pa)
   {
      if (UsesTensorBasis(fespace))
      {
         if (algebraic_ceed)
         {
            prec = new ceed::AlgebraicSolver(a, ess_tdof_list);
         }
         else
         {
            prec = new OperatorJacobiSmoother(a, ess_tdof_list);
         }
      }
   }
   else
   {
      prec = new HypreBoomerAMG;
   }
   CGSolver cg(MPI_COMM_WORLD);
   cg.SetRelTol(FP.tol);
   cg.SetMaxIter(FP.num_iterations);
   cg.SetPrintLevel(1);
   if (prec) { cg.SetPreconditioner(*prec); }
   cg.SetOperator(*A);
   cg.Mult(B, X);
   delete prec;

   FP.sizeSys = A->Height();
   a.RecoverFEMSolution(X, b, x);
   FP.L2error = x.ComputeL2Error(f_sol);

//Create Vectorial Space and get the Laplacian of x
   H1_FECollection vectorfec = H1_FECollection(order, pmesh->Dimension());
   ParFiniteElementSpace *vectorfes = new ParFiniteElementSpace(pmesh,&vectorfec,pmesh->Dimension());
   ParGridFunction Gradx = get_gradient(x,vectorfes);
   ParGridFunction Grad_exact_sol = get_gradient(exact_sol,vectorfes);
   VectorFunctionCoefficient vec_grad_exact(pmesh->Dimension(),grad_exact);


//14.5 Compute L2 grad error
   FP.grad_error = get_error(Gradx,vec_grad_exact,FP.order);
   if(myid == 0){ FP.SaveConvergenceInfo();}

   // Save the refined mesh and the solution.
    SaveParams(FP,x,pmesh);
    //Send the solution by socket to a GLVis server.
    Visualize(visualization,pmesh,x);
    //  Save data in the ParaView format
    SaveInParaView(FP,pmesh,x,exact_sol,Gradx,Grad_exact_sol);


   // 15. Free the used memory.

    delete fec;
    delete vectorfes;

}
