///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <iterator>

#include "algo_evolutionnary.hpp"



///////////////////////////////////////////////////////////
EvolutionnaryAlgorithm::EvolutionnaryAlgorithm(int nbIter) : Algorithm(nbIter){}


///////////////////////////////////////////////////////////
EvolutionnaryAlgorithm::~EvolutionnaryAlgorithm(){}


///////////////////////////////////////////////////////////
void EvolutionnaryAlgorithm::execute()
{
  // Parameters
  int nbEval(_nbIter);
  const int lambda = 20;
  const int mu = 10;
  const int offset = 10;
  const double mutationProbability = 1 / Algorithm::solution_size;
  
  // Generate a population of lambda solution
  std::vector<Solution> parents;
  
  for (unsigned i = 0; i < lambda; i++)
  {
    // Initialize solution size
    Solution s;
    s.resize(Algorithm::solution_size, 1);
    
    // Generate a random solution
    s.setRand(&_rand);
    Algorithm::randomSolution(s);
    
    // Evaluate and store the solution
    _eval(s);
    parents.push_back(std::move(s));
  }
  
  // Sort parents according to their fitness
  auto cmp = [](const Solution& a, const Solution& b) {
        return a.fitness() < b.fitness();   
  };
  
  std::sort(parents.begin(), parents.end(), cmp);
  
  std::vector<Solution> genitors;
  
  do {
    genitors.clear();

    // Select the mu best parents (genitors)
    for (unsigned i = 0; i < mu; i++)
    {
      genitors.push_back(parents[i]);
    }

    // Mutation of genitors (children)
    for (Solution& genitor : genitors)
    {
      for (unsigned index = 0; index < Algorithm::solution_size; index++)
      {
        double u = _rand.getDouble();

        if (u <= mutationProbability)
        {
          genitor[index] = (genitor[index] + offset) % 100;
        }
      }
      
      _eval(genitor);
    }
    
    // Add left parents
    genitors.insert(genitors.end(), parents.begin(), parents.end());
    parents.clear();
    
    // genitors become children
    std::sort(genitors.begin(), genitors.end(), cmp);
    
    // select the lambda best between children and parents
    // children become parents
    for (unsigned i = 0; i < lambda; i++)
    {
      parents.push_back(std::move(genitors[i]));
    }
  } while(--nbEval > 0);
  
  std::cout << _nbIter << ";";
  
  for (auto& i : parents) {
    std::cout << i.fitness() << ";";
  }
  std::cout << std::endl;
}