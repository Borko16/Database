#include "SaveAsCommand.h"
#include "../../Memento/DatabaseMemento.h"
#include "../../Utils/StringUtils.h"

SaveAsCommand::SaveAsCommand(Database*& database,DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void SaveAsCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string newFilePath = args[0];
	if (database->saveToFile(newFilePath))
	{
		delete memento;
		memento = new DatabaseMemento(*database);

		hasUnsavedChanges = false;
	}
}