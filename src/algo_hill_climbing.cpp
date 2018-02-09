///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_hill_climbing.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <algorithm>


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
  int nbSteps(10);
  bool hasBestNeighbor(false);
  Solution bestNeighbor;
  
  std::vector<HCBIThread> threads;
  
  do {
    hasBestNeighbor = false;
    _eval(currentSolution);

    // For All Neighbors of the current solution
    int iterPerThread = Algorithm::solution_size / Algorithm::n_threads;
    
    // Initialize threads
    for (i = 0; i < Algorithm::solution_size - iterPerThread; i+= iterPerThread)
    {
      HCBIThread thread(currentSolution, i, i + iterPerThread - 1, offset, _eval);
      thread.start();
      threads.push_back(thread);
    }
    
    // We are waiting all threads to finish
    for (unsigned i = 0; i < threads.size(); i++)
    {
      threads[i].join();
    }
    
    HCBIThread& minThread = std::min(threads.begin(); thread.end(); [&](HCBIThread& t1, HCBIThread& t2){
      return t1.fitness() < t2.fitness();
    });
    
    if (minThread.fitness() < currentSolution.fitness())
    {
      hasBestNeighbor = true;
      currentSolution = minThread.getBestSolution();     
    }
 
  } while(hasBestNeighbor && --nbSteps > 0);
  
  std::cout << _nbIter << ";" << currentSolution.fitness() << std::endl;
}


///////////////////////////////////////////////////////////
HCBIThread::HCBIThread(Solution s, int start, int end, int offset, EvalCC& eval) :
  _solution(s),
  _start(start),
  _end(end),
  _offset(offset),
  _eval(eval)
{
  
}


///////////////////////////////////////////////////////////
void HCBIThread::start()
{
   _thread = std::thread(&HCBIThread::execute, this);
}


///////////////////////////////////////////////////////////
void HCBIThread::join()
{
  _thread.join();
}


///////////////////////////////////////////////////////////
void HCBIThread::execute()
{
  int bestFitness(999);
  
  for (int i = _start; i < _end; i++)
  {
    _solution[i] = (_solution[i] + _offset) % 100;
    // Evaluate the Neighbor
    _eval(_solution);
      
    // Fitness of neighbor is lower than the bestFitness
    if (_solution.fitness() < bestFitness) {
        _bestSolution = _solution;  
      
        // The best Fitness is the fitness of the bestNeighbor
        bestFitness = _solution.fitness();
      }
      
      // Reset 
      _solution[i] = (_solution[i] - _offset) % 100;
    }
}


///////////////////////////////////////////////////////////
int HCBIThread::fitness()
{
  return _bestSolution.fitness();
}


///////////////////////////////////////////////////////////
Solution& HCBIThread::getBestSolution()
{
  return _bestSolution;
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