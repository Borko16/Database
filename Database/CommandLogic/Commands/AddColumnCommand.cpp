#include "AddColumnCommand.h"
AddColumnCommand::AddColumnCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void AddColumnCommand::execute()
{
}
