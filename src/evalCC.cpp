
#include <evalCC.hpp>

namespace cc {

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

void EvalCC::operator()(Solution & solution) {
    GlobalParameters p;

    p.preferences = solution;

    artis::common::RootCoordinator <
        DoubleTime, artis::pdevs::Coordinator <
            DoubleTime,
            RootGraphManager,
            GlobalParameters >
        > rc(0, 4800, "root", p, artis::common::NoParameters());

    rc.attachView("CC", new ::MyView());

    rc.run();

    const ::MyView::Values& values = rc.observer().view("CC").get("Crane:moveNumber");
    int move_number;

    values.back().second(move_number);

    solution.fitness(move_number);
}

} // namespace cc
