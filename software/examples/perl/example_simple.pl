#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Tilt Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $t = Tinkerforge::BrickletTilt->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current tilt state
my $state = $t->get_tilt_state();

if ($state == $t->TILT_STATE_CLOSED)
{
    print "Tilt State: Closed\n";
}
elsif ($state == $t->TILT_STATE_OPEN)
{
    print "Tilt State: Open\n";
}
elsif ($state == $t->TILT_STATE_CLOSED_VIBRATING)
{
    print "Tilt State: Closed Vibrating\n";
}

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
