#pragma once
#include <iostream>

inline void notFound(const std::string& type, std::ostream& os = std::cout)
{
	os << type << " not found\n";
}

inline void unknownColumnType(std::ostream& os = std::cout)
{
	os << "Unknown column type";
}

inline void invalidValueCount(std::ostream& os = std::cout)
{
	os << "Invalid value count";
}

inline void invalidValue(std::ostream& os = std::cout)
{
	os << "Invalid value";
}