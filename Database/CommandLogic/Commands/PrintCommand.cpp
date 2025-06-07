#include "PrintCommand.h"

PrintCommand::PrintCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2)
{
}

void PrintCommand::execute()
{
}
