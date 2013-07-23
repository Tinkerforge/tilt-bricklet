/* tilt-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * tilt.c: Implementation of Tilt Bricklet messages
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

#include "tilt.h"

#include "bricklib/utility/init.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "brickletlib/bricklet_entry.h"
#include "config.h"

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_GET_TILT_STATE: {
			get_tilt_state(com, (GetTiltState*)data);
			return;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			break;
		}
	}
}

void get_tilt_state(const ComType com, const GetTiltState *data) {
	GetTiltStateReturn gtsr;
	gtsr.header        = data->header;
	gtsr.header.length = sizeof(GetTiltStateReturn);
	gtsr.state         = BC->state;

	BA->send_blocking_with_timeout(&gtsr, sizeof(GetTiltStateReturn), com);
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	PIN_TILT.type = PIO_INPUT;
	PIN_TILT.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_TILT, 1);
}

void destructor(void) {
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->debounce == 0) {
			if(PIN_TILT.pio->PIO_PDSR & PIN_TILT.mask) {
				if(BC->state != TILT_STATE_CLOSED) {
					BC->state = TILT_STATE_CLOSED;
					BC->debounce = TILT_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			} else {
				if(BC->state != TILT_STATE_OPEN) {
					BC->state = TILT_STATE_OPEN;
					BC->debounce = TILT_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			}
		} else {
			BC->debounce--;
		}
	}

	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->state_changed) {
			send_state_changed_callback();
			BC->state_changed = false;
		}
	}
}

void send_state_changed_callback(void) {
	TiltStateChanged tsc;
	BA->com_make_default_header(&tsc, BS->uid, sizeof(TiltStateChanged), FID_TILT_STATE_CHANGED);
	tsc.state = BC->state;

	BA->send_blocking_with_timeout(&tsc,
								   sizeof(TiltStateChanged),
								   *BA->com_current);
}
