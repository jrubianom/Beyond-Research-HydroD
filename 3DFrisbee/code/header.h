#ifndef _HEADER_H
#define _HEADER_H


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "mfem.hpp"

using namespace std;
using namespace mfem;

struct flowParameters{
    //PDE params
    double speed = 1.0;
    double radius = 2.0;
    double side = 60;

    //FEM params
    int refine_param = 10;
    int order = 1;
    int num_iterations;
    double tol;
    double hmin = 0.0;
    double hmax = 0.0;
    double kappamin = 0.0;
    double kappamax = 0.0;
    int NE = 0; //Number of elements
    int sizeSys = 0;
    double grad_error = 100;
    double L2error = 100;


    bool start = true; //Indicates the first iteration

    //Files names
    string nameFile(){
        return to_string(refine_param) +"-order-"+ to_string(order);
    }
    string SolFile(){
        return nameFile() + ".gf";
    }
    string meshFile(){
        return nameFile() + "refined.mesh";
    }

    void SaveConvergenceInfo();
};
/* /
extern flowParameters PP;
extern double vel;
extern double radius;
extern double side;
*/

int DefaultParser(OptionsParser &args,int myid,const char *mesh_file,
                  int order,bool static_cond,bool pa,
                  const char *device_config,
                  bool visualization,bool algebraic_ceed);

void SaveParams(flowParameters &FP, ParGridFunction &x,ParMesh *mesh);
void Visualize(bool visualization,ParMesh *mesh, ParGridFunction &x);
void SaveInParaView(flowParameters &FP,ParMesh *mesh,
                    ParGridFunction &x);

int Refine_mesh(ParMesh *pmesh,int ref_levels);


#endif
