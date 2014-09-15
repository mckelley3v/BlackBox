#!/usr/bin/python

import sys
import os
import fnmatch

thisdir = os.path.abspath(os.path.dirname(sys.argv[0]))
gypdir = os.path.join(thisdir, 'external_tools/gyp/pylib')
sys.path.append(gypdir)
import gyp

def main(argv):
	gyp.main(argv[1:] + ['--depth=' + thisdir, 'all.gyp'])
	return 0

if __name__ == '__main__':
	sys.exit(main(sys.argv))
