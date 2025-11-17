/////////////////////////////////////////////////////////////////////
// Traffic light modelisation by Luc and Claire PREVOST, 2022-2024 //
/////////////////////////////////////////////////////////////////////

// Header files
#include "../headers/Network.h"
# if DEBUG
#include "../Tests/Test.h"
#endif

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
