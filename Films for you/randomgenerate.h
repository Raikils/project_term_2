#ifndef RANDOMGENERATE_H
#define RANDOMGENERATE_H

/*!
 * \brief The RandomGenerate class
 * Class to generate random numbers
 */
class RandomGenerate
{
public:
    /*!
     * Basic constructor of class
     */
    RandomGenerate();
    /*!
     * Returns random number in a given range
     */
    int randomBetween(int low, int high);
};

#endif // RANDOMGENERATE_H
