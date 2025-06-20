#include "OpenCommand.h"
#include "../../Memento//DatabaseMemento.h"
#include "../../Utils/StringUtils.h"

OpenCommand::OpenCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges,const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void OpenCommand::execute()
{
    if (database && hasUnsavedChanges)
    {
        printUnsavedChanges();
        std::string input;
        std::cin >> input;

        if (toLowerString(input) == "yes")
        {
            if (database->saveToFile(filePath))
            {
                hasUnsavedChanges = false;
                delete database;
            }
            else
            {
                return;
            }
        }
    }
    
    database = new Database();
    const std::string newFilePath = args[0];

    if(!database->loadFromFile(newFilePath))
    {
        delete database;
        database = nullptr;
        return;
    }

    filePath = newFilePath;

    delete memento;
    memento = new DatabaseMemento(*database);

    hasUnsavedChanges = false;
}
