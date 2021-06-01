#include "profile.h"
#include <cmath>
#include <QString>

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

Profile::Profile()
{
    double weight = 1.0 / 12;
    _genre["Comedy"] = weight;
    _genre["SCI-FI"] = weight;
    _genre["Horror"] = weight;
    _genre["Ramance"] = weight;
    _genre["Action"] = weight;
    _genre["Thriller"] = weight;
    _genre["Drama"] = weight;
    _genre["Mystary"] = weight;
    _genre["Crime"] = weight;
    _genre["Animation"] = weight;
    _genre["Adventure"] = weight;
    _genre["Fantasy"] = weight;
    _genre["Comedy-romance"] = weight;
    _genre["Superhero"] = weight;
    _genre["Action-comedy"] = weight;
}

void Profile::like(std::vector<std::string> genre, std::vector<std::string> country, std::vector<std::string> director, std::vector<std::string> actors)
{
    for (auto key : genre) change_weight(_genre, key, 0.1);
    for (auto key : country) {
        if (_country[key]) {
            _country[key] += 0.1;
        } else {
            _country[key] = 0.1;
        }
    }
    for (auto key : director) {
        if (_country[key]) {
            _country[key] += 0.1;
        } else {
            _country[key] = 0.1;
        }
    }
    for (auto key : actors) {
        if (_country[key]) {
            _country[key] += 0.1;
        } else {
            _country[key] = 0.1;
        }
    }
}

void Profile::dislike(std::vector<std::string> genre, std::vector<std::string> country, std::vector<std::string> director, std::vector<std::string> actors)
{
    for (auto key : genre) change_weight(_genre, key, -0.1);
    for (auto key : country) {
        if (_country[key]) {
            _country[key] -= 0.1;
        } else {
            _country[key] = -0.1;
        }
    }
    for (auto key : director) {
        if (_country[key]) {
            _country[key] -= 0.1;
        } else {
            _country[key] = -0.1;
        }
    }
    for (auto key : actors) {
        if (_country[key]) {
            _country[key] -= 0.1;
        } else {
            _country[key] = -0.1;
        }
    }
}

std::map<std::string, double> Profile::genre() const
{
    return _genre;
}

std::map<std::string, double> Profile::country() const
{
    return _country;
}

std::map<std::string, double> Profile::director() const
{
    return _director;
}

std::map<std::string, double> Profile::actors() const
{
    return _actors;
}

void Profile::set_genre(const std::map<std::string, double> &value)
{
    _genre = value;
}

void Profile::set_country(const std::map<std::string, double> &value)
{
    _country = value;
}

void Profile::set_director(const std::map<std::string, double> &value)
{
    _director = value;
}

void Profile::set_actors(const std::map<std::string, double> &value)
{
    _actors = value;
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
    for (const auto& elem : profile.genre()) {
        out << QString::fromStdString(elem.first) << elem.second;
    }

    out << profile.actors().size();
    for (const auto& elem : profile.actors()) {
        out << QString::fromStdString(elem.first) << elem.second;
    }

    out << profile.country().size();
    for (const auto& elem : profile.country()) {
        out << QString::fromStdString(elem.first) << elem.second;
    }

    out << profile.director().size();
    for (const auto& elem : profile.director()) {
        out << QString::fromStdString(elem.first) << elem.second;
    }
}
QDataStream &operator>>(QDataStream &in, Profile &profile)
{
    int n;
    std::map<std::string, double> container;
    QString name;
    double weight;
    for (int i = 0; i < 12; i++) {
        in >> name;
        in >> weight;
        container[name.toStdString()] = weight;
    }
    profile.set_genre(container);

    container.clear();
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> name;
        in >> weight;
        container[name.toStdString()] = weight;
    }
    profile.set_actors(container);

    container.clear();
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> name;
        in >> weight;
        container[name.toStdString()] = weight;
    }
    profile.set_country(container);

    container.clear();
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> name;
        in >> weight;
        container[name.toStdString()] = weight;
    }
    profile.set_director(container);

    container.clear();
}


size_t Profile::curlWriteFunc(char *data, size_t size, size_t nmemb, string *buffer)
{

   size_t result = 0;

   if (buffer != NULL)
   {
           buffer->append(data, size * nmemb);
           result = size * nmemb;
   }
   return result;

}
std::map<std::string, int> Profile::count_of_films_by_genre()
{
    std::map<std::string, int> result;
    for (auto &elem : genre()) {

    std::string url = "https://imdb8.p.rapidapi.com/title/get-popular-movies-by-genre?genre=%2Fchart%2Fpopular%2Fgenre%2F"+elem.first+"&rapidapi-key=7108452cfbmsha343da9f70d1991p19f5bfjsn4fee4d4b283c";
    char curlErrorBuffer[CURL_ERROR_SIZE];

    CURL *curl = curl_easy_init();
    if (curl) {
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
            CURLcode curlResult = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (curlResult == CURLE_OK)
            {
                std::vector<string> counter;
                int a = 0;
                int second_slash = 0;
                bool isSecondSlash = false;
                for(size_t i =0; i<=curlBuffer.length(); i++){

                    if(curlBuffer[i]=='/'){
                        a++;
                    }
                    if(a==2 && !isSecondSlash){
                        isSecondSlash =true;
                        second_slash = i;
                    }
                    if(a==3){
                        int start = second_slash+1;
                        int count = i-start;
                        std::string additional = curlBuffer.substr (start,count);
                        counter.push_back(additional);
                        isSecondSlash = false;
                        a = 0;
                    }

                }
                  result[elem.first] = counter.size();
                 counter.clear();
            }
            else {
                std::cout << "Error(" << curlResult << "): " << curlErrorBuffer << std::endl;

            }
             curlBuffer.clear();
    }

    }
    return result;
}
