#import <iostream>
#import <string>
#import "distanceMath.hpp"
#import "mathHelper.hpp"

int main(){
	// Initialize starting, closest, and farther location information variables
	double startLat; std::string startLatDirection;
	double startLong; std::string startLongDirection;
	std::string startLoc;

	double closestLat; std::string closestLatDirection;
	double closestLong; std::string closestLongDirection;
	std::string closestLoc;
	double closestDistance = -1;

	double farthestLat; std::string farthestLatDirection;
	double farthestLong; std::string farthestLongDirection;
	std::string farthestLoc;
	double farthestDistance = -1;

	// Initializes target locations variable
	int targetLocations;

	// Get user input for starting location
	std::cin >> startLat >> startLatDirection >>
	 startLong >> startLongDirection;
	std::cin.ignore(1);
	std::getline(std::cin, startLoc);

	// Fixes positive/negative sign of lat and long
	startLat = SignLat(startLatDirection, startLat);
	startLong = SignLong(startLongDirection, startLong);

	std::cin >> targetLocations;

	for (int i=0; i < targetLocations; i++){
		double currentLat; std::string currentLatDirection;
		double currentLong; std::string currentLongDirection;
		std::string currentLoc;
		double currentDistance;

		std::cin >> currentLat >> currentLatDirection >>
	 	currentLong >> currentLongDirection;
	 	std::cin.ignore(1);
		std::getline(std::cin, currentLoc);

		currentLat = SignLat(currentLatDirection, currentLat);
		currentLong = SignLong(currentLongDirection, currentLong);

		currentDistance = distance(startLat, currentLat, startLong, currentLong);

		if (closestDistance == -1 or closestDistance >= currentDistance){
			closestDistance = currentDistance;
			closestLat = currentLat; closestLatDirection = currentLatDirection;
			closestLong = currentLong; closestLongDirection = currentLongDirection;
			closestLoc = currentLoc;
		}

		if (farthestDistance == -1 or farthestDistance <= currentDistance){
			farthestDistance = currentDistance;
			farthestLat = currentLat; farthestLatDirection = currentLatDirection;
			farthestLong = currentLong; farthestLongDirection = currentLongDirection;
			farthestLoc = currentLoc;
		}
	}

	// Outputs starting, closest, and farthest locations information
	std::cout << "Start Location: " << absVal(startLat) << startLatDirection << " " <<
	absVal(startLong) << startLongDirection << " (" << startLoc << ")" << std::endl <<

	"Closest Location: " << absVal(closestLat) << closestLatDirection << " " <<
	absVal(closestLong) << closestLongDirection << " (" << closestLoc << ")" << 
	" (" << closestDistance << " miles)" << std::endl <<

	"Farthest Location: " << absVal(farthestLat) << farthestLatDirection << " " <<
	absVal(farthestLong) << farthestLongDirection << " (" << farthestLoc << ")" << 
	" (" << farthestDistance << " miles)" << std::endl;

    return 0;
}
