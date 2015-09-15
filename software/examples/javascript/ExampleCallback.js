var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var t = new Tinkerforge.BrickletTilt(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Enable tilt state callback
        t.enableTiltStateCallback();
    }
);

// Register tilt state callback
t.on(Tinkerforge.BrickletTilt.CALLBACK_TILT_STATE,
    // Callback function for tilt state callback
    function (state) {
        switch(state) {
        case Tinkerforge.BrickletTilt.TILT_STATE_CLOSED:
            console.log('Tilt State: Closed');
            break;
        case Tinkerforge.BrickletTilt.TILT_STATE_OPEN:
            console.log('Tilt State: Open');
            break;
        case Tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING:
            console.log('Tilt State: Closed Vibrating');
            break;
        }
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
