var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Tilt Bricklet

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
        // Get current tilt state
        t.getTiltState(
            function (state) {
                if(state === Tinkerforge.BrickletTilt.TILT_STATE_CLOSED) {
                    console.log('Tilt State: Closed');
                }
                else if(state === Tinkerforge.BrickletTilt.TILT_STATE_OPEN) {
                    console.log('Tilt State: Open');
                }
                else if(state === Tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING) {
                    console.log('Tilt State: Closed Vibrating');
                }
            },
            function (error) {
                console.log('Error: ' + error);
            }
        );
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
