#pragma once

#include <zcalc/json/element.hpp>
#include <zcalc/network.hpp>

#include <optional>

namespace zcalc {

class NetworkBuilder {
public:
    static std::optional<Network> from_json (const json::Element& json) {
        Network network {};
        try {
            const auto num_nodes = static_cast<std::size_t>(json.as_object().at("num_nodes").as_number());
            for (std::size_t i = 0; i < num_nodes; ++i) {
                network.add_node(std::to_string(i));
            }
            const auto& components = json.as_object().at("components").as_array();
            for (const auto& component_obj : components) {
                const auto component = component_obj.as_object();
                const auto component_type = component.at("type").as_string();
                const auto id = static_cast<std::size_t>(component.at("id").as_number());
                if (component_type == "resistor") {
                    const auto node_0 = static_cast<std::size_t>(component.at("node_0").as_number());
                    const auto node_1 = static_cast<std::size_t>(component.at("node_1").as_number());
                    const auto resistance = component.at("value").as_number();
                    // TODO prefix
                    double prefix = 1.0;
                    network.add_resistor (std::to_string(id), resistance, std::to_string(node_0), std::to_string(node_1));
                }
                else if (component_type == "vsource") {
                    const auto node_0 = static_cast<std::size_t>(component.at("node_0").as_number());
                    const auto node_1 = static_cast<std::size_t>(component.at("node_1").as_number());
                    const auto value = component.at("value").as_number();
                    const auto frequency = component.at("frequency").as_number();
                    // TODO prefix
                    double prefix = 1.0;
                    network.add_voltage_source (std::to_string(id), value, math::Frequency::create_from_rad_per_sec(frequency), std::to_string(node_0), std::to_string(node_1));
                }
                else {
                    std::cerr << "unsupported component type " << component_type << std::endl;
                    return std::nullopt;
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