using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletTilt tilt = new BrickletTilt(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current tilt state
		byte tiltState = tilt.GetTiltState();

		switch(tiltState)
		{
    		case BrickletTilt.TILT_STATE_CLOSED: System.Console.WriteLine("closed"); break;
    		case BrickletTilt.TILT_STATE_OPEN: System.Console.WriteLine("open"); break;
    		case BrickletTilt.TILT_STATE_CLOSED_VIBRATING: System.Console.WriteLine("closed vibrating"); break;
		}

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
		ipcon.Disconnect();
	}
}
