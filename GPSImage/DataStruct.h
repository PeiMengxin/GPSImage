#ifndef _DATASTRUCT_H__
#define _DATASTRUCT_H__
#include <iostream>

class GPS
{
public:
	GPS();
	~GPS();

	double latitude;
	double longitude;
	double height;

	friend std::ostream& operator<< (std::ostream &os, const GPS &gps)
	{
		os << gps.longitude << " " << gps.latitude << " " << gps.height;
		return os;
	}
	friend std::istream& operator>> (std::istream &is, GPS &gps)
	{
		is >> gps.longitude >> gps.latitude >> gps.height;
		return is;
	}

private:

};

#endif // _DATASTRUCT_H__
