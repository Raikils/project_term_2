#ifndef FILMFORM_H
#define FILMFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QTextBrowser>
#include "film.h"
#include "profile.h"
namespace Ui {
class FilmForm;
}

class FilmForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilmForm( Profile *&profile,QWidget *parent = nullptr);
    explicit FilmForm( Profile *&profile,const Film& film, QWidget *parent = nullptr);
    ~FilmForm();
public:
    void SetImageFilm(QString ImageFilmLink);
    void SetTitleFilm(QString TitleFilm);
    void SetDescription(QTextBrowser *Description);
    void SetIdFilm(QString IdFilm);
    QPixmap GetImageFilm();
    QString GetTitleFilm();
    QTextBrowser* GetDescription();
    QString GetIdFilm();
    void SetFilm(const Film& film);
    Film GetFilm();
private slots:
    QPixmap downloadFinished(QNetworkReply*);
    void on_Like_clicked();
    void on_Dislike_clicked();
private:
    Profile *&profile;
    Film film;
    QString IdFilm;
    QPixmap imageFilm;
    Ui::FilmForm *ui;
};

#endif // FILMFORM_H
