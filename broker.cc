#include <gflags/gflags.h>
#include <glog/logging.h>
#include <zmq.hpp>

#include <exception>
#include <iostream>

DEFINE_string(in, "tcp://*:8000", "Frontend socket");
DEFINE_string(out, "tcp://*:8001", "Backend socket");
DEFINE_int32(io_threads, 1, "Number of threads dedicated to I/O operations");

int main (int argc, char *argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  zmq::context_t context(FLAGS_io_threads);
  zmq::socket_t fe(context, ZMQ_ROUTER);
  zmq::socket_t be(context, ZMQ_DEALER);

  try {
    fe.bind(FLAGS_in.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to bind frontend socket: " << FLAGS_in << std::endl;
  }

  try {
    be.bind(FLAGS_out.c_str());
  } catch (std::exception& e) {
    LOG(FATAL) << "Failed to bind backend socket: " << FLAGS_out << std::endl;
  }

  zmq::device(ZMQ_QUEUE, fe, be);
}
