#include "CreateTableCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>

CreateTableCommand::CreateTableCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void CreateTableCommand::execute()
{
	if (!database)
	{
		throw std::logic_error("createTableCommand execute database is nullptr");
	}

	database->addTable(args[0]);
	
}
