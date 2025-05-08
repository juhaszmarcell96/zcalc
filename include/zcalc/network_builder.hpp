#pragma once

#include <zcalc/json/element.hpp>
#include <zcalc/network.hpp>
#include <zcalc/common.hpp>

#include <optional>
#include <string>

namespace zcalc {

enum class component_types {
    resistor                          = 0,
    capacitor                         = 1,
    inductor                          = 2,
    current_source                    = 3,
    voltage_source                    = 4,
    ammeter                           = 5,
    voltmeter                         = 6,
    current_controlled_current_source = 7,
    current_controlled_voltage_source = 8,
    voltage_controlled_current_source = 9,
    voltage_controlled_voltage_source = 10,
    gyrator                           = 11,
    ideal_amplifier                   = 12,
    ideal_transformer                 = 13,
    coupled_inductor                  = 14
};

static const std::string key_num_nodes { "n" };
static const std::string key_components { "c" };
static const std::string key_index { "i" };
static const std::string key_type { "t" };
static const std::string key_node_0 { "n0" };
static const std::string key_node_1 { "n1" };
static const std::string key_prefix { "u" };
static const std::string key_resistance { "r" };
static const std::string key_capacitance { "c" };
static const std::string key_inductance { "l" };
static const std::string key_voltage { "v" };
static const std::string key_frequency { "f" };
static const std::string key_phase { "p" };

class NetworkBuilder {
public:
    static std::optional<Network> from_json (const json::Element& json) {
        Network network {};
        try {
            const auto num_nodes = static_cast<std::size_t>(json.as_object().at(key_num_nodes).as_number());
            for (std::size_t i = 0; i < num_nodes; ++i) {
                network.add_node(std::to_string(i));
            }
            const auto& components = json.as_object().at(key_components).as_array();
            for (const auto& component_obj : components) {
                const auto component = component_obj.as_object();
                const auto component_type = static_cast<component_types>(static_cast<int>(component.at(key_type).as_number()));
                const auto id = static_cast<std::size_t>(component.at(key_index).as_number());
                switch (component_type) {
                    case component_types::resistor : {
                        const auto node_0 = static_cast<std::size_t>(component.at(key_node_0).as_number()); // TODO : node index check?
                        const auto node_1 = static_cast<std::size_t>(component.at(key_node_1).as_number()); // TODO : node index check?
                        const auto resistance = component.at(key_resistance).as_number(); // TODO : resistance value check?
                        const auto prefix = static_cast<unit_prefix>(static_cast<int>(component.at(key_index).as_number())); // TODO : prefix check or just go with base?
                        network.add_resistor(std::to_string(id), get_prefixed_unit_value(resistance, prefix), std::to_string(node_0), std::to_string(node_1));
                        break;
                    }
                    case component_types::capacitor : {
                        const auto node_0 = static_cast<std::size_t>(component.at(key_node_0).as_number()); // TODO : node index check?
                        const auto node_1 = static_cast<std::size_t>(component.at(key_node_1).as_number()); // TODO : node index check?
                        const auto capacitance = component.at(key_capacitance).as_number(); // TODO : capacitance value check?
                        const auto prefix = static_cast<unit_prefix>(static_cast<int>(component.at(key_index).as_number())); // TODO : prefix check or just go with base?
                        network.add_capacitor(std::to_string(id), get_prefixed_unit_value(capacitance, prefix), std::to_string(node_0), std::to_string(node_1));
                        break;
                    }
                    case component_types::inductor : {
                        const auto node_0 = static_cast<std::size_t>(component.at(key_node_0).as_number()); // TODO : node index check?
                        const auto node_1 = static_cast<std::size_t>(component.at(key_node_1).as_number()); // TODO : node index check?
                        const auto inductance = component.at(key_inductance).as_number(); // TODO : inductance value check?
                        const auto prefix = static_cast<unit_prefix>(static_cast<int>(component.at(key_index).as_number())); // TODO : prefix check or just go with base?
                        network.add_inductor(std::to_string(id), get_prefixed_unit_value(inductance, prefix), std::to_string(node_0), std::to_string(node_1));
                        break;
                    }
                    case component_types::voltage_source : {
                        const auto node_0 = static_cast<std::size_t>(component.at(key_node_0).as_number());
                        const auto node_1 = static_cast<std::size_t>(component.at(key_node_1).as_number());
                        const auto voltage = component.at(key_voltage).as_number();
                        const auto frequency = component.at(key_frequency).as_number();
                        // TODO : phase
                        const auto prefix = static_cast<unit_prefix>(static_cast<int>(component.at(key_index).as_number())); // TODO : prefix check or just go with base?
                        network.add_voltage_source (std::to_string(id), get_prefixed_unit_value(voltage, prefix), math::Frequency::create_from_rad_per_sec(frequency), std::to_string(node_0), std::to_string(node_1));
                        break;
                    }
                    default : {
                        std::cerr << "unsupported component type" << std::endl;
                        return std::nullopt;
                    }
                }
            }
        }
        catch (const std::out_of_range& e) {
            std::cerr << "did not find mandatory element" << std::endl;
            return std::nullopt;
        }
        catch (const std::bad_variant_access& e) {
            std::cerr << "encountered unexpected type" << std::endl;
            return std::nullopt;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "json contains an invalid network" << std::endl;
            return std::nullopt;
        }
        catch (...) {
            std::cerr << "unknown exception" << std::endl;
            return std::nullopt;
        }
        return network;
    }
};

} /* namespace zcalc */