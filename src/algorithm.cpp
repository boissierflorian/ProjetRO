///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algorithm.hpp"
#include <random>

// constants related to the dimension of the optimization problem 
const unsigned int Algorithm::size_stack = 5;
const unsigned int Algorithm::n_destination = 8;
const unsigned int Algorithm::solution_size = n_destination + (size_stack - 1) * n_destination * n_destination; // solution size


///////////////////////////////////////////////////////////
Algorithm::Algorithm(int nbIteration) : 
_nbIter(nbIteration)
{
  // Initialisation de la graine
  _rand.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}


///////////////////////////////////////////////////////////
Algorithm::~Algorithm(){}


///////////////////////////////////////////////////////////
void Algorithm::randomSolution(Solution& s)
{
  for (unsigned i = 0; i < Algorithm::solution_size; i++)
  {
    s[i] = getInt(1, 100);
  }
}


///////////////////////////////////////////////////////////
int Algorithm::getInt(int begin, int end)
{
  return _rand.getInt(begin, end);
}