#ifndef STOPNALREGIONSMT2HIGGS_H
#define STOPNALREGIONSMT2HIGGS_H

#include <string>
#include "TTree.h"
#include "SR.h"

std::vector<SR> getStopSignalRegions();
std::vector<SR> getStopControlRegions();
std::vector<SR> getStopControlRegionsDilepton();
std::vector<SR> getStopControlRegionsNoBTags();

#endif // STOPNALREGIONSMT2HIGGS_H
