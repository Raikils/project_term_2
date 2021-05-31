#include "profile.h"

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

std::map<std::string, double> Profile::genre()
{
    return _genre;
}

std::map<std::string, double> Profile::country()
{
    return _country;
}

std::map<std::string, double> Profile::director()
{
    return _director;
}

std::map<std::string, double> Profile::actors()
{
    return _actors;
}

std::map<std::string, std::string> Profile::recommendation()
{
    std::map<std::string, std::string> recom;
    recom["Genre"] = "Comedy";
    double maxx = _genre["Comedy"];
    for (const auto &elem : _genre) {
        if (elem.second > maxx) {
            maxx = elem.second;
            recom["Genre"] = elem.first;
        }
    }
    recom["Country"] = "";
    maxx = 0;
    for (const auto &elem : _country) {
        if (elem.second > maxx) {
            maxx = elem.second;
            recom["Country"] = elem.first;
        }
    }

    recom["Director"] = "";
    maxx = 0;
    for (const auto &elem : _director) {
        if (elem.second > maxx) {
            maxx = elem.second;
            recom["Director"] = elem.first;
        }
    }

    recom["Actors"] = "";
    maxx = 0;
    for (const auto &elem : _actors) {
        if (elem.second > maxx) {
            maxx = elem.second;
            recom["Actors"] = elem.first;
        }
    }
    return recom;
}
