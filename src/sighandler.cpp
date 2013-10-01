#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#include <unistd.h>

static sig_atomic_t should_terminate = false;

template<size_t N>
static void
write (int fd, char const (&msg)[N])
{
  write (fd, msg, N - 1);
}

static void
throw_signal (int signum)
{
  if (should_terminate)
    {
      write (STDOUT_FILENO, "second interrupt caught - exiting");
      _Exit (1);
    }
  write (STDOUT_FILENO, "interrupt caught - terminating");
  should_terminate = true;
}

static bool
init ()
{
  signal (SIGINT, throw_signal);
  return true;
}

static bool const inited = init ();
