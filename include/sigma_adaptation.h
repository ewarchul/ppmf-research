#ifndef SIGMA_ADAPTATION_H
#define SIGMA_ADAPTATION_H
#include "solutions.h"

class CSA {
public:
  static void update(Solutions &solutions, Parameters &params);
};

class PPMF {
public:
  static void update(Solutions &solutions, Parameters &params);
};

class MSR {
public:
  static void update(Solutions &solutions, Parameters &params);
};

class PSR {
public:
  static void update(Solutions &solutions, Parameters &params);
};

class IdentitySigmAdaptation {
public:
  static void update(Solutions &solutions, Parameters &params);
};

#endif
