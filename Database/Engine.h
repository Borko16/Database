#pragma once
#include <string>
#include <vector>
class Database;
class DatabaseMemento;

class Engine
{
public:
	static Engine& getInstance();
	void run();

	void processCommand(std::vector<std::string>& commandArgs);
private:
	Engine() = default;
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;


	Database* currentDatabase = nullptr;
	DatabaseMemento* lastSaved = nullptr;
	std::string currentFilePath;
	bool hasUnsavedChanges = false;
};