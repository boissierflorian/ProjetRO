///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_random.hpp"
#include "solution.hpp"
#include <iostream>


///////////////////////////////////////////////////////////
RandomAlgorithm::RandomAlgorithm(int nbIter) :
Algorithm(nbIter)
{
  
}


///////////////////////////////////////////////////////////
RandomAlgorithm::~RandomAlgorithm()
{
  
}


///////////////////////////////////////////////////////////
void RandomAlgorithm::execute()
{
  Solution s;
  s.resize(Algorithm::solution_size, 1);
  int minFitness(999);
  
  // We are looking for the lowest random solution fitness
  for (int i = 0; i < _nbIter; i++)
  {
    Algorithm::randomSolution(s);
    _eval(s);
    
    int tmp = s.fitness();
    if (tmp < minFitness)
    {
      minFitness = tmp;
    }
  }
  
  std::cout << minFitness << std::endl;
}