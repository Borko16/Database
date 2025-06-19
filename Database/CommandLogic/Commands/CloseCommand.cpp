#include "CloseCommand.h"
#include <iostream>


CloseCommand::CloseCommand(Database*& database, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CloseCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open\n";
		return;
	}

	if (database && hasUnsavedChanges)
	{
		std::cout << "Unsaved changes detected. Do you want to save them? (yes/no): ";
		std::string input;
		std::cin >> input;

		if (input == "yes")
		{
			database->saveToFile(filePath);
			{
				std::cout << "The file could not be saved.";
				return;
			}
			std::cout << "The file was saved.";
		}

		hasUnsavedChanges = false;
	}

	std::cout << database->getName() << " was closed\n";

	delete database;
	database = nullptr;

}