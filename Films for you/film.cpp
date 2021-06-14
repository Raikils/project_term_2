#include "film.h"
#include "rapidjson-master/include/rapidjson/document.h"
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"
#include <QFile>
#include <QDebug>
#include "rapidapikey.h"



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
   get_info_by_id(id);
}

std::string Film::main_picture() const
{
    return _main_picture;
}

std::vector<std::string> Film::genre() const
{
    return _genre;
}

void Film::get_info_by_id(std::string id)
{
    qDebug() << QString::fromStdString(id);
    CURL* curl = curl_easy_init();
    std::string url = "https://imdb8.p.rapidapi.com/title/get-overview-details?tconst=" + id + "&currentCountry=US";
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& title_parse = doc["title"]["title"];
    rapidjson::Value& img = doc["title"]["image"]["url"];
    rapidjson::Value& genre_parse = doc["genres"];
    _title = title_parse.GetString();
    _main_picture = img.GetString();
    for (int i = 0; i < genre_parse.Size(); i++) {
        _genre.push_back(genre_parse[i].GetString());
    }
    if (doc.HasMember("plotSummary")) {
        _description = doc["plotSummary"]["text"].GetString();
    } else if (doc.HasMember("plotOutline")) {
        _description = doc["plotOutline"]["text"].GetString();
    } else _description = "";

    buffer.clear();
}

void Film::get_ratings_type_date(std::map<std::string, std::string> &result)
{
    CURL* curl = curl_easy_init();
    std::string url = "https://imdb8.p.rapidapi.com/title/get-overview-details?tconst=" + _id + "&currentCountry=US";
    curl_set_options(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    qDebug() << doc.IsObject();
    result["type"] = doc["title"]["titleType"].GetString();
    result["Date"] = doc["releaseDate"].GetString();
    if (doc["ratings"].HasMember("rating")) {
    result["Rating"] = std::to_string(doc["ratings"]["rating"].GetDouble());
    }
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

std::map<std::string, std::string> Film::get_full_info()
{
    std::map<std::string, std::string> result;
    std::string value;
    for (int i = 0; i < _genre.size(); i++) {
        if (i != _genre.size() - 1) value += _genre[i] + ", ";
        else value += _genre[i];
    }
    result["genre"] = value;

    get_ratings_type_date(result);

    result["src"] = "https://www.imdb.com/title/" + _id;

    result["Plot"] = _description;

    return result;
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
    RapidAPIKey key;
    key_rapid_api = key.get_key();
}

Film::Film(std::string id)
{
    RapidAPIKey key;
    key_rapid_api = key.get_key();
    _id = id;
    get_info_by_id(id);
}
