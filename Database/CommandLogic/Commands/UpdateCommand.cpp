#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 5)
{
}

void UpdateCommand::execute()
{
}
