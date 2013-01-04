#!/usr/bin/env python
import sys,os
import json,yaml
import pygenerator; generator=pygenerator.Generator()


data = sys.stdin.read()

if os.environ["QUERY_STRING"] == '':
	pass
elif os.environ["QUERY_STRING"] == 'json':
	print 'Content-Type: application/json'
	print ''
	a = json.loads(data)
	print a
	b = yaml.dump(a)
	print b
	c = generator(b)
	print c
	d = yaml.load(c)
	print d
	e = json.dumps(d)
