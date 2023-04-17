#include <include/common.hpp>
#include <include/network.hpp>
#include <include/resistor.hpp>
#include <include/capacitor.hpp>
#include <include/inductor.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {
    zcalc::Network test_network { 50.0e3 };
    test_network.add_node("gnd");
    test_network.add_node("in");
    test_network.add_node("out");
    test_network.add_source("U1", 5, "in", "gnd");
    test_network.add_resistor("R1", 10, "in", "out");
    test_network.add_resistor("R2", 10, "out", "gnd");
    test_network.compute();
    test_network.print();
    test_network.print_cycles();
    test_network.print_equations();

/*
    zcalc::Network network;
    network.add_node("gnd");
    network.add_node("in");
    network.add_node("a");
    network.add_node("b");
    network.add_node("out");
    network.add_edge("U1", "in", "gnd");
    network.add_edge("R1", "in", "a");
    network.add_edge("L1", "a", "b");
    network.add_edge("R2", "b", "gnd");
    network.add_edge("R3", "b", "out");
    network.add_edge("R4", "out", "gnd");
    network.add_edge("C1", "out", "gnd");
    network.print();
    network.compute_cycles();
    network.print_cycles();
    network.compute_equations();
    network.print_equations();

    zcalc::Resistor R { 10.0 };
    zcalc::Capacitor C { 100e-6, 50.0 };
    zcalc::Inductor L { 0.15, 50.0 };
    
    std::cout << "R=" << R << std::endl;
    std::cout << "C=" << C << std::endl;
    std::cout << "L=" << L << std::endl;

    std::cout << zcalc::Impedance::series(zcalc::Impedance::series(R, C), L) << std::endl;
    std::cout << zcalc::Impedance::series(zcalc::Impedance::series(C, L), R) << std::endl;
    std::cout << zcalc::Impedance::series(zcalc::Impedance::series(L, R), C) << std::endl;

    R = zcalc::Resistor{ 10.0 };
    C = zcalc::Capacitor{ 500e-9, 50.0 };
    L = zcalc::Inductor{ 2e-3, 50.0 };
    
    std::cout << "R=" << R << std::endl;
    std::cout << "C=" << C << std::endl;
    std::cout << "L=" << L << std::endl;

    std::cout << zcalc::Impedance::parallel(zcalc::Impedance::parallel(R, C), L) << std::endl;
    std::cout << zcalc::Impedance::parallel(zcalc::Impedance::parallel(C, L), R) << std::endl;
    std::cout << zcalc::Impedance::parallel(zcalc::Impedance::parallel(L, R), C) << std::endl;
*/
    return 0;
}





/*


bool plot_resistance () {
    std::fstream html_file ("tmp.html", std::ios::out | std::ios::trunc);
    if (!html_file.is_open()) {
        std::cout << "ERROR : could not open file" << std::endl;
        return false;
    }

    zcalc::Resistor R50 { 50.0 };

    double freq_limit = 10.0;
    double freq_increment = 0.1;
    double x_offset = 30.0;
    double frequency = 1.0;
    html_file << "<!DOCTYPE html>" << std::endl;
    html_file << "<html>" << std::endl;
    html_file << "<body>" << std::endl;
    html_file << "<svg height=\"1000\" width=\"1000\">" << std::endl;
    html_file << "<line x1=\"" << x_offset << "\" y1=\"5\" x2=\"" << x_offset << "\" y2=\"200\" stroke=\"black\" stroke-width=\"4\"/>" << std::endl;
    double prev_x = 0.0;
    double prev_y = 0.0;
    double prev_y_f = 0.0;
    bool prev_values_set = false;
    while (frequency < 1e10) {
        zcalc::Network pi_filter_3 { frequency, "gnd" };
        pi_filter_3.add_capacitor(3.5e-12, "input", "gnd");
        pi_filter_3.add_inductor(9.2e-9, "input", "output");
        pi_filter_3.add_capacitor(3.5e-12, "output", "gnd");

        zcalc::Impedance input_z = pi_filter_3.calculate_impedance("input", "output", R50);

        double curr_x = x_offset + 40.0 * std::log(frequency);
        double curr_y = 5.0 * input_z.get_modulus();
        double curr_y_f = 500 + 180.0 + input_z.get_argument() * 180.0 / zcalc::pi;

        if (prev_values_set == true) {
            //html_file << "<circle ";
            //html_file << "cx=\"" << curr_x << "\" ";
            //html_file << "cy=\"" << curr_y << "\" ";
            //html_file << "r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />" << std::endl;
            
            html_file << "<line x1=\"" << prev_x <<
                           "\" y1=\"" << prev_y <<
                           "\" x2=\"" << curr_x <<
                           "\" y2=\"" << curr_y <<
                           "\" stroke=\"red\" stroke-width=\"1\"/>" << std::endl;

            prev_x = curr_x;
            prev_y = curr_y;
            prev_y_f = curr_y_f;
        }
        else {
            prev_values_set = true;
            prev_x = curr_x;
            prev_y = curr_y;
            prev_y_f = curr_y_f;
        }

        frequency += freq_increment;
        if (frequency >= freq_limit) {
            freq_increment *= 10.0;
            freq_limit *= 10.0;
        }
    }
    html_file << "</svg>" << std::endl;
    html_file << "</body>" << std::endl;
    html_file << "</html>" << std::endl;

    html_file.close();

    return true;
}
*/