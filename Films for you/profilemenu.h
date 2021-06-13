#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include "profile.h"
#include <QWidget>
#include <QVector>

namespace Ui {
class ProfileMenu;
}

class ProfileMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileMenu(QWidget *parent = nullptr);
    ~ProfileMenu();

private slots:
    void on_addProfile_clicked();

    void on_deleteProfile_clicked();

    void on_SelectProfile_clicked();

signals: void sendProfile(Profile profile);

private:
    Ui::ProfileMenu *ui;
    QVector<Profile> profile_vector;
};

#endif // PROFILEMENU_H
