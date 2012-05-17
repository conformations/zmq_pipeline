#include "zmq_util.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <zmq.hpp>

#include <exception>
#include <iostream>
#include <sstream>

DEFINE_string(out, "tcp://localhost:8000", "Request queue");
DEFINE_int32(messages, 100, "Number of messages to transmit");
DEFINE_int32(io_threads, 1, "Number of threads dedicated to I/O operations");

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  zmq::context_t context(FLAGS_io_threads);
  zmq::socket_t push(context, ZMQ_PUSH);

  try {
    push.connect(FLAGS_out.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to connect outbound socket: " << FLAGS_out << std::endl;
  }

  for (int i = 0; i < FLAGS_messages; ++i) {
    stringstream ss;
    ss << i + 1;

    string req = ss.str();
    s_send(push, req);
    cout << "Sent: " << req << endl;
  }

  sleep(5);
}
