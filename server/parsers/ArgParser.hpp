#include <iostream>
#include <string>

class ArgParser
{
public:
	static int parseArguments(int argc, char** argv, int& port);
private:
	static void changePort(int& oldPort, char* newPort)
	{
		oldPort = std::stoi(newPort);
	}
	static void printHelp()
	{
		std::cout << "Usage: minesync_server.exe [options] <arguments>\n"
			<< "Options:\n"
			<< "  -h, --help\t\tDisplay this help message\n"
			<< "  -P, --port\t\tSpecify server Port number\n\n";
	}
};