var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'fgfds';//Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var tilt = new Tinkerforge.BrickletTilt(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

//Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Get current tilt state
        tilt.getTiltState(
            function(tiltState) {
                if(tiltState === Tinkerforge.BrickletTilt.TILT_STATE_CLOSED) {
                    console.log('Closed');
                } 
                if(tiltState === Tinkerforge.BrickletTilt.TILT_STATE_OPEN) {
                    console.log('Open');
                }
                if(tiltState === Tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING) {
                    console.log('Close Vibrating');
                }
            },
            function(error) {
                console.log('Error: '+error);
            }
        );
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

