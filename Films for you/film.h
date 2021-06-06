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
    std::vector<std::string> _country;
    std::vector<std::string> _director;
    std::vector<std::string> _actors;
    std::string key_rapid_api;
    static size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream);
    void curl_set_options(CURL *curl);
    std::vector<std::string> get_genre_by_id(std::string id);
    std::vector<std::string> get_director_by_id(std::string id);
    std::vector<std::string> get_actors_by_title(std::string title);
    std::string get_description_by_id(std::string id);
    void set_title_img_by_id(std::string id);
public:
    Film();
    Film(std::string id);
    std::string title() const;
    std::string id() const;
    void setId(const std::string &id);
    std::string main_picture() const;
    std::vector<std::string> genre() const;
    std::vector<std::string> country() const;
    std::vector<std::string> director() const;
    std::vector<std::string> actors() const;
    std::string getKey_rapid_api() const;
    void setKey_rapid_api(const std::string &value);
    std::string getDescription() const;
};

#endif // FILM_H
