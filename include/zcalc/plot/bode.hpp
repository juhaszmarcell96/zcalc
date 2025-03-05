#pragma once

#include <cmath>

#include "zcalc/network.hpp"
#include "zcalc/network_calculator.hpp"
#include "zcalc/plot/magnitude_plot.hpp"
#include "zcalc/plot/phase_plot.hpp"
#include "zcalc/plot/plotter.hpp"

namespace zcalc {
namespace plot {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class Bode {
private:
    MagnitudePlot m_magnitude_plot;
    PhasePlot m_phase_plot;
public:
    Bode () = default;
    ~Bode () = default;

    void plot (html::Figure* fig_magnitude, html::Figure* fig_phase, Network& network, const PlotterConfig& config) {
        fig_magnitude->set_plot(&m_magnitude_plot);
        fig_phase->set_plot(&m_phase_plot);
        component::id_t output_component_id = network.get_component_id(config.output_component);
        auto input_source_ptr = network.get_component(config.input_source);
        if (!input_source_ptr->is_source()) {
            throw std::invalid_argument("component " + config.input_source + " must be a source");
        }
        auto frequency = config.min_frequency;
        while (frequency < config.max_frequency) {
            try {
                input_source_ptr->set_frequency(frequency); // set the frequency of the input source
                const auto results = NetworkCalculator::compute(network);
                math::Complex response { 0.0, 0.0 };
                for (const auto& voltage : results.at(output_component_id).voltages)
                {
                    // response is the voltage accross the output component at the given frequency -> TODO : check for source component ID rather than frequency
                    if (voltage.get_frequency() == frequency) {
                        response = voltage.to_complex();
                        break;
                    }
                }
                m_magnitude_plot.add(frequency, response);
                m_phase_plot.add(frequency, response);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "could not solve network for frequency " << frequency << std::endl;
                network.print();
                std::cerr << e.what() << std::endl;
            }
            frequency *= 1.0 + config.granularity;
        }

        m_magnitude_plot.process();
        m_phase_plot.set_3db_points(m_magnitude_plot.get_3db_points());
        m_phase_plot.process();
    }

    void mark_frequency (const math::Frequency& frequency) {
        m_magnitude_plot.mark_frequency(frequency);
        m_phase_plot.mark_frequency(frequency);
    }
};

} /* namespace plot */
} /* namespace zcalc */