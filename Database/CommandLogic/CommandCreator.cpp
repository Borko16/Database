#include "CommandCreator.h"
#include "../Database/Database.h"
#include "Commands/BaseCommand.h"
#include "Commands/CreateDBCommand.h"
#include "Commands/OpenCommand.h"
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
#include "../Utils/StringUtils.h"

BaseCommand* CommandCreator::create(Database*& database, DatabaseMemento*& memento,
	std::string& filePath, bool& hasUnsavedChanges, const std::string& commandName, std::vector<std::string>& args) const
{

	BaseCommand* result = nullptr;
	const std::string name = toLowerString(commandName);
	if (name == "close")
	{
		result = new CloseCommand(database, filePath, hasUnsavedChanges, args);
	}
	else if (name == "help")
	{
		result = new HelpCommand(database, args);
	}
	else if (name == "create")
	{
		if (toLowerString(args[0]) == "database")
		{
			args.erase(args.begin());
			result = new CreateDBCommand(database, hasUnsavedChanges, args);
		}
		else if(toLowerString(args[0]) == "table")
		{
			args.erase(args.begin());
			result = new CreateTableCommand(database, hasUnsavedChanges,args);
		}
	}
	else if (name == "save")
	{
		if(args.size() > 0 && toLowerString(args[0]) == "as")
		{
			std::string first = args.front();
			args.erase(args.begin());
			result = new SaveAsCommand(database, memento, filePath, hasUnsavedChanges, args);
		}

		result = new SaveCommand(database, memento, filePath, hasUnsavedChanges, args);
	}
	else if (name == "showtables")
	{
		result = new ShowtablesCommand(database, args);
	}
	else if (name == "describe")
	{
		result = new DescribeCommand(database, args);
	}
	else if (name == "print")
	{
		result = new PrintCommand(database, args);
	}
	else if (name == "export")
	{
		result = new ExportCommand(database, args);
	}
	else if (name == "select")
	{
		result = new SelectCommand(database, args);
	}
	else if (name == "modify")
	{
		result = new ModifyCommand(database, hasUnsavedChanges, args);
	}
	else if (name == "addcolumn")
	{
		result = new AddColumnCommand(database, hasUnsavedChanges,args);
	}
	else if (name == "update")
	{
		result = new UpdateCommand(database, hasUnsavedChanges,args);
	}
	else if (name == "delete")
	{
		result = new DeleteCommand(database, hasUnsavedChanges, args);
	}
	else if (name == "insert")
	{
		result = new InsertCommand(database, hasUnsavedChanges,args);
	}
	else if (name == "open")
	{
		result = new OpenCommand(database, memento, filePath, hasUnsavedChanges, args);
	}
	else
	{
		return nullptr;
	}

	return result;
}
