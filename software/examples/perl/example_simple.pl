#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletTilt;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'fgfds'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $tilt = Tinkerforge::BrickletTilt->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current tilt state
my $tilt_state = $tilt->get_tilt_state();

if ($tilt_state == $tilt->TILT_STATE_CLOSED)
{
    print "closed\n";
}
elsif ($tilt_state == $tilt->TILT_STATE_OPEN)
{
    print "open\n";
}
elsif ($tilt_state == $tilt->TILT_STATE_CLOSED_VIBRATING)
{
    print "closed vibrating\n";
}

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();


