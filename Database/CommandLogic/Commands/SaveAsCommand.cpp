#include "SaveAsCommand.h"

SaveAsCommand::SaveAsCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void SaveAsCommand::execute()
{
}
