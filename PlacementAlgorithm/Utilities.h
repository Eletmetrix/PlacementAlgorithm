#pragma once

#include <iostream>
#include <string>
#include <vector>

class Rectangle
{
public:
    Rectangle(uint16_t X, uint16_t Y)
        : length1(X), length2(Y)
    { }

    void CalculatePossibilities(std::vector<Rectangle*>& AllAreas);

    virtual uint16_t GetLength(const bool FirstOne) const;
    virtual uint32_t GetArea() const;
    virtual std::vector<Rectangle*> GetPossibilities() const;
    virtual std::string toString() const;

private:
    uint16_t length1;
    uint16_t length2;

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
        : height(Height)
        , Rectangle(0, Height)
    { }

    virtual uint16_t GetLength(const bool FirstOne = false) const override;
    virtual void NewHeight(uint16_t newHeight);

private:
    uint16_t height;
};

class CalculatedArea : public std::vector<Rectangle*>
{
public:
    CalculatedArea(uint8_t col_count, uint16_t TotalWidth);

    virtual uint16_t GetPreservedAreaHeight() const;

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

private:
    uint16_t totalWidth;
    uint16_t totalHeight;
};

