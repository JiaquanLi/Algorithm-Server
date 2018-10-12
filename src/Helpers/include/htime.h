#include <stdint.h>
typedef enum {
	MONOTONIC,
	BOOTTIME,//Identical to CLOCK_MONOTONIC, except it also includes any time that the system is suspended
} ClockType_t;
uint64_t get_time_us(void);
uint64_t get_time_ms(ClockType_t type = MONOTONIC);
