#ifndef PROFILE_H
#define PROFILE_H

#include <map>
#include <string>
#include <vector>
#include <QDataStream>

class Profile
{
private:
    std::map<std::string, double> _genre;
    std::map<std::string, double> _country;
    std::map<std::string, double> _director;
    std::map<std::string, double> _actors;
    void change_weight(std::map<std::string, double>& characteristic, std::string key, double delta);
public:
    Profile();
    void like(std::vector<std::string> genre, std::vector<std::string> country, std::vector<std::string> director, std::vector<std::string> actors);
    void dislike(std::vector<std::string> genre, std::vector<std::string> country, std::vector<std::string> director, std::vector<std::string> actors);
    std::map<std::string, double> genre();
    std::map<std::string, double> country();
    std::map<std::string, double> director();
    std::map<std::string, double> actors();
    std::map<std::string, std::string> recommendation();
    friend QDataStream &operator<<(QDataStream &out, const Profile &profile);
    friend QDataStream &operator>>(QDataStream &in, Profile &profile);
};

#endif // PROFILE_H
