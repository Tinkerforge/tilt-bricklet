function matlab_example_callback
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletTilt;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'fgfds'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    tilt = BrickletTilt(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Enable tilt state callback
    tilt.enableTiltStateCallback();

    % Register tilt state callback to function cb_tilt_state
    set(tilt, 'TiltStateCallback', @(h, e)cb_tilt_state(e));

    input('\nPress any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback function for tilt state callback
function cb_tilt_state(tilt_state)
    if tilt_state.state == com.tinkerforge.BrickletTilt.TILT_STATE_CLOSED
        fprintf('Closed\n');
    elseif tilt_state.state == com.tinkerforge.BrickletTilt.TILT_STATE_OPEN
        fprintf('Open\n');
    elseif tilt_state.state == com.tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING
        fprintf('Closed Vibrating\n');
    end
end
