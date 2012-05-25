#! /usr/bin/env python
import argparse
import sys
import zmq

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--in', default = 'tcp://localhost:8001', help = 'Incoming socket')
    parser.add_argument('--out', default = 'tcp://localhost:8002', help = 'Outgoing socket')
    options = vars(parser.parse_args())

    context = zmq.Context()
    fe = context.socket(zmq.PULL)
    be = context.socket(zmq.PUSH)

    try:
        fe.connect(options['in'])
    except:
        sys.stderr.write('Failed to connect incoming socket: %s\n' % options['in'])
        sys.exit(1)

    try:
        be.connect(options['out'])
    except:
        sys.stderr.write('Failed to connect outgoing socket: %s\n' % options['out'])
        sys.exit(1)

    while True:
        uid = fe.recv()
        req = fe.recv()
        print 'Received:', req

        rep = 'done_' + req
        be.send(rep)
        
