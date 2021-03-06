#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "profile.h"
#include "film.h"
#include "filmform.h"
#include "profilemenu.h"
#include <QVector>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \brief Main window of programme
 * Main window of programme
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * Basic constructor of class
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * Sets profile
     */
    void setProfile(const Profile &profile);
    /*!
     * Returns current profile
     */
    Profile GetProfile();  
    ~MainWindow();

public slots:
    /*!
     * Slot for receiving profile from profilemenu
     */
    void get_Profile_from_Profilemenu(Profile prof);

private slots:
    void film_search();
    void on_pushButton_clicked();
    void on_pushButton_toProfile_clicked();

private:
    Ui::MainWindow *ui;
    ProfileMenu *profilemenu;
    Profile profile;
    QVector<QPair<Film,FilmForm*>> films;
};
#endif // MAINWINDOW_H
