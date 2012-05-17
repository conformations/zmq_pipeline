#include "zmq_util.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <zmq.hpp>

#include <exception>
#include <iostream>
#include <string>

DEFINE_string(in, "tcp://localhost:8001", "Frontend socket");
DEFINE_string(out, "tcp://localhost:8002", "Backend socket");
DEFINE_int32(io_threads, 1, "Number of threads dedicated to I/O operations");

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  zmq::context_t context(FLAGS_io_threads);
  zmq::socket_t fe(context, ZMQ_PULL);
  zmq::socket_t be(context, ZMQ_PUSH);

  try {
    fe.connect(FLAGS_in.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to connect frontend socket: " << FLAGS_in << std::endl;
  }

  try {
    be.connect(FLAGS_out.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to connect backend socket: " << FLAGS_out << std::endl;
  }

  while (true) {
    string uid = s_recv(fe);
    string req = s_recv(fe);
    cout << "Received: " << req << endl;

    string rep = "done_" + req;
    s_send(be, rep);
  }
}
