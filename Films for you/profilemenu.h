#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include "profile.h"
#include <QWidget>
#include <QVector>

namespace Ui {
class ProfileMenu;
}

/*!
 * \brief The ProfileMenu class
 * Window for work with profiles
 */
class ProfileMenu : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief ProfileMenu
     * \param parent
     * Constructor
     */
    explicit ProfileMenu(QWidget *parent = nullptr);
    /*!
     * Destructor
     */
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
