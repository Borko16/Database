#include "CreateDBCommand.h"
#include <iostream>

CreateDBCommand::CreateDBCommand(Database*& database, bool& hasUnsavedChanges,const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CreateDBCommand::execute()
{
	if (!database)
	{
		database = new Database(args[0]);
		std::cout << database->getName() << "was successfully created\n";
		hasUnsavedChanges = true;
		return;
	}

	std::cout << "You already have a database. You can't have a two or more at the same time\n";

}