#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <evalCC.hpp>
#include "solution.hpp"
#include "utils/rand.hpp"

using namespace cc::utils;

class Algorithm
{
protected: 
  int _nbIter;
  EvalCC _eval;
  Rand _rand;
protected:
  void randomSolution(Solution& s);
  int getInt(int begin, int end);
public:
  Algorithm(int nbIter);
  virtual ~Algorithm() = 0;
  virtual void execute() = 0;
public:
  static const unsigned int size_stack;    // maximum size of a stack
  static const unsigned int n_destination; // maximum number of destination for a slab
  static const unsigned int solution_size; // solution size
};
#endif