#include "AddColumnCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>

AddColumnCommand::AddColumnCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3), hasUnsavedChanges(hasUnsavedChanges)
{
}

void AddColumnCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	const std::string table = args[0];
	const std::string column = args[1];
	const std::string type = args[2];
	
	database->addColumn(table, column, type);
	{
		std::cout << "Column was not added\n";
		return;
	}

	hasUnsavedChanges = true;
	std::cout << "Column was added\n";
}
