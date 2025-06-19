#pragma once
#include <vector>
#include <string>
#include "../Table/Table.h"

class Database
{
public:
    Database() = default;
    Database(const std::string& name);
    void addColumn(const std::string& table, const std::string& column, const std::string& type); // bool
    void createTable(const std::string& table); // bool
    void describe(const std::string& table);
    void deleteRows(const std::string& table, const std::string& column, const std::string& value);
    void exportTable(const std::string& table, const std::string& filePath);
    void insert(const std::string& table, const std::vector<std::string>& values);
    void modify(const std::string& table, const std::string& column, const std::string& type);
    void print(const std::string& table, size_t rowsPerPage);
    void select(const std::string& column, const std::string& value, const std::string& table);
    void showTables();
    void update(const std::string& table, const std::string& column, const std::string& value
                , const std::string& newColumn, const std::string& newValue);


    void saveToFile(const std::string& filePath);
    void loadFromFile(const std::string& filePath);

    const std::string& getName() const;
private:
    std::vector<Table> tables;
    std::string name;
};