#include <eigen3/Eigen/Eigen>
#include <functional>
#include <vector>

#include "cma.h"
#include "sigma_adaptation.h"

#include "types.h"

class Solutions {};

class Population {};

class Parameters {};

template <typename T_CMAUpdate, typename T_SigmaUpdate> class cmaes {
public:
  cmaes(){};
  Solutions optimize();

private:
  Population ask();
  void tell();
  bool terminate();
  void increase_iter();

  Parameters m_parameters;
  Solutions m_solutions;
  T_CMAUpdate m_CMAupdate;
  T_SigmaUpdate m_SigmaUpdate;
};
