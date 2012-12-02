import serial
import sys
if len(sys.argv) < 2:
	s = "Hello World"
else:
	s = sys.argv[1]
print s
i = 0
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write(' ')
while ser.read():
	if i >= len(s):
		ser.write(" ")
		break
	ser.write(s[i])
	i += 1
ser.close()
