import tweetstream
import serial
import re
from pprint import pprint

ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write(" ");
	
regexTestString = "Hello @DigitalClacks !"
print re.sub(r'[^\w+]', ' ', re.sub(r'(@\S+)', '', regexTestString))
	
stream = tweetstream.FilterStream("DigitalClacks", "outofcheese", [982842908])
i = 0
for tweet in stream:
	ser.write("@")
	startingText = re.sub(r'[^\w+]', ' ', re.sub(r'(@\S+)', '', tweet["text"]))
	print startingText
	for c in startingText:
		ser.read()
		ser.write(c)
	
