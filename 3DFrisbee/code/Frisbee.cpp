#include "mfem.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Simulate.h"

using namespace std;
using namespace mfem;


int main(int argc, char *argv[])
{
   Mpi::Init();
   int num_procs = Mpi::WorldSize();
   int myid = Mpi::WorldRank();
   Hypre::Init();

   const char *mesh_file = "mesh.msh";
   Mesh mesh(mesh_file, 1, 1);

   ParMesh pmesh(MPI_COMM_WORLD, mesh);
   mesh.Clear();

   int max_order = 2;
   int ref_levels = 2;
   flowParameters FP;
   FP.refine_param = 1;
   FP.num_iterations = 2000;
   FP.tol = 1e-12;
   int order = 2;
   for(int l = 0; l < ref_levels;l++){
      FP.NE = Refine_mesh(&pmesh,FP.refine_param); //Number of elements
   }
   FP.order = order;
   PerformExp(FP,myid,&pmesh,order,FP.num_iterations,1e-12);
return 0;
}
