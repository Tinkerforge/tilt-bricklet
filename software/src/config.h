/* heart-rate-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * config.h: Heart Rate Bricklet specific configuration
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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/drivers/board/sam3s/SAM3S.h"

#include "heart-rate.h"

#define BRICKLET_FIRMWARE_VERSION_MAJOR 1
#define BRICKLET_FIRMWARE_VERSION_MINOR 0
#define BRICKLET_FIRMWARE_VERSION_REVISION 0

#define BRICKLET_HARDWARE_VERSION_MAJOR 1
#define BRICKLET_HARDWARE_VERSION_MINOR 0
#define BRICKLET_HARDWARE_VERSION_REVISION 0

#define BRICKLET_DEVICE_IDENTIFIER 245

#define LOGGING_LEVEL LOGGING_DEBUG
#define DEBUG_BRICKLET 0

#define BRICKLET_NO_OFFSET
#define BRICKLET_HAS_SIMPLE_SENSOR
#define INVOCATION_IN_BRICKLET_CODE
#define NUM_SIMPLE_VALUES 1
#define SIMPLE_VALUE_TYPE uint16_t

#define BEAT_INTERVALS_SIZE 8
#define DEBOUNCE_HIGH_TIMES_SIZE 8
#define DEBOUNCE_LOW_TIMES_SIZE 8
#define MAX_DEBOUNCE 75
#define MIN_DEBOUNCE 20
#define REDUCE_DEBOUNCE 3

#define PIN_SIGNAL (BS->pin1_ad)

typedef struct {
    uint32_t beat_intervals[BEAT_INTERVALS_SIZE];
    uint32_t debounce_high_times[DEBOUNCE_HIGH_TIMES_SIZE];
    uint32_t debounce_low_times[DEBOUNCE_LOW_TIMES_SIZE];
    uint32_t last_high_at;
    uint32_t last_low_at;
    uint32_t debounce_high;
    uint32_t debounce_low;
    uint8_t  beat_intervals_iterator;
    uint8_t  debounce_high_iterator;
	int32_t value[NUM_SIMPLE_VALUES];
	int32_t last_value[NUM_SIMPLE_VALUES];
    uint8_t     beat_state;
    uint8_t     beat_state_changed;
    uint8_t     beat_state_changed_callback_enabled;
    bool     beat_intervals_filled;
    bool     debounce_high_filled;
    bool     previous_signal_state;

	uint32_t signal_period[NUM_SIMPLE_VALUES];
	uint32_t signal_period_counter[NUM_SIMPLE_VALUES];

	uint32_t threshold_debounce;
	uint32_t threshold_period_current[NUM_SIMPLE_VALUES];
	int32_t threshold_min[NUM_SIMPLE_VALUES];
	int32_t threshold_max[NUM_SIMPLE_VALUES];
	char     threshold_option[NUM_SIMPLE_VALUES];

	int32_t threshold_min_save[NUM_SIMPLE_VALUES];
	int32_t threshold_max_save[NUM_SIMPLE_VALUES];
	char     threshold_option_save[NUM_SIMPLE_VALUES];

	uint32_t tick;
    uint32_t tick_counter;
} BrickContext;

#endif
