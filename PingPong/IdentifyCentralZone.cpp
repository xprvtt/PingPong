#include "main.h"


vector<bool> IdentifyCentralZone(unsigned int CountCell)
{
    vector<bool> result;

    // центральная зона
    const int CENTER_ZONE = CountCell / 2;
    int CorrectCount = 0;
    int CorrectCount2 = 0;

    for (int row = 0; row < CountCell; row++)
    {
        for (int coll = 0; coll < CountCell; coll++)
        {

            if (CorrectCount > 0)
            {
                result.push_back(true);
                CorrectCount--;
            }

            // первый и последний столбец и строка всегда будут белыми
            else if (row == 0 || coll == 0 || row == CountCell - 1 || coll == CountCell - 1)
            {
                result.push_back(false);
                CorrectCount = 0;
            }

            else
            {
                if (row <= CENTER_ZONE && coll == CountCell - CENTER_ZONE - row)
                {
                    result.push_back(true);
                    CorrectCount = row * 2 - 2;
                }
                else if (row > CENTER_ZONE && coll == row + 1 - CENTER_ZONE)
                {
                    result.push_back(true);
                    CorrectCount = CountCell - 4 - 1 - CorrectCount2;
                    CorrectCount2+=2;
                }
                else
                {
                    result.push_back(false);
                    CorrectCount = 0;
                }
            }
        }
    }

    return result;
}