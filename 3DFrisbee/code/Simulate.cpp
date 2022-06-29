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
   ess_bdr = 0; ess_bdr[2] = 1; ess_bdr[3] = 1; 
   fespace.GetEssentialTrueDofs(ess_bdr, ess_tdof_list);
   Array<int> dbdr2(pmesh->bdr_attributes.Max());
   dbdr2 = 0; dbdr2[2] = 1;
   Array<int> dbdr3(pmesh->bdr_attributes.Max());
   dbdr3 = 0; dbdr3[3] = 1;
   
   double hmin,hmax,kappamin,kappamax;
   pmesh->GetCharacteristics(hmin,hmax,kappamin,kappamax);
   FP.hmin = hmin; FP.hmax = hmax;
   FP.kappamin = kappamin; FP.kappamax = kappamax;

   //Define and set the linear form
   ParLinearForm b(&fespace);
   ConstantCoefficient one(1.0);
   ConstantCoefficient in2(-1.0);
   ConstantCoefficient out3(1.0);
   ConstantCoefficient zero(0.0);
   //b.AddDomainIntegrator(new DomainLFIntegrator(zero));
   //b.AddBoundaryIntegrator(new BoundaryLFIntegrator(airfoil),nbdr);
   //b.AddBoundaryIntegrator(new BoundaryLFIntegrator(airfoil),nbdr2);
   b.Assemble();

   // 8. Define the solution vector x as a finite element grid function
   //    corresponding to fespace. Initialize x with initial guess of zero,
   //    which satisfies the boundary conditions.

   ParGridFunction x(&fespace);
   ParGridFunction exact_sol(&fespace);
   x = 0.0;
   //FunctionCoefficient f_sol(f_exact);
   x.ProjectBdrCoefficient(in2,dbdr2);
   x.ProjectBdrCoefficient(out3,dbdr3);
   //x.ProjectBdrCoefficient(one,ess_bdr);
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
   //FP.L2error = x.ComputeL2Error(f_sol);


//14.5 Compute L2 grad error
   if(myid == 0){ FP.SaveConvergenceInfo();}

   // Save the refined mesh and the solution.
    SaveParams(FP,x,pmesh);
    //Send the solution by socket to a GLVis server.
    Visualize(visualization,pmesh,x);
    //  Save data in the ParaView format
    SaveInParaView(FP,pmesh,x);


   // 15. Free the used memory.

    delete fec;

}
