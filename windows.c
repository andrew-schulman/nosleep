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
#include <windows.h>
#include "nosleep.h"

bool
get_AC_power_state() {
  SYSTEM_POWER_STATUS *lpSystemPowerStatus;
  if (GetSystemPowerStatus(lpSystemPowerStatus)
      && lpSystemPowerStatus->ACLineStatus == 1)
    return true;
  return false;
}

enum power_return
set_sleep_inhibition_state(struct power_options poweropts,
    char *error, int error_len) {
  int execution_state = ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED;
  SetThreadExecutionState(execution_state);
  return NOSLEEP_OP_SUCCESS;
}

enum power_return
clear_sleep_inhibition_state(struct power_options poweropts,
    char *error, int error_len) {
  return NOSLEEP_OP_SUCCESS;
}
