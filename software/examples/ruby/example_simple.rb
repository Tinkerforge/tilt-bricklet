#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_tilt'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
t = BrickletTilt.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current tilt state
state = t.get_tilt_state

case state
  when BrickletTilt::TILT_STATE_CLOSED 
    puts 'Tilt State: Closed'
  when BrickletTilt::TILT_STATE_OPEN
    puts 'Tilt State: Open'
  when BrickletTilt::TILT_STATE_CLOSED_VIBRATING
    puts 'Tilt State: Closed Vibrating'
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
