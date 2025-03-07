#pragma once

#include <zcalc/component/component.hpp>
#include <zcalc/network.hpp>
#include <zcalc/math/linear_equation.hpp>
#include <zcalc/math/linear_equation_system.hpp>
#include <zcalc/math/symbolic_linear_equation.hpp>
#include <zcalc/math/symbolic_linear_equation_system.hpp>

#include <zcalc/graph/vertex.hpp>
#include <zcalc/graph/edge.hpp>
#include <zcalc/graph/graph.hpp>

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <optional>

namespace zcalc {

class NetworkCalculator {
private:
    Network m_net {};

public:
    NetworkCalculator () = default;
    ~NetworkCalculator () = default;

    static std::map<std::string, std::vector<math::Phasor>> compute (const Network& network) {
        // convert to graph
        auto g = network.to_graph_pointers();
        std::vector<zcalc::component::IComponent*> sources;
        // collect the sources and eliminate all of them
        for (auto& e : g.get_edges()) {
            if (e.get_weight()->is_source()) {
                e.get_weight()->eliminate();
                sources.push_back(e.get_weight());
            }
        }
        // define the results
        std::map<std::string, std::vector<math::Phasor>> results {};
        // go over the sources, reactivate them one by one, add the result at the end -> supoerposition
        for (auto source : sources) {
            // create the equation system
            //const auto num_equations = g.get_vertices() + 
            math::SymbolicLinearEquationSystem<math::Complex> equation_system {};
            // reactive this single source
            source->reactivate();
            // set the frequency of the network
            const auto& frequency = source->get_frequency();
            for (auto& e : g.get_edges()) {
                auto& component = *(e.get_weight());
                if (!component.is_source()) {
                    component.set_frequency(frequency);
                }
            }
            // derive the equations
            // Kirchhoff's current law -> one equation per node
            for (graph::Vertex v = 0; v < g.get_vertices(); ++v) {
                math::SymbolicLinearEquation<math::Complex> equ { std::string{"kcl_"} + std::to_string(v) };
                for (const auto& e : g.get_edges()) {
                    const auto& component = *(e.get_weight());
                    equ.merge(component.kcl(v));
                }
                equation_system.add(std::move(equ));
            }
            // Kirchhoff's voltage law -> one equation per loop
            const auto cycles = g.find_cycles();
            for (const auto& c : cycles.get_cycles()) {
                math::SymbolicLinearEquation<math::Complex> equ { "kvl" };
                const auto& edges = c.get_edges();
                for (std::size_t i = 0; i < edges.size(); ++i) {
                    const auto& e = edges[i];
                    const auto& component = *(e.get_weight());
                    equ.merge(component.kvl(e.get_v0()));
                }
                equation_system.add(std::move(equ));
            }
            // equation for every component -> one equation per component
            for (const auto& e : g.get_edges()) {
                const auto& component = *(e.get_weight());
                equation_system.add(std::move(component.own()));
            }
            //std::cout << equation_system << std::endl;
            // solve the equation
            const auto solutions = equation_system.solve();
            if (!solutions.has_value()) {
                throw std::runtime_error("could not solve equation system");
            }
            for (const auto& [var, val] : solutions.value()) {
                val.set_print_format(math::Complex::print_format::euler_deg);
                results[var].push_back(math::Phasor{val, frequency});
            }
            source->eliminate(); // eliminate the source again
        }
        return results;
    }
};

} /* namespace zcalc */