#include "CommandCreator.h"
#include "../Database/Database.h"
#include "Commands/BaseCommand.h"
#include "Commands/CreateDBCommand.h"
#include "Commands/CreateTableCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/CloseCommand.h"
#include "Commands/AddColumnCommand.h"
#include "Commands/DeleteCommand.h"
#include "Commands/DescribeCommand.h"
#include "Commands/ExportCommand.h"
#include "Commands/InsertCommand.h"
#include "Commands/ModifyCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SaveAsCommand.h"
#include "Commands/SaveCommand.h"
#include "Commands/SelectCommand.h"
#include "Commands/ShowtablesCommand.h"
#include "Commands/UpdateCommand.h"
BaseCommand* CommandCreator::create(Database*& database, const std::string& commandName, std::vector<std::string>& args) const
{

	BaseCommand* result = nullptr;
	if (commandName == "close")
	{
		result = new CloseCommand(database, args);
	}
	else if (commandName == "help")
	{
		result = new HelpCommand(database, args);
	}
	else if (commandName == "create")
	{
		if (args[0] == "database")
		{
			std::string first = args.front();
			args.erase(args.begin());
			result = new CreateDBCommand(database, args);
		}
		else if(args[0] == "table")
		{
			std::string first = args.front();
			args.erase(args.begin());
			result = new CreateTableCommand(database, args);
		}
	}
	else if (commandName == "save")
	{
		if(args.size() == 1)
		{
			std::string first = args.front();
			args.erase(args.begin());
			result = new SaveAsCommand(database, args);
		}

		result = new SaveCommand(database, args);
	}
	else if (commandName == "showtables")
	{
		result = new ShowtablesCommand(database, args);
	}
	else if (commandName == "describe")
	{
		result = new DescribeCommand(database, args);
	}
	else if (commandName == "print")
	{
		result = new PrintCommand(database, args);
	}
	else if (commandName == "export")
	{
		result = new ExportCommand(database, args);
	}
	else if (commandName == "select")
	{
		result = new SelectCommand(database, args);
	}
	else if (commandName == "modify")
	{
		result = new ModifyCommand(database, args);
	}
	else if (commandName == "addcolumn")
	{
		result = new AddColumnCommand(database, args);
	}
	else if (commandName == "update")
	{
		result = new UpdateCommand(database, args);
	}
	else if (commandName == "delete")
	{
		result = new DeleteCommand(database, args);
	}
	else if (commandName == "insert")
	{
		result = new InsertCommand(database, args);
	}
	else
	{
		return nullptr;
	}

	return result;
}
