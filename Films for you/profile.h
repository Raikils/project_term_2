#ifndef PROFILE_H
#define PROFILE_H

#include <map>
#include <string>
#include <vector>
#include <QDataStream>
#include <iostream>
#include "rapidjson-master/include/rapidjson/document.h"
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"
#include <stdlib.h>
#include <string>
#include <curl/curl.h>
#include "film.h"

/*!
 * \brief The Profile class
 * This class is user`s profile. It contains user`s preferences
 */
class Profile
{
private:
    std::map<std::string, double> _genre;
    std::string buffer;
    std::string _name;
    std::string key_rapid_api;
    std::vector<std::string> _liked_films;
    void change_weight(std::map<std::string, double>& characteristic, std::vector<std::string> key, double delta);

    std::map<std::string, int> recommendation_genre(int number_of_films);
    std::vector<std::string> more_like_leked(int number_of_films);
    static size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream);
public:
    /*!
     * Basic constructor of class. Sets standart preferences
     */
    Profile();
    /*!
     * Changes user`s parameters acording to given film
     */
    void like(Film film);
    /*!
     * Changes user`s parameters acording to given film
     */
    void dislike(Film film);
    /*!
     * Looks for number of films for given genre
     */
    std::vector<std::string> search_films(int n, std::string genre);
    /*!
     * Returns genres weight
     */
    std::map<std::string, double> genre() const;
    /*!
     * Sets genres weight
     */
    void set_genre(const std::map<std::string, double>& value);
    /*!
     * Returns list of films acording to user`s preferences
     */
    std::vector<std::string> recommendation();
    /*!
     * Returns name of profile
     */
    std::string name() const;
    /*!
     * Sets name of profile
     */
    void setName(const std::string &name);
    /*!
     * Returns list of liked films
     */
    std::vector<std::string> liked_films() const;
    /*!
     * Sets list of liked films
     */
    void setLiked_films(const std::vector<std::string> &liked_films);
};
/*!
 * Overloaded operator to write in file
 */
QDataStream &operator<<(QDataStream &out, const Profile &profile);
/*!
 * Overloaded operator to read from file
 */
QDataStream &operator>>(QDataStream &in, Profile &profile);

#endif // PROFILE_H
