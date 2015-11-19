#ifndef APP_HPP
#define APP_HPP

#include "HashMap.hpp"

class Application
{
public:
	// MAIN FUNCTIONS

	Application();

	void manageCommands();

	void start();

	// DISPLAYERS

	void printRawDB() const;

	void displayInvalid() const;

	// MAIN COMMAND HELPERS

	void createAccount(std::string parameters);

	void testLogin(std::string parameters);

	void removeUser(std::string parameters);

	void clear(std::string parameters);

	// DEBUG COMMAND HELPERS

	void debugRun(std::string parameters);

	void debugBucket(std::string parameters) const;

	void debugLoadFactor(std::string parameters) const;

	void debugMaxBucket(std::string parameters) const;

private:
	HashMap database;
	bool debug;
	std::string command;
};


#endif // APP_HPP
