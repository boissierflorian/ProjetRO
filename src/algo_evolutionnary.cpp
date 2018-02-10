///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>
#include<functional>
#include <evalCC.hpp>

#include "algo_evolutionnary.hpp"


///////////////////////////////////////////////////////////
EvolutionnaryAlgorithm::EvolutionnaryAlgorithm(int nbIter) : Algorithm(nbIter){}


///////////////////////////////////////////////////////////
EvolutionnaryAlgorithm::~EvolutionnaryAlgorithm(){}


///////////////////////////////////////////////////////////
void run(std::vector<std::reference_wrapper<Solution>> genitors)
{
  EvalCC eval;
  for (Solution& solution : genitors)
     eval(solution);
}


///////////////////////////////////////////////////////////
void EvolutionnaryAlgorithm::execute()
{
  // Parameters
  int nbEval(_nbIter);
  const int lambda = 200;
  const int mu = 80;
  const int offset = 50;
  const double mutationProbability = 0.01;
  const int genitorPerThread = mu / 4;
  int tmp = 0;
  
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
  bool hasMutated(false);
  std::vector<std::reference_wrapper<Solution>> threadGenitors;
  std::vector<std::thread> threads;
  
  do {
    genitors.clear();
    threads.clear();
    threadGenitors.clear();

    // Select the mu best parents (genitors)
    for (unsigned i = 0; i < mu; i++)
    {
      genitors.push_back(parents[i]);
    }

    // Mutation of genitors (children)
    for (Solution& genitor : genitors)
    {
      hasMutated = false;
      
      for (unsigned index = 0; index < Algorithm::solution_size; index++)
      {
        double u = _rand.getDouble();

        if (u <= mutationProbability)
        {
          genitor[index] = (genitor[index] + offset) % 100;
          hasMutated = true;
        }
      }
      
      if (hasMutated) {
        tmp++;
        threadGenitors.push_back(std::ref(genitor));
        
        if (tmp == genitorPerThread) {
          threads.push_back(std::thread(&run, threadGenitors));
          tmp = 0;
          threadGenitors.clear();
        }
      }
    }
    
    // Waiting for threads to finish
    for (auto& th : threads)
    {
      if (th.joinable()) th.join();
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
    std::cout << i.fitness() << ",";
  }
  std::cout << std::endl;
}