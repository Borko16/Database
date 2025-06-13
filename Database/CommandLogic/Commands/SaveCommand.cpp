#include "SaveCommand.h"

SaveCommand::SaveCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void SaveCommand::execute()
{
}

SaveCommand::operator bool() const
{
	return true;
}

bool SaveCommand::requiresSnapshot() const
{
	return true;
}
