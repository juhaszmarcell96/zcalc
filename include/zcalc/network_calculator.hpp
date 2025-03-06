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

struct Result {
    std::vector<math::Phasor> voltages {};
    std::vector<math::Phasor> currents {};
};

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
                equation_system.add(equ);
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
                equation_system.add(equ);
            }
            // equation for every component -> one equation per component
            for (const auto& e : g.get_edges()) {
                const auto& component = *(e.get_weight());
                equation_system.add(component.own());
            }
            // solve the equation
            const auto solutions = equation_system.solve();
            if (!solutions.has_value()) {
                throw std::runtime_error("could not solve equation system");
            }
            for (const auto& [var, val] : solutions.value()) {
                results[var].push_back(math::Phasor{val, frequency});
            }
            source->eliminate(); // eliminate the source again
        }



        // // set up the linear equation system
        // math::LinearEquationSystem lin_equ_system { num_variables };
        // if (log_enabled) {
        //     for (const auto& e : g.get_edges()) {
        //         const auto& component = *(e.get_weight());
        //         auto component_id = component.get_id();
        //         const auto designator = network.get_designator_of_component(component_id).value();
        //         lin_equ_system.set_label(std::string{"I_"} + designator, 2 * component_id + equ_current_offset);
        //         lin_equ_system.set_label(std::string{"U_"} + designator, 2 * component_id + equ_voltage_offset);
        //     }
        //     lin_equ_system.set_label("result", num_variables);
        // }
        // // go over the sources, reactivate them one by one, add the result at the end -> supoerposition
        // for (auto source : sources) {
        //     source->reactivate(); // reactive this single source
        //     // set the frequency of the network
        //     const auto& frequency = source->get_frequency();
        //     for (auto& e : g.get_edges()) {
        //         auto& component = *(e.get_weight());
        //         if (!component.is_source()) {
        //             component.set_frequency(frequency);
        //         }
        //     }
        //     // clear the equations of the linear equation system (leave the labels)
        //     lin_equ_system.clear_equations();
        //     // derive the equations
        //     // Kirchhoff's current law -> one equation per node
        //     for (graph::Vertex v = 0; v < g.get_vertices(); ++v) {
        //         math::LinearEquation<math::Complex> equ { num_variables, std::string{"kcl_"} + std::to_string(v) };
        //         for (const auto& e : g.get_edges()) {
        //             const auto& component = *(e.get_weight());
        //             equ.set_result(math::Complex{0.0, 0.0});
        //             equ[2 * component.get_id() + equ_current_offset] = component.kcl(v); // TODO : cast?
        //             equ[2 * component.get_id() + equ_voltage_offset] = math::Complex{0.0, 0.0};
        //         }
        //         lin_equ_system.append_equation(equ);
        //     }
        //     // Kirchhoff's voltage law -> one equation per loop
        //     const auto cycles = g.find_cycles();
        //     for (const auto& c : cycles.get_cycles()) {
        //         math::LinearEquation<math::Complex> equ { num_variables, "kvl" };
        //         const auto& edges = c.get_edges();
        //         graph::Vertex last_v = 0;
        //         for (std::size_t i = 0; i < edges.size(); ++i) {
        //             const auto& e = edges[i];
        //             if (i == 0) { last_v = e.get_v0(); } // initialize it to something meaningful in case of a 1 edge loop
        //             const auto& component = *(e.get_weight());
        //             equ.set_result(math::Complex{0.0, 0.0});
        //             equ[2 * component.get_id() + equ_current_offset] = math::Complex{0.0, 0.0};
        //             if (i < edges.size() - 1) {
        //                 const auto& next_e = edges[i + 1];
        //                 if ((e.get_v0() == next_e.get_v0()) || (e.get_v0() == next_e.get_v1())) {
        //                     equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e.get_v1()); // TODO : cast?
        //                     last_v = e.get_v0();
        //                 }
        //                 else if ((e.get_v1() == next_e.get_v0()) || (e.get_v1() == next_e.get_v1())) {
        //                     equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e.get_v0()); // TODO : cast?
        //                     last_v = e.get_v1();
        //                 }
        //                 else {
        //                     throw std::runtime_error("unexpected edge in the cycle");
        //                 }
        //             }
        //             else {
        //                 if (e.get_v0() == last_v) {
        //                     equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e.get_v0()); // TODO : cast?
        //                 }
        //                 else if (e.get_v1() == last_v) {
        //                     equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e.get_v1()); // TODO : cast?
        //                 }
        //                 else {
        //                     throw std::runtime_error("unexpected edge in the cycle");
        //                 }
        //             }
        //         }
        //         lin_equ_system.append_equation(equ);
        //     }
        //     // equation for every component -> one equation per component
        //     for (const auto& e : g.get_edges()) {
        //         const auto& component = *(e.get_weight());
        //         math::LinearEquation<math::Complex> equ { num_variables, std::string{"own_"} + std::to_string(component.get_id()) };
        //         equ.set_result(component.own_r());
        //         equ[2 * component.get_id() + equ_current_offset] = component.own_i();
        //         equ[2 * component.get_id() + equ_voltage_offset] = component.own_u();
        //         lin_equ_system.append_equation(equ);
        //     }
        //     // solve the linear equation system
        //     std::vector<math::Complex> solution;
        //     bool success = lin_equ_system.solve(solution);
        //     if (!success) {
        //         throw std::runtime_error("could not solve equation system");
        //     }
        //     if (solution.size() != num_variables) {
        //         throw std::runtime_error("unexpected solution size");
        //     }
        //     // std::cout << std::fixed << std::setprecision(2);
        //     // std::cout << lin_equ_system << std::endl;
        //     // for (const auto& c : solution) {
        //     //     std::cout << c << ",";
        //     // }
        //     // std::cout << std::endl;
        //     for (std::size_t i = 0; i < num_variables; i += 2) {
        //         auto component_id = i / 2;
        //         results[component_id].currents.push_back(math::Phasor{solution[i + equ_current_offset], frequency});
        //         results[component_id].voltages.push_back(math::Phasor{solution[i + equ_voltage_offset], frequency});
        //     }
        //     // for (const auto& res : results) {
        //     //     std::cout << network.get_designator_of_component(res.component_id).value() << " : " << std::endl;
        //     //     std::cout << "    voltage : " << res.voltage << std::endl;
        //     //     std::cout << "    current : " << res.current << std::endl;
        //     // }
        //     source->eliminate(); // eliminate the source again
        // }
        return results;
    }
};

} /* namespace zcalc */