import serial
import time
import struct
import sys
import binascii

ttydev = "/dev/ttyUSB0"
baud = 230400

port = serial.Serial(ttydev, baud)

while True:
	time.sleep(0.075)
	bytesToRead = port.in_waiting
	if (bytesToRead > 0):
		data = port.read(bytesToRead)
		buffer = bytearray(data)

		if (buffer[0] == 0xe2):
			if (0xe0 in buffer):
				geaPacket = buffer[0:(buffer[2] + 1)]
			else:
				geaPacket = buffer[0:buffer[2]]

				dst = hex(geaPacket[1])
				len = geaPacket[2]
				src = hex(geaPacket[3])
				cmd = hex(geaPacket[4])
				if (cmd == 0xb8 or 0xf0 or 0xf1 or 0xf2 or 0xf3 or 0xf4 or 0xf5):
					erdCount = hex(geaPacket[5])
					payload = binascii.hexlify(geaPacket[6:(len-7)])
					print "Received message: Dst: " + dst + " Src: " + src + " Cmd: " + cmd + " numErds: " + erdCount + " Payload: " + payload
				else:
					payload = binascii.hexlify(geaPacket[5:(len-7)])
					print "Received message: Dst: " + dst + " Src: " + src + " Cmd: " + cmd + " Payload: " + payload
