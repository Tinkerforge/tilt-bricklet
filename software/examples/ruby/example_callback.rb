#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_tilt'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Tilt Bricklet

ipcon = IPConnection.new # Create IP connection
t = BrickletTilt.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Enable tilt state callback
t.enable_tilt_state_callback

# Register tilt state callback
t.register_callback(BrickletTilt::CALLBACK_TILT_STATE) do |state|
  if state == BrickletTilt::TILT_STATE_CLOSED
    puts "Tilt State: Closed"
  elsif state == BrickletTilt::TILT_STATE_OPEN
    puts "Tilt State: Open"
  elsif state == BrickletTilt::TILT_STATE_CLOSED_VIBRATING
    puts "Tilt State: Closed Vibrating"
  end
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
