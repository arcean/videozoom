#!/usr/bin/python

import sys, shutil

src = sys.argv[1]

des = sys.argv[2]

copy = sys.argv[3]

if (copy == "1"):

	try:

		shutil.copy2(src, des)

	except IOError:

		print "Fail to move file"

else:

	try:

		shutil.move(src, des)

	except IOError:

		print "Fail to move file"
