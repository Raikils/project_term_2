#include "randomgenerate.h"
#include <QRandomGenerator>

RandomGenerate::RandomGenerate()
{

}

int RandomGenerate::randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}
