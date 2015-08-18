Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback function for tilt state callback
    Sub TiltStateCB(ByVal sender As BrickletTilt, ByVal tiltState As Byte)
        Select Case tiltState
            Case BrickletTilt.TILT_STATE_CLOSED
                System.Console.WriteLine("closed")
            Case BrickletTilt.TILT_STATE_OPEN
                System.Console.WriteLine("open")
            Case BrickletTilt.TILT_STATE_CLOSED_VIBRATING
                System.Console.WriteLine("closed vibrating")
        End Select
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim t As New BrickletTilt(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Enable tilt state callback
        t.EnableTiltStateCallback()

        ' Register tilt state callback to function TiltStateCB
        AddHandler t.TiltState, AddressOf TiltStateCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
