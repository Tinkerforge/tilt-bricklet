Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Tilt Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim t As New BrickletTilt(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current tilt state
        Dim state As Byte = t.GetTiltState()

        If state = BrickletTilt.TILT_STATE_CLOSED Then
            Console.WriteLine("Tilt State: Closed")
        Else If state = BrickletTilt.TILT_STATE_OPEN Then
            Console.WriteLine("Tilt State: Open")
        Else If state = BrickletTilt.TILT_STATE_CLOSED_VIBRATING Then
            Console.WriteLine("Tilt State: Closed Vibrating")
        End If

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
