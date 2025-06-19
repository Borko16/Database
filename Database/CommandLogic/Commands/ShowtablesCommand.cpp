#include "ShowtablesCommand.h"

ShowtablesCommand::ShowtablesCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void ShowtablesCommand::execute()
{
	if (!database)
	{
		std::cout << "No database is open";
		return;
	}

	database->showTables();
}
