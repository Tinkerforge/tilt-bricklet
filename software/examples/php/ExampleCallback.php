<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletTilt.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletTilt;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Tilt Bricklet

// Callback function for tilt state callback
function cb_tiltState($state)
{
    switch($state) {
    case BrickletTilt::TILT_STATE_CLOSED:
        echo "Tilt State: Closed\n";
        break;
    case BrickletTilt::TILT_STATE_OPEN:
        echo "Tilt State: Open\n";
        break;
    case BrickletTilt::TILT_STATE_CLOSED_VIBRATING:
        echo "Tilt State: Closed Vibrating\n";
        break;
    }
}

$ipcon = new IPConnection(); // Create IP connection
$t = new BrickletTilt(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Enable tilt state callback
$t->enableTiltStateCallback();

// Register tilt state callback to function cb_tiltState
$t->registerCallback(BrickletTilt::CALLBACK_TILT_STATE, 'cb_tiltState');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
