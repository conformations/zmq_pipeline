#! /usr/bin/env python
import argparse
import sys
import zmq

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--in', default = 'tcp://*:8000', help = 'Incoming socket')
    parser.add_argument('--out', default = 'tcp://*:8001', help = 'Outgoing socket')
    options = vars(parser.parse_args())

    context = zmq.Context()
    fe = context.socket(zmq.ROUTER)
    be = context.socket(zmq.DEALER)

    try:
        fe.bind(options['in'])
    except:
        sys.stderr.write('Failed to bind incoming socket: %s\n' % options['in'])
        sys.exit(1)

    try:
        be.bind(options['out'])
    except:
        sys.stderr.write('Failed to bind outgoing socket: %s\n' % options['out'])
        sys.exit(1)

    zmq.device(zmq.QUEUE, fe, be)
