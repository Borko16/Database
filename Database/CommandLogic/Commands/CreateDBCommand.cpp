#include "CreateDBCommand.h"
#include "../../Database/Database.h"
#include <iostream> // временно
CreateDBCommand::CreateDBCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void CreateDBCommand::execute() // в момента прав€ само една база с една таблица. ј би тр€бвало да мога да прав€ повече от една таблици
{
	if (!database)
	{

		database = new Database(args[0]);
		std::cout << "successfully created\n";
	}
}
