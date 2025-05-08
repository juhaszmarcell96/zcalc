/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#pragma once

#include <cstddef>

namespace zcalc {

typedef double magnitude_t;

static constexpr double epsilon = 1e-4;

static constexpr bool log_enabled = true;

static constexpr std::size_t equ_current_offset = 0;
static constexpr std::size_t equ_voltage_offset = 1;

enum class unit_prefix {
    peta     = 0,      // 1e15
    tera     = 1,      // 1e12
    giga     = 2,      // 1e9
    mega     = 3,      // 1e6
    kilo     = 4,      // 1e3
    hecto    = 5,      // 1e2
    deka     = 6,      // 1e1
    base     = 7,      // 1e0
    deci     = 8,      // 1e-1
    centi    = 9,      // 1e-2
    milli    = 10,     // 1e-3
    micro    = 11,     // 1e-6
    nano     = 12,     // 1e-9
    angstrom = 13,     // 1e-10
    pico     = 14      // 1e-12
};

static inline double get_prefixed_unit_value (double value, unit_prefix prefix) {
    switch (prefix) {
        case unit_prefix::peta : {
            return value * 1.0e15;
        };
        case unit_prefix::tera : {
            return value * 1.0e12;
        };
        case unit_prefix::giga : {
            return value * 1.0e9;
        };
        case unit_prefix::mega : {
            return value * 1.0e6;
        };
        case unit_prefix::kilo : {
            return value * 1.0e3;
        };
        case unit_prefix::hecto : {
            return value * 1.0e2;
        };
        case unit_prefix::deka : {
            return value * 10;
        };
        case unit_prefix::base : {
            return value;
        };
        case unit_prefix::deci : {
            return value * 0.1;
        };
        case unit_prefix::centi : {
            return value * 1.0e-2;
        };
        case unit_prefix::milli : {
            return value * 1.0e-3;
        };
        case unit_prefix::micro : {
            return value * 1.0e-6;
        };
        case unit_prefix::nano : {
            return value * 1.0e-9;
        };
        case unit_prefix::angstrom : {
            return value * 1.0e-10;
        };
        case unit_prefix::pico : {
            return value * 1.0e-12;
        };
        default : {
            return 0.0;
        }
    }
}

} /* namespace zcalc */