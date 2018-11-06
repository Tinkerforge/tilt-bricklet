use std::{error::Error, io, thread};
use tinkerforge::{ipconnection::IpConnection, tilt_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Tilt Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let tilt_bricklet = TiltBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Enable tilt state callback
    tilt_bricklet.enable_tilt_state_callback();

    //Create listener for tilt state events.
    let tilt_state_listener = tilt_bricklet.get_tilt_state_receiver();
    // Spawn thread to handle received events. This thread ends when the tilt_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in tilt_state_listener {
            if event == TILT_BRICKLET_TILT_STATE_CLOSED {
                println!("Tilt State: Closed");
            } else if event == TILT_BRICKLET_TILT_STATE_OPEN {
                println!("Tilt State: Open");
            } else if event == TILT_BRICKLET_TILT_STATE_CLOSED_VIBRATING {
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
