#include "SaveCommand.h"
#include "../../Memento/DatabaseMemento.h"

SaveCommand::SaveCommand(Database*& database, DatabaseMemento*& memento, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void SaveCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	database->saveToFile(filePath);
	{
		std::cout << "The file could not be saved.";
		return;
	}

	delete memento;
	memento = new DatabaseMemento(*database);

	hasUnsavedChanges = false;
	std::cout << "Successfully saved file: " << filePath << "\n";
}