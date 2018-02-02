#ifndef _evalCC_hpp
#define _evalCC_hpp

#include <graph_manager.hpp>
#include <models.hpp>

#include <artis-star/common/RootCoordinator.hpp>

#include <solution.hpp>

using namespace cc;
using namespace artis::common;

namespace cc {

class MyView : public cc::View
{
public:
    MyView()
    {
        selector("Stack:height", { RootGraphManager::CC,
                    SubGraphManager::STACK, cc::View::ALL, Stack::HEIGHT });
        selector("Crane:moveNumber", { RootGraphManager::CC,
                    SubGraphManager::CRANE, Crane::MOVE_NUMBER });
        selector("Crane:slabNumber", { RootGraphManager::CC,
                    SubGraphManager::CRANE, Crane::SLAB_NUMBER });
    }
};

/*
    *** Evaluation function ***

    Number of cranes movements for a solution with the following representation:


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

    length of a solution is then: destination_max + (stack_size_max - 1) * destination_max * destination_max


    At each selection step of the gantry crane, the (free) stack with the highest scrore is selected.
    If there is ties, the stack with the clostest width is selected, and if ties, then a random one
*/

class EvalCC
{
public:

    void operator()(Solution & /* solution */) ;

};

} // namespace cc

#endif