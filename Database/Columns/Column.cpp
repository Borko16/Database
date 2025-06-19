#include "Column.h"
#include "../Utils/PrintUtils.h"

size_t Column::getSize() const
{
    return isNULL.size();
}

void Column::saveNameAndSize(std::ostream& ofs) const
{
	size_t nameLen = name.size();
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
	ofs.write(name.c_str(), nameLen);

	size_t size = getSize();
	ofs.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
}

void Column::saveNullFlags(std::ostream& ofs) const
{
	for (size_t i = 0; i < getSize(); ++i)
	{
		bool isNull = isNULL[i];
		ofs.write(reinterpret_cast<const char*>(&isNull), sizeof(bool));
	}
}

void Column::loadNameAndSize(std::istream& ifs)
{
	size_t nameLen;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));

	std::string colName(nameLen, '\0');
	ifs.read(&colName[0], nameLen);
	name = colName;

	size_t size;
	ifs.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	
	resize(size);
}

void Column::loadNullFlags(std::istream& ifs)
{
	for (size_t i = 0; i < getSize(); ++i)
	{
		bool flag;
		ifs.read(reinterpret_cast<char*>(&flag), sizeof(bool));
		isNULL[i] = flag;
	}
}

bool Column::isStringNull(const std::string& str) const
{
	return str == "NULL";
}

bool Column::updateIfNull(size_t index, const std::string& newValue)
{
	if (isStringNull(newValue))
	{
		setNull(index);
		return true;
	}
	return false;
}

bool Column::isCellNull(size_t index) const
{
	return isNULL[index];
}
