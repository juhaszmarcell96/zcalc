#include <include/common.hpp>
#include <include/network.hpp>
#include <include/resistor.hpp>
#include <include/capacitor.hpp>
#include <include/inductor.hpp>

#include <cmath>
#include <fstream>
#include <iostream>

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
            
            /*html_file << "<line x1=\"" << prev_x <<
                           "\" y1=\"" << prev_y_f <<
                           "\" x2=\"" << curr_x <<
                           "\" y2=\"" << curr_y_f <<
                           "\" stroke=\"blue\" stroke-width=\"1\"/>" << std::endl;*/

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

int main () {
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

    /* pi network */
    std::cout << std::endl;

    zcalc::Capacitor C1 { 3.5e-12, 868e6 };
    zcalc::Inductor L1 { 9.2e-9, 868e6 };
    zcalc::Capacitor C2 { 3.5e-12, 868e6 };
    zcalc::Resistor RL { 50.0 };
    
    std::cout << "C1=" << C1 << std::endl;
    std::cout << "L1=" << L1 << std::endl;
    std::cout << "C2=" << C2 << std::endl;
    std::cout << "RL=" << RL << std::endl;
    
    std::cout << "input impedance of PI filter with open termination :" << std::endl;
    std::cout << zcalc::Impedance::parallel(C1, zcalc::Impedance::series(L1, C2)) << std::endl;
    std::cout << "input impedance of PI filter with short termination :" << std::endl;
    std::cout << zcalc::Impedance::parallel(C1, L1) << std::endl;
    std::cout << "input impedance of PI filter with 50ohm termination :" << std::endl;
    std::cout << zcalc::Impedance::parallel(C1, zcalc::Impedance::series(L1, zcalc::Impedance::parallel(C2, RL))) << std::endl;
    std::cout << "output impedance of PI filter with 50ohm termination :" << std::endl;
    std::cout << zcalc::Impedance::parallel(C2, zcalc::Impedance::series(L1, zcalc::Impedance::parallel(C1, RL))) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    zcalc::Network pi_filter { 868e6, "gnd" };
    pi_filter.add_capacitor(3.5e-12, "input", "gnd");
    pi_filter.add_inductor(9.2e-9, "input", "output");
    pi_filter.add_capacitor(3.5e-12, "output", "gnd");

    zcalc::Resistor R50 { 50.0 };
    zcalc::Resistor Rinf { 1e30 };
    zcalc::Resistor R0 { 0.0 };
    
    std::cout << "input impedance of PI filter with open termination :" << std::endl;
    std::cout << pi_filter.calculate_impedance("input", "output", Rinf) << std::endl;
    std::cout << "input impedance of PI filter with short termination :" << std::endl;
    std::cout << pi_filter.calculate_impedance("input", "output", R0) << std::endl;
    std::cout << "input impedance of PI filter with 50ohm termination :" << std::endl;
    std::cout << pi_filter.calculate_impedance("input", "output", R50) << std::endl;
    std::cout << "output impedance of PI filter with 50ohm termination :" << std::endl;
    std::cout << pi_filter.calculate_impedance("output", "input", R50) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    zcalc::Network net0 { 5000, "gnd" };
    net0.add_resistor(500, "input", "a");
    net0.add_inductor(0.01, "a", "b");
    net0.add_resistor(1000, "b", "gnd");
    net0.add_resistor(800, "b", "output");
    net0.add_resistor(600, "output", "gnd");
    net0.add_capacitor(120e-9, "output", "gnd");
    
    std::cout << "input impedance of net0 filter with open termination :" << std::endl;
    std::cout << net0.calculate_impedance("input", "output", Rinf) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    zcalc::Network net1 { 5000, "gnd" };
    net1.add_resistor(500, "input", "a");
    net1.add_resistor(500, "a", "b");
    net1.add_resistor(500, "b", "gnd");
    net1.add_resistor(500, "b", "output");
    net1.add_resistor(500, "output", "gnd");
    net1.add_resistor(500, "output", "gnd");
    
    std::cout << "input impedance of net1 filter with open termination :" << std::endl;
    std::cout << net1.calculate_impedance("input", "output", Rinf) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    double C_increment = 0.1e-12;
    double L_increment = 0.1e-9;
    double C_min = 3e-12;
    double C_max = 4e-12;
    double L_min = 9e-9;
    double L_max = 10e-9;

    //Capacitor C1 { 3.5e-12, 868e6 };
    //Inductor L1 { 9.2e-9, 868e6 };
    //Capacitor C2 { 3.5e-12, 868e6 };
        
    double C1_val = C_min;
    double L1_val = L_min;
    double C2_val = C_min;
    while (true) {
        zcalc::Network pi_filter_2 { 868e6, "gnd" };
        pi_filter_2.add_capacitor(C1_val, "input", "gnd");
        pi_filter_2.add_inductor(L1_val, "input", "output");
        pi_filter_2.add_capacitor(C2_val, "output", "gnd");

        zcalc::Impedance input_z = pi_filter_2.calculate_impedance("input", "output", R50);
        zcalc::Impedance output_z = pi_filter_2.calculate_impedance("output", "input", R50);

        if ((input_z.get_modulus() > 49.5) &&
            (input_z.get_modulus() < 50.5) &&
            ((input_z.get_argument() * 180.0 / zcalc::pi) > -0.03) &&
            ((input_z.get_argument() * 180.0 / zcalc::pi) < 0.03))
        {
            if ((output_z.get_modulus() > 49.5) &&
                (output_z.get_modulus() < 50.5) &&
                ((output_z.get_argument() * 180.0 / zcalc::pi) > -0.03) &&
                ((output_z.get_argument() * 180.0 / zcalc::pi) < 0.03))
            {
                std::cout << C1_val << std::endl;
                std::cout << L1_val << std::endl;
                std::cout << C2_val << std::endl;
                std::cout << input_z << std::endl;
            }
        }

        C2_val += C_increment;
        if (C2_val >= C_max) {
            C2_val = C_min;
            L1_val += L_increment;
        }
        if (L1_val >= L_max) {
            L1_val = L_min;
            C1_val += C_increment;
        }
        if (C1_val >= C_max) break;
    }

    plot_resistance();



    
/*
    double freq_limit = 10.0;
    double freq_increment = 1.0;
    double x_offset = 30.0;
    double frequency = 1.0;
    std::cout << "<svg height=\"1000\" width=\"0100\">" << std::endl;
    <line x1="0" y1="0" x2="0" y2="200" stroke="red" stroke-width="1" />
    while (frequency < 1e10) {
        zcalc::Network pi_filter_3 { frequency, "gnd" };
        pi_filter_3.add_capacitor(3.5e-12, "input", "gnd");
        pi_filter_3.add_inductor(9.2e-9, "input", "output");
        pi_filter_3.add_capacitor(3.5e-12, "output", "gnd");

        zcalc::Impedance input_z = pi_filter_3.calculate_impedance("input", "output", R50);

        std::cout << "<circle ";
        std::cout << "cx=\"" << x_offset + 40.0 * std::log(frequency) << "\" ";
        std::cout << "cy=\"" << 250.0 + ((20.0 * std::log(input_z.get_modulus() / 50.0)) * -5) << "\" ";
        std::cout << "r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />" << std::endl;

        frequency += freq_increment;
        if (frequency >= freq_limit) {
            freq_increment *= 10.0;
            freq_limit *= 10.0;
        }
    }
    std::cout << "</svg>" << std::endl;
*/

    return 0;
}