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

using namespace rapidjson;
class Profile
{
private:
    std::map<std::string, double> _genre;
    std::string buffer;
    std::string _name;
    std::string key_rapid_api;
    std::vector<std::string> _liked_films;
    void change_weight(std::map<std::string, double>& characteristic, std::string key, double delta);
    static size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream);
public:
    Profile();
    std::vector<std::string> search_films(int n, std::string genre);
    void like(Film film);
    void dislike(Film film);
    std::map<std::string, double> genre() const;
    void set_genre(const std::map<std::string, double>& value);
    std::map<std::string, int> recommendation_genre();
    std::vector<std::string> recommendation();
    std::string name() const;
    void setName(const std::string &name);
    std::vector<std::string> liked_films() const;
    void setLiked_films(const std::vector<std::string> &liked_films);
};

QDataStream &operator<<(QDataStream &out, const Profile &profile);
QDataStream &operator>>(QDataStream &in, Profile &profile);

#endif // PROFILE_H
