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

#include <argp.h>
#include <stdlib.h>

/* Help */
const char *argp_program_version = "nosleep v1.0";
const char *argp_program_bug_address = "Andrew Schulman <schulman.andrew@epa.gov>";
static char doc[] = "Run a command while inhibiting computer sleep or hibernation.";
static struct argp argp = { 0, 0, 0, doc };

int main(int argc, char *argv[]) {

  argp_parse(&argp, argc, argv, 0, 0, 0);

  exit(0);
}
