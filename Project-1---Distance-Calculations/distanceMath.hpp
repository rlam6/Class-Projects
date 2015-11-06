#ifndef DISTANCE_MATH_HPP
#define DISTANCE_MATH_HPP

double SignLat(std::string direction, double lat);

double SignLong(std::string direction, double lon);

double dLatLong(double latLong1, double latLong2);

double haverSineA(double lat1, double lat2, 
						double long1, double long2);

double haverSineC(double a);

double distance(double lat1, double lat2,
				double long1, double long2);

#endif //DISTANCE_MATH_HPP
