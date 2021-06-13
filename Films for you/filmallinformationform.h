#ifndef FILMALLINFORMATIONFORM_H
#define FILMALLINFORMATIONFORM_H

#include <QWidget>
#include "film.h"
#include <QListWidgetItem>
#include <QTextBrowser>
namespace Ui {
class FilmAllInformationForm;
}

class FilmAllInformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilmAllInformationForm(QWidget *parent = nullptr);
    ~FilmAllInformationForm();
    void SetFilm(const Film& film);
    void SetInfoToListWidget();
    void SetImageFilm(const  QPixmap& imageFilm);
private:
    Film film;
    QPixmap imageFilm;
    Ui::FilmAllInformationForm *ui;
};

#endif // FILMALLINFORMATIONFORM_H
