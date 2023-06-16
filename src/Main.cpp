////////////////////////////////////////////////////////////////
// Traffic light modelisation by Luc and Claire PREVOST, 2023 //
////////////////////////////////////////////////////////////////

// Header files
#include "../headers/Network.h"
#include "../Tests/Test.h"
#include "omp.h"           // To parallelize
#include <iostream>        // To use input/output
using namespace std;

int main(void) {
   //Tests
# if DEBUG
   runTests();
#endif

   // INITIALIZATION
   Network net = Network();
 
   // VISUALTISATION
   net.displayNetwork();

   return 0;
}
