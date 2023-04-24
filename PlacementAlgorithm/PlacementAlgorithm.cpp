
#include "Utilities.h"
#include <algorithm>


static uint8_t minEdgeWidth = 10;
static uint8_t minEdgeHeight = 6;

static uint8_t bigAreaWidth = 350;
static uint8_t bigAreaHeight = 250;

int main()
{
    // Add new small areas to our list.
    RectanglesList Areas({
        AmountOfRectangle(10, new Rectangle(30, 20)),
        AmountOfRectangle(4, new Rectangle(60, 30)),
        AmountOfRectangle(6, new Rectangle(45, 20)),
    });

    // Create big area.
    CalculatedAreaList calculatedArea(minEdgeWidth - 1, minEdgeHeight - 1, bigAreaWidth, bigAreaHeight);

    // If big area is smaller than small areas total, don't continue
    // because all small areas can't fit in.
    {
        uint32_t SmallAreasTotalSize = 0;

        for (auto Area : Areas)
        {
            SmallAreasTotalSize += Area.GetRectangle()->GetArea();
            if (SmallAreasTotalSize > calculatedArea.GetArea())
            {
                std::cout << "Big area size is smaller than total small area sizes. This is not allowed!" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    // Sort small areas as descending.
    std::sort(Areas.begin(), Areas.end(), SortAreasDescending());

    // Calculate possibilities.
    for (auto& Area : Areas)
    {
        Area.GetRectangle()->CalculatePossibilities(Areas.GetRectangleList());
    }

    // Now let's start. Place first element from our list to area.
}
