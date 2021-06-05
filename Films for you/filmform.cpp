#include "filmform.h"
#include "ui_filmform.h"

FilmForm::FilmForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilmForm)
{
    ui->setupUi(this);
}

FilmForm::~FilmForm()
{
    delete ui;
}

QPixmap FilmForm::downloadFinished(QNetworkReply *reply)
{
   imageFilm.loadFromData(reply->readAll());
   ui->FilmImage->setPixmap(imageFilm.scaled(ui->FilmImage->width(),ui->FilmImage->height(),Qt::KeepAspectRatio));
   return imageFilm;
}

void FilmForm::SetImageFilm(QString ImageFilmLink)
{
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man,&QNetworkAccessManager::finished,this, &FilmForm::downloadFinished);
    const QUrl url = QUrl(ImageFilmLink);
    QNetworkRequest request(url);
    man->get(request);
}

void FilmForm::SetTitleFilm(QString TitleFilm)
{
   ui->FilmTitle->setText(TitleFilm);
}

void FilmForm::SetDescription(QTextBrowser *Description)
{
    ui->FilmDescription->setText(Description->toPlainText());
}


