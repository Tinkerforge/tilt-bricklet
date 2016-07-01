Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Tilt Bricklet

    ' Callback subroutine for tilt state callback
    Sub TiltStateCB(ByVal sender As BrickletTilt, ByVal state As Byte)
        Select Case state
            Case BrickletTilt.TILT_STATE_CLOSED
                Console.WriteLine("Tilt State: Closed")
            Case BrickletTilt.TILT_STATE_OPEN
                Console.WriteLine("Tilt State: Open")
            Case BrickletTilt.TILT_STATE_CLOSED_VIBRATING
                Console.WriteLine("Tilt State: Closed Vibrating")
        End Select
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim t As New BrickletTilt(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Enable tilt state callback
        t.EnableTiltStateCallback()

        ' Register tilt state callback to subroutine TiltStateCB
        AddHandler t.TiltState, AddressOf TiltStateCB

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
