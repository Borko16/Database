#include "CreateDBCommand.h"


CreateDBCommand::CreateDBCommand(Database*& database, bool& hasUnsavedChanges,const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CreateDBCommand::execute()
{
	if (!database)
	{
		database = new Database(args[0]);
		printCreatedDB(database->getName());
		hasUnsavedChanges = true;
		return;
	}

	printDBAlreadyOpen();
}