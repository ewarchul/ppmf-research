#include <functional>
#include <eigen3/Eigen/Eigen>
#include <vector>

#include "types.h"

class cmaes_ew {
public:
  cmaes_ew(FitnessFunction eval);
private:
  void optimize();
  DummyPopulation ask();
  void tell();
  bool terminate();

  void update_eval(int evals);
  void inc_iter();

  int m_eval;
  int m_iter;

};
