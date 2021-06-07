#ifndef FILM_H
#define FILM_H
#include <QString>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <QWidget>

class Film
{
private:
    std::string _title;
    std::string _id;
    std::string _main_picture;
    std::string buffer;
    std::string _description;
    std::vector<std::string> _genre;
    std::string key_rapid_api;
    static size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream);
    void curl_set_options(CURL *curl);
    void get_info_by_id(std::string id);
public:
    Film();
    Film(std::string id);
    std::string title() const;
    std::string id() const;
    void setId(const std::string &id);
    std::string main_picture() const;
    std::vector<std::string> genre() const;
    std::string getKey_rapid_api() const;
    void setKey_rapid_api(const std::string &value);
    std::string getDescription() const;
};

#endif // FILM_H
