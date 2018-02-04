#ifndef SIMU_CLIMBING_HPP
#define SIMU_CLIMBING_HPP

#include "algorithm.hpp"

class SimulatedAnnealingAlgorithm  : public Algorithm
{
public:
  SimulatedAnnealingAlgorithm(int nbIter);
  ~SimulatedAnnealingAlgorithm() override;
  void execute() override;
};

#endif