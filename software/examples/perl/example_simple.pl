#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'fgfds'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
my $tilt = BrickletTilt->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current tilt state
my $tilt_state = $tilt->get_tilt_state();

if (tilt_state == $tilt->TILT_STATE_CLOSED)
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

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

