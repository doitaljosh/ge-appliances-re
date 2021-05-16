import serial
import time
import struct
import sys
import binascii

# Serial port constants.
ttydev = "/dev/ttyUSB0"
baud = 19200
port = serial.Serial(ttydev, baud)

# Gea message flag bytes.
geaEsc = 0xe0
geaAck = 0xe1
geaStx = 0xe2
geaEtx = 0xe3

# Gea message size constants.
geaPacketOverheadSize = 7
geaHeaderSize = geaPacketOverheadSize - 3

msgBuf = 0x00

# Continuously read and parse gea messages.
while True:
	time.sleep(0.075)
	bytesToRead = port.in_waiting
	# Check if there is data available, then validate it if true.
	if (bytesToRead >= geaHeaderSize):
		# Convert raw data into a byte array so the parser can work with it.
		msgBuf = bytearray(port.read(bytesToRead))
		# Check if msgBuf starts with a valid gea SOF.
		if (msgBuf[0] == geaStx):
			# Handle escape flags properly.
			if (geaEsc in msgBuf):
				# In the instance that a data byte equals the escape byte, it needs to be handled differently.
				numDoubleEscape = msgBuf.count([0xe0, 0xe0])
				if (numDoubleEscape):
					geaPacket = msgBuf[0:(msgBuf[2] + (msgBuf.count([0xe0]) - numDoubleEscape))]
				else:
					geaPacket = msgBuf[0:(msgBuf[2] + msgBuf.count([0xe0]))]
			else:
				geaPacket = msgBuf[0:msgBuf[2]]

				# Parse out fields to be printed.
				dst = hex(geaPacket[1])
				len = geaPacket[2]
				src = hex(geaPacket[3])
				cmd = hex(geaPacket[4])
				# Determine if the gea message uses ERDs or not. If so, print the number of ERDs.
				if (cmd == 0xb8 or 0xf0 or 0xf1 or 0xf2 or 0xf3 or 0xf4 or 0xf5):
					erdCount = hex(geaPacket[5])
					payload = binascii.hexlify(geaPacket[6:(len-geaPacketOverheadSize)])
					print "Received message: Dst: " + dst + " Src: " + src + " Cmd: " + cmd + " numErds: " + erdCount + " Payload: " + payload
				else:
					payload = binascii.hexlify(geaPacket[5:(len-geaPacketOverheadSize)])
					print "Received message: Dst: " + dst + " Src: " + src + " Cmd: " + cmd + " Payload: " + payload
