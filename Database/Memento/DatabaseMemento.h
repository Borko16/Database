#pragma once
class Database;

class DatabaseMemento
{
public:
	DatabaseMemento(const Database& db);
	~DatabaseMemento();
	Database* restore() const;
private:
	Database* snapshot;
};