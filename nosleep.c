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

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <windows.h>

/* Program docs */
const char *argp_program_version = "nosleep v1.0 | Copyright 2011 Andrew E. Schulman";
const char *argp_program_bug_address = "the Cygwin mailing list <cygwin@cygwin.com>";
static char doc[] = "Run a command while inhibiting computer sleep or hibernation.";
static char args_doc[] = "command [args]";	/* non-option arguments */

/* Options */
static struct argp_option options[] = {
  {"awaymode",  'a', 0, 0,  "Substitute away mode for sleep mode" },
  {"display",   'd', 0, 0,  "Keep the display on" },
  {"powerplan", 'p', 0, 0,  "Manipulate the active power plan" },
  { 0 }
};
     
/* Argument structure, for communication from parse_opt to main */
struct arguments
{
  char *args[2];                /* arg1 & arg2 */
  int silent, verbose;
  char *output_file;
};

/* argp parser */
static error_t parse_opt(int, char *, struct argp_state *);
static struct argp argp = {options, parse_opt, args_doc, doc};


/*
 * main()
 */

int
main(int argc, char *argv[]) {

  argp_parse(&argp, argc, argv, 0, 0, 0);

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

/*
 * parse_opt():  Parse a single option.
 */

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key) {
    case 'q':
    case 's':
      arguments->silent = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_ARG:
      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 2)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
