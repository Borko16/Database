#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void DeleteCommand::execute()
{
}
