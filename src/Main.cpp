////////////////////////////////////////////////////////////////
// Traffic light modelisation by Luc and Claire PREVOST, 2022 //
////////////////////////////////////////////////////////////////

// Header files
#include "../headers/Network.h"

using namespace std;

int main(void) {
   // INITIALIZATION
   Network net = Network();
 
   // VISUALTISATION
   net.displayNetwork();

   // OPTIMIZATION
   //net.optimization(0);

   // VISUALTISATION
   //net.displayNetwork();
   return 0;
}
