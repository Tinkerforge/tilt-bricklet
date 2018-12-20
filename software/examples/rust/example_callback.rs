use std::{io, error::Error};
use std::thread;
use tinkerforge::{ip_connection::IpConnection, 
                  tilt_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Tilt Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let t = TiltBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

		// Enable tilt state callback
		t.enable_tilt_state_callback();

     let tilt_state_receiver = t.get_tilt_state_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `t` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for tilt_state in tilt_state_receiver {           
                		if tilt_state == TILT_BRICKLET_TILT_STATE_CLOSED { 
			println!("Tilt State: Closed");
		}
		else if tilt_state == TILT_BRICKLET_TILT_STATE_OPEN { 
			println!("Tilt State: Open");
		}
		else if tilt_state == TILT_BRICKLET_TILT_STATE_CLOSED_VIBRATING { 
			println!("Tilt State: Closed Vibrating");
		}
            }
        });

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
