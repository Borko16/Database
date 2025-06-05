#include "DatabaseMemento.h"
#include "Database.h"

DatabaseMemento::DatabaseMemento(const Database& db)
{
	snapshot = new Database(db);
}

DatabaseMemento::~DatabaseMemento()
{
	delete snapshot;
}

Database* DatabaseMemento::restore() const
{
	return snapshot;
}
