///////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////
#include "algo_hill_climbing.hpp"
#include "solution.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>


///////////////////////////////////////////////////////////
HCBIAlgorithm::HCBIAlgorithm(int nbIter) : Algorithm(nbIter){}


///////////////////////////////////////////////////////////
HCBIAlgorithm::~HCBIAlgorithm(){}


///////////////////////////////////////////////////////////
void run(std::vector<Solution>& solutions, Solution solution, int start, int end)
{
    Solution bestSolution = solution;
    EvalCC eval;

    for (int i = start; i < end; i++)
    {
	solution[i] = (solution[i] + 10) % 100;

	eval(solution);

	if (solution.fitness() < bestSolution.fitness())
	{
	    bestSolution = solution;
	}

	// reset
	solution[i] = (solution[i] - 10) % 100;
    }

    solutions.push_back(bestSolution);
}


///////////////////////////////////////////////////////////
void HCBIAlgorithm::execute() 
{
    // Solution initialization
    Solution currentSolution;
    currentSolution.resize(Algorithm::solution_size, 1);

    // Save random instance
    currentSolution.setRand(&_rand);
    Algorithm::randomSolution(currentSolution);

    _eval(currentSolution);
    int currentFitness(currentSolution.fitness());
    
    bool hasBestNeighbor(false);
    Solution bestNeighbor = currentSolution;
    
    std::vector<Solution> bestSolutions;
    std::vector<std::thread> threads;

    do {
	hasBestNeighbor = false;
	bestSolutions.clear();

	for (unsigned i = 0; i < Algorithm::solution_size; i += 66)
	{
	    Solution s(currentSolution);
	    std::thread th(&run, std::ref(bestSolutions), s, i, i + 65);
	    threads.push_back(std::move(th));
	}
   
	// Wait for all threads joins
	for (auto& th : threads)
	{
	    if (th.joinable())
		th.join();
	}

	
	for (Solution& s : bestSolutions)
	{
	    if (s.fitness() < currentFitness)
	    {
		currentSolution = s;
		currentFitness = s.fitness();
		hasBestNeighbor = true;
	    }
	}
    } while(hasBestNeighbor);

  
    std::cout << _nbIter << ";" << currentSolution.fitness() << std::endl;
}


///////////////////////////////////////////////////////////

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
