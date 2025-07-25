#include "PrintCommand.h"

PrintCommand::PrintCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2)
{
}

void PrintCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string table = args[0];
	size_t rowsPerPage = stoi(args[1]);
	database->print(table, rowsPerPage);
}
