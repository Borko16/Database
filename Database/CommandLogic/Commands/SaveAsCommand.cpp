#include "SaveAsCommand.h"
#include "../../Memento/DatabaseMemento.h"

SaveAsCommand::SaveAsCommand(Database*& database,DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void SaveAsCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	const std::string newFilePath = args[0];
	database->saveToFile(newFilePath);
	{
		std::cout << "The file could not be saved.";
		return;
	}

	delete memento;
	memento = new DatabaseMemento(*database);

	hasUnsavedChanges = false;
	std::cout << "Successfully saved file: " << filePath << "\n";
}