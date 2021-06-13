#include "filmallinformationform.h"
#include "ui_filmallinformationform.h"

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
    for (auto &elem : film.get_full_info()) {
        if(elem.first == "Plot"){
            QListWidgetItem * listelem= new QListWidgetItem;
            listelem->setSizeHint(QSize(200,250));
            QTextBrowser* description = new QTextBrowser();
            description->setText(elem.second.c_str());
            ui->listWidget_FilmInfo->addItem(QString::fromStdString(elem.first.c_str())+":");
            ui->listWidget_FilmInfo->addItem(listelem);
            ui->listWidget_FilmInfo->setItemWidget(listelem,description);
        }
        else{
            ui->listWidget_FilmInfo->addItem(QString::fromStdString(elem.first.c_str())+":");
            ui->listWidget_FilmInfo->addItem(elem.second.c_str());
        }

    }

}

void FilmAllInformationForm::SetImageFilm(const QPixmap &imageFilm)
{
    this->imageFilm = imageFilm;
    ui->label_ImageFilm->setPixmap(imageFilm.scaled(ui->label_ImageFilm->width(),ui->label_ImageFilm->height(),Qt::KeepAspectRatio));
}
