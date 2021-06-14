#ifndef RAPIDAPIKEY_H
#define RAPIDAPIKEY_H
#include <string>
/*!
 * \brief The RapidAPIKey class
 * Class to get key for imdb api
 */
class RapidAPIKey
{
public:
    /*!
     * Basic constructor of class
     */
    RapidAPIKey();
    /*!
     * Returns key of imdb api
     */
    std::string get_key();
};

#endif // RAPIDAPIKEY_H
