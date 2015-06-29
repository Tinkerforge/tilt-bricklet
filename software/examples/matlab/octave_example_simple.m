function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "fgfds"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    tilt = java_new("com.tinkerforge.BrickletTilt", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    state = short2int(tilt.getTiltState());

    if state == 0
        fprintf("Closed\n");
    elseif state == 1
        fprintf("Open\n");
    elseif state == 2
        fprintf("Closed Vibrating\n");
    end

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

function int = short2int(short)
    if compare_versions(version(), "3.8", "<=")
        int = short.intValue();
    else
        int = short;
    end
end
