#include "ArgParser.hpp"

int ArgParser::parseArguments(int argc, char** argv, int& port)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--help" || arg == "-h")
		{
			printHelp();
			return 2; // exit program after showing -h
		}

		try
		{
			if (arg == "--port" || arg == "-P")
			{
				if (i + 1 >= argc)
				{
					throw std::invalid_argument("Port requires a value.");
				}
				changePort(port, argv[++i]);
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << "Error: port must be a valid number\n";
			return 1; // exit program due to errors
		}
	}
	return 0; // continue executing program
}
