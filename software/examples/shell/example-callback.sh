#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# Enable tilt state callback
tinkerforge call tilt-bricklet $uid enable-tilt-state-callback

# handle incoming tilt state callbacks
tinkerforge dispatch tilt-bricklet $uid tilt-state
