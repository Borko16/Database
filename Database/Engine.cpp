#include "Engine.h"
#include "Database.h"
#include "DatabaseMemento.h"
#include <iostream>
#include "CommandLogic/CommandCreator.h"
#include "CommandLogic/Commands/BaseCommand.h"

char toUpper(char elem)
{
	int diff = 'a' - 'A';
	if ('A' <= elem && elem <= 'Z')
	{
		return elem + diff;
	}
	return elem;
}

bool isDelimiter(char elem)
{
	std::vector<char> tokenDelimiters = { ' ', '\t', '\n', '\r', '\f', '\v' };
	for (size_t i = 0; i < tokenDelimiters.size(); i++)
	{
		if (elem == tokenDelimiters[i])
		{
			return true;
		}
	}

	return false;
}

std::vector<std::string> splitWords(std::string& command)
{
	std::vector<std::string> result;
	std::string current;

	for (size_t i = 0; i < command.length(); i++)
	{
		if (!isDelimiter(command[i]))
		{
			current += toUpper(command[i]);
		}
		else
		{
			if (!current.empty())
			{
				result.push_back(current);
				current.clear();
			}
		}
	}

	if (!isDelimiter(command[command.length() - 1]))
	{
		result.push_back(current);
	}
	

	return result;
}

void Engine::processCommand(std::vector<std::string>& commandArgs)
{
	if (commandArgs.empty())
	{
		return;
	}

	std::string first = commandArgs.front();
	commandArgs.erase(commandArgs.begin());

	CommandCreator factory;

	BaseCommand* command = factory.create(currentDatabase, first, commandArgs);

	if (!command)
	{
		std::cout << "\n[ERROR] Unknown command or invalid arguments.\n";
		return;
	}

	command->execute();
}

Engine& Engine::getInstance()
{
	static Engine engine;
	return engine;
}
void Engine::run()
{
	std::cout << "Welcome to dbProject\n";
	std::cout << "Type 'help' for available commands.\n";
	std::cout << ">";
	std::string input;
	std::getline(std::cin, input, ';');

	while (input != "exit")
	{
		std::vector<std::string> command = splitWords(input);
		processCommand(command);


		std::getline(std::cin, input, ';');
	}

}

Engine::~Engine()
{
	delete currentDatabase;
	delete lastSaved;
}
