#pragma once

#include <zcalc/component/component.hpp>
#include <zcalc/network.hpp>
#include <zcalc/math/linear_equation.hpp>
#include <zcalc/math/linear_equation_system.hpp>

#include <zcalc/graph/vertex.hpp>
#include <zcalc/graph/edge.hpp>
#include <zcalc/graph/graph.hpp>

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <optional>

namespace zcalc {

struct Result {
    component::id_t component_id { 0 };
    math::Complex voltage { 0.0, 0.0 };
    math::Complex current { 0.0, 0.0 };
};

class NetworkCalculator {
private:
    Network m_net {};

public:
    NetworkCalculator () = default;
    ~NetworkCalculator () = default;

    static std::map<component::id_t, Result> compute (const Network& network) {
        // convert to graph
        auto g = network.to_graph_pointers();
        std::vector<std::shared_ptr<zcalc::component::Component>> sources;
        // collect the sources and eliminate all of them
        for (auto& e : g.get_edges()) {
            if (e.weight->is_source()) {
                e.weight->eliminate();
                sources.push_back(e.weight);
            }
        }
        // count the number of variables
        std::size_t num_variables { 0 };
        for (const auto& e : g.get_edges()) {
            num_variables += e.weight->get_num_variables();
        }
        if ((num_variables % 2) != 0) {
            throw std::runtime_error("cannot deal with an odd number of variables");
        }
        // define the results
        std::map<component::id_t, Result> results {};
        for (auto& e : g.get_edges()) {
            auto& component = *(e.weight);
            results[component.get_id()] = Result {};
        }
        // set up the linear equation system
        math::LinearEquationSystem lin_equ_system { num_variables };
        if (log_enabled) {
            for (const auto& e : g.get_edges()) {
                const auto& component = *(e.weight);
                auto component_id = component.get_id();
                const auto designator = network.get_designator_of_component(component_id).value();
                lin_equ_system.set_label(std::string{"I_"} + designator, 2 * component_id + equ_current_offset);
                lin_equ_system.set_label(std::string{"U_"} + designator, 2 * component_id + equ_voltage_offset);
            }
            lin_equ_system.set_label("result", num_variables);
        }
        // go over the sources, reactivate them one by one, add the result at the end -> supoerposition
        for (auto source : sources) {
            source->reactivate(); // reactive this single source
            // set the frequency of the network
            frequency_t frequency = source->get_frequency();
            for (auto& e : g.get_edges()) {
                auto& component = *(e.weight);
                if (!component.is_source()) {
                    component.set_frequency(frequency);
                }
            }
            // clear the equations of the linear equation system (leave the labels)
            lin_equ_system.clear_equations();
            // derive the equations
            // Kirchhoff's current law -> one equation per node
            for (graph::Vertex v = 0; v < g.get_vertices(); ++v) {
                math::LinearEquation<math::Complex> equ { num_variables };
                for (const auto& e : g.get_edges()) {
                    const auto& component = *(e.weight);
                    equ.set_result(math::Complex{0.0, 0.0});
                    equ[2 * component.get_id() + equ_current_offset] = component.kcl(v); // TODO : cast?
                    equ[2 * component.get_id() + equ_voltage_offset] = math::Complex{0.0, 0.0};
                }
                lin_equ_system.append_equation(equ);
            }
            // Kirchhoff's voltage law -> one equation per loop
            const auto cycles = g.find_cycles();
            for (const auto& c : cycles) {
                math::LinearEquation<math::Complex> equ { num_variables };
                const auto& edges = c.get_edges();
                graph::Vertex last_v = 0;
                for (std::size_t i = 0; i < edges.size(); ++i) {
                    const auto& e = edges[i];
                    if (i == 0) { last_v = e->v0; } // initialize it to something meaningful in case of a 1 edge loop
                    const auto& component = *(e->weight);
                    equ.set_result(math::Complex{0.0, 0.0});
                    equ[2 * component.get_id() + equ_current_offset] = math::Complex{0.0, 0.0};
                    if (i < edges.size() - 1) {
                        const auto& next_e = edges[i + 1];
                        if ((e->v0 == next_e->v0) || (e->v0 == next_e->v1)) {
                            equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e->v1); // TODO : cast?
                            last_v = e->v0;
                        }
                        else if ((e->v1 == next_e->v0) || (e->v1 == next_e->v1)) {
                            equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e->v0); // TODO : cast?
                            last_v = e->v1;
                        }
                        else {
                            throw std::runtime_error("unexpected edge in the cycle");
                        }
                    }
                    else {
                        if (e->v0 == last_v) {
                            equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e->v0); // TODO : cast?
                        }
                        else if (e->v1 == last_v) {
                            equ[2 * component.get_id() + equ_voltage_offset] = component.kvl(e->v1); // TODO : cast?
                        }
                        else {
                            throw std::runtime_error("unexpected edge in the cycle");
                        }
                    }
                }
                lin_equ_system.append_equation(equ);
            }
            // equation for every component -> one equation per component
            for (const auto& e : g.get_edges()) {
                math::LinearEquation<math::Complex> equ { num_variables };
                const auto& component = *(e.weight);
                equ.set_result(component.own_r());
                equ[2 * component.get_id() + equ_current_offset] = component.own_i();
                equ[2 * component.get_id() + equ_voltage_offset] = component.own_u();
                lin_equ_system.append_equation(equ);
            }
            // solve the linear equation system
            std::vector<math::Complex> solution;
            bool success = lin_equ_system.solve(solution);
            if (!success) {
                throw std::runtime_error("could not solve equation system");
            }
            if (solution.size() != num_variables) {
                throw std::runtime_error("unexpected solution size");
            }
            // std::cout << std::fixed << std::setprecision(2);
            // std::cout << lin_equ_system << std::endl;
            // for (const auto& c : solution) {
            //     std::cout << c << ",";
            // }
            // std::cout << std::endl;
            for (std::size_t i = 0; i < num_variables; i += 2) {
                auto component_id = i / 2;
                results[component_id].current += solution[i + equ_current_offset];
                results[component_id].voltage += solution[i + equ_voltage_offset];
            }
            // for (const auto& res : results) {
            //     std::cout << network.get_designator_of_component(res.component_id).value() << " : " << std::endl;
            //     std::cout << "    voltage : " << res.voltage << std::endl;
            //     std::cout << "    current : " << res.current << std::endl;
            // }
            source->eliminate(); // eliminate the source again
        }
        return results;
    }
};

} /* namespace zcalc */