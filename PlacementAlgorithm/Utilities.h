#pragma once

#include <iostream>
#include <string>
#include <vector>

class Rectangle
{
public:
    Rectangle(uint16_t X, uint16_t Y)
        : width(X), height(Y)
    { }

    void CalculatePossibilities(std::vector<Rectangle*>& AllAreas);

    virtual uint16_t GetWidth() const;
    virtual uint16_t GetHeight() const;
    virtual uint32_t GetArea() const;
    virtual std::vector<Rectangle*> GetPossibilities() const;
    virtual std::string toString() const;

protected:
    uint16_t height;
    uint16_t width;

    std::vector<Rectangle*> Possibilities;
};

struct SortAreasDescending
{
    bool operator()(Rectangle* const a, Rectangle* const b) const
    {
        return a->GetArea() > b->GetArea();
    }
};

class PreservedArea : public Rectangle
{
public:
    PreservedArea(uint16_t Height)
        : Rectangle(0, Height)
    { }

    virtual void NewHeight(uint16_t newHeight);
};

class CalculatedArea : public std::vector<Rectangle*>
{
public:
    CalculatedArea(uint8_t col_count, uint16_t TotalWidth);

    virtual uint16_t GetPreservedAreaHeight() const;
    virtual uint16_t GetAreaWidth() const;
    virtual bool IsThereAnyArea() const;

private:
    uint16_t totalHeight;
};

class CalculatedAreaList : public std::vector<CalculatedArea>
{
public:
    CalculatedAreaList(uint8_t row_count, uint8_t col_count, uint16_t TotalWidth, uint16_t TotalHeight)
        : std::vector<CalculatedArea>(row_count, CalculatedArea(col_count, TotalHeight))
        , totalWidth(TotalWidth)
        , totalHeight(TotalHeight)
    { }

    virtual uint32_t GetArea() const;
    virtual uint16_t GetPreservedAreaHeightAtCol(uint8_t col) const;
    virtual Rectangle GetPlacedArea() const;

private:
    uint16_t totalWidth;
    uint16_t totalHeight;
};

