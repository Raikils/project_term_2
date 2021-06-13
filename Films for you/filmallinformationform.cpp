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
    ui->listWidget_FilmInfo->addItem(QString::fromStdString("Title :"));
    ui->listWidget_FilmInfo->addItem(film.title().c_str());
    for (auto &elem : film.get_full_info()) {
        if(elem.first == "Plot"){
            QListWidgetItem * listelem= new QListWidgetItem;
            listelem->setSizeHint(QSize(200,75));
            QTextBrowser* description = new QTextBrowser();
            description->setText(elem.second.c_str());
            description->setStyleSheet("border:0px solid;color:yellow; font-size:14px");
            std::string plot = elem.first;
            ui->listWidget_FilmInfo->addItem(QString::fromStdString(elem.first.c_str())+":");
            ui->listWidget_FilmInfo->addItem(listelem);
            ui->listWidget_FilmInfo->setItemWidget(listelem,description);
        }
        else if(elem.first =="src"){
            ui->listWidget_FilmInfo->addItem(QString::fromStdString(elem.first.c_str())+":");
            ui->listWidget_FilmInfo->addItem(elem.second.c_str());
        }
        else if(elem.first =="Date"){
            std::string link = elem.first+": "+elem.second;
            ui->listWidget_FilmInfo->addItem(link.c_str());
        }
        else{
            std::string plot = elem.first;
            ui->listWidget_FilmInfo->addItem(QString::fromStdString(plot.c_str())+":");
            ui->listWidget_FilmInfo->addItem(elem.second.c_str());
        }

    }

}

void FilmAllInformationForm::SetImageFilm(const QPixmap &imageFilm)
{
    this->imageFilm = imageFilm;
    ui->label_ImageFilm->setPixmap(imageFilm.scaled(ui->label_ImageFilm->width(),ui->label_ImageFilm->height(),Qt::KeepAspectRatio));
}
