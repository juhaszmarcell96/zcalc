#include <include/network.hpp>
#include <include/common.hpp>
#include <include/capacitor.hpp>
#include <include/inductor.hpp>
#include <include/resistor.hpp>

namespace zcalc {

Network::Network(double frequency, const std::string& ref_node) : m_frequency(frequency), m_ref_node(ref_node) {}

void Network::add_resistor (double resistance, const std::string& endpoint_0, const std::string& endpoint_1) {
    std::shared_ptr<Impedance> R = std::make_shared<Resistor>(resistance);
    R->connect(endpoint_0, endpoint_1);
    m_components.push_back(std::move(R));
}

void Network::add_capacitor (double capacitance, const std::string& endpoint_0, const std::string& endpoint_1) {
    std::shared_ptr<Impedance> C = std::make_shared<Capacitor>(capacitance, m_frequency);
    C->connect(endpoint_0, endpoint_1);
    m_components.push_back(std::move(C));
}

void Network::add_inductor (double inductance, const std::string& endpoint_0, const std::string& endpoint_1) {
    std::shared_ptr<Impedance> L = std::make_shared<Inductor>(inductance, m_frequency);
    L->connect(endpoint_0, endpoint_1);
    m_components.push_back(std::move(L));
}

void Network::clear () { m_components.clear(); }

Impedance Network::calculate_impedance (const std::string& input_node, const std::string& output_node, const Impedance& termination) {
    std::vector<std::shared_ptr<Impedance>> components = m_components;
    std::shared_ptr<Impedance> z_term = std::make_shared<Impedance>(termination);
    z_term->connect(output_node, m_ref_node);
    components.push_back(z_term);
    while (true) {
        bool something_changed = false;
        while (true) {
            /* do parallel stuff iterative until nothing changes in an iteration */
            /* find 2 parralel elements, meaning that their two einpoints are the same */
            /* calculate the impedance */
            std::size_t component_id_0 = 0;
            std::size_t component_id_1 = 0;
            std::string endpoint_0;
            std::string endpoint_1;
            /* do stuff */
            for (std::size_t i = 0; i < components.size(); ++i) {
                for (std::size_t e = i + 1; e < components.size(); ++e) {
                    if ((components[i]->get_endpoint_0().compare(components[e]->get_endpoint_0()) == 0) &&
                        (components[i]->get_endpoint_1().compare(components[e]->get_endpoint_1()) == 0))
                    {
                        endpoint_0 = components[i]->get_endpoint_0();
                        endpoint_1 = components[i]->get_endpoint_1();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                    else if ((components[i]->get_endpoint_0().compare(components[e]->get_endpoint_1()) == 0) &&
                                (components[i]->get_endpoint_1().compare(components[e]->get_endpoint_0()) == 0))
                    {
                        endpoint_0 = components[i]->get_endpoint_0();
                        endpoint_1 = components[i]->get_endpoint_1();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                }
            }
            if ((component_id_0 == 0) && (component_id_1 == 0)) break;

            something_changed = true;

            std::shared_ptr<Impedance> z = std::make_shared<Impedance>(Impedance::parallel(*components[component_id_0], *components[component_id_1]));
            z->connect(endpoint_0, endpoint_1);

            if constexpr (log_enabled) {
                std::cout << "+------------------------------------------------------------+" << std::endl;
                std::cout << "calculating impedance for parallel components" << std::endl;
                std::cout << *components[component_id_0] << std::endl;
                std::cout << *components[component_id_1] << std::endl;
                std::cout << "between nodes '" << endpoint_0 << "' and '" << endpoint_1 << "'" << std::endl;
                std::cout << "result is" << std::endl;
                std::cout << *z << std::endl;
                std::cout << "+------------------------------------------------------------+" << std::endl;
            }

            /* delete component_id_1 first because it is the larger index */
            components.erase(components.begin() + component_id_1);
            components.erase(components.begin() + component_id_0);

            components.push_back(std::move(z));
        }
        while (true) {
            /* do series stuff iterative until nothing changes in an iteration */
            /* find 2 series elements */
            /* two elements that have one node in common and their other node is different */
            /* plus the common node cannot be the reference node */
            /* and it cannot be the input node */
            /* calculate the impedance */
            std::size_t component_id_0 = 0;
            std::size_t component_id_1 = 0;
            std::string endpoint_0;
            std::string endpoint_1;
            /* do stuff */
            for (std::size_t i = 0; i < components.size(); ++i) {
                for (std::size_t e = i + 1; e < components.size(); ++e) {
                    if ((components[i]->get_endpoint_0().compare(components[e]->get_endpoint_0()) == 0) &&
                        (components[i]->get_endpoint_1().compare(components[e]->get_endpoint_1()) != 0) &&
                        (components[i]->get_endpoint_0().compare(m_ref_node) != 0) &&
                        (components[i]->get_endpoint_0().compare(input_node) != 0))
                    {
                        bool appears_elsewhere = false;
                        for (std::size_t j = 0; j < components.size(); ++j) {
                            if ((j != i) && (j != e)) {
                                if (components[i]->get_endpoint_0().compare(components[j]->get_endpoint_0()) == 0) appears_elsewhere = true;
                                if (components[i]->get_endpoint_0().compare(components[j]->get_endpoint_1()) == 0) appears_elsewhere = true;
                            }
                        }
                        if (appears_elsewhere == true) continue;
                        endpoint_0 = components[i]->get_endpoint_1();
                        endpoint_1 = components[e]->get_endpoint_1();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                    else if ((components[i]->get_endpoint_1().compare(components[e]->get_endpoint_1()) == 0) &&
                                (components[i]->get_endpoint_0().compare(components[e]->get_endpoint_0()) != 0) &&
                                (components[i]->get_endpoint_1().compare(m_ref_node) != 0) &&
                                (components[i]->get_endpoint_1().compare(input_node) != 0))
                    {
                        bool appears_elsewhere = false;
                        for (std::size_t j = 0; j < components.size(); ++j) {
                            if ((j != i) && (j != e)) {
                                if (components[i]->get_endpoint_1().compare(components[j]->get_endpoint_0()) == 0) appears_elsewhere = true;
                                if (components[i]->get_endpoint_1().compare(components[j]->get_endpoint_1()) == 0) appears_elsewhere = true;
                            }
                        }
                        if (appears_elsewhere == true) continue;
                        endpoint_0 = components[i]->get_endpoint_0();
                        endpoint_1 = components[e]->get_endpoint_0();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                    else if ((components[i]->get_endpoint_0().compare(components[e]->get_endpoint_1()) == 0) &&
                                (components[i]->get_endpoint_1().compare(components[e]->get_endpoint_0()) != 0) &&
                                (components[i]->get_endpoint_0().compare(m_ref_node) != 0) &&
                                (components[i]->get_endpoint_0().compare(input_node) != 0))
                    {
                        bool appears_elsewhere = false;
                        for (std::size_t j = 0; j < components.size(); ++j) {
                            if ((j != i) && (j != e)) {
                                if (components[i]->get_endpoint_0().compare(components[j]->get_endpoint_0()) == 0) appears_elsewhere = true;
                                if (components[i]->get_endpoint_0().compare(components[j]->get_endpoint_1()) == 0) appears_elsewhere = true;
                            }
                        }
                        if (appears_elsewhere == true) continue;
                        endpoint_0 = components[i]->get_endpoint_1();
                        endpoint_1 = components[e]->get_endpoint_0();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                    else if ((components[i]->get_endpoint_1().compare(components[e]->get_endpoint_0()) == 0) &&
                                (components[i]->get_endpoint_0().compare(components[e]->get_endpoint_1()) != 0) &&
                                (components[i]->get_endpoint_1().compare(m_ref_node) != 0) &&
                                (components[i]->get_endpoint_1().compare(input_node) != 0))
                    {
                        bool appears_elsewhere = false;
                        for (std::size_t j = 0; j < components.size(); ++j) {
                            if ((j != i) && (j != e)) {
                                if (components[i]->get_endpoint_1().compare(components[j]->get_endpoint_0()) == 0) appears_elsewhere = true;
                                if (components[i]->get_endpoint_1().compare(components[j]->get_endpoint_1()) == 0) appears_elsewhere = true;
                            }
                        }
                        if (appears_elsewhere == true) continue;
                        endpoint_0 = components[i]->get_endpoint_0();
                        endpoint_1 = components[e]->get_endpoint_1();
                        component_id_0 = i;
                        component_id_1 = e;
                    }
                }
            }
            if ((component_id_0 == 0) && (component_id_1 == 0)) break;

            something_changed = true;

            std::shared_ptr<Impedance> z = std::make_shared<Impedance>(Impedance::series(*components[component_id_0], *components[component_id_1]));
            z->connect(endpoint_0, endpoint_1);

            if constexpr (log_enabled) {
                std::cout << "+------------------------------------------------------------+" << std::endl;
                std::cout << "calculating impedance for series components" << std::endl;
                std::cout << *components[component_id_0] << std::endl;
                std::cout << *components[component_id_1] << std::endl;
                std::cout << "between nodes '" << endpoint_0 << "' and '" << endpoint_1 << "'" << std::endl;
                std::cout << "result is" << std::endl;
                std::cout << *z << std::endl;
                std::cout << "+------------------------------------------------------------+" << std::endl;
            }

            /* delete component_id_1 first because it is the larger index */
            components.erase(components.begin() + component_id_1);
            components.erase(components.begin() + component_id_0);

            components.push_back(std::move(z));
        }
        /* break if there was no series and parallel changes */
        if (something_changed == false) break;
    }
    /* only one single impedance should be in the vector */
    return std::move(*components[0]);
}

} /* namespace zcalc */