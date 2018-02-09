#ifndef HILL_CLIMBING_HPP
#define HILL_CLIMBING_HPP

#include "algorithm.hpp"
#include <thread>

class HCBIAlgorithm  : public Algorithm
{
public:
    HCBIAlgorithm(int nbIter);
    ~HCBIAlgorithm() override;
    void execute() override;
};

class HCFIAlgorithm  : public Algorithm
{
public:
    HCFIAlgorithm(int nbIter);
    ~HCFIAlgorithm() override;
    void execute() override;
};

class HCBIThread
{
public:
    HCBIThread(Solution s, int start, int end, int offset);
    HCBIThread(const HCBIThread& t);
    void start();
    void execute();
    bool hasFinished();
    int fitness() const;
    Solution& getBestSolution();
private:
    Solution _solution;
    int _start;
    int _end;
    int _offset;
    EvalCC _eval;
    bool _finished;
    Solution _bestSolution;
    int _bestFitness;
    std::thread _thread;
};

Solution getMinSolution(std::vector<HCBIThread>& threads);

#endif
