function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletTilt;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'fgfds'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    tilt = BrickletTilt(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current tilt state
    state = tilt.getTiltState();

    if state == tilt.TILT_STATE_CLOSED
        fprintf('Closed\n');
    elseif state == tilt.TILT_STATE_OPEN
        fprintf('Open\n');
    elseif state == tilt.TILT_STATE_CLOSED_VIBRATING
        fprintf('Closed vibrating\n');
    end

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end
