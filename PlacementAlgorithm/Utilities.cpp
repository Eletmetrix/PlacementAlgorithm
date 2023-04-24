#include "Utilities.h"

#include <cmath>

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
        return CastedArea->GetHeight();
    }

    return 0;
}

uint16_t CalculatedArea::GetAreaWidth() const
{
    if (!IsThereAnyArea())
    {
        return 0;
    }

    return this->at(0)->GetWidth();
}

bool CalculatedArea::IsThereAnyArea() const
{
    PreservedArea* CastedArea = dynamic_cast<PreservedArea*>(this->back());
    if (CastedArea != nullptr)
    {
        return CastedArea->GetHeight() < totalHeight;
    }

    return true;
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

Rectangle CalculatedAreaList::GetPlacedArea() const
{
    uint16_t width = 0, height = 0;
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        if (it->IsThereAnyArea())
        {
            width += it->GetAreaWidth();
        }

        height = fmax(totalHeight - it->GetPreservedAreaHeight(), height);
    }

    return Rectangle(width, height);
}

void Rectangle::CalculatePossibilities(std::vector<Rectangle*> const AllAreas)
{
    for (auto Area : AllAreas)
    {
        if (Area->toString() == this->toString())
        {
            continue;
        }

        uint16_t areaHeight = Area->GetHeight();
        uint16_t areaWidth = Area->GetWidth();

        if (areaHeight == height || areaWidth == width || areaWidth == height || areaHeight == width)
        {
            Possibilities.push_back(Area);
        }
    }
}

uint16_t Rectangle::GetHeight() const
{
    return height;
}

uint16_t Rectangle::GetWidth() const
{
    return width;
}

uint32_t Rectangle::GetArea() const
{
    return height * width;
}

std::vector<Rectangle*> Rectangle::GetPossibilities() const
{
    return Possibilities;
}

std::string Rectangle::toString() const
{
    return std::to_string(width) + "x" + std::to_string(height);
}

std::vector<Rectangle*> RectanglesList::GetRectangleList() const
{
    std::vector<Rectangle*> List;
    for (auto it = begin(); it != end(); ++it)
    {
        List.push_back(it->GetRectangle());
    }

    return List;
}

void PreservedArea::NewHeight(uint16_t newHeight)
{
    height = newHeight;
}
