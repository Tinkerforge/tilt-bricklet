function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Tilt Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    t = javaObject("com.tinkerforge.BrickletTilt", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Enable tilt state callback
    t.enableTiltStateCallback();

    % Register tilt state callback to function cb_tilt_state
    t.addTiltStateCallback(@cb_tilt_state);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for tilt state callback
function cb_tilt_state(e)
    state = java2int(e.state);

    if state == 0
        fprintf("Tilt State: Closed\n");
    elseif state == 1
        fprintf("Tilt State: Open\n");
    elseif state == 2
        fprintf("Tilt State: Closed Vibrating\n");
    end
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
