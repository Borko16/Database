#include "CreateTableCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>


CreateTableCommand::CreateTableCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CreateTableCommand::execute()
{
	if (!validateDatabase()) return;

	if (database->createTable(args[0]))
	{
		hasUnsavedChanges = true;
	}
}
