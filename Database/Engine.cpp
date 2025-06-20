#include "Engine.h"
#include "Database/Database.h"
#include "Memento/DatabaseMemento.h"
#include "CommandLogic/CommandCreator.h"
#include "CommandLogic/Commands/BaseCommand.h"
#include "Utils/StringUtils.h"

void Engine::processCommand(std::vector<std::string>& commandArgs)
{
	if (commandArgs.empty())
	{
		return;
	}

	std::string first = commandArgs.front();
	commandArgs.erase(commandArgs.begin());

	CommandCreator factory;
	try
	{
		BaseCommand* command = factory.create(currentDatabase, lastSaved, currentFilePath, hasUnsavedChanges, first, commandArgs);

		if (!command)
		{
			printMessage("\nUnknown command or invalid arguments.\n");
			return;
		}

		delete command;
	}
	catch (...)
	{
		printMessage("\nUnexpected failure.\n");
	}
}

Engine& Engine::getInstance()
{
	static Engine engine;
	return engine;
}

void Engine::run()
{
	printMessage("Welcome to dbProject\n");
	printMessage("Type 'help' for available commands.\n");
	printMessage(">");
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
