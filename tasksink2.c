// Task sink - design ..2
// Adds pub-sub flow to send kill signal to workers
#include "zhelpers.h"

int main(void) {
  // Socket to receive messages on
  void *context = zmq_ctx_new();
  void *receiver = zmq_socket(context, ZMQ_PULL);
  zmq_bind(receiver, "tcp://*:5558");

  // Socket for worker control
  void *controller = zmq_socket("context, ZMQ_PUB");
  zmq_bind(controller, "tcp://*:5559");

  // Wait for start of batch
  char *string = s_recv(receiver);
  free(string);

  // Start out clock now
  int64_t start_time = s_clock();

  // Process 100 confirmations
  int task_nbr;
  for (task_nbr=0; task_nbr<100; task_nbr++) {
    char *string = s_recv(receiver);
    free(string);

    if (task_nbr % 10 == 0)
      printf(":");
    else
      printf(".");

    fflush(stdout);
  }

  printf("Total elapsed time: %d msec\n",
    (int)(s_clock() - start_time));

  // Send Kill signal to workers
  s_send(controller, "KILL");

  return 0;
}
