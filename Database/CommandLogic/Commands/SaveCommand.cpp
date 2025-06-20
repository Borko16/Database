#include "SaveCommand.h"
#include "../../Memento/DatabaseMemento.h"

SaveCommand::SaveCommand(Database*& database, DatabaseMemento*& memento, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void SaveCommand::execute()
{
	if (!validateDatabase()) return;

	if (database->saveToFile(filePath))
	{
		delete memento;
		memento = new DatabaseMemento(*database);

		hasUnsavedChanges = false;
	}
}