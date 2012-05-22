zmq_pipeline
============

Illustrates the use of a multiple producer, multiple consumer paradigm in 0mq
(http://en.wikipedia.org/wiki/Producer-consumer_problem). One or more `source`
processes transmit requests through a Queue device to one or more `worker`
processes. Results are sent to a `sink` process.

Because this example was excised from a production system, it has a small
number of dependencies that are helpful, but not strictly speaking required.
At some point in the future, these may be removed.

Dependencies
-------------
* gflags (http://code.google.com/p/google-gflags/)
* glog (http://code.google.com/p/google-glog/)
* zeromq (http://www.zeromq.org/)

Building
-------------
To build the example, ensure that the settings in `Makefile` reflect your
local installation. The relevant variables are CC, CFLAGS, and LDFLAGS.
Once complete, the binaries can be built by executing "make".

$ make

Running
-------------
To run the example, execute the following commands (in any order).

$ ./broker
$ ./sink
$ ./worker
$ ./source

If multiple producers (sources) or consumers (workers) are desired,
simply start additional processes. Currently, only a single broker
and sink are supported.
