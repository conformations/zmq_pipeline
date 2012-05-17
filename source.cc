#include "zmq_util.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <zmq.hpp>

#include <exception>
#include <iostream>
#include <sstream>

DEFINE_string(in, "tcp://*:9000", "Response socket");
DEFINE_string(out, "tcp://localhost:8000", "Request socket");
DEFINE_int32(messages, 100, "Number of messages to transmit");
DEFINE_int32(io_threads, 1, "Number of threads dedicated to I/O operations");

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  zmq::context_t context(FLAGS_io_threads);
  zmq::socket_t in(context, ZMQ_PULL);
  zmq::socket_t out(context, ZMQ_PUSH);

  try {
    in.bind(FLAGS_in.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to bind incoming socket: " << FLAGS_in << std::endl;
  }

  try {
    out.connect(FLAGS_out.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to connect outgoing socket: " << FLAGS_out << std::endl;
  }

  // send requests
  for (int i = 0; i < FLAGS_messages; ++i) {
    stringstream ss;
    ss << i + 1;

    string req = ss.str();
    s_send(out, req);
    cout << "Sent: " << req << endl;
  }

  // receive responses
  int num_responses = 0;
  while (true) {
    string rep = s_recv(in);
    cout << "Received message number " << ++num_responses << endl;
  }
}
