/**
 * \file
 * \brief Linux <termios.h>-related utilities.
 */
#pragma once

/* linux */
#include <termios.h>

/* toolchain */
#include <cstdint>
#include <iostream>

/* internal */
#include "result.h"

namespace Coral
{

void dump_input_modes(std::ostream &stream, const struct termios &data);
void dump_output_modes(std::ostream &stream, const struct termios &data);
void dump_control_modes(std::ostream &stream, const struct termios &data);
void dump_local_modes(std::ostream &stream, const struct termios &data);
void dump_specials(std::ostream &stream, const struct termios &data);
void dump_term_all(std::ostream &stream, int fd, const struct termios &data);

const char *speed_str(speed_t data);
Result baud_to_speed(uint32_t baud, speed_t &output);

} // namespace Coral
