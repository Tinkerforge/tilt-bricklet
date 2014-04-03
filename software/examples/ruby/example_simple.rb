#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_tilt'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
tilt = BrickletTilt.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current tilt state
tilt_state = tilt.get_tilt_state

case tilt_state
  when BrickletTilt::TILT_STATE_CLOSED 
    puts 'closed'
  when BrickletTilt::TILT_STATE_OPEN
    puts 'open'
  when BrickletTilt::TILT_STATE_CLOSED_VIBRATING
    puts 'closed vibrating'
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
