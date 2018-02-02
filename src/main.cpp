/**
 * @file main.cpp
 * See the AUTHORS or Authors.txt file
 */

/*
 * Copyright (C) 2017-2018 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <graph_manager.hpp>
#include <models.hpp>

#include <artis-star/common/RootCoordinator.hpp>

#include <solution.hpp>
#include <evalCC.hpp>
#include <algorithm.hpp>
#include <algo_random.hpp>

#include <chrono>
#include <fstream>
#include <iostream>

using namespace cc;
using namespace artis::common;


/*
    *** Coding of a solution ***
    
    solution[indice] = score

    score for:
      - a stack of size: s \in [0, stack_size_max - 1], 
      - a slab on the top of the stack with destination: top_slab_dest \in [1, destination_max], 
      - a slab to stack with destination: slab_dest \in [1, destination_max]

    with indice = 
       slab_dest - 1        when s == 0
       destination_max + (s - 1) * (destination_max * destination_max) 
                       + (top_slab_dest - 1) * destination_max
                       + (slab_dest - 1)        when s > 1

    length of a solution is: destination_max + (stack_size_max - 1) * destination_max * destination_max
*/


int convertToInt(char* c, int default_value)
{
  int v = std::atoi(c);

  if (v <= 0)
	  return default_value;
    
  return v;
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Usage ./src/cc-simulator-main <nom algo> <nb iterations>" << std::endl;
    return -1;
  }

  // Parsing
  std::string algoName(argv[1]);
  int nbIter = convertToInt(argv[2], 5);

  // Initialisation de l'algorithme
  Algorithm* algo(nullptr); 
  
  if (algoName == "random")
  {
      algo = new RandomAlgorithm(nbIter);
  }
  else
  {
    std::cerr << "Algorithme inconnu" << std::endl;
    return -1;  
  }
  
  // Éxécution de l'algorithm 
  algo->execute();
  // algo.printResult();

  // evaluation function from the Continuous Casting simulator
 //EvalCC eval;

  // Declaration of one solution of the optimization problem
  //Solution s ;

  // solution for random selection: all stacks have the same preference 1
  //s.resize(solution_size, 1);  // as an example, set all scores to one

  // evaluation of the solution
  //eval(s);

  // print the result
  //std::cout << s.to_string() << std::endl;
  
  delete algo;
  
  return 0;
}
