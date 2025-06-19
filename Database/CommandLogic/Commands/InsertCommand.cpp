#include "InsertCommand.h"

InsertCommand::InsertCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2), hasUnsavedChanges(hasUnsavedChanges)
{
}

void InsertCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	const std::string table = args[0];
	args.erase(args.begin());

	database->insert(table, args);
	{
		std::cout << "Column was not added\n";
		return;
	}
	
	hasUnsavedChanges = true;
	std::cout << "Row was added\n";
}