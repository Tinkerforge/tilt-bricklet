var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'fgfds'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var tilt = new Tinkerforge.BrickletTilt(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Enable tilt state callback
        tilt.enableTiltStateCallback();
    }
);

// Register tilt state callback
tilt.on(Tinkerforge.BrickletTilt.CALLBACK_TILT_STATE,
    function(tiltState) {
        switch(tiltState) {
        case Tinkerforge.BrickletTilt.TILT_STATE_CLOSED:
            console.log('Closed');
            break;
        case Tinkerforge.BrickletTilt.TILT_STATE_OPEN:
            console.log('Open');
            break;
        case Tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING:
            console.log('Closed vibrating');
            break;
        }
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
