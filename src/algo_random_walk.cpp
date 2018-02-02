///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_random_walk.hpp"
#include "solution.hpp"
#include <iostream>


const int RandomWalkAlgorithm::MaxSteps = 100;

///////////////////////////////////////////////////////////
RandomWalkAlgorithm::RandomWalkAlgorithm(int nbIter) :
Algorithm(nbIter)
{
  
}


///////////////////////////////////////////////////////////
RandomWalkAlgorithm::~RandomWalkAlgorithm()
{
  
}


///////////////////////////////////////////////////////////
void RandomWalkAlgorithm::execute()
{
  // Solution initialization
  Solution currentSolution;
  currentSolution.resize(Algorithm::solution_size, 1);
  Algorithm::randomSolution(currentSolution);
  
  // Save random instance
  currentSolution.setRand(&_rand);
 
  int currentFitness(currentSolution.fitness());
  int steps(RandomWalkAlgorithm::MaxSteps);
  
  // The random walk algorithm goal is to achieve
  // a deep exploration of the solution neighborhood
  do 
  {
    // Generate random neighbor data
    Solution neighbor = currentSolution.generateNeighbor();
    _eval(neighbor);
    int neighborEval = neighbor.fitness();
    
    // Update current solution
    currentSolution = neighbor;
    currentFitness = neighborEval;
    
    // Save random instance
    currentSolution.setRand(&_rand);
    
    std::cout << currentFitness << std::endl;
  }
  while (--steps > 0);
}
