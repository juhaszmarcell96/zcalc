#include <zcalc/common.hpp>
#include <zcalc/network.hpp>
#include <zcalc/resistor.hpp>
#include <zcalc/capacitor.hpp>
#include <zcalc/inductor.hpp>

#include <cmath>
#include <fstream>
#include <iostream>


int main () {
    zcalc::Network lora_filter { 868.0e6 };
    lora_filter.add_node("gnd");
    lora_filter.add_node("in");
    lora_filter.add_node("out");
    lora_filter.add_source("U1", 1, "in", "gnd");
    lora_filter.add_capacitor("C1", 4.7e-12, "in", "gnd");
    lora_filter.add_capacitor("C2", 1.2e-12, "in", "out");
    lora_filter.add_inductor("L1", 6.2e-9, "in", "out");
    lora_filter.add_capacitor("C3", 1.8e-12, "out", "gnd");
    lora_filter.add_resistor("RL", 50.0, "out", "gnd");
    std::vector<zcalc::Complex> result = lora_filter.compute();
    lora_filter.print();
    lora_filter.print_equations();
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