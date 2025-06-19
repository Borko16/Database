#include "CreateTableCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>


CreateTableCommand::CreateTableCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CreateTableCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	database->createTable(args[0]);
	{
		std::cout << "Table was not created\n";
		return;
	}
	std::cout << "Table was created\n";

}
