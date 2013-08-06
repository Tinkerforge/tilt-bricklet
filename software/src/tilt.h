/* tilt-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * tilt.h: Implementation of Tilt Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef TILT_H
#define TILT_H

#include <stdint.h>
#include "bricklib/com/com_common.h"

#define TILT_STATE_CLOSED            0
#define TILT_STATE_OPEN              1
#define TILT_STATE_CLOSED_VIBRATING  2
#define TILT_DEBOUNCE_TIME 100 // in ms

#define FID_GET_TILT_STATE 1
#define FID_ENABLE_TILT_STATE_CALLBACK 2
#define FID_DISABLE_TILT_STATE_CALLBACK 3
#define FID_IS_TILT_STATE_CALLBACK_ENABLED 4
#define FID_TILT_STATE 5

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetTiltState;

typedef struct {
	MessageHeader header;
	uint8_t state;
} __attribute__((__packed__)) GetTiltStateReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) EnableTiltStateCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) DisableTiltStateCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsTiltStateCallbackEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsTiltStateCallbackEnabledReturn;

typedef struct {
	MessageHeader header;
	uint8_t state;
} __attribute__((__packed__)) TiltState;

void get_tilt_state(const ComType com, const GetTiltState *data);
void enable_tilt_state_callback(const ComType com, const EnableTiltStateCallback *data);
void disable_tilt_state_callback(const ComType com, const DisableTiltStateCallback *data);
void is_tilt_state_callback_enabled(const ComType com, const IsTiltStateCallbackEnabled *data);

void send_state_changed_callback(void);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
