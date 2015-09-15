Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim t As New BrickletTilt(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current tilt state
        Dim state As Byte = t.GetTiltState()

        Select Case state
            Case BrickletTilt.TILT_STATE_CLOSED
                Console.WriteLine("Tilt State: Closed")
            Case BrickletTilt.TILT_STATE_OPEN
                Console.WriteLine("Tilt State: Open")
            Case BrickletTilt.TILT_STATE_CLOSED_VIBRATING
                Console.WriteLine("Tilt State: Closed Vibrating")
        End Select

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
