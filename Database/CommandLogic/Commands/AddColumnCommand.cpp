#include "AddColumnCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>

AddColumnCommand::AddColumnCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3)
{
}

void AddColumnCommand::execute()
{
	if (!database)
	{
		throw std::logic_error("addColumnComand execute database is nullptr");
	}

	const std::string table = args[0];
	const std::string column = args[1];
	const std::string type = args[2];
	database->addColumn(table, column, type);
}

AddColumnCommand::operator bool() const
{
	return true;
}
