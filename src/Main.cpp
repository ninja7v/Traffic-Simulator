//////////////////////////////////////////////////
// Traffic light modelisation by Luc PREVOST, 2021
//////////////////////////////////////////////////

// Header files
#include "Network.h"

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
