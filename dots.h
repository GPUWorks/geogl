#ifndef _SM3D_DOTS_H_
#define _SM3D_DOTS_H_

#include <map>

struct Dot {
	double lng;
	double lat;
	int64_t seen_at;
};

class Dots {
public:
	std::map<int, Dot> dots;
	void run();
};

#endif
