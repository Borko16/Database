#include "IntColumn.h"

#include <stdexcept>
void IntColumn::resize(size_t newSize)
{
    if (isNULL.size() < newSize)
    {
        size_t oldSize = isNULL.size();
        values.resize(newSize);
        isNULL.resize(newSize);

        for (size_t i = oldSize - 1; i < isNULL.size(); i++)
        {
            setNull(i);
            isNULL[i] = true;
            return;
        }

        
    }
}

size_t IntColumn::getSize() const
{
    return values.size();
}

void IntColumn::setNull(size_t index)
{
    values[index] = 0;
}
