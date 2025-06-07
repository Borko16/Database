#include "IntColumn.h"

#include <stdexcept>
void IntColumn::resize(size_t newSize)
{
    if (isNULL.size() < newSize) // възможно е да ми потрявба за insert, ако не, ще я махна
    {
        size_t oldSize = isNULL.size();
        values.resize(newSize);
        isNULL.resize(newSize);

        for (size_t i = oldSize - 1; i < isNULL.size(); i++) // ако size е нула. ДА ПРОВЕРЯ ТОЗИ СЛУЧАЙ ПОСЛЕ
        {
            setNull(i);
            isNULL[i] = true;
            return;
        }

        
    }

    //throw std::logic_error("int column resize"); // това е само докато го пиша, няма да го предавам с този throw

}

size_t IntColumn::getSize() const
{
    return values.size();
}

void IntColumn::setNull(size_t index)
{
    values[index] = 0;
}
