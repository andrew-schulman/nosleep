/**
 * nosleep.h
 */

/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Copyright 2011 Andrew E. Schulman */

#ifndef NOSLEEP_H_
#define NOSLEEP_H_

#include <stdbool.h>

/**
 * nosleep power configuration API:
 *
 * Any OS-specific implementation of nosleep must implement
 * the following functions for getting and setting power
 * and sleep states.
 */

/* Set of power and sleep options: */
struct power_options {
	int
    awaymode,   /* force away mode instead of sleep mode */
    display,    /* keep the display on */
    idlesleep,  /* inhibit sleep during idle periods */
    powerplan;  /* manipulate the active power plan to disable sleep */
};

/* Return value of functions that manipulate power states: */
enum power_return {
  NOSLEEP_OP_SUCCESS,  /* Operation succeeded. */
  NOSLEEP_OP_WARNING,  /* Operation failed, but a workaround or
    fallback was implemented.  Execution should continue. */
  NOSLEEP_OP_ERROR,     /* Operation failed, and something bad
    happened.  Program should exit immediately. */
};

/**
 * get_AC_power_state()
 *
 * Return:
 *  true  if the host is known to be running on AC power;
 *  false if the host is not running on AC power, OR if the
 *        AC power state can't be determined.
 */
bool
get_AC_power_state();

/**
 * set_sleep_inhibition_state()
 *
 * Inhibit sleep and hibernation according to the options in poweropts.
 *
 * Inputs:
 *   poweropts = set of power and sleep options to be implemented.
 *   error = buffer to receive an error message.
 *   error_len = length of error buffer.
 * Return:
 *   A power_return value for whether the operation succeeded.
 * Side effects:
 *   If the operation fails (fatally or non-fatally), write an error
 *   message to the error buffer.
 */
enum power_return
set_sleep_inhibition_state(struct power_options poweropts, char *error,
    int error_len);

/**
 * clear_sleep_inhibition_state()
 *
 * Undo the inhibition of sleep and hibernation previously set by
 * set_sleep_inhibition_state().
 *
 * Inputs/Returns/Side effects: same as for set_sleep_inhibition_state().
 */
enum power_return
clear_sleep_inhibition_state(struct power_options poweropts, char *error,
    int error_len);

#endif /* NOSLEEP_H_ */
