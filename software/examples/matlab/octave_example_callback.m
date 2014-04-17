function octave_example_callback
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "fgfds"; % Change to your UID
    
    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    tilt = java_new("com.tinkerforge.BrickletTilt", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Enable tilt state callback
    tilt.enableTiltStateCallback();

    % Register tilt state callback to function cb_tilt_state
    tilt.addTiltStateCallback(@cb_tilt_state);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for tilt state callback
function cb_tilt_state(e)
    if str2double(e.state.toString()) == 0
        fprintf("Closed\n");
    elseif str2double(e.state.toString()) == 1
        fprintf("Open\n");
    elseif str2double(e.state.toString()) == 2
        fprintf("Closed Vibrating\n");
    end
end
