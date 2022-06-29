#include "mfem.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace mfem;

double func(const Vector &X);
double Divfunc(const Vector &X);
double Chi(const Vector &X){
   double r2 = X(0)*X(0) + X(1)*X(1) + X(2)*X(2);
   if(abs(r2) < 4){
      return 0;
   }
   else{
      return 1;
   }
}


class FF: public VectorCoefficient
{
   private:
      double a;
      //void (*Function)(const Vector &,Vector &);
   public:

      FF(int dim):VectorCoefficient(dim){};
      virtual ~FF(){};
      virtual void Eval(Vector &K, ElementTransformation &T,
                        const IntegrationPoint &ip)
      {
         double transip[3];
         Vector x(transip, 3);
         T.Transform(ip, x);
         K.SetSize(vdim);
         double r2 = x(0)*x(0) + x(1)*x(1) + x(2)*x(2);
         double r = sqrt(r2);
         K(0) = x(0)*x(0)/r;
         K(1) = x(0)*x(1)/r;
         K(2) = x(0)*x(2)/r;
      }
};

int main(int argc, char *argv[])
{
   // 1. Parse command-line options.
   const char *mesh_file = "mesh.msh";
   int order = 1;
   bool static_cond = false;
   bool pa = false;
   const char *device_config = "cpu";
   bool visualization = true;
   bool algebraic_ceed = false;
   Device device(device_config);
   device.Print();

   // 3. Read the mesh from the given mesh file. We can handle triangular,
   //    quadrilateral, tetrahedral, hexahedral, surface and volume meshes with
   //    the same code.
   Mesh mesh(mesh_file, 1, 1);
   int dim = mesh.Dimension();
   {
      int ref_levels = 0;
      cout << "ref_levels\t" << ref_levels << endl;
      for (int l = 0; l < ref_levels; l++)
      {
         mesh.UniformRefinement();
      }
   }
   cout << "Finalize ref\n";
   cout << "Number of attr\t" << mesh.bdr_attributes.Max() <<endl;
    cout << "Number of elements\t" << mesh.GetNE() <<endl;
   cout << "Dim\t" << dim << endl;

   FiniteElementCollection *fec;
   bool delete_fec;
   fec = new H1_FECollection(order, dim);
   FiniteElementSpace fespace(&mesh, fec);

   //Characteristic function for sphere bdr
   Vector Xi(mesh.bdr_attributes.Max());
   Xi = 0.0;
   Xi[4] = 1.0;
   PWConstCoefficient XiCoeff = PWConstCoefficient(Xi);

   Array<int> ess_tdof_list, ess_bdr(mesh.bdr_attributes.Max());
   ess_bdr = 1;

   //fespace.GetEssentialTrueDofs(ess_bdr, ess_tdof_list);


   GridFunction x(&fespace),y(&fespace);
   //GridFunction *x = new GridFunction(&fespace);
   x = 0.0; //y = 0.0;
   ConstantCoefficient one(1.0);
   //x.ProjectBdrCoefficient(one,ess_bdr);
   FunctionCoefficient funcCoeff(func);
   FunctionCoefficient DivfuncCoeff(Divfunc);
   x.ProjectBdrCoefficient(funcCoeff,ess_bdr);
   //y.ProjectCoefficient(one);
   //x.ProjectBdrCoefficient(funcCoeff,ess_bdr);
   //x.ProjectBdrCoefficient(zero,ess_bdr2);
//x->ProjectBdrCoefficient(one,ess_bdr);

   FF normalF(dim);
   LinearForm lf_bdr(&fespace);
   //lf_bdr.AddBoundaryIntegrator(new BoundaryNormalLFIntegrator(normalF));
   lf_bdr.AddBoundaryIntegrator(new BoundaryLFIntegrator(XiCoeff));
   lf_bdr.Assemble();
   double bdr_int = lf_bdr(x);

/* FunctionCoefficient ChiC(Chi);
   LinearForm lf_dom(&fespace);
   lf_dom.AddDomainIntegrator(new DomainLFIntegrator(DivfuncCoeff));
   lf_dom.Assemble();
   double dom_int = lf_dom(y);
*/

   //cout << "Error\t" << abs(bdr_int-100*6) << endl;
   //cout << "Error\t" << abs(bdr_int-(4*M_PI*pow(2,2))) << endl;
   cout << "Error\t" << abs(bdr_int-(4.0/3.0*M_PI*pow(2,4))) << endl;
   cout << "Error\t" << abs(bdr_int) << endl;

   //cout << "Error\t" << abs(dom_int - bdr_int) << endl;
   delete fec;
   //delete XiCoeff;e

   return 0;
}


double func(const Vector &X){
   return X(0);//*X(0);
}

double Divfunc(const Vector &X){
   double r2 = X(0)*X(0) + X(1)*X(1) + X(2)*X(2);
   return 3*X(0)/sqrt(r2);
}
