#include "CommandCreator.h"
#include "../Database.h"
#include "Commands/BaseCommand.h"
#include "Commands/CreateCommand.h"
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

BaseCommand* CommandCreator::create(Database* database, const std::string& commandName, const std::vector<std::string>& args) const
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
        result = new CreateCommand(database, args);
    }
    else if (commandName == "save")
    {
        result = new SaveCommand(database, args);
    }
    else if (commandName == "save as")
    {
        result = new SaveAsCommand(database, args);
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
