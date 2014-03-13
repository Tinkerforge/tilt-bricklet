<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletTilt.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletTilt;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$tilt = new BrickletTilt(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
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
