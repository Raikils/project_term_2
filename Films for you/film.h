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
    void set_title_img_by_id(std::string id);
public:
    Film();
    Film(std::string id);
    std::string title() const;
    void setTitle(const std::string &title);
    std::string id() const;
    void setId(const std::string &id);
    std::string main_picture() const;
    void setMain_picture(const std::string &main_picture);
    std::vector<std::string> genre() const;
    void setGenre(const std::vector<std::string> &genre);
    std::vector<std::string> country() const;
    void setCountry(const std::vector<std::string> &country);
    std::vector<std::string> director() const;
    void setDirector(const std::vector<std::string> &director);
    std::vector<std::string> actors() const;
    void setActors(const std::vector<std::string> &actors);
    std::string getKey_rapid_api() const;
    void setKey_rapid_api(const std::string &value);

    void print_ui(QWidget* widget);
};

#endif // FILM_H
