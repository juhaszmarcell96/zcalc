#pragma once

#include <cmath>

#include "zcalc/network.hpp"
#include "zcalc/network_calculator.hpp"
#include "zcalc/plot/magnitude_plot.hpp"
#include "zcalc/plot/phase_plot.hpp"

namespace zcalc {
namespace plot {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class Bode {
private:
    MagnitudePlot m_magnitude_plot;
    PhasePlot m_phase_plot;

    Network& m_network;

    double m_min_freq { 1.0 };
    double m_max_freq { 1e10 };
public:
    Bode () = delete;
    Bode (Network& network, double min_freq = 1.0, double max_freq = 1e10) :
        m_network(network), m_min_freq(min_freq), m_max_freq(max_freq), m_magnitude_plot(min_freq, max_freq), m_phase_plot(min_freq, max_freq) {}
    ~Bode () = default;

    std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }

    void plot (html::Figure* fig_magnitude, html::Figure* fig_phase, const std::string& input_source, const std::string& output_component) {
        fig_magnitude->set_plot(&m_magnitude_plot);
        fig_phase->set_plot(&m_phase_plot);
        double frequency = m_min_freq;
        component::id_t output_component_id = m_network.get_component_id(output_component);
        auto input_source_ptr = m_network.get_component(input_source);
        if (!input_source_ptr->is_source()) {
            throw std::invalid_argument("component " + input_source + " must be a source");
        }
        while (frequency < m_max_freq) {
            try {
                input_source_ptr->set_frequency(frequency); // set the frequency of the input source
                const auto results = NetworkCalculator::compute(m_network);
                math::Complex response { 0.0, 0.0 };
                for (const auto& voltage : results.at(output_component_id).voltages)
                {
                    // response is the voltage accross the output component at the given frequency -> TODO : check for source component ID rather than frequency
                    if (voltage.get_frequency() == frequency) {
                        response = voltage.to_complex();
                        break;
                    }
                }
                m_magnitude_plot.add_point(std::log10(frequency), 20.0 * std::log10(response.abs()));
                m_phase_plot.add_point(std::log10(frequency), 180.0 + response.arg() * 180.0 / pi);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "could not solve network for frequency " << frequency << std::endl;
                m_network.print();
                std::cerr << e.what() << std::endl;
            }
            frequency *= 1.05;
        }

        m_magnitude_plot.process();
        m_phase_plot.set_3db_points(m_magnitude_plot.get_3db_points());
        m_phase_plot.process();
    }
};

} /* namespace plot */
} /* namespace zcalc */