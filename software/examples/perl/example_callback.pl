#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'fgfds'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
our $tilt = BrickletTilt->new(&UID, $ipcon); # Create device object

# Callback function for tilt state callback
sub cb_tilt_state
{
    my ($tilt_state) = @_;

    if ($tilt_state == $tilt->TILT_STATE_CLOSED)
    {
        print "\nclosed\n";
    }

    if ($tilt_state == $tilt->TILT_STATE_OPEN)
    {
        print "\nopen\n";
    }

    if ($tilt_state == $tilt->TILT_STATE_CLOSED_VIBRATING)
    {
        print "\nclosed vibrating\n";
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Enable tilt state callback
$tilt->enable_tilt_state_callback();

# Register tilt state callback to function cb_tilt_state
$tilt->register_callback($tilt->CALLBACK_TILT_STATE, 'cb_tilt_state');

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

