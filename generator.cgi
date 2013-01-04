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
	print json.dumps(yaml.load(generator(yaml.dump(json.loads(data)))))

