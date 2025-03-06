#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <zcalc/network_calculator.hpp>


int main () {
    //
    //                          B(1)       ┌──────┐    C(2)
    //     ┌────────────────────o──────────┤  R3  ├──────┐
    //     │                    │          └──────┘      │
    //   ┌─┴─┐                  │                        └─┐
    //   │R1 │                  │                        ┌─┘
    //   │   │                  │                        └─┐
    //   └─┬─┘                  │                        ┌─┘ L
    //     │ A(0)               │                        └─┐
    //  ┌──┼──┐ |             ┌─┴─┐                      ┌─┘
    //  │  │  │ | U1          │R2 │                      │ D(3)
    //  │  │  │ |             │   │                      │
    //  └──┼──┘ v             └─┬─┘                   ┌──┼──┐ |
    //     │                    │                     │  │  │ | U2
    //     │                    │  | I                │  │  │ |
    //     │                    │  V                  └──┼──┘ v
    //     │       gnd(4)       │                        │
    //     └────────────────────o────────────────────────┘
    //
    zcalc::Network network {};
    network.add_node ("A");
    network.add_node ("B");
    network.add_node ("C");
    network.add_node ("D");
    network.add_node ("gnd");

    network.add_voltage_source ("U1", 4.0, zcalc::math::Frequency::create_from_hz(0.0), "A", "gnd"); // 4VDC
    network.add_voltage_source ("U2", std::sqrt(2.0) * 6.0, zcalc::math::Frequency::create_from_rad_per_sec(10.0e3), "D", "gnd"); // sqrt(2)* 6V, 10krad/s (1591.5Hz)

    network.add_resistor("R1", 10, "B", "A"); // 10ohm
    const auto r_id = network.add_resistor("R2", 50, "B", "gnd"); // 50ohm
    network.add_resistor("R3", 5, "B", "C"); // 5ohm
    network.add_inductor("L", 1.0e-3, "C", "D"); // 1mH

    std::vector<double> durations;
    int iterations = 10000;
    int throw_out = 100;

    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        const auto results = zcalc::NetworkCalculator::compute(network);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "\r #" << i << " - result : " << results.at("R2_i")[0] << " computation time: " << elapsed.count() << " ms                   " << std::flush;
        durations.push_back(elapsed.count());
    }

    std::sort(durations.begin(), durations.end());
    auto sum = std::accumulate(durations.begin() + throw_out, durations.end() - throw_out, 0.0);
    std::cout << "\r average: " << sum / (static_cast<double>(iterations - 2 * throw_out)) << " ms                                                                   " << std::endl;
}