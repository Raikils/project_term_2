#ifndef FILMFORM_H
#define FILMFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QTextBrowser>
namespace Ui {
class FilmForm;
}

class FilmForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilmForm(QWidget *parent = nullptr);
    ~FilmForm();
public:
    void SetImageFilm(QString ImageFilmLink);
    void SetTitleFilm(QString TitleFilm);
    void SetDescription(QTextBrowser *Description);
    QString GetImageFilm();
    QString GetTitleFilm();
    QTextBrowser GetDescription();

private slots:
     QPixmap downloadFinished(QNetworkReply*);
private:
    QPixmap imageFilm;
    Ui::FilmForm *ui;
};

#endif // FILMFORM_H
