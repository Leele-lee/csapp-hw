#include "csapp.h"

/* SIGINT handler */
void sigint_handler(int sig) {
  return; /* Catch the signal and return */
}

unsigned int snooze(unsigned int secs) {
  unsigned int rc = sleep(secs);
  printf("Slept for %d of %d secs.\n", secs-rc, secs);
  return rc;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <secs>\n", argv[0]);
    exit(0);
  }

  if (signal(SIGINT, sigint_handler) == SIG_ERR) { /* install handler */
    fprintf(stderr, "signal_error\n");
  }
  (void)snooze(atoi(argv[1]));
  exit(0);
}
