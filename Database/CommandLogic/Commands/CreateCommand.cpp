#include "CreateCommand.h"
#include "../../Database.h"
#include <iostream> // временно
CreateCommand::CreateCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void CreateCommand::execute()
{
	if (!database)
	{
		database = new Database();
		std::cout << "successfully created";
	}
}
