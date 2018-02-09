#ifndef HILL_CLIMBING_HPP
#define HILL_CLIMBING_HPP

#include "algorithm.hpp"
#include <thread>

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

class HCBIThread
{
public:
  HCBIThread(Solution s, int start, int end, int offset, EvalCC& eval);
  void start();
  void execute();
  void join();
  int fitness();
  Solution& getBestSolution();
private:
  Solution _solution;
  int _start;
  int _end;
  int _offset;
  EvalCC& _eval;
  Solution _bestSolution;
  std::thread _thread;
};


#endif