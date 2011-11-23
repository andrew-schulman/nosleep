/**
 * windows.c
 *
 * Windows implementation of the nosleep power configuration API.
 * See:
 *   nosleep.h
 *   http://msdn.microsoft.com/en-us/library/windows/desktop/aa373163(v=vs.85).aspx
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

#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include "nosleep.h"

/* ES_AWAYMODE_REQUIRED is undefined in Windows XP and earlier.
 * Define it here only for compilation. */
#ifndef ES_AWAYMODE_REQUIRED
#define ES_AWAYMODE_REQUIRED 0x00000040
#endif

bool
is_AC_power_on() {
  SYSTEM_POWER_STATUS SystemPowerStatus;
  if (GetSystemPowerStatus(&SystemPowerStatus)
      && SystemPowerStatus.ACLineStatus == 1)
    return true;
  return false;
}

enum op_return
set_sleep_inhibition_state(struct power_options poweropts,
    char *error, int error_len) {
  int execution_state = 0;

  if (poweropts.noidlesleep)
    execution_state |= ES_CONTINUOUS | ES_SYSTEM_REQUIRED;
  if (poweropts.awaymode)
    execution_state |= ES_CONTINUOUS | ES_AWAYMODE_REQUIRED;
  if (poweropts.display)
    execution_state |= ES_CONTINUOUS | ES_DISPLAY_REQUIRED;

  if (!SetThreadExecutionState(execution_state)) {
    snprintf(error, error_len, "Failed to inhibit sleep. Continuing execution with sleep not inhibited.");
    return NOSLEEP_OP_WARNING;
  }
  return NOSLEEP_OP_SUCCESS;
}

enum op_return
clear_sleep_inhibition_state(struct power_options poweropts,
    char *error, int error_len) {
  /* It's probably not necessary to reset the power options in
   * Windows, but there's no harm in trying. But neither is it
   * worth bothering to check if we succeeded. */
  SetThreadExecutionState(ES_CONTINUOUS);
  return NOSLEEP_OP_SUCCESS;
}
