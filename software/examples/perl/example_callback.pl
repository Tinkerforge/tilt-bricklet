#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $t = Tinkerforge::BrickletTilt->new(&UID, $ipcon); # Create device object

# Callback function for tilt state callback
sub cb_tilt_state
{
    my ($tilt_state) = @_;

    if ($tilt_state == $t->TILT_STATE_CLOSED)
    {
        print "closed\n";
    }
    elsif ($tilt_state == $t->TILT_STATE_OPEN)
    {
        print "open\n";
    }
    elsif ($tilt_state == $t->TILT_STATE_CLOSED_VIBRATING)
    {
        print "closed vibrating\n";
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Enable tilt state callback
$t->enable_tilt_state_callback();

# Register tilt state callback to function cb_tilt_state
$t->register_callback($t->CALLBACK_TILT_STATE, 'cb_tilt_state');

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
