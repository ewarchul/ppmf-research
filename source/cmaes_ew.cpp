#include "../include/cmaes_ew.h"
#include "../include/types.h"


DummyPopulation cmaes_ew::ask() { return std::vector<Eigen::VectorXd>(1); };

void cmaes_ew::tell(){};

bool cmaes_ew::terminate() { return true; };
