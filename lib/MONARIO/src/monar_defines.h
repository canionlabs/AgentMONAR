#pragma once

// ███╗   ███╗ ██████╗ ███╗   ██╗ █████╗ ██████╗
// ████╗ ████║██╔═══██╗████╗  ██║██╔══██╗██╔══██╗
// ██╔████╔██║██║   ██║██╔██╗ ██║███████║██████╔╝
// ██║╚██╔╝██║██║   ██║██║╚██╗██║██╔══██║██╔══██╗
// ██║ ╚═╝ ██║╚██████╔╝██║ ╚████║██║  ██║██║  ██║
// ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// List of Defines used by all systems
// The ports may not be in numeric order

/**
 * List of OUTPUT ports
 *
 * [5-50]
 */

                                   // [type, description]
#define MONAR_OUTPUT_VOLTAGE     5 // [float, input voltage of the board]
#define MONAR_OUTPUT_CURRENT     6 // [float, ]
#define MONAR_OUTPUT_TEMPERATURE 7 // [float]

/**
 * List of INPUT ports
 *
 * [51-100]
 */
                                       // [type]
#define MONAR_INPUT_TEMPERATURE_MIN 51 // [int]
#define MONAR_INPUT_TEMPERATURE_MAX 52 // [int]
