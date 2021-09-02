#ifndef CMA_H
#define CMA_H

#include "solutions.h"

class ClassicCMA {
public:
  static void update(Solutions &solutions, Parameters &params) {}
};

class IdleCMA {
public:
  static void update(Solutions &solutions, Parameters &params) {}
};

#endif
