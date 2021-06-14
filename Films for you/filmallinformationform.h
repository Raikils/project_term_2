#ifndef FILMALLINFORMATIONFORM_H
#define FILMALLINFORMATIONFORM_H

#include <QWidget>
#include "film.h"
#include <QListWidgetItem>
#include <QTextBrowser>
namespace Ui {
class FilmAllInformationForm;
}

/*!
 * \brief The FilmAllInformationForm class
 *  This widget is used to display all information about the movie.
 */
class FilmAllInformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilmAllInformationForm(QWidget *parent = nullptr);
    ~FilmAllInformationForm();
    /*!
        Method to get movie
    */
    void SetFilm(const Film& film);
    /*!
        Method to set information to the list
    */
    void SetInfoToListWidget();
    /*!
        Method to set image
    */
    void SetImageFilm(const  QPixmap& imageFilm);
private:
    Film film;
    QPixmap imageFilm;
    Ui::FilmAllInformationForm *ui;
};

#endif // FILMALLINFORMATIONFORM_H
