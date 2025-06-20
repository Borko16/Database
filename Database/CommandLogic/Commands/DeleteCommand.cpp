#include "DeleteCommand.h"
#include "../../Utils/StringUtils.h"

DeleteCommand::DeleteCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3), hasUnsavedChanges(hasUnsavedChanges)
{
}

void DeleteCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string table = args[0];
	const std::string column = args[1];
	const std::string value = args[2];
	if (database->deleteRows(table, column, value))
	{
		hasUnsavedChanges = true;
	}
}