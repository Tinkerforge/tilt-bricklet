function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletTilt;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Tilt Bricklet

    ipcon = IPConnection(); % Create IP connection
    t = handle(BrickletTilt(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Enable tilt state callback
    t.enableTiltStateCallback();

    % Register tilt state callback to function cb_tilt_state
    set(t, 'TiltStateCallback', @(h, e) cb_tilt_state(e));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for tilt state callback
function cb_tilt_state(e)
    if e.state == com.tinkerforge.BrickletTilt.TILT_STATE_CLOSED
        fprintf('Tilt State: Closed\n');
    elseif e.state == com.tinkerforge.BrickletTilt.TILT_STATE_OPEN
        fprintf('Tilt State: Open\n');
    elseif e.state == com.tinkerforge.BrickletTilt.TILT_STATE_CLOSED_VIBRATING
        fprintf('Tilt State: Closed Vibrating\n');
    end
end
