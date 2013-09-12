<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletTilt.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletTilt;

$host = 'localhost';
$port = 4223;
$uid = 'XYZ'; // Change to your UID

// Callback function for tilt state callback
function cb_tiltState($tiltState)
{
	switch($tiltState) {
 	   case BrickletTilt::TILT_STATE_CLOSED: echo "closed\n"; break;
 	   case BrickletTilt::TILT_STATE_OPEN: echo "open\n"; break;
 	   case BrickletTilt::TILT_STATE_CLOSED_VIBRATING: echo "closed vibrating\n"; break;
	}
}

$ipcon = new IPConnection(); // Create IP connection
$tilt = new BrickletTilt($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Enable tilt state callback
$tilt->enableTiltStateCallback();

// Register tiltState callback to function cb_tiltState
$tilt->registerCallback(BrickletTilt::CALLBACK_TILT_STATE, 'cb_tiltState');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
