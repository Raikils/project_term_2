#include "profile.h"
#include <cmath>
#include <QString>
#include <QDebug>

std::string Profile::name() const
{
    return _name;
}

void Profile::setName(const std::string &name)
{
    _name = name;
}

std::vector<std::string> Profile::liked_films() const
{
    return _liked_films;
}

void Profile::setLiked_films(const std::vector<std::string> &liked_films)
{
    _liked_films = liked_films;
}

void Profile::change_weight(std::map<std::string, double> &characteristic, std::string key, double delta)
{
    for (auto &elem : characteristic) {
        if (elem.first == key) {
            elem.second += delta;
        } else {
            elem.second -= delta;
        }
    }
}

std::vector<std::string> Profile::search_films(int n, std::string genre)
{
    std::vector<std::string> films;
    CURL* curl = curl_easy_init();
    CURLcode result;
    std::string url = "https://imdb8.p.rapidapi.com/title/get-popular-movies-by-genre?genre=%2Fchart%2Fpopular%2Fgenre%2F" + genre;
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    struct curl_slist *headers = NULL;
    std::string key = "x-rapidapi-key: 0085a34427mshc7f717b41100917p17b262jsn6199c1564134";
    headers = curl_slist_append(headers, key.c_str());
    headers = curl_slist_append(headers, "x-rapidapi-host: imdb8.p.rapidapi.com");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    rapidjson::Document doc;
    doc.Parse(buffer.c_str());
    rapidjson::Value& film_parse = doc;
    std::string film;
    for (int i = 0; i < n; i++) {
        film = film_parse[i].GetString();
        film.erase(film.end() - 1);
        film.erase(0,7);
        films.push_back(film);
    }
    buffer.clear();
    return films;
}

size_t Profile::curl_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
    ((std::string*)stream)->append((char*)ptr, size*nmemb);
    return size*nmemb;
}

Profile::Profile()
{
    double weight = 1.0 / 12;
    _genre["comedy"] = weight;
    _genre["sci-fi"] = weight;
    _genre["horror"] = weight;
    _genre["ramance"] = weight;
    _genre["action"] = weight;
    _genre["thriller"] = weight;
    _genre["drama"] = weight;
    _genre["mystary"] = weight;
    _genre["crime"] = weight;
    _genre["animation"] = weight;
    _genre["adventure"] = weight;
    _genre["fantasy"] = weight;
    _genre["comedy-romance"] = weight;
    _genre["superhero"] = weight;
    _genre["action-comedy"] = weight;
}

void Profile::like(Film film)
{
    for (auto key : film.genre()) change_weight(_genre, key, 0.1);
}

void Profile::dislike(Film film)
{
    for (auto key : film.genre()) change_weight(_genre, key, -0.1);
}

std::map<std::string, double> Profile::genre() const
{
    return _genre;
}

void Profile::set_genre(const std::map<std::string, double> &value)
{
    _genre = value;
}

std::map<std::string, int> Profile::recommendation_genre()
{
    double sum = 0;
    const int number_of_films = 10;
    std::map<std::string, int> result;
    for (const auto& elem : _genre) {
        sum += elem.second;
    }
    for (const auto& elem : _genre) {
        result[elem.first] = qRound((elem.second / sum) * number_of_films);
    }
    return result;
}

QDataStream &operator<<(QDataStream &out, const Profile &profile)
{
    out << int(profile.genre().size());
    for (const auto& elem : profile.genre()) {
        out << QString(QString::fromStdString(elem.first)) << double(elem.second);
    }

    out << QString(QString::fromStdString(profile.name()));

    out << int(profile.liked_films().size());
    for (const auto& elem : profile.liked_films()) {
        out << QString(QString::fromStdString(elem));
    }
}
QDataStream &operator>>(QDataStream &in, Profile &profile)
{
    int n;
    std::map<std::string, double> container;
    QString name;
    double weight;
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> name;
        in >> weight;
        container[name.toStdString()] = weight;
    }
    profile.set_genre(container);

    container.clear();

    in >> name;
    profile.setName(name.toStdString());

    in >> n;
    std::vector<std::string> liked;
    for (int i = 0; i < n; i++) {
        in >> name;
        liked.push_back(name.toStdString());
    }
    profile.setLiked_films(liked);
}

std::vector<std::string> Profile::recommendation()
{
    std::map<std::string, int> recomends = recommendation_genre();
    std::vector<std::string> films;
    std::vector<std::string> temp;
    for (const auto &elem : recomends) {
        if (elem.second > 0) {
            temp = search_films(elem.second, elem.first);
            films.insert(films.end(), temp.begin(), temp.end());
        }
    }
    return films;
}
