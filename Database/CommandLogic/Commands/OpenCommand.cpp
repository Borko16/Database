#include "OpenCommand.h"

OpenCommand::OpenCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void OpenCommand::execute()
{
}
