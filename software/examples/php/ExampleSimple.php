<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletTilt.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletTilt;

$host = 'localhost';
$port = 4223;
$uid = 'XYZ'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$tilt = new BrickletTilt($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Get current tilt state
$tiltState = $tilt->getTiltState() / 10.0;

switch($tiltState) {
   case BrickletTilt::TILT_STATE_CLOSED: echo "closed\n"; break;
   case BrickletTilt::TILT_STATE_OPEN: echo "open\n"; break;
   case BrickletTilt::TILT_STATE_CLOSED_VIBRATING: echo "closed vibrating\n"; break;
}

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
