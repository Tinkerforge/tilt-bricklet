#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Tilt Bricklet

# Enable tilt state callback
tinkerforge call tilt-bricklet $uid enable-tilt-state-callback

# Handle incoming tilt state callbacks
tinkerforge dispatch tilt-bricklet $uid tilt-state &

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
