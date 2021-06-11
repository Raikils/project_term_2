#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include <QWidget>

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

private:
    Ui::ProfileMenu *ui;
};

#endif // PROFILEMENU_H
