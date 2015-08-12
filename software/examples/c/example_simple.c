#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_tilt.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

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

	// Get current tilt state
	uint8_t tilt_state;
	if(tilt_get_tilt_state(&t, &tilt_state) < 0) {
		fprintf(stderr, "Could not get value, probably timeout\n");
		exit(1);
	}

	switch(tilt_state) {
	case TILT_TILT_STATE_CLOSED:           printf("closed\n"); break;
	case TILT_TILT_STATE_OPEN:             printf("open\n"); break;
	case TILT_TILT_STATE_CLOSED_VIBRATING: printf("closed vibrating\n"); break;
	}

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
