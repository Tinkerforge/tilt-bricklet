Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim tilt As New BrickletTilt(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current tilt state
        Dim tiltState As Byte = tilt.GetTiltState()

        Select Case tiltState
            Case BrickletTilt.TILT_STATE_CLOSED
                System.Console.WriteLine("closed")
            Case BrickletTilt.TILT_STATE_OPEN
                System.Console.WriteLine("open")
            Case BrickletTilt.TILT_STATE_CLOSED_VIBRATING
                System.Console.WriteLine("closed vibrating")
        End Select

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
