#import <iostream>
#import <string>
#import "listHelper.hpp"

void fillIntList(int len, int* array){
	for (int i=0; i < len; i++){
		std::cin >> array[i];
		std::cin.ignore(1);
	}
}

void fillStrList(int len, std::string* array){
	std::getline(std::cin, array[0]);
	for (int i=0; i < len; i++){
		std::getline(std::cin, array[i]);
	}
}
