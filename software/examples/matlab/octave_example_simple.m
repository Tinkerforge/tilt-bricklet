function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "fgfds"; % Change to your UID
    
    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    tilt = java_new("com.tinkerforge.BrickletTilt", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    state = tilt.getTiltState();
    
    if str2double(state.toString()) == 0
        fprintf("Closed\n");
    elseif str2double(state.toString()) == 1
        fprintf("Open\n");
    elseif str2double(state.toString()) == 2
        fprintf("Closed Vibrating\n");
    end

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
