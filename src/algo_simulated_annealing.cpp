///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_simulated_annealing.hpp"
#include "solution.hpp"
#include <iostream>
#include <cmath>


SimulatedAnnealingAlgorithm::SimulatedAnnealingAlgorithm(int nbIter) : Algorithm(nbIter)
{
  
}


///////////////////////////////////////////////////////////
SimulatedAnnealingAlgorithm::~SimulatedAnnealingAlgorithm()
{
  
}


///////////////////////////////////////////////////////////
void SimulatedAnnealingAlgorithm::execute()
{
  // Solution initialization
  Solution currentSolution;
  currentSolution.resize(Algorithm::solution_size, 1);
  
  // Save random instance
  currentSolution.setRand(&_rand);
  Algorithm::randomSolution(currentSolution);

  // Evaluate current solution
  _eval(currentSolution);
  int currentFitness = currentSolution.fitness();
  
  // Random generation stuff
  const int lastElementIndex = Algorithm::solution_size - 1;
  const int offset = 10;
  
  // Parameters
  double temp(1000);
  const double alpha(0.85);

  // Keep track of the best solution encountered
  Solution bestSolution = currentSolution;
  int bestFitness = currentSolution.fitness();

  // Maximum iterations
  int steps(_nbIter);
  
  do
  {
    // Evaluate current solution
    _eval(currentSolution);
    currentFitness = currentSolution.fitness();
    
    // Generate a random neighbor
    int randomIndex = _rand.getInt(0, lastElementIndex);
    currentSolution[randomIndex] = (currentSolution[randomIndex] + offset) % 100;
    
    // Evaluate random neighbor
    _eval(currentSolution);
    int neighborFitness(currentSolution.fitness());

    // This neigbor is worse than the current solution
    if (neighborFitness >= currentFitness)
    {
	// Generate a number between 0.0 and 1.0
	double u = _rand.getDouble();

	// We don't accept a worse solution
	if (u >= std::exp((double) currentFitness - neighborFitness / temp))
	{
	    // Reset 
	    currentSolution[randomIndex] = (currentSolution[randomIndex] - offset) % 100;
	    currentSolution.fitness(currentFitness);
	}
    }

    if (currentSolution.fitness() < bestFitness)
    {
	bestFitness = currentSolution.fitness();
	std::cout << bestFitness << std::endl;
    }

    // Temperature update
    temp *= alpha;
  } while (--steps > 0);
  
  std::cout << _nbIter << ";" << bestFitness << std::endl;
}
