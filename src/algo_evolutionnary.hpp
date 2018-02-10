#ifndef ALGO_EVOLUTIONNARY_HPP
#define ALGO_EVOLUTIONNARY_HPP

#include "algorithm.hpp"

class EvolutionnaryAlgorithm  : public Algorithm
{
public:
    EvolutionnaryAlgorithm(int nbIter);
    ~EvolutionnaryAlgorithm() override;
    void execute() override;
};

#endif