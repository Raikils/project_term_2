#ifndef FILMFORM_H
#define FILMFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QTextBrowser>
#include "film.h"
#include "profile.h"
#include "filmallinformationform.h"
namespace Ui {
class FilmForm;
}
/*!
 * \brief The FilmForm class
 * This widget is used to display basic information about the movie. It is passed to the mainwindow
 */
class FilmForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilmForm( Profile &profile,QWidget *parent = nullptr);
    explicit FilmForm( Profile &profile,const Film& film, QWidget *parent = nullptr);
    ~FilmForm();
public:
    /*!
        Method to set image of the movie
    */
    void SetImageFilm(QString ImageFilmLink);
    /*!
        Method to set title of the movie
    */
    void SetTitleFilm(QString TitleFilm);
    /*!
        Method to set description of the movie
    */
    void SetDescription(QTextBrowser *Description);
    /*!
        Method to set id of the movie
    */
    void SetIdFilm(QString IdFilm);
    /*!
        Method to get image of the movie
    */
    QPixmap GetImageFilm();
    /*!
        Method to get title of the movie
    */
    QString GetTitleFilm();
    /*!
        Method to get description of the movie
    */
    QTextBrowser* GetDescription();
    /*!
        Method to get id of the movie
    */
    QString GetIdFilm();
    /*!
        Method to set movie
    */
    void SetFilm(const Film& film);
    /*!
        Method to get movie
    */
    Film GetFilm();
private slots:
    void on_Like_clicked();
    void on_Dislike_clicked();
    void on_pushButton_All_Information_clicked();
private:
    QPixmap downloadFinished(QNetworkReply*);
    Profile &profile;
    Film film;
    QString IdFilm;
    QPixmap imageFilm;
    Ui::FilmForm *ui;
    FilmAllInformationForm *filmallinformation;
};

#endif // FILMFORM_H
