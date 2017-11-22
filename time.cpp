#include <stdint.h>
#include <unistd.h>
#include <ctime>

#include "time.h"

uint64_t get_time() {
	const uint64_t NSPS = 1000000000;

	//struct timespec {  __time_t tv_sec;    long int tv_nsec;  };  -- total 8 bytes
	struct timespec ts;

	// CLOCK_REALTIME - system wide real time clock
	clock_gettime(CLOCK_REALTIME, &ts);

	// to 8 byte     from   4 byte
	uint64_t uli_nsec = static_cast<uint64_t>(ts.tv_nsec);
	uint64_t uli_sec  = static_cast<uint64_t>(ts.tv_sec);

	uint64_t total_ns = uli_nsec + (uli_sec * NSPS);

	return total_ns;
 }