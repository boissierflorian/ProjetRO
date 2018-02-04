#ifndef HILL_CLIMBING_HPP
#define HILL_CLIMBING_HPP

#include "algorithm.hpp"

class HCBIAlgorithm  : public Algorithm
{
public:
  HCBIAlgorithm(int nbIter);
  ~HCBIAlgorithm() override;
  void execute() override;
};

class HCFIAlgorithm  : public Algorithm
{
public:
  HCFIAlgorithm(int nbIter);
  ~HCFIAlgorithm() override;
  void execute() override;
};

  


#endif