#! /usr/bin/env python
import argparse
import sys
import zmq

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--in', default = 'tcp://*:8002', help = 'Incoming socket')
    parser.add_argument('--io_threads', default = 1, help = 'Number of threads dedicated to I/O operations')
    options = vars(parser.parse_args())

    context = zmq.Context()
    pull = context.socket(zmq.PULL)

    try:
        pull.bind(options['in'])
    except:
        sys.stderr.write('Failed to bind incoming socket: %s\n' % options['in'])
        sys.exit(1)

    while True:
        msg = pull.recv()
        print 'Received:', msg
