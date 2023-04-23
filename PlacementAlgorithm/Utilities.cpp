#include "Utilities.h"

CalculatedArea::CalculatedArea(uint8_t col_count, uint16_t TotalHeight)
    : std::vector<Rectangle*>(col_count)
    , totalHeight(TotalHeight)
{
    for (int j = 0; j < col_count; ++j)
    {
        if (j == col_count - 1)
        {
            this->at(j) = new PreservedArea(TotalHeight);
            continue;
        }

        this->at(j) = new Rectangle(0, 0);
    }
}

uint16_t CalculatedArea::GetPreservedAreaHeight() const
{
    PreservedArea* CastedArea = dynamic_cast<PreservedArea*>(this->back());
    if (CastedArea != nullptr)
    {
        return CastedArea->GetLength();
    }

    return 0;
}

uint32_t CalculatedAreaList::GetArea() const
{
    return totalWidth * totalHeight;
}

uint16_t CalculatedAreaList::GetPreservedAreaHeightAtCol(uint8_t col) const
{
    if (col > this->size() - 1)
    {
        return 0;
    }

    return this->at(col).GetPreservedAreaHeight();
}

void Rectangle::CalculatePossibilities(std::vector<Rectangle*>& AllAreas)
{
    for (auto Area : AllAreas)
    {
        if (Area->toString() == this->toString())
        {
            continue;
        }

        uint16_t areaLength1 = Area->GetLength(false);
        uint16_t areaLength2 = Area->GetLength(true);

        if (areaLength1 == length1 || areaLength2 == length2 || areaLength1 == length2 || areaLength2 == length1)
        {
            Possibilities.push_back(Area);
        }
    }
}

uint16_t Rectangle::GetLength(const bool FirstOne) const
{
    return FirstOne ? length1 : length2;
}

uint32_t Rectangle::GetArea() const
{
    return length1 * length2;
}

std::vector<Rectangle*> Rectangle::GetPossibilities() const
{
    return Possibilities;
}

std::string Rectangle::toString() const
{
    return std::to_string(length1) + "x" + std::to_string(length2);
}

uint16_t PreservedArea::GetLength(const bool FirstOne) const
{
    return height;
}

void PreservedArea::NewHeight(uint16_t newHeight)
{
    height = newHeight;
}