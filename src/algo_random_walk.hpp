#ifndef RANDOM_WALK_HPP
#define RANDOM_WALK_HPP

#include "algorithm.hpp"

class RandomWalkAlgorithm : public Algorithm
{
public:
  RandomWalkAlgorithm(int nbIter);
  ~RandomWalkAlgorithm() override;
  void execute() override;
private:
  static const int MaxSteps;
};

#endif