#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_tilt.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for tilt state callback
void cb_tilt_state(uint8_t state, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	switch(state) {
	case TILT_TILT_STATE_CLOSED:
		printf("Tilt State: Closed\n");
		break;
	case TILT_TILT_STATE_OPEN:
		printf("Tilt State: Open\n");
		break;
	case TILT_TILT_STATE_CLOSED_VIBRATING:
		printf("Tilt State: Closed Vibrating\n");
		break;
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Tilt t;
	tilt_create(&t, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Enable tilt state callback
	tilt_enable_tilt_state_callback(&t);

	// Register tilt state callback to function cb_tilt_state
	tilt_register_callback(&t,
	                       TILT_CALLBACK_TILT_STATE,
	                       (void *)cb_tilt_state,
	                       NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
