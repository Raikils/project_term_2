#include "filmform.h"
#include "ui_filmform.h"

FilmForm::FilmForm( Profile *&profile,QWidget *parent) :
    QWidget(parent),
    profile(profile),
    ui(new Ui::FilmForm)
{
    ui->setupUi(this);
}

FilmForm::FilmForm( Profile *&profile,const Film &film, QWidget *parent):
    QWidget(parent),
    profile(profile),
    ui(new Ui::FilmForm)
{
    ui->setupUi(this);
    this->SetIdFilm(film.id().c_str());
    this->SetTitleFilm(film.title().c_str());
    this->SetImageFilm(film.main_picture().c_str());
    QTextBrowser  *text = new QTextBrowser;
    text->setText(film.getDescription().c_str());
    this->SetDescription(text);
    this->film = film;
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

void FilmForm::SetIdFilm(QString IdFilm)
{
    this->IdFilm = IdFilm;
}

QPixmap FilmForm::GetImageFilm()
{
    return imageFilm;
}

QString FilmForm::GetTitleFilm()
{
    return ui->FilmTitle->text();
}

QTextBrowser* FilmForm::GetDescription()
{
    QTextBrowser* text = ui->FilmDescription;
    return text;
}

QString FilmForm::GetIdFilm()
{
    return this->IdFilm;
}

void FilmForm::SetFilm(const Film &film)
{
    this->film = film;
}

Film FilmForm::GetFilm()
{
    return film;
}



void FilmForm::on_Like_clicked()
{
    profile->like(GetFilm());
}


void FilmForm::on_Dislike_clicked()
{
     profile->dislike(GetFilm());
}


