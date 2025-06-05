#include "ExportCommand.h"

ExportCommand::ExportCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2)
{
}

void ExportCommand::execute()
{
}
