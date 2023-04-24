
#include "Utilities.h"
#include <algorithm>


static uint8_t minEdgeWidth = 10;
static uint8_t minEdgeHeight = 6;

static uint8_t bigAreaWidth = 350;
static uint8_t bigAreaHeight = 250;

int main()
{
    std::vector<Rectangle*> Areas;
    Areas.push_back(new Rectangle(30, 20));
    Areas.push_back(new Rectangle(60, 30));
    Areas.push_back(new Rectangle(45, 20));

    CalculatedAreaList calculatedArea(minEdgeWidth - 1, minEdgeHeight - 1, bigAreaWidth, bigAreaHeight);

    {
        uint32_t SmallAreasTotalSize = 0;

        for (auto Area : Areas)
        {
            SmallAreasTotalSize += Area->GetArea();
            if (SmallAreasTotalSize > calculatedArea.GetArea())
            {
                std::cout << "Big area size is smaller than total small area sizes. This is not allowed!" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    std::sort(Areas.begin(), Areas.end(), SortAreasDescending());

    for (auto Area : Areas)
    {
        Area->CalculatePossibilities(Areas);
    }

    std::cout << calculatedArea.GetPlacedArea().toString();
}
