#!/usr/bin/python3

import os
import sys
import traceback
import curses
import struct
import codecs
import serial
import time
import argparse

parseArgs = argparse.ArgumentParser()
parseArgs.add_argument("-d", "--device", help = "TTY device")
args = parseArgs.parse_args()

if not args.device:
	sys.exit("Please specify the TTY device.")

# Serial port instance
instance = serial.Serial(args.device,19200,timeout=5)

# Pre-built Gea2 packets to send to door board
getDoorBoardInfo = [0xe2,0x03,0x08,0x00,0xb4,0x7f,0x73,0xe3]
heartbeat = [0xe2,0x03,0x08,0x00,0xc0,0x41,0x60,0xe3]

refreshRate = 0.05 # Refresh period for data retrieval

# Init ncurses
scr = curses.initscr()
curses.noecho()
curses.cbreak()
curses.start_color()

curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)
curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)

# Print template for ncurses
scr.addstr(0, 0, "|‾‾‾‾‾‾‾‾‾‾‾‾|Door board info:|‾‾‾‾‾‾‾‾‾‾‾‾|")
scr.addstr(1, 0, "|Gea2 Packet Dst:      Src:      Cmd:      |")
scr.addstr(2, 0, "|------------------------------------------|")
scr.addstr(3, 0, "|IceMakerMold Temp:       °F               |")
scr.addstr(4, 0, "|IceMakerCvty Temp:       °F               |")
scr.addstr(5, 0, "|HotWater1 Temp:          °F               |")
scr.addstr(6, 0, "|HotWater2 Temp:          °F               |")
scr.addstr(7, 0, "|DC Switch State:                          |")
scr.addstr(8, 0, "|Relay State:                              |")
scr.addstr(9, 0, "|Duct door state:                          |")
scr.addstr(10, 0, "|Flow meter count:                         |")
scr.addstr(11, 0, "|H/W level state:                          |")
scr.addstr(12, 0, " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾")

# Send the native mode command to disable other state machines
instance.write(serial.to_bytes(heartbeat))

# Initialize to different values than 0 or 1 to show some data as unknown if not read correctly
ddState = 2
hwLvlSwState = 2

# The function that parses the Gea2 packet and prints data
def parsePacket():

	packet = instance.read(40)

	# Get the packet header from the packet buffer
	address=hex(packet[1]) # Door board address (0x03)
	command=hex(packet[4]) # Gea command
	source=hex(packet[3]) # Our address

	# Print the packet information for debugging
	scr.addstr(1, 18, str(address), curses.A_BOLD | curses.color_pair(1))
	scr.addstr(1, 38, str(command), curses.A_BOLD | curses.color_pair(1))
	scr.addstr(1, 28, str(source), curses.A_BOLD | curses.color_pair(1))

	# Gather our uint16 temp values from the packet buffer.
	immTemp=round((convertTemp(packet[14:16]) - 30), 3)
	icTemp=convertTemp(packet[16:18])
	hw1Temp=round((convertTemp(packet[18:20]) - 30), 3) # H/W therms are calibrated differently. Let's equalize them.
	hw2Temp=round((convertTemp(packet[20:22]) - 30), 3)
#	dcLdState=hex(packet[22])
#	relayState=hex(packet[23])
#	ddState=hexToInt(packet[24:25])
#	fmCount=hexToInt(packet[28:30])
#	hwLvlSwState=hexToInt(packet[30])

	# Print all data parsed from the packet buffer.
	scr.addstr(3, 20, str(immTemp), curses.A_BOLD | curses.color_pair(1))
	scr.addstr(4, 20, str(icTemp), curses.A_BOLD | curses.color_pair(1))
	scr.addstr(5, 20, str(hw1Temp), curses.A_BOLD | curses.color_pair(1))
	scr.addstr(6, 20, str(hw2Temp), curses.A_BOLD | curses.color_pair(1))
#	scr.addstr(7, 20, str(dcLdState))
#	scr.addstr(8, 20, str(relayState))

	if (ddState == 0):
		scr.addstr(9, 20, "Closed", curses.A_BOLD | curses.color_pair(1))
	elif (ddState == 1):
		scr.addstr(9, 20, "Open", curses.A_BOLD | curses.color_pair(1))
	else:
		scr.addstr(9, 20, "Unknown", curses.A_BOLD | curses.color_pair(2))

#	scr.addstr(10, 20, str(fmCount))

	if (hwLvlSwState == 0):
		scr.addstr(11, 20, "Not full", curses.A_BOLD | curses.color_pair(1))
	elif (hwLvlSwState == 1):
		scr.addstr(11, 20, "Full", curses.A_BOLD | curses.color_pair(1))
	else:
		scr.addstr(11, 20, "Unknown", curses.A_BOLD | curses.color_pair(2))

# Simple function to convert hexadecimal to integer.
def hexToInt(data):
	return int.from_bytes(data, byteorder='big', signed=False) # Geabus messages are in big-endian order

# Simple function that converts temps in byte format to degrees Farenheit.
def convertTemp(data):
	return round((hexToInt(data) / 100), 3)

# Main while loop.
try:
	while True:
		instance.write(serial.to_bytes(getDoorBoardInfo))
		instance.flushInput()
		instance.flushOutput()
		parsePacket()
		time.sleep(refreshRate)
		scr.refresh()
except:
	traceback.print_exc()
finally:
	curses.echo()
	curses.nocbreak()
	curses.endwin()
