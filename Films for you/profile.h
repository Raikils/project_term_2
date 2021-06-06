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
    std::map<std::string, double> _country;
    std::map<std::string, double> _director;
    std::map<std::string, double> _actors;
    std::string curlBuffer;
    std::string buffer;
    std::string _name;
    void change_weight(std::map<std::string, double>& characteristic, std::string key, double delta);
    static size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream);
public:
    Profile();
    std::vector<std::string> search_films(int n, std::string genre);
    void like(Film film);
    void dislike(Film film);
    std::map<std::string, double> genre() const;
    std::map<std::string, double> country() const;
    std::map<std::string, double> director() const;
    std::map<std::string, double> actors() const;
    void set_genre(const std::map<std::string, double>& value);
    void set_country(const std::map<std::string, double>& value);
    void set_director(const std::map<std::string, double>& value);
    void set_actors(const std::map<std::string, double>& value);
    std::map<std::string, int> recommendation_genre();
    std::map<std::string, double> recommendation_country();
    std::map<std::string, double> recommendation_director();
    std::map<std::string, double> recommendation_actors();
    static size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer);
    std::map<std::string, int> count_of_films_by_genre();
    std::vector<std::string> recommendation();
    std::string name() const;
    void setName(const std::string &name);
};

QDataStream &operator<<(QDataStream &out, const Profile &profile);
QDataStream &operator>>(QDataStream &in, Profile &profile);

#endif // PROFILE_H
