#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Tilt Bricklet

# Get current tilt state
tinkerforge call tilt-bricklet $uid get-tilt-state
