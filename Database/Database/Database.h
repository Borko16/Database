#pragma once
#include <vector>
#include <string>
#include "../Table/Table.h"

class Database
{
public:
    Database() = default;
    Database(const std::string& name);
    size_t getTablesCount() const;
    bool addColumn(const std::string& table, const std::string& column, const std::string& type);
    bool createTable(const std::string& table);
    void describe(const std::string& table) const;
    bool deleteRows(const std::string& table, const std::string& column, const std::string& value);
    void exportTable(const std::string& table, const std::string& filePath) const;
    bool insert(const std::string& table, const std::vector<std::string>& values);
    bool modify(const std::string& table, const std::string& column, const std::string& type);
    void print(const std::string& table, size_t rowsPerPage) const;
    void select(const std::string& column, const std::string& value, const std::string& table) const;
    void showTables() const;
    bool update(const std::string& table, const std::string& column, const std::string& value
                , const std::string& newColumn, const std::string& newValue);
    bool saveToFile(const std::string& filePath) const;
    bool loadFromFile(const std::string& filePath);
    const std::string& getName() const;
private:
    const size_t findTableIndex(const std::string& table) const;
    bool ensureTablesExist() const;
    bool hasCorrectExtension(const std::string& filePath, const std::string& expectedExt = ".dbbg") const;
    void printTables() const;
    std::vector<Table> tables;
    std::string name;
};