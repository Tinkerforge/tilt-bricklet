import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletTilt;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletTilt t = new BrickletTilt(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Enable tilt state callback
		t.enableTiltStateCallback();

		// Add tilt state listener
		t.addTiltStateListener(new BrickletTilt.TiltStateListener() {
			public void tiltState(short state) {
				switch(state) {
				case BrickletTilt.TILT_STATE_CLOSED:
					System.out.println("Tilt State: Closed");
					break;
				case BrickletTilt.TILT_STATE_OPEN:
					System.out.println("Tilt State: Open");
					break;
				case BrickletTilt.TILT_STATE_CLOSED_VIBRATING:
					System.out.println("Tilt State: Closed Vibrating");
					break;
				}
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
