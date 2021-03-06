using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Tilt Bricklet

	// Callback function for tilt state callback
	static void TiltStateCB(BrickletTilt sender, byte state)
	{
		if(state == BrickletTilt.TILT_STATE_CLOSED)
		{
			Console.WriteLine("Tilt State: Closed");
		}
		else if(state == BrickletTilt.TILT_STATE_OPEN)
		{
			Console.WriteLine("Tilt State: Open");
		}
		else if(state == BrickletTilt.TILT_STATE_CLOSED_VIBRATING)
		{
			Console.WriteLine("Tilt State: Closed Vibrating");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletTilt t = new BrickletTilt(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Enable tilt state callback
		t.EnableTiltStateCallback();

		// Register tilt state callback to function TiltStateCB
		t.TiltStateCallback += TiltStateCB;

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
