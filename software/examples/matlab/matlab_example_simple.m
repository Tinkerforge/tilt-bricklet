function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletTilt;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    t = BrickletTilt(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current tilt state
    state = t.getTiltState();

    if state == t.TILT_STATE_CLOSED
        fprintf('Tilt State: Closed\n');
    elseif state == t.TILT_STATE_OPEN
        fprintf('Tilt State: Open\n');
    elseif state == t.TILT_STATE_CLOSED_VIBRATING
        fprintf('Tilt State: Closed Vibrating\n');
    end

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
