function octave_example_callback()
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
    state = short2int(e.state);

    if state == 0
        fprintf("Closed\n");
    elseif state == 1
        fprintf("Open\n");
    elseif state == 2
        fprintf("Closed Vibrating\n");
    end
end

function int = short2int(short)
    if compare_versions(version(), "3.8", "<=")
        int = short.intValue();
    else
        int = short;
    end
end
