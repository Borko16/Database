#include "SelectCommand.h"

SelectCommand::SelectCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void SelectCommand::execute()
{
}
