#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "profile.h"
#include "film.h"
#include "filmform.h"
#include <QVector>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void film_search();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Profile profile;
    QVector<QPair<Film,FilmForm*>> films;
};
#endif // MAINWINDOW_H
