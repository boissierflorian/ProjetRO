///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_hill_climbing.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>


///////////////////////////////////////////////////////////
HCBIAlgorithm::HCBIAlgorithm(int nbIter) : Algorithm(nbIter){}


///////////////////////////////////////////////////////////
HCBIAlgorithm::~HCBIAlgorithm(){}


///////////////////////////////////////////////////////////
void HCBIAlgorithm::execute() 
{
  // Solution initialization
  Solution currentSolution;
  currentSolution.resize(Algorithm::solution_size, 1);
  // Save random instance
  currentSolution.setRand(&_rand);
  Algorithm::randomSolution(currentSolution);
  
  const int offset = 10;
  bool hasBestNeighbor(false);
  Solution bestNeighbor;
  
  do {
    hasBestNeighbor = false;
    _eval(currentSolution);
    int bestFitness(currentSolution.fitness());

    // For All Neighbors of the current solution
    for (unsigned i = 0; i < currentSolution.size(); i++) {
      currentSolution[i] = (currentSolution[i] + offset) % 100;
      // Evaluate the Neighbor
      _eval(currentSolution);
      
      // Fitness of neighbor is lower than the bestFitness
      if (currentSolution.fitness() < bestFitness) {
        // The BestNeighbor become the current neighbor
        bestNeighbor = currentSolution;
        // A best Neighbor has been found
        hasBestNeighbor = true;
        // The best Fitness is the fitness of the bestNeighbor
        bestFitness = currentSolution.fitness();
      }
      
      // Reset 
      currentSolution[i] = (currentSolution[i] - offset) % 100;
    }
    
    if (hasBestNeighbor) {
      currentSolution = bestNeighbor;
    }
    
  } while(hasBestNeighbor);
  
  std::cout << _nbIter << ";" << currentSolution.fitness() << std::endl;
}


///////////////////////////////////////////////////////////
HCFIAlgorithm::HCFIAlgorithm(int nbIter) : Algorithm(nbIter){}


///////////////////////////////////////////////////////////
HCFIAlgorithm::~HCFIAlgorithm(){}


///////////////////////////////////////////////////////////
void HCFIAlgorithm::execute() 
{
  // Solution initialization
  Solution currentSolution;
  currentSolution.resize(Algorithm::solution_size, 1);
  
  // Save random instance
  currentSolution.setRand(&_rand);
  
  // Generate a random solution
  Algorithm::randomSolution(currentSolution);
  
  // Evaluate the current solution
  _eval(currentSolution);
  
  int currentFitness;
  int nbEval(_nbIter);
  const int lastElementIndex = Algorithm::solution_size - 1;
  const int offset = 10;
 
  do 
  {
    currentFitness = currentSolution.fitness();
    
    // Random neighbor
    int randomIndex = _rand.getInt(0, lastElementIndex);
    currentSolution[randomIndex] = (currentSolution[randomIndex] + offset) % 100;
    
    // Evaluate the neighbor
    _eval(currentSolution);
    
    // Neighbor's fitness isn't greater than the current solution one
    if (currentSolution.fitness() >= currentFitness)
    {
      // Reset the current solution
      currentSolution[randomIndex] = (currentSolution[randomIndex] - offset) % 100;
      currentSolution.fitness(currentFitness);
    }
    // Otherwise the neigbor becomes the current solution !
  }
  while (--nbEval > 0);
  
  std::cout << _nbIter << ";" << currentSolution.fitness() << std::endl;
}