/*  =======================================================
    zhelpers.h

    Helper header file for example applications.
    =======================================================
*/

#ifndef __ZHELPERS_H_INCLUDED__
#define __ZHELPERS_H_INCLUDED__

#include <zmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include <assert.h>

// Provide random number from 0 ... (num-1)
#define randof(num) (int)((float)(num) * random() / (RAND_MAX + 1.0))

// Convert C string to 0MQ string and ... send to socket
static int s_send(void *socket, char *string) {
  int size = zmq_send(socket, string, strlen(string), 0);

  return size;
}

// Receive 0MQ string fromsocket and convert into C string
// Caller must free returned string.
// Returns NULL if context is being terminated.
static char *
s_recv(void *socket) {
  char buffer[256];
  int size = zmq_recv(socket, buffer, 255, 0);
  if (size == -1)
    return NULL;
  buffer[size] = '\0';

  return strndup(buffer, sizeof(buffer)-1);
}

// Returns current system clock as milliseconds
static int64_t
s_clock(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Sleep for a number of milliseconds
static void
s_sleep(int msecs) {
  struct timespec t;
  t.tv_sec = msecs/1000;
  t.tv_nsec = (msecs % 1000) * 1000000;

  nanosleep(&t, NULL);
}
#endif
