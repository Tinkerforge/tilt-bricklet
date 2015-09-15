#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

# Callback subroutine for tilt state callback
sub cb_tilt_state
{
    my ($state) = @_;

    if ($state == Tinkerforge::BrickletTilt->TILT_STATE_CLOSED)
    {
        print "Tilt State: Closed\n";
    }
    elsif ($state == Tinkerforge::BrickletTilt->TILT_STATE_OPEN)
    {
        print "Tilt State: Open\n";
    }
    elsif ($state == Tinkerforge::BrickletTilt->TILT_STATE_CLOSED_VIBRATING)
    {
        print "Tilt State: Closed Vibrating\n";
    }
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $t = Tinkerforge::BrickletTilt->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Enable tilt state callback
$t->enable_tilt_state_callback();

# Register tilt state callback to subroutine cb_tilt_state
$t->register_callback($t->CALLBACK_TILT_STATE, 'cb_tilt_state');

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
