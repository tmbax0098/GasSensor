import os
import threading
from time import sleep
from pyA20.gpio import gpio
from pyA20.gpio import port

rootFolder = "/home/koorosh/files"

def readFile(filePath):
	f=open(filePath , "r")
	line =f.readlines()
	f.close()
	return line[0]

def removeFile(filePath):
	os.remove(filePath)

def getFileList(path = "/"):
    list = []
    for file in os.listdir(path):
        if file.endswith(".txt") == False:
            list.append(os.path.join(path, file))
    return list

def readSettingFile():
    line = readFile(rootFolder + "/setting.txt").split(" ")
    list = []
    for item in line :
        list.append(item == "1")
    return list

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

def execFile(path , flag = False):
	if flag :
		line = readFile(path)
		line = line.split(" ")
		runCommand(line)
	removeFile(path)


def runCommand(argv):

	ErrorMessage = False
	gpio.init()
	try:
		#print ("Press CTRL+C to exit")
		if len(argv) != 2:
			return ErrorMessage
		else:
			pin = pinName(argv[0])
			if int(argv[1]) == 2 :
				gpio.setcfg(pin, gpio.INPUT)
				status= gpio.input(pin)
				return status
			elif int(argv[1]) == 1 or int(argv[1]) == 0:
				gpio.setcfg(pin, gpio.OUTPUT)
				gpio.output(pin, int(argv[1]))
				return True
			else:
				return ErrorMessage

	except KeyboardInterrupt:
		#print ("Goodbye.")
		return ErrorMessage


def manageOutput(setting):
	if setting[2]:
		if setting[0] and runCommand(["PA7" , "2"]) == 1:
			runCommand(["PC7" , "1"])
		if setting[1] and runCommand(["PA7" , "2"]) == 1:
			runCommand(["PC7" , "1"])
		else:
			runCommand(["PC7" , "0"])


def run():
        global rootFolder
        while True:
            runCommand(["PD14" , "0"])
            setting = readSettingFile()
            manageOutput(setting)
            sleep(0.3)
            list = getFileList(rootFolder)
            for path in list:
                execFile(path , setting[3])
            sleep(0.4)


run()

