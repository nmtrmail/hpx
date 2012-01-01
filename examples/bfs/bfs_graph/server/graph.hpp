//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_BFS_SERVER_GRAPH_DEC_31_2011_0316PM)
#define HPX_EXAMPLE_BFS_SERVER_GRAPH_DEC_31_2011_0316PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>

#include <vector>

#include "graph.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace bfs { namespace server
{
    class HPX_COMPONENT_EXPORT graph
      : public hpx::components::managed_component_base<graph>
    {
    public:
        /// Action codes.
        enum actions
        {
            graph_init = 0,
            graph_bfs = 1,
            graph_get_parents = 2,
            graph_reset = 3
        };

        graph() : idx_(0) {}

        // initialize the graph
        void init(std::size_t idx, std::size_t grainsize,
            std::vector<std::pair<std::size_t, std::size_t> > const& edgelist);

        // execute a breadth-first search for the given root node
        double bfs(std::size_t root);

        // return the created parent list
        std::vector<std::size_t> get_parents();

        // reset all internal data structures for next BFS run
        void reset();

        // action definitions
        typedef hpx::actions::action3<
            graph, graph_init,
            std::size_t, std::size_t,
                std::vector<std::pair<std::size_t, std::size_t> > const&,
            &graph::init
        > init_action;

        typedef hpx::actions::result_action1<
            graph, double, graph_bfs, std::size_t, &graph::bfs
        > bfs_action;

        typedef hpx::actions::result_action0<
            graph, std::vector<std::size_t>, graph_get_parents,
            &graph::get_parents
        > get_parents_action;

        typedef hpx::actions::action0<
            graph, graph_reset, &graph::reset
        > reset_action;

    private:
        std::size_t idx_;
        std::vector<std::vector<std::size_t> > neighbors_;
        std::vector<std::size_t> parents_;
    };
}}

// Declaration of serialization support for the actions
HPX_REGISTER_ACTION_DECLARATION_EX(
    bfs::server::graph::init_action,
    bfs_graph_init_action);

HPX_REGISTER_ACTION_DECLARATION_EX(
    bfs::server::graph::bfs_action,
    bfs_graph_bfs_action);

HPX_REGISTER_ACTION_DECLARATION_EX(
    bfs::server::graph::get_parents_action,
    bfs_graph_get_parents_action);

HPX_REGISTER_ACTION_DECLARATION_EX(
    bfs::server::graph::reset_action,
    bfs_graph_reset_action);

#endif
