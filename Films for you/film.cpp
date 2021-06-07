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
    if (doc["plotSummary"].IsObject()) {
        _description = doc["plotSummary"]["text"].GetString();
    } else {
        _description = doc["plotOutline"]["text"].GetString();
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
    key_rapid_api = "0085a34427mshc7f717b41100917p17b262jsn6199c1564134";
}

Film::Film(std::string id)
{
    key_rapid_api = "0085a34427mshc7f717b41100917p17b262jsn6199c1564134";
    _id = id;
    get_info_by_id(id);
}
