#include "ExportCommand.h"

ExportCommand::ExportCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2)
{
}

void ExportCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string table = args[0];
	const std::string filePath = args[1];
	database->exportTable(table, filePath);
}
