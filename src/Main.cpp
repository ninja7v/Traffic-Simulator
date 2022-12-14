////////////////////////////////////////////////////////////////
// Traffic light modelisation by Luc and Claire PREVOST, 2022 //
////////////////////////////////////////////////////////////////

// Header files
#include "../headers/Network.h"
#include "omp.h"           // To parallelize
#include <iostream>        // To use input/output
using namespace std;

int main(void) {
   // INITIALIZATION
   Network net = Network();
 
   // VISUALTISATION
   net.displayNetwork();

   return 0;
}
