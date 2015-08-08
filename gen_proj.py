#!/usr/bin/python

import sys
import os
import gyp

def main(argv):
    thisdir = os.path.abspath(os.path.dirname(sys.argv[0]))
    gyp.main(argv[1:] + ["--include=include.gypi", "--depth=" + thisdir, "BlackBox.gyp"])
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))
