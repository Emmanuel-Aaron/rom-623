board="nano"
device_path="/dev/ttyUSB0"
board_type="arduino:avr:$board"

arduino-cli compile -b $board_type -p $device_path
echo -e "compiled\n"

arduino-cli upload gyro.ino -b $board_type -p $device_path
echo -e "uploaded\n"

