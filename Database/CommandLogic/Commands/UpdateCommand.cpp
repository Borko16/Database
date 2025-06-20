#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 5), hasUnsavedChanges(hasUnsavedChanges)
{
}

void UpdateCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string& table = args[0];
	const std::string& column = args[1];
	const std::string& value = args[2];
	const std::string& newColumn = args[3];
	const std::string& newValue = args[4];

	database->update(table, column, value, newColumn, newValue);
	{
		hasUnsavedChanges = true;
	}
}