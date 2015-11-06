#import <cmath>
#import "mathHelper.hpp"

double radian(double n){
	return n * (pi / 180);
}

double absVal(double n){
	return std::abs(n);
}

double squared(double n){
	return std::pow(n, 2);
}
