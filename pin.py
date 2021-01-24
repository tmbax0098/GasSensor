#!/usr/bin/env python

import os
import sys

if not os.getegid() == 0:
    sys.exit('Script must be run as root')


from time import sleep
from pyA20.gpio import gpio
from pyA20.gpio import port


def pinName (name):
	if name == "PA10":
		return port.PA10
	elif name == "PA20":
		return port.PA20
	elif name == "PD14":
		return port.PD14
	elif name == "PC4":
		return port.PC4
	elif name == "PC7":
		return port.PC7
	elif name == "PA7":
		return port.PA7
	elif name == "PA8":
		return port.PA8
	else:
		return 0

#led = port.PA10

def setPin():
	try:
		gpio.init()
		gpio.setcfg(port.PD14 , gpio.OUTPUT)
		gpio.output(port.PD14 , 0)
		return true
	except :
		return false

def run():

	gpio.init()

	ErrorMessage = "ERROR : arguments is not true! " 

	try:
		#print ("Press CTRL+C to exit")
		if len(sys.argv) != 3:
			print (ErrorMessage)
			return ErrorMessage
		else:
			pin = pinName(sys.argv[1])
			if int(sys.argv[2]) == 2 :
				gpio.setcfg(pin, gpio.INPUT)
				status= gpio.input(pin)
				print("status => ",status)
				return status
			elif int(sys.argv[2]) == 1 or int(sys.argv[2]) == 0:
				gpio.setcfg(pin, gpio.OUTPUT)
				gpio.output(pin, int(sys.argv[2]))
				#print("output => OK")
			else:
				return ErrorMessage

	except KeyboardInterrupt:
		#print ("Goodbye.")
		return ErrorMessage

run()
