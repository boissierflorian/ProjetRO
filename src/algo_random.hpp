#ifndef ALGO_RANDOM_HPP
#define ALGO_RANDOM_HPP

#include "algorithm.hpp"

class RandomAlgorithm : public Algorithm
{
public:
  RandomAlgorithm(int nbIter);
  ~RandomAlgorithm() override;
  void execute() override;
  
};

#endif