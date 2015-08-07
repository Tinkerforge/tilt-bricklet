#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_tilt import BrickletTilt

# Callback function for tilt state callback
def cb_tilt_state(tilt_state):
    if tilt_state == Tilt.TILT_STATE_CLOSED:
        print('closed')
    elif tilt_state == Tilt.TILT_STATE_OPEN:
        print('open')
    elif tilt_state == Tilt.TILT_STATE_CLOSED_VIBRATING:
        print('closed vibrating')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    t = BrickletTilt(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Enable tilt state callback
    t.enable_tilt_state_callback()

    # Register tilt state callback to function cb_tilt_state
    t.register_callback(t.CALLBACK_TILT_STATE, cb_tilt_state)

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
