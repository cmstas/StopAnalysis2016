#include "met-resolution.h"

int main() {

	// Run the neutrino pT looper
	looper_nu();

	// Combine the output files into a single file
	mergeStopBabies( "Output/Histos/", "Output/Histos/", true);

	return 0;
}
