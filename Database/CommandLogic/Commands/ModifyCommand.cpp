#include "ModifyCommand.h"

ModifyCommand::ModifyCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void ModifyCommand::execute()
{
}

ModifyCommand::operator bool() const
{
	return true;
}
