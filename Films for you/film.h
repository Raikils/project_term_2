#ifndef FILM_H
#define FILM_H
#include <QString>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <QWidget>
/*!
 * \brief The Film class
 * This class represents information about film.
 */
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
    void get_ratings_type_date(std::map<std::string, std::string>& result);
public:
    /*!
     * Basic constructor of class
     */
    Film();
    /*!
     * Class constructor has one parameter, id of film, whitch sets all other parameters using this id
     */
    Film(std::string id);
    /*!
     * Returns title of film
     */
    std::string title() const;
    /*!
     * Returns id of film
     */
    std::string id() const;
    /*!
     * Sets new id, all other parameters will be reassigned taking in acount new id
     */
    void setId(const std::string &id);
    /*!
     * Returns url of picture of film
     */
    std::string main_picture() const;
    /*!
     * Returns genres of film
     */
    std::vector<std::string> genre() const;
    /*!
     *  Returns key of imdb api
     */
    std::string getKey_rapid_api() const;
    /*!
     * Sets key of imdb api
     */
    void setKey_rapid_api(const std::string &value);
    /*!
     * Returns description of film
     */
    std::string getDescription() const;
    /*!
     * Return full information about film
     */
    std::map<std::string, std::string> get_full_info();
};

#endif // FILM_H
