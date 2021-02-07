#!/usr/bin/env python

import os
import sys

if not os.getegid() == 0:
    sys.exit('Script must be run as root')


from time import sleep
# from pyA20.gpio import gpio
# from pyA20.gpio import port

import OPi.GPIO as GPIO


GPIO.setboard(GPIO.PCPCPLUS)
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(false)

def pinName (name):
	if name == "PA10":
		return 35
	elif name == "PA20":
		return 37
	elif name == "PD14":
		return 12
	elif name == "PC4":
		return 16
	elif name == "PC7":
		return 18
	elif name == "PA7":
		return 29
	elif name == "PA8":
		return 31
	else:
		return 0

def run():

	ErrorMessage = "ERROR : arguments is not true! "

	try:
		#print ("Press CTRL+C to exit")
		if len(sys.argv) != 3:
			print (ErrorMessage)
			return ErrorMessage
		else:
			pin = pinName(sys.argv[1])
			if int(sys.argv[2]) == 2 :
				GPIO.setup(pin, GPIO.IN)
				status= GPIO.input(pin)
				#print("status => ",status)
				return status
			elif int(sys.argv[2]) == 1 or int(sys.argv[2]) == 0:
				GPIO.setup(pin, GPIO.OUT)
				GPIO.output(pin, int(sys.argv[2]))
				#print("output => OK")
				return "OK"
			else:
				return ErrorMessage

	except KeyboardInterrupt:
		#print ("Goodbye.")
		return ErrorMessage

run()
