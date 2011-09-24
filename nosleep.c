/**
 * nosleep.c
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

#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "nosleep.h"

/* Program docs */
static char version[]     = "nosleep v0.1.1 | Copyright 2011 Andrew E. Schulman";
static char bug_address[] = "the Cygwin mailing list <cygwin@cygwin.com>";
static char doc[]         = "Run a command while inhibiting computer sleep or hibernation.";
static char args_doc[]    = "command [args]"; /* non-option arguments */

/* Command-line options */
static struct argp_option options[] = {
  { "awaymode",  'a', 0, 0, "Force away mode instead of sleep mode" },
  { "display",   'd', 0, 0, "Keep the display on" },
  { "ifacpower", 'i', 0, 0, "Following options only apply if AC power is on" },
  { "powerplan", 'p', 0, 0, "Disable sleep in the active power plan" },
  { 0 }
};

/* argp parser */
static error_t parse_opt(int, char *, struct argp_state *);
static struct argp argp = {options, parse_opt, args_doc, doc};

/* Option states, as determined on the command line */
#define NOSLEEP_OPTION_OFF     0
#define NOSLEEP_OPTION_ON      1
#define NOSLEEP_OPTION_AC_ONLY 2

#define NOSLEEP_EXIT_ERROR 128
#define ERROR_LEN          256


/**
 * main()
 */

int
main(int argc, char *argv[]) {

  char error[ERROR_LEN] = "unknown error";
  struct power_options poweropts;
  int firstarg, child_status, i;

  /* Process command-line options */
  poweropts.noidlesleep = NOSLEEP_OPTION_ON;
  poweropts.awaymode    = NOSLEEP_OPTION_OFF;
  poweropts.display     = NOSLEEP_OPTION_OFF;
  poweropts.powerplan   = NOSLEEP_OPTION_OFF;

  argp_program_version = version;
  argp_program_bug_address = bug_address;

  if (argp_parse(&argp, argc, argv, 0, &firstarg, &poweropts))
    exit(NOSLEEP_EXIT_ERROR);

  /* Filter out AC-only options, if AC power isn't on */
  if (!get_AC_power_state()) {
    poweropts.noidlesleep &= ~NOSLEEP_OPTION_AC_ONLY;
    poweropts.awaymode    &= ~NOSLEEP_OPTION_AC_ONLY;
    poweropts.display     &= ~NOSLEEP_OPTION_AC_ONLY;
    poweropts.powerplan   &= ~NOSLEEP_OPTION_AC_ONLY;
  }

  /* Inhibit sleep/hibernation */
  switch (set_sleep_inhibition_state(poweropts, error, sizeof(error))) {
  case NOSLEEP_OP_WARNING:
    fprintf(stderr, "%s: Warning: %s\n", argv[0], error);
    break;
  case NOSLEEP_OP_ERROR:
    fprintf(stderr, "%s: Error: %s\n", argv[0], error);
    exit(NOSLEEP_EXIT_ERROR);
    break;
  }

  /* Start child process */
  switch (fork()) {
  case 0: /* child */
    execvp(argv[firstarg], argv+firstarg);
    fprintf(stderr, "%s: Error: failed to execute command:", argv[0]);
    for (i = firstarg; i<argc; ++i)
      fprintf(stderr, " %s", argv[i]);
    fprintf(stderr, "\n");
    exit(NOSLEEP_EXIT_ERROR);
    break;
  case -1: /* parent (error) */
    fprintf(stderr, "%s: Error: could not fork\n", argv[0]);
    exit(NOSLEEP_EXIT_ERROR);
    break;
  }

  /* Wait for child to exit */
  wait(&child_status);

  /* Restore power options */
  switch(clear_sleep_inhibition_state(poweropts, error, sizeof(error))) {
  case NOSLEEP_OP_WARNING:
    fprintf(stderr, "%s: Warning: %s\n", argv[0], error);
    break;
  case NOSLEEP_OP_ERROR:
    fprintf(stderr, "%s: Error: %s\n", argv[0], error);
    exit(NOSLEEP_EXIT_ERROR);
    break;
  }

  /* Exit */
  if (WIFEXITED(child_status))
    exit(WEXITSTATUS(child_status));
  else
    exit(NOSLEEP_EXIT_ERROR);
}


/*
 * parse_opt():  Parse a single option.
 */

static error_t parse_opt(int key, char *arg, struct argp_state *state) {

  static int ac_state = NOSLEEP_OPTION_ON;
  struct power_options *poweropts = state->input;

  switch (key) {
  case 'a':
    poweropts->awaymode  = ac_state;
    break;
  case 'd':
    poweropts->display   = ac_state;
    break;
  case 'p':
    poweropts->powerplan = ac_state;
    break;
  case 'i':
    ac_state = NOSLEEP_OPTION_AC_ONLY;
    break;

  case ARGP_KEY_ARG:
  case ARGP_KEY_ARGS:
    /* don't handle non-option arguments here; send them back to main() */
    return ARGP_ERR_UNKNOWN;
    break;

  case ARGP_KEY_NO_ARGS:
    argp_usage(state);
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}
