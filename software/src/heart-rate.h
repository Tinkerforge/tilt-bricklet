/* heart-rate-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * heart-rate.h: Heart Rate Bricklet specific configuration
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

#ifndef HEART_RATE_H
#define HEART_RATE_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

#define FID_GET_HEART_RATE 1
#define FID_SET_HEART_RATE_CALLBACK_PERIOD 2
#define FID_GET_HEART_RATE_CALLBACK_PERIOD 3
#define FID_SET_HEART_RATE_CALLBACK_THRESHOLD 4
#define FID_GET_HEART_RATE_CALLBACK_THRESHOLD 5
#define FID_SET_DEBOUNCE_PERIOD 6
#define FID_GET_DEBOUNCE_PERIOD 7
#define FID_HEART_RATE 8
#define FID_HEART_RATE_REACHED 9
#define FID_BEAT_STATE_CHANGED 10
#define FID_ENABLE_BEAT_CHANGED_CALLBACK 11
#define FID_DISABLE_BEAT_CHANGED_CALLBACK 12
#define FID_IS_BEAT_CHANGED_CALLBACK_ENABLED 13

typedef struct {
	MessageHeader header;
	uint8_t beat_state_changed_callback_status;
} __attribute__((__packed__)) BeatStateChangedCallback;

typedef struct {
	MessageHeader header;
	uint8_t current_beat_state;
} __attribute__((__packed__)) BeatState;


int32_t get_heart_rate(const int32_t value);
void send_beat_state_changed_callback(void);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
