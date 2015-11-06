#import <cmath>
#import <string>
#import "distanceMath.hpp"
#import "mathHelper.hpp"

const double earthRadius = 3959.9;

double SignLat(std::string direction, double lat){
	if(direction == "/S" or direction == "/s"){
		return -lat;
	}
	return lat;
}

double SignLong(std::string direction, double lon){
	if(direction == "/W" or direction == "/w"){
		return -lon;
	}
	return lon;
}

double dLatLong(double latLong1, double latLong2){
	return latLong2 - latLong1;
}

double haverSineA(double lat1, double lat2, 
						double long1, double long2){
	double dlat = dLatLong(lat1, lat2);
	double dlong = dLatLong(long1, long2);

	return std::pow(std::sin(dlat/2), 2) + std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlong/2), 2);;
}

double haverSineC(double lat1, double lat2,
					double long1, double long2){
	double a = haverSineA(lat1, lat2, long1, long2);

	return 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
}

double distance(double lat1, double lat2,
				double long1, double long2){
	double c = haverSineC(radian(lat1), radian(lat2), radian(long1), radian(long2));

	return earthRadius * c;
}
