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
public:
    Bode (Network& network) : m_network(network) {}
    ~Bode () = default;

    constexpr std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }

    void plot (Figure* fig_magnitude, Figure* fig_phase) {
        double frequency = m_min_freq;
        while (frequency < m_max_freq) {
            m_network.set_frequency(frequency);
            std::vector<Complex> result = m_network.compute();
            //double curr_y_f = 500 + 180.0 + result[5].arg() * 180.0 / pi;
            m_magnitude_plot.add_point(std::log10(frequency), 20.0 * std::log10(result[5].abs()));
            frequency *= 1.05;
        }
        /*
        for (std::size_t i = 1; i < get_num_decades(); ++i) {
            fig_magnitude->draw_line((fig_magnitude->get_w() / get_num_decades()) * i, 0, (fig_magnitude->get_w() / get_num_decades()) * i, fig_magnitude->get_h(), colors::black, 1);
            fig_magnitude->draw_text((fig_magnitude->get_w() / get_num_decades()) * i, fig_magnitude->get_h() / 2, "10^" + std::to_string(i) + "Hz");
        }
        */

        double min_x, min_y, max_x, max_y;
        m_magnitude_plot.get_min_max(min_x, min_y, max_x, max_y);

        /* add the vertical decade lines and text */
        frequency = m_min_freq * 10.0;
        while (frequency < m_max_freq) {
            m_magnitude_plot.add_line(std::log10(frequency), min_y, std::log10(frequency), max_y);
            m_magnitude_plot.add_text("10^" + std::to_string((int)std::log10(frequency)) + "Hz", std::log10(frequency), min_y + ((max_y - min_y) / 2.0));
            frequency *= 10.0;
        }

        /* add horizontal 20dB lines and texts */
        int y_tmp = std::ceil(min_y);
        while (y_tmp < max_y) {
            if (y_tmp % 20 == 0) {
                m_magnitude_plot.add_line(min_x, y_tmp, max_x, y_tmp);
                m_magnitude_plot.add_text(std::to_string(y_tmp) + "dB", min_x, y_tmp);
                y_tmp += 20;
            }
            else {
                ++y_tmp;
            }
        }

        /* perform calculations for the -3dB point */
        if (min_y < -3.0 && max_y > -3.0) {
                m_magnitude_plot.add_line(min_x, -3.0, max_x, -3.0, 1.0, colors::blue);
        }
        for (std::size_t index = 1; index < m_magnitude_plot.get_points().size(); ++index) {
            const Point& curr = m_magnitude_plot.get_points()[index];
            const Point& prev = m_magnitude_plot.get_points()[index - 1];
            if ((curr.y > -3.0 && prev.y < -3.0) || (curr.y < -3.0 && prev.y > -3.0)) {
                /* interpolate with a straight line */
                double slope = (curr.y - prev.y) / (curr.x - prev.x);
                double y_dist = curr.y - (-3.0);
                double x_dist = y_dist / slope;
                m_magnitude_plot.add_point(curr.x + x_dist, -3.0, 2.0, 1.0, colors::blue, colors::blue);
                m_magnitude_plot.add_line(curr.x + x_dist, min_y, curr.x + x_dist, max_y, 1.0, colors::blue);
                m_magnitude_plot.add_text("10^" + std::to_string(curr.x + x_dist) + "Hz", curr.x + x_dist, min_y + 2.0, 12, colors::blue);
            }
        }

        fig_magnitude->plot(m_magnitude_plot);
    }
};

} /* namespace zcalc */