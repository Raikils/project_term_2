#include "film.h"
#include "rapidjson-master/include/rapidjson/document.h"
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"
#include <QFile>
#include <QDebug>



std::string Film::title() const
{
    return _title;
}

std::string Film::id() const
{
    return _id;
}

void Film::setId(const std::string &id)
{
    _id = id;
}

std::string Film::main_picture() const
{
    return _main_picture;
}

std::vector<std::string> Film::genre() const
{
    return _genre;
}

std::vector<std::string> Film::country() const
{
    return _country;
}

std::vector<std::string> Film::director() const
{
    return _director;
}

std::vector<std::string> Film::actors() const
{
    return _actors;
}

std::vector<std::string> Film::get_genre_by_id(std::string id)
{
    std::vector<std::string> genres;
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-genres?tconst=" + id;
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& genre_array = doc;
    for (int i = 0; i < genre_array.Size(); i++) {
        genres.push_back(genre_array[i].GetString());
    }
    buffer.clear();
    return genres;
}

std::vector<std::string> Film::get_director_by_id(std::string id)
{
    std::vector<std::string> directors;
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-full-credits?tconst=" + id;
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& directors_parse = doc["crew"]["director"];
    for (int i = 0; i < directors_parse.Size(); i++) {
        directors.push_back(directors_parse[i]["name"].GetString());
    }
    buffer.clear();
    return directors;
}

std::vector<std::string> Film::get_actors_by_title(std::string title)
{
    std::vector<std::string> directors;
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-full-credits?tconst=" + title;
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
}

std::string Film::get_description_by_id(std::string id)
{
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-overview-details?tconst=" + id + "&currentCountry=US";
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& title_parse = doc["plotSummary"]["text"];
    buffer.clear();
    return title_parse.GetString();
}

void Film::set_title_img_by_id(std::string id)
{
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-details?tconst=" + id;
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& title_parse = doc["title"];
    rapidjson::Value& img = doc["image"]["url"];
    _title = title_parse.GetString();
    _main_picture = img.GetString();
    buffer.clear();
}

std::string Film::getKey_rapid_api() const
{
    return key_rapid_api;
}

void Film::setKey_rapid_api(const std::string &value)
{
    key_rapid_api = value;
}

std::string Film::getDescription() const
{
    return _description;
}

size_t Film::curl_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
    ((std::string*)stream)->append((char*)ptr, size*nmemb);
    return size*nmemb;
}

void Film::curl_set_options(CURL *curl)
{
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    struct curl_slist *headers = NULL;
    std::string key = "x-rapidapi-key: " + key_rapid_api;
    headers = curl_slist_append(headers, key.c_str());
    headers = curl_slist_append(headers, "x-rapidapi-host: imdb8.p.rapidapi.com");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
}

Film::Film(): _title(""), _id(""), _main_picture("")
{
    key_rapid_api = "c84a33e5ecmsh30280f927a53eecp11581ejsn7aeefb165750";
}

Film::Film(std::string id)
{
    key_rapid_api = "c84a33e5ecmsh30280f927a53eecp11581ejsn7aeefb165750";
    set_title_img_by_id(id);
    _genre = get_genre_by_id(id);
    _director = get_director_by_id(id);
    _description = get_description_by_id(id);
    _id = id;
}
