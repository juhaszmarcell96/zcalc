#pragma once

#include <cmath>

#include "zcalc/network.hpp"
#include "zcalc/plot/plot.hpp"
#include "zcalc/plot/figure.hpp"

namespace zcalc {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class Bode {
private:
    Plot m_magnitude_plot;
    Plot m_phase_plot;

    Network& m_network;

    static constexpr double m_min_freq { 1.0 };
    static constexpr double m_max_freq { 1e10 };

    void add_data (double frequency, double amplitude, double phase) {
        if (frequency < m_min_freq) return;
        if (frequency > m_max_freq) return;
        std::cout << "amplitude : " << amplitude << std::endl;
        std::cout << "dB : " << 20.0 * std::log10(amplitude) << std::endl;
        m_magnitude_plot.add_point(std::log10(frequency), 20.0 * std::log10(amplitude));
        /* TODO : phase plot */
    }

    const Plot& plot_magnitude () const {
        return m_magnitude_plot;
    }

    const Plot& plot_phase_ () const {
        return m_phase_plot;
    }

    constexpr std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }
public:
    Bode (Network& network) : m_network(network) {}
    ~Bode () = default;

    void plot (Figure* fig_magnitude, Figure* fig_phase) {
        double frequency = m_min_freq;
        while (frequency < m_max_freq) {
            m_network.set_frequency(frequency);
            std::vector<Complex> result = m_network.compute();
            //double curr_y_f = 500 + 180.0 + result[5].arg() * 180.0 / pi;
            add_data(frequency, result[5].abs(), 0);
            frequency *= 1.05;
        }
        for (std::size_t i = 1; i < get_num_decades(); ++i) {
            fig_magnitude->draw_line((fig_magnitude->get_w() / get_num_decades()) * i, 0, (fig_magnitude->get_w() / get_num_decades()) * i, fig_magnitude->get_h(), colors::black, 1);
            fig_magnitude->draw_text((fig_magnitude->get_w() / get_num_decades()) * i, fig_magnitude->get_h() / 2, "10^" + std::to_string(i) + "Hz");
        }
        fig_magnitude->plot(m_magnitude_plot);
    }
};

} /* namespace zcalc */