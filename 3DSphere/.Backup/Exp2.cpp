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
   int ref_levels = 3;
   flowParameters FP;
   FP.refine_param = 1;
   FP.num_iterations = 2000;
   FP.tol = 1e-12;
   for(int l = 0; l < ref_levels;l++){
      FP.NE = Refine_mesh(&pmesh,FP.refine_param); //Number of elements
      for(int order = 1; order <= max_order; order++){
         FP.order = order;
         PerformExp(FP,myid,&pmesh,order,7000,1e-12);
         FP.start = false;
      }
   }
return 0;
}
