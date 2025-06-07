#include "Table.h"
#include <stdexcept>
#include "../Columns/IntColumn.h"
#include "../Columns/StringColumn.h"
#include "../Columns/DoubleColumn.h"
#include "../Columns/DateColumn.h"

Table::Table(const std::string& name)
    : name(name)
{
}

void Table::addColumn(const std::string& column, const std::string& type)
{
    if (type == "int")
    {
        columns.push_back(new IntColumn(column, this));
        columns.back()->resize(columns.front()->getSize());
    }
    else if (type == "double")
    {

    }
    else if (type == "date")
    {

    }
    else if (type == "string")
    {

    }
    else
    {
        throw std::invalid_argument("table addColumn type");
    }
}

const std::string& Table::getName() const
{
    return name;
}
