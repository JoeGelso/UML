//Documentation in Ants_and_DoodleBugs.h
#include "Ants_and_Doodlebugs.h"
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main(){
	World w;
	//int num_ants, num_doodlebugs;
	w.init_world();
	w.init_critters();
	cout << "Once simulation begins, press Enter to go to next time step.\n"
		<< "Hold Enter to keep cycling.\n"
		<< "Press Enter to begin simulation.";
	cin.get();
	system("CLS");
	w.run_simulation();
	return 0;
}
