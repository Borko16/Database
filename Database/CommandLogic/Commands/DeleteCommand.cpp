#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void DeleteCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	const std::string table = args[0];
	const std::string column = args[1];
	const std::string value = args[2];
	database->deleteRows(table, column, value);
}