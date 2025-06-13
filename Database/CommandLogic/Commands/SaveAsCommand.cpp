#include "SaveAsCommand.h"

SaveAsCommand::SaveAsCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void SaveAsCommand::execute()
{
}

SaveAsCommand::operator bool() const
{
	return true;
}

bool SaveAsCommand::requiresSnapshot() const
{
	return true;
}

bool SaveAsCommand::shouldAskToSave() const
{
	return true;
}
