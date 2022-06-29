#ifndef _SIMULATE_H
#define _SIMULATE_H

#include "mfem.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Error.h"

using namespace std;
using namespace mfem;


void PerformExp(flowParameters &FP,int myid,ParMesh *pmesh,int order = 1,int num_iterations = 1000,
                double tol = 1e-9);

#endif
