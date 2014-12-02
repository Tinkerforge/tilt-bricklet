using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for tilt state callback 
	static void TiltStateCB(BrickletTilt sender, byte tiltState)
	{
		switch(tiltState)
		{
    		case BrickletTilt.TILT_STATE_CLOSED: System.Console.WriteLine("closed"); break;
    		case BrickletTilt.TILT_STATE_OPEN: System.Console.WriteLine("open"); break;
    		case BrickletTilt.TILT_STATE_CLOSED_VIBRATING: System.Console.WriteLine("closed vibrating"); break;
		}
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletTilt tilt = new BrickletTilt(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Enable tilt state callback
		tilt.EnableTiltStateCallback();

		// Register tiltState callback to function TiltStateCB
		tilt.TiltState += TiltStateCB;

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
