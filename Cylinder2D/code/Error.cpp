#include "mfem.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Error.h"

using namespace std;
using namespace mfem;

flowParameters PP;
double vel = PP.speed;
double radius = PP.radius;
double side = PP.side;

ParGridFunction get_gradient(const ParGridFunction &X,
                   ParFiniteElementSpace *VectFes){
   ParGridFunction Gradx(VectFes);
   Gradx = 0.0;
   GradientGridFunctionCoefficient grad(&X);
   Gradx.ProjectCoefficient(grad);
   return Gradx;
}


double f_exact(const Vector &x){
    double r2 = x(0)*x(0) + x(1)*x(1);
    return vel*(1+radius*radius/r2)*x(0);
}

void grad_exact(const Vector &X, Vector &Grad){
    double r2 = X(0)*X(0) + X(1)*X(1);
    Grad(0) = vel*(1 + pow(radius/r2,2)*(X(1)*X(1)-X(0)*X(0)));
    Grad(1) = -2*vel*pow(radius/r2,2)*X(0)*X(1);
}


double get_error(ParGridFunction &GF,
                 VectorFunctionCoefficient &VF,int order){
    const IntegrationRule *irs[Geometry::NumGeom];
    int order_quad = max(2, 2*order+1);
    for (int ii=0; ii < Geometry::NumGeom; ++ii)
        irs[ii] = &(IntRules.Get(ii, order_quad));

return GF.ComputeL2Error(VF,irs);
}
