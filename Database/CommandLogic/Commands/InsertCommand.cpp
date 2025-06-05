#include "InsertCommand.h"

InsertCommand::InsertCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2)
{
}

void InsertCommand::execute()
{
}
