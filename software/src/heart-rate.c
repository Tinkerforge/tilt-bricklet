/* heart-rate-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * heart-rate.c: Implementation of Heart Rate Bricklet messages
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

#include "heart-rate.h"

#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/utility/util_definitions.h"
#include "config.h"

#define SIMPLE_UNIT_HEART_RATE 0

const SimpleMessageProperty smp[] = {
	{SIMPLE_UNIT_HEART_RATE, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_HEART_RATE
	{SIMPLE_UNIT_HEART_RATE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_HEART_RATE_CALLBACK_PERIOD
	{SIMPLE_UNIT_HEART_RATE, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_HEART_RATE_CALLBACK_PERIOD
	{SIMPLE_UNIT_HEART_RATE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_HEART_RATE_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_HEART_RATE, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_HEART_RATE_CALLBACK_THRESHOLD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_SET}, // TYPE_SET_DEBOUNCE_PERIOD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_GET}, // TYPE_GET_DEBOUNCE_PERIOD
};

const SimpleUnitProperty sup[] = {
	{get_heart_rate, SIMPLE_SIGNEDNESS_UINT, FID_HEART_RATE, FID_HEART_RATE_REACHED, SIMPLE_UNIT_HEART_RATE} // heart rate
};

const uint8_t smp_length = sizeof(smp);

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {

        case FID_GET_HEART_RATE:
        case FID_SET_HEART_RATE_CALLBACK_PERIOD:
        case FID_GET_HEART_RATE_CALLBACK_PERIOD:
        case FID_SET_HEART_RATE_CALLBACK_THRESHOLD:
        case FID_GET_HEART_RATE_CALLBACK_THRESHOLD:
        case FID_SET_DEBOUNCE_PERIOD:
		case FID_GET_DEBOUNCE_PERIOD: {
			simple_invocation(com, data);
			break;
		}
        case FID_ENABLE_BEAT_CHANGED_CALLBACK: {
            BC->beat_state_changed_callback_enabled = 1;
            BA->com_return_setter(com, data);
            break;
        }
        case FID_DISABLE_BEAT_CHANGED_CALLBACK: {
            BC->beat_state_changed_callback_enabled = 0;
            BA->com_return_setter(com, data);
            break;
        }
        case FID_IS_BEAT_CHANGED_CALLBACK_ENABLED: {
            BeatStateChangedCallback bscc;
            if(BC->beat_state_changed_callback_enabled) {
                bscc.beat_state_changed_callback_status = 1;
            }
            else {
                bscc.beat_state_changed_callback_status = 0;
            }
            BA->send_blocking_with_timeout(&bscc,
                                           sizeof(BeatStateChangedCallback),
                                           *BA->com_current);
            break;
        }
		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			break;
		}
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

    BC->value[SIMPLE_UNIT_HEART_RATE] = 0;
    
    BC->beat_intervals_filled = false;
    BC->debounce_high_filled = false;
    BC->previous_signal_state = false;
    BC->beat_state = 0;
    BC->beat_state_changed = 0;
    BC->beat_state_changed_callback_enabled = 0;
    BC->beat_intervals_iterator = 0;
    BC->debounce_high_iterator = 0;
    BC->tick_counter = 0;
    BC->last_high_at = 0;
    BC->last_low_at = 0;
    
    BC->beat_intervals[0] = 0;
    BC->beat_intervals[1] = 0;
    BC->beat_intervals[2] = 0;
    BC->beat_intervals[3] = 0;
    BC->beat_intervals[4] = 0;
    BC->beat_intervals[5] = 0;
    BC->beat_intervals[6] = 0;
    BC->beat_intervals[7] = 0;
    
    BC->debounce_high_times[0] = 0;
    BC->debounce_high_times[1] = 0;
    BC->debounce_high_times[2] = 0;
    BC->debounce_high_times[3] = 0;
    BC->debounce_high_times[4] = 0;
    BC->debounce_high_times[5] = 0;
    BC->debounce_high_times[6] = 0;
    BC->debounce_high_times[7] = 0;
    
    BC->debounce_low_times[0] = 0;
    BC->debounce_low_times[1] = 0;
    BC->debounce_low_times[2] = 0;
    BC->debounce_low_times[3] = 0;
    BC->debounce_low_times[4] = 0;
    BC->debounce_low_times[5] = 0;
    BC->debounce_low_times[6] = 0;
    BC->debounce_low_times[7] = 0;
    
    //default debounce values
    BC->debounce_high = MIN_DEBOUNCE;
    BC->debounce_low = MIN_DEBOUNCE;
    
    // Setting the signal pin as input
    PIN_SIGNAL.pio->PIO_ODR  = PIN_SIGNAL.mask;
    PIN_SIGNAL.pio->PIO_PER  = PIN_SIGNAL.mask;

	simple_constructor();
}

void destructor(void) {
	simple_destructor();
}

void tick(const uint8_t tick_type) {
    if(tick_type & TICK_TASK_TYPE_CALCULATION) {
        BC->tick_counter++;
        if(BC->tick_counter > 60000/10) {
            BC->tick_counter = 0;
            for(uint8_t i = 0; i < BEAT_INTERVALS_SIZE; i++) {
                BC->beat_intervals[i] = 0;
            }
            BC->beat_intervals_filled = false;
            BC->value[SIMPLE_UNIT_HEART_RATE] = 0;
        }
        
        if(PIN_SIGNAL.pio->PIO_PDSR & PIN_SIGNAL.mask) {
            // Debounce mechanism after high was detected
            if (BC->tick_counter < BC->debounce_high/REDUCE_DEBOUNCE) {
                simple_tick(tick_type);
                return;
            }
            if(!(BC->previous_signal_state)) {
                BC->beat_state_changed = 1;
                BC->beat_state = 1;
                
                BC->last_high_at = BC->tick_counter;
                if(BC->beat_intervals_iterator == BEAT_INTERVALS_SIZE) {
                    BC->beat_intervals_iterator = 0;
                    BC->beat_intervals_filled = true;
                }
                BC->beat_intervals[BC->beat_intervals_iterator] = BC->tick_counter;
                if(BC->last_low_at != 0) {
                    BC->debounce_low_times[BC->beat_intervals_iterator] = BC->tick_counter - BC->last_low_at; // current detected low time
                }
                else {
                    BC->debounce_low_times[BC->beat_intervals_iterator] = BC->debounce_low;
                }
                BC->tick_counter = 0;
                
                if(BC->beat_intervals_iterator >= 0 && BC->beat_intervals_iterator < 8) {
                    if(BC->beat_intervals_filled) {
                        uint32_t sum = 0;
                        uint32_t sum_debounce_low = 0;
                        for(uint8_t i = 0; i < BEAT_INTERVALS_SIZE; i++) {
                            sum += BC->beat_intervals[i];
                            sum_debounce_low += BC->debounce_low_times[i];
                        }
                        BC->value[SIMPLE_UNIT_HEART_RATE] = (BEAT_INTERVALS_SIZE*60000)/sum;
                        BC->debounce_low = BETWEEN(MIN_DEBOUNCE, sum_debounce_low/BEAT_INTERVALS_SIZE, MAX_DEBOUNCE);
                    }
                    else {
                        uint32_t sum = 0;
                        uint32_t sum_debounce_low = 0;
                        for(uint8_t i = 0; i < BC->beat_intervals_iterator+1; i++) {
                            sum += BC->beat_intervals[i];
                            sum_debounce_low += BC->debounce_low_times[i];
                        }
                        BC->value[SIMPLE_UNIT_HEART_RATE] = ((BC->beat_intervals_iterator+1)*60000)/sum;
                        BC->debounce_low = BETWEEN(MIN_DEBOUNCE, sum_debounce_low/(BC->beat_intervals_iterator+1), MAX_DEBOUNCE);
                    }
                    BC->beat_intervals_iterator ++;
                }
                BC->previous_signal_state = true;
            }
        }
        if(!(PIN_SIGNAL.pio->PIO_PDSR & PIN_SIGNAL.mask)) {
            // Debounce mechanism after low was detected
            if (BC->tick_counter < BC->debounce_low/REDUCE_DEBOUNCE) {
                simple_tick(tick_type);
                return;
            }
            if(BC->previous_signal_state) {
                BC->beat_state_changed = 1;
                BC->beat_state = 0;
                
                BC->last_low_at = BC->tick_counter;
                if(BC->debounce_high_iterator == DEBOUNCE_HIGH_TIMES_SIZE) {
                    BC->debounce_high_iterator = 0;
                    BC->debounce_high_filled = true;
                }
                BC->debounce_high_times[BC->debounce_high_iterator] = BC->tick_counter; //current detected high time
                if(BC->debounce_high_iterator >= 0 && BC->debounce_high_iterator < DEBOUNCE_HIGH_TIMES_SIZE) {
                    if(BC->debounce_high_filled) {
                        uint32_t sum_debounce_high = 0;
                        for(uint8_t i = 0; i < DEBOUNCE_HIGH_TIMES_SIZE; i++) {
                            sum_debounce_high += BC->debounce_high_times[i];
                        }
                        BC->debounce_high = BETWEEN(MIN_DEBOUNCE, sum_debounce_high/DEBOUNCE_HIGH_TIMES_SIZE, MAX_DEBOUNCE);
                    }
                    else {
                        uint32_t sum_debounce_high = 0;
                        for(uint8_t i = 0; i < BC->debounce_high_iterator+1; i++) {
                            sum_debounce_high += BC->debounce_high_times[i];
                        }
                        BC->debounce_high = BETWEEN(MIN_DEBOUNCE, sum_debounce_high/BC->debounce_high_iterator+1, MAX_DEBOUNCE);
                    }
                    BC->debounce_high_iterator ++;
                }
                BC->previous_signal_state = false;
            }
        }
    }
    if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->beat_state_changed_callback_enabled) {
			if(BC->beat_state_changed) {
                BC->beat_state_changed = 0;
                send_beat_state_changed_callback();
            }
		}
	}
    simple_tick(tick_type);
}

int32_t get_heart_rate(const int32_t value) {
    return BC->value[SIMPLE_UNIT_HEART_RATE];
}

void send_beat_state_changed_callback(void) {
    BeatState bstate;
	BA->com_make_default_header(&bstate, BS->uid, sizeof(BeatState), FID_BEAT_STATE_CHANGED);
	bstate.current_beat_state = BC->beat_state;

	BA->send_blocking_with_timeout(&bstate,
								   sizeof(BeatState),
								   *BA->com_current);
}

