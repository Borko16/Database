#pragma once
#include <vector>
#include <string>
#include "../Table/Table.h"

class Database
{
public:
    Database(const std::string& name);
    void addColumn(const std::string& table, const std::string& column, const std::string& type);
    void addTable(const std::string& table);
private:
    std::vector<Table> tables;
    std::string name;
};