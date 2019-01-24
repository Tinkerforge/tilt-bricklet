package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/tilt_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Tilt Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	t, _ := tilt_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get current tilt state.
	state, _ := t.GetTiltState()

	if state == tilt_bricklet.TiltStateClosed {
		fmt.Println("Tilt State: Closed")
	} else if state == tilt_bricklet.TiltStateOpen {
		fmt.Println("Tilt State: Open")
	} else if state == tilt_bricklet.TiltStateClosedVibrating {
		fmt.Println("Tilt State: Closed Vibrating")
	}

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
