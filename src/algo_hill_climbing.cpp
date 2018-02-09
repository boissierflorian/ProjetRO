///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_hill_climbing.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>


int g_counter = 0;
std::mutex g_mutex;

Solution getMinSolution(std::vector<HCBIThread>& threads)
{
    unsigned bestIndex = 0;
    int bestFitness = 999;
    
    for (unsigned i = 0; i < threads.size(); i++)
    {	
	if (threads[i].fitness() < bestFitness)
	{
	    bestIndex = i;
	    bestFitness = threads[i].fitness();
	}
    }

    return threads[bestIndex].getBestSolution();
}



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
    int nbSteps(_nbIter);
    bool hasBestNeighbor(false);
    Solution bestNeighbor;
  
    std::vector<HCBIThread> threads;
    int iterPerThread = Algorithm::solution_size / Algorithm::n_threads;
    
    do {
	std::cout << "STEP " << nbSteps << std::endl;
	g_counter = 0;
	hasBestNeighbor = false;
	_eval(currentSolution);

	// For All Neighbors of the current solution
	threads.clear();

	// Initialize threads
	for (int i = 0; i <= Algorithm::solution_size - iterPerThread; i+= iterPerThread)
	{
	    Solution s(currentSolution);
	    HCBIThread thread(s, i, i + iterPerThread - 1, offset);
	    thread.start();
	    threads.push_back(thread);
	}

	while (g_counter != Algorithm::n_threads)
	{
	    std::this_thread::sleep_for (std::chrono::seconds(1));
	};
        
	Solution minNeighbor = getMinSolution(threads);
    
	if (minNeighbor.fitness() < currentSolution.fitness())
	{
	    hasBestNeighbor = true;
	    currentSolution = minNeighbor;
	}

	std::cout << "BEST SOL " <<  minNeighbor.fitness() << std::endl;
    } while(hasBestNeighbor && --nbSteps > 0);

  
    std::cout << _nbIter << ";" << currentSolution.fitness() << std::endl;
}


///////////////////////////////////////////////////////////
HCBIThread::HCBIThread(Solution s, int start, int end, int offset) :
    _solution(s),
    _start(start),
    _end(end),
    _offset(offset),
    _finished(false)
{
  
}


///////////////////////////////////////////////////////////
HCBIThread::HCBIThread(const HCBIThread& t)
{
    this->_bestFitness = t._bestFitness;
    this->_bestSolution = t._bestSolution;
    //this->_eval = t._eval;
}
  

///////////////////////////////////////////////////////////
void HCBIThread::start()
{
    _thread = std::thread(&HCBIThread::execute, this);
    _thread.detach();
}


///////////////////////////////////////////////////////////
bool HCBIThread::hasFinished()
{
    return _finished;
}


///////////////////////////////////////////////////////////
void HCBIThread::execute()
{
    _bestFitness = 999;

    try
    {
	for (int i = _start; i < _end; i++)
	{
	    _solution[i] = (_solution[i] + _offset) % 100;

	    // Evaluate the Neighbor
	    _eval(_solution);
      
	    // Fitness of neighbor is lower than the bestFitness
	    if (_solution.fitness() < _bestFitness) {
		_bestSolution = _solution;
      
		// The best Fitness is the fitness of the bestNeighbor
		_bestFitness = _solution.fitness();
	    }

	    // Reset 
	    _solution[i] = (_solution[i] - _offset) % 100;
	}

	std::cout << "Best fitness" << _bestFitness << std::endl;
    }
    catch (std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }

    std::cout << "FINISHED" << std::endl;
    _finished = true;

    std::lock_guard<std::mutex> lock(g_mutex);
    g_counter++;
}


///////////////////////////////////////////////////////////
int HCBIThread::fitness() const
{
    return _bestFitness;
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
