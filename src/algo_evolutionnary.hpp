#ifndef ALGO_EVOLUTIONNARY_HPP
#define ALGO_EVOLUTIONNARY_HPP

#include <functional>
#include <vector>
#include "algorithm.hpp"

void run(std::vector<std::reference_wrapper<Solution>> genitors);

class EvolutionnaryAlgorithm  : public Algorithm
{
public:
    EvolutionnaryAlgorithm(int nbIter);
    ~EvolutionnaryAlgorithm() override;
    void execute() override;
};

#endif