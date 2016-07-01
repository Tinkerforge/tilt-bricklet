function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Tilt Bricklet

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    t = java_new("com.tinkerforge.BrickletTilt", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current tilt state
    state = java2int(t.getTiltState());

    if state == 0
        fprintf("Tilt State: Closed\n");
    elseif state == 1
        fprintf("Tilt State: Open\n");
    elseif state == 2
        fprintf("Tilt State: Closed Vibrating\n");
    end

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
