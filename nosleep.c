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

/*#include <argp.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <windows.h>

/* Help */
const char *argp_program_version = "nosleep v1.0 | Copyright 2011 Andrew E. Schulman";
const char *argp_program_bug_address = "the Cygwin mailing list <cygwin@cygwin.com>";
static char doc[] = "Run a command while inhibiting computer sleep or hibernation.";
/*static struct argp argp = { 0, 0, 0, doc };*/

int main(int argc, char *argv[]) {

/*  argp_parse(&argp, argc, argv, 0, 0, 0);*/

  int execution_state = ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED;
  pid_t child;

  /* Inhibit sleep/hibernation */
  if (! SetThreadExecutionState(execution_state)) {
    fprintf(stderr, "%s: Error: sleep inhibition failed", argv[0]);
	exit(EXIT_FAILURE);
  }
  
  /* Start child process */
  child = fork();
  if (child == 0)
    execvp(argv[1], argv+1);
  if (child == -1) {
    fprintf(stderr, "%s: Error: failed to create child process", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Wait for child to exit */
  waitpid(child, 0, 0);

  /* Restore power options if necessary */

  exit(EXIT_SUCCESS);
}
