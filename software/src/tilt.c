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

		case FID_ENABLE_TILT_STATE_CALLBACK: {
			enable_tilt_state_callback(com, (EnableTiltStateCallback*)data);
			return;
		}

		case FID_DISABLE_TILT_STATE_CALLBACK: {
			disable_tilt_state_callback(com, (DisableTiltStateCallback*)data);
			return;
		}

		case FID_IS_TILT_STATE_CALLBACK_ENABLED: {
			is_tilt_state_callback_enabled(com, (IsTiltStateCallbackEnabled*)data);
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

void enable_tilt_state_callback(const ComType com, const EnableTiltStateCallback *data) {
	BC->callback_enabled = true;
	BA->com_return_setter(com, data);
}

void disable_tilt_state_callback(const ComType com, const DisableTiltStateCallback *data) {
	BC->callback_enabled = false;
	BA->com_return_setter(com, data);
}

void is_tilt_state_callback_enabled(const ComType com, const IsTiltStateCallbackEnabled *data) {
	IsTiltStateCallbackEnabledReturn itscer;
	itscer.header        = data->header;
	itscer.header.length = sizeof(IsTiltStateCallbackEnabledReturn);
	itscer.enabled       = BC->callback_enabled;

	BA->send_blocking_with_timeout(&itscer, sizeof(IsTiltStateCallbackEnabledReturn), com);
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	PIN_TILT.type = PIO_INPUT;
	PIN_TILT.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_TILT, 1);

    BC->count_open = 0;
    BC->callback_enabled = false;
    BC->state = TILT_STATE_CLOSED;
    BC->debounce = TILT_DEBOUNCE_TIME;
}

void destructor(void) {
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->debounce == 0) {
			uint8_t new_state = TILT_STATE_CLOSED_VIBRATING;
			if(BC->count_open >= TILT_DEBOUNCE_TIME - TILT_DEBOUNCE_TIME/50) { // 2% bounce or less is ignored
				new_state = TILT_STATE_OPEN;
			} else if(BC->count_open <= TILT_DEBOUNCE_TIME/50) { // 2% bounce or less is ignored
				new_state = TILT_STATE_CLOSED;
			}
			if(BC->state != new_state) {
				BC->state = new_state;
				if(BC->callback_enabled) {
					BC->state_changed = true;
				}
			}
			BC->count_open = 0;
			BC->debounce = TILT_DEBOUNCE_TIME;
		} else {
			if(PIN_TILT.pio->PIO_PDSR & PIN_TILT.mask) {
				BC->count_open++;
			}
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
	TiltState ts;
	BA->com_make_default_header(&ts, BS->uid, sizeof(TiltState), FID_TILT_STATE);
	ts.state = BC->state;

	BA->send_blocking_with_timeout(&ts,
								   sizeof(TiltState),
								   *BA->com_current);
}
