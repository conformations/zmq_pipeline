#! /usr/bin/env python
import argparse
import sys
import zmq

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--out', default = 'tcp://localhost:8000', help = 'Outgoing socket')
    parser.add_argument('--messages', type = int, default = 100, help = 'Number of messages to send')
    options = vars(parser.parse_args())

    context = zmq.Context()
    out = context.socket(zmq.PUSH)

    try:
        out.connect(options['out'])
    except:
        sys.stderr.write('Failed to connect outgoing socket: %s\n' % options['out'])
        sys.exit(1)

    for i in range(options['messages']):
        msg = str(i + 1)
        out.send(msg)
        print 'Sent:', msg
