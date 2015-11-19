#include <iostream>
#include <sstream>
#include "app.hpp"

namespace 
{
	std::string EMPTY = "";
}

// MAIN FUNCTIONS

Application::Application()
	: database{HashMap()}, debug{false}, command{""}
{
}

void Application::manageCommands(){
	// initialize all strings for command
	std::string entireCommand;	// entire line for command
	std::string mainCommand;	// main command (eg. first word of command)
	std::string parameters;		// following sub commands from main command
	std::stringstream ss;

	// set all strings to proper part of command
	std::getline(std::cin, entireCommand);
	ss << entireCommand;
	ss >> mainCommand;
	std::getline(ss, parameters);
	command = mainCommand;

	// handle all commands by the main command chosen, run with subcommands
	if(command == "CREATE"){
		createAccount(parameters);
	}
	else if (command == "LOGIN"){
		testLogin(parameters);
	}
	else if (command == "REMOVE"){
		removeUser(parameters);
	}
	else if (command == "PRINT"){
		printRawDB();
	}
	else if (command == "CLEAR"){
		clear(parameters);
	}
	else if (command == "DEBUG"){
		debugRun(parameters);
	}
	else if (command == "BUCKET"){
		debugBucket(parameters);
	}
	else if (command == "LOAD"){
		debugLoadFactor(parameters);
	}
	else if (command == "MAX"){
		debugMaxBucket(parameters);
	}
	else if (command == "QUIT"){
		return;
	}
	else{
		displayInvalid();	
	}
}

void Application::start(){
	// run application until user quits
	while (command != "QUIT"){
		manageCommands();
	}
	
	// closing goodbye output
	std::cout << "GOODBYE" << std::endl;
}

// DISPLAY FUNCTIONS

void Application::displayInvalid() const{
	std::cout << "INVALID" << std::endl;
}

void Application::printRawDB() const{
	if (debug){
		database.printAll();
	}
	else{
		displayInvalid();
	}
}

// COMMAND HELPER FUNCTIONS

void Application::createAccount(std:: string parameters){
	// initialize the username, password, and any extra subcommands input by user
	std::string newUsername, newPassword, extra;
	std::stringstream ss;
	ss << parameters; 
	ss >> newUsername >> newPassword >> extra;

	// Invalid if wrong input (eg. no username, password, or extra subcommands)
	if (newUsername == EMPTY or newPassword == EMPTY or extra != EMPTY){
		displayInvalid();
	} 
	else{
		if (not database.contains(newUsername)){
			std::cout << "CREATED" << std::endl;
			database.add(newUsername, newPassword);
		}
		else{
			std::cout << "EXISTS" << std::endl;
		}
	}
}

void Application::testLogin(std::string parameters){
	// initialize username, password to be tested, initialize extra information string
	std::string username, password, extra;
	std::stringstream ss;
	ss << parameters; 
	ss >> username >> password >> extra;

	// debug command for subcommand COUNT, gets size of database
	if (username == "COUNT" and debug and password == EMPTY and extra == EMPTY){
		std::cout << database.size() << std::endl;
		return;
	}

	// invalid if username or password is empty or extra subcommands present
	if (username == EMPTY or password == EMPTY or extra != EMPTY){
		displayInvalid();
	} 
	else{
		if (database.value(username) != password){
			std::cout << "FAILED" << std::endl;
		}
		else{
			std::cout << "SUCCEEDED" << std::endl;
		}
	}
}

void Application::removeUser(std::string parameters){
	// initialize username, any extra information
	std::string username, extra;
	std::stringstream ss;
	ss << parameters;
	ss >> username >> extra;

	// invalid if user name is empty or extra information is present
	if (username == EMPTY or extra != EMPTY){
		displayInvalid();
	}
	else if (not database.contains(username)){
		std::cout << "NONEXISTENT" << std::endl;
	}
	else {
		database.remove(username);
		std::cout << "REMOVED" << std::endl;
	}
}

void Application::clear(std::string parameters){
	// invalid if extra information present, should only be "CLEAR"
	if (parameters == EMPTY){
		database = HashMap();
		std::cout << "CLEARED" << std::endl;
	}
	else{
		displayInvalid();
	}
}

void Application::debugRun(std::string parameters){
	// initialize any erroneous extra information
	std::string status, extra;
	std::stringstream ss;
	ss << parameters;
	ss >> status >> extra;

	// invalid if extra info is present
	if (extra != EMPTY){
		displayInvalid();
		return;
	}

	// handle debug member variable by subcommand
	// ON -> true, OFF -> false
	if (status == "ON"){
		if (debug){
			std::cout << "ON ALREADY" << std::endl;
		}
		else{
			debug = true;
			std::cout << "ON NOW" << std::endl;
		}
	}
	else if (status == "OFF"){
		if (debug){
			debug = false;
			std::cout << "OFF NOW" << std::endl;
		}
		else{
			std::cout << "OFF ALREADY" << std::endl;
		}
	}
	else{
		displayInvalid();
	}
}

void Application::debugBucket(std::string parameters) const{
	// don't run if debug is off
	if (debug){
		// get amount of buckets from database
		std::string countStr, extra;
		std::stringstream ss;
		ss << parameters;
		ss >> countStr >> extra;

		if (countStr == "COUNT" and extra == EMPTY){
			std::cout << database.bucketCount() << std::endl;
		}
		else{
			displayInvalid();
		}
	}
	else {
		displayInvalid();
	}
}

void Application::debugLoadFactor(std::string parameters) const{
	// don't run if debug is off
	if (debug){
		// output load factor if input is correct
		std::string factor, extra;
		std::stringstream ss;
		ss << parameters;
		ss >> factor >> extra;

		if (factor == "FACTOR" and extra == EMPTY){
			std::cout << database.loadFactor() << std::endl;
		}
		else{
			displayInvalid();
		}
	}
	else {
		displayInvalid();
	}
}

void Application::debugMaxBucket(std::string parameters) const{
	// don't run if debug is off
	if (debug){
		// output max bucket size if input is correct
		std::string bucketStr, sizeStr, extra;
		std::stringstream ss;
		ss << parameters;
		ss >> bucketStr >> sizeStr >> extra;

		if (bucketStr == "BUCKET" and sizeStr == "SIZE" and extra == EMPTY){
			std::cout << database.maxBucketSize	() << std::endl;
		}
		else{
			displayInvalid();
		}
	}
	else {
		displayInvalid();
	}
}
