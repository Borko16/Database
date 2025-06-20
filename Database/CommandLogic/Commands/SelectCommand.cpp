#include "SelectCommand.h"

SelectCommand::SelectCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void SelectCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string& column = args[0];
	const std::string& value = args[1];
	const std::string& table = args[2];
	database->select(column, value, table);
}
