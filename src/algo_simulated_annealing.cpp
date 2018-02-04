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
  
  int steps(_nbIter);
  int currentFitness;
  
  // Random generation stuff
  const int lastElementIndex = Algorithm::solution_size - 1;
  const int offset = 10;
  
  // Parameters
  int temperature(100);
  const int alpha = 0.89;
  
  do
  {
    // Evaluate current solution
    _eval(currentSolution);
    currentFitness = currentSolution.fitness();
    
    // Random neighbor
    int randomIndex = _rand.getInt(0, lastElementIndex);
    currentSolution[randomIndex] = (currentSolution[randomIndex] + offset) % 100;
    
    // Evaluate random neighbor
    _eval(currentSolution);
    int neighborFitness(currentSolution.fitness());
    
    int delta = neighborFitness - currentFitness;
    
    if (delta >= 0)
    {
      double u = _rand.getDouble(); // 0.0 to 1.0
      if (u >= std::exp((double) delta / (double) temperature))
      {
        // Reset 
        currentSolution[randomIndex] = (currentSolution[randomIndex] - offset) % 100;
        currentSolution.fitness(currentFitness);
      }
    }
      
    temperature *= alpha;
  } while (--steps > 0);
  
  std::cout << _nbIter << ";" << currentFitness << std::endl;
}