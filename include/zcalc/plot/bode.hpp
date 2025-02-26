#pragma once

#include <cmath>

#include "zcalc/network.hpp"
#include "zcalc/network_calculator.hpp"
#include "zcalc/plot/plot.hpp"
#include "zcalc/plot/figure.hpp"

namespace zcalc {

/* bode plot supports frequencies between 1Hz and 10 GHz -> 10 decades */
class Bode {
private:
    Plot m_magnitude_plot;
    Plot m_phase_plot;

    Network& m_network;

    double m_min_freq { 1.0 };
    double m_max_freq { 1e10 };
public:
    Bode () = delete;
    Bode (Network& network, double min_freq = 1.0, double max_freq = 1e10) : m_network(network), m_min_freq(min_freq), m_max_freq(max_freq) {}
    ~Bode () = default;

    std::size_t get_num_decades () const {
        return std::log10(m_max_freq) - std::log10(m_min_freq);
    }

    void plot (Figure* fig_magnitude, Figure* fig_phase, component::id_t component_id) {
        double frequency = m_min_freq;
        while (frequency < m_max_freq) {
            try {
                m_network.set_frequency(frequency);
                const auto results = NetworkCalculator::compute(m_network);
                math::Complex response = results.at(component_id).voltage;
                m_magnitude_plot.add_point(std::log10(frequency), 20.0 * std::log10(response.abs()), 1.0, 1.0);
                m_phase_plot.add_point(std::log10(frequency), 180.0 + response.arg() * 180.0 / pi);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "could not solve network for frequency " << frequency << std::endl;
                m_network.print();
                std::cerr << e.what() << std::endl;
            }
            frequency *= 1.05;
        }

        double m_min_x, m_min_y, m_max_x, m_max_y;
        double p_min_x, p_min_y, p_max_x, p_max_y;

        m_magnitude_plot.get_min_max(m_min_x, m_min_y, m_max_x, m_max_y);
        m_phase_plot.get_min_max(p_min_x, p_min_y, p_max_x, p_max_y);

        /* add the vertical decade lines and text */
        frequency = m_min_freq * 10.0;
        while (frequency < m_max_freq) {
            m_magnitude_plot.add_line(std::log10(frequency), m_min_y, std::log10(frequency), m_max_y);
            m_magnitude_plot.add_text("10^" + std::to_string((int)std::log10(frequency)) + "Hz", std::log10(frequency), m_min_y + ((m_max_y - m_min_y) / 2.0));
            m_phase_plot.add_line(std::log10(frequency), p_min_y, std::log10(frequency), p_max_y);
            
            for (int i = 1; i < 10; ++i) {
                m_magnitude_plot.add_line(std::log10(frequency + i * frequency), m_min_y, std::log10(frequency + i * frequency), m_max_y, 0.2);
                m_phase_plot.add_line(std::log10(frequency + i * frequency), p_min_y, std::log10(frequency + i * frequency), p_max_y, 0.2);
            }

            frequency *= 10.0;
        }

        /* add horizontal 20dB lines and texts */
        int y_tmp = std::ceil(m_min_y);
        while (y_tmp < m_max_y) {
            if (y_tmp % 20 == 0) {
                m_magnitude_plot.add_line(m_min_x, y_tmp, m_max_x, y_tmp);
                m_magnitude_plot.add_text(std::to_string(y_tmp) + "dB", m_min_x, y_tmp);
                y_tmp += 20;
            }
            else {
                ++y_tmp;
            }
        }

        /* add horizontal 5 degree (°) lines and texts */
        y_tmp = std::ceil(p_min_y);
        while (y_tmp < p_max_y) {
            if (y_tmp % 5 == 0) {
                m_phase_plot.add_line(p_min_x, y_tmp, p_max_x, y_tmp);
                m_phase_plot.add_text(std::to_string(y_tmp - 180) + "°", p_min_x, y_tmp);
                y_tmp += 5;
            }
            else {
                ++y_tmp;
            }
        }

        /* perform calculations for the -3dB point */
        if (m_min_y < -3.0 && m_max_y > -3.0) {
                m_magnitude_plot.add_line(m_min_x, -3.0, m_max_x, -3.0, 1.0, colors::blue);
        }
        for (std::size_t index = 1; index < m_magnitude_plot.get_points().size(); ++index) {
            const Point& curr = m_magnitude_plot.get_points()[index];
            const Point& prev = m_magnitude_plot.get_points()[index - 1];
            if ((curr.y > -3.0 && prev.y < -3.0) || (curr.y < -3.0 && prev.y > -3.0)) {
                /* interpolate with a straight line */
                double slope = (curr.y - prev.y) / (curr.x - prev.x);
                double y_dist = curr.y - (-3.0);
                double x_dist = y_dist / slope;
                m_magnitude_plot.add_point(curr.x - x_dist, -3.0, 2.0, 1.0, colors::blue, colors::blue);
                m_magnitude_plot.add_line(curr.x - x_dist, m_min_y, curr.x - x_dist, m_max_y, 1.0, colors::blue);
                //m_magnitude_plot.add_text(std::to_string((int)std::pow(10.0, curr.x - x_dist)) + "Hz", curr.x - x_dist, m_min_y, 12, colors::blue);
                m_phase_plot.add_line(curr.x - x_dist, p_min_y, curr.x - x_dist, p_max_y, 1.0, colors::blue);
            }
        }

        fig_magnitude->plot(m_magnitude_plot);
        fig_phase->plot(m_phase_plot);
    }
};

} /* namespace zcalc */