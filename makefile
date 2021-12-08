compile:
	arduino-cli compile -b "arduino:avr:nano" src/

upload:
	arduino-cli upload -b "arduino:avr:nano" -p /dev/ttyUSB0 src/src.ino


