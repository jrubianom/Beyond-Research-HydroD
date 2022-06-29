#include "mfem.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Error.h"
#include <cmath>

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
    double r2 = x(0)*x(0) + x(1)*x(1)+x(2)*x(2);
    return vel*(1+0.5*pow(radius,3)/pow(r2,3.0/2.0))*x(2);
}

void grad_exact(const Vector &x, Vector &Grad){
    double r2 = x(0)*x(0) + x(1)*x(1) + x(2)*x(2);
    double cte = vel*0.5*pow(radius,3)/pow(r2,3.0/2.0);
    Grad(0) = -3*cte*x(2)*x(0)/r2;
    Grad(1) = -3*cte*x(2)*x(1)/r2;
    Grad(2) = vel + cte*(1-3*pow(x(2),2)/r2);
}


double get_error(ParGridFunction &GF,
                 VectorFunctionCoefficient &VF,int order){
    const IntegrationRule *irs[Geometry::NumGeom];
    int order_quad = max(2, 2*order+1);
    for (int ii=0; ii < Geometry::NumGeom; ++ii)
        irs[ii] = &(IntRules.Get(ii, order_quad));

return GF.ComputeL2Error(VF,irs);
}
