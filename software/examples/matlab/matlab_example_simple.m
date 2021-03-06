function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletTilt;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Tilt Bricklet

    ipcon = IPConnection(); % Create IP connection
    t = handle(BrickletTilt(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current tilt state
    state = t.getTiltState();

    if state == BrickletTilt.TILT_STATE_CLOSED
        fprintf('Tilt State: Closed\n');
    elseif state == BrickletTilt.TILT_STATE_OPEN
        fprintf('Tilt State: Open\n');
    elseif state == BrickletTilt.TILT_STATE_CLOSED_VIBRATING
        fprintf('Tilt State: Closed Vibrating\n');
    end

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
