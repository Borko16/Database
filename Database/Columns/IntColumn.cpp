#include "IntColumn.h"

#include <stdexcept>
void IntColumn::resize(size_t newSize)
{
    if (isNULL.size() < newSize) // �������� � �� �� �������� �� insert, ��� ��, �� � �����
    {
        size_t oldSize = isNULL.size();
        values.resize(newSize);
        isNULL.resize(newSize);

        for (size_t i = oldSize - 1; i < isNULL.size(); i++) // ��� size � ����. �� ������� ���� ������ �����
        {
            setNull(i);
            isNULL[i] = true;
            return;
        }

        
    }

    //throw std::logic_error("int column resize"); // ���� � ���� ������ �� ����, ���� �� �� �������� � ���� throw

}

size_t IntColumn::getSize() const
{
    return values.size();
}

void IntColumn::setNull(size_t index)
{
    values[index] = 0;
}
