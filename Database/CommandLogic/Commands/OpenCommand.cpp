#include "OpenCommand.h"
#include "../../Memento//DatabaseMemento.h"
#include <iostream>

OpenCommand::OpenCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges,const std::vector<std::string>& args)
	: BaseCommand(database, args, 1), memento(memento), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void OpenCommand::execute()
{
    if (database && hasUnsavedChanges)
    {
        std::cout << "Unsaved changes detected. Do you want to save them? (yes/no): ";
        std::string input;
        std::cin >> input;

        if (input == "yes")
        {
            database->saveToFile(filePath);
            {
                std::cout << "The file could not be saved.";
                return;
            }
            std::cout << "The file was saved.";
        }

        hasUnsavedChanges = false;
        delete database;
    }
    
    database = new Database();
    const std::string newFilePath = args[0];

    database->loadFromFile(newFilePath);
    {
        delete database;
        database = nullptr;
        std::cout << "File was not loaded";
    }

    filePath = newFilePath;

    delete memento;
    memento = new DatabaseMemento(*database);

    hasUnsavedChanges = false;

    std::cout << "Successfully opened file: " << filePath << "\n";
}
