#include "rapidapikey.h"
#include <QFile>
#include <QTextStream>

RapidAPIKey::RapidAPIKey()
{

}

std::string RapidAPIKey::get_key()
{
    QFile f("RapidAPI.txt");
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);
   std::string res = in.readLine().toStdString();
   f.close();
   return res;
}
