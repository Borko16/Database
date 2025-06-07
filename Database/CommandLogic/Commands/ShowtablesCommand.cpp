#include "ShowtablesCommand.h"

ShowtablesCommand::ShowtablesCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void ShowtablesCommand::execute()
{
}
