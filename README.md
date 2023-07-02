# nosleep

nosleep runs a command while inhibiting the computer from sleeping or hibernating until the command finishes executing.  By default nosleep just prevents the computer from going to sleep during idle periods.  More aggressive options are available to inhibit sleep or hibernation, but these come with warnings and an onerous Disclaimer.  The manual page (nosleep(1)) has full details.

nosleep is currently only implemented in Cygwin, for Windows. It calls Win32 API functions to get and set power control options. However, the Win32 functions are encapsulated behind a somewhat generic internal power control API (defined in nosleep.h, implemented for Windows in windows.c). nosleep should be easily portable to any other operating system that can implement the power control API. Not even all of the API would need to be implemented; the more is available, the more functional nosleep will be on that platform.

* License: GPLv3
* Home page: https://github.com/andrew-schulman/nosleep
* Author: Andrew E. Schulman <andrex.e.schulman@gmail.com>
