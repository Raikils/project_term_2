#include "filmallinformationform.h"
#include "ui_filmallinformationform.h"
#include <string>

FilmAllInformationForm::FilmAllInformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilmAllInformationForm)
{
    ui->setupUi(this);
}

FilmAllInformationForm::~FilmAllInformationForm()
{
    delete ui;
}

void FilmAllInformationForm::SetFilm(const Film &film)
{
    this->film = film;
}

void FilmAllInformationForm::SetInfoToListWidget()
{
    std::string title ="<font face=Sitka>";
    title+="Title: ";
    title+="</font>";
    title+= film.title();
    ui->textBrowser_FilmInfo->append(QString::fromStdString(title));
     ui->textBrowser_FilmInfo->append(" ");
    std::map<std::string, std::string> full_info = film.get_full_info();
    for (auto &elem : full_info) {
        if(elem.first == "Plot"){
            std::string plot ="<font face=Sitka>";
            plot+="Plot: ";
            plot+="</font>";
            ui->textBrowser_FilmInfo->append(QString::fromStdString(plot));
            ui->textBrowser_FilmInfo->append(elem.second.c_str());
            ui->textBrowser_FilmInfo->append(" ");
        }
        else if(elem.first =="src"){
            std::string date ="<font face=Sitka>";
            date+="Src: ";
            date+="</font>";
            date+=elem.second;
            ui->textBrowser_FilmInfo->append(QString::fromStdString(date));
            ui->textBrowser_FilmInfo->append(" ");
        }
        else if(elem.first =="Date"){
            std::string src ="<font face=Sitka>";
            src+="Date: ";
            src+="</font>";
            src+= elem.second;
            ui->textBrowser_FilmInfo->append(src.c_str());
            ui->textBrowser_FilmInfo->append(" ");
        }
        else{
           std::string info ="<font face=Sitka>";
           info+= elem.first+": ";
           info+="</font>";
           info+=elem.second;
           ui->textBrowser_FilmInfo->append(QString::fromStdString(info.c_str()));
           ui->textBrowser_FilmInfo->append(" ");
        }

    }

}

void FilmAllInformationForm::SetImageFilm(const QPixmap &imageFilm)
{
    this->imageFilm = imageFilm;
    ui->label_ImageFilm->setPixmap(imageFilm.scaled(ui->label_ImageFilm->width(),ui->label_ImageFilm->height(),Qt::KeepAspectRatio));
}
