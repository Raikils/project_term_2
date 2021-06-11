#include "profilemenu.h"
#include "ui_profilemenu.h"
#include "mainwindow.h"
#include <QMessageBox>

ProfileMenu::ProfileMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileMenu)
{
    ui->setupUi(this);
}

ProfileMenu::~ProfileMenu()
{
    delete ui;
}

void ProfileMenu::on_addProfile_clicked()
{
   if((ui->UserName->text()!="")&&(ui->UserName->text()[0]!=" "))
   {
      ui->listWidget_Profile->addItem(ui->UserName->text());
   }
   else
   {
      QMessageBox::warning(this, "UserName", "User name must contain non-empty first letter");
   }
}

void ProfileMenu::on_deleteProfile_clicked()
{
    QList<QListWidgetItem*> toDelete =ui->listWidget_Profile->selectedItems();
    if(toDelete.size()==0)
    {
        QMessageBox::warning(this, "DeleteProfile", "Select a Profile to delete");
    }
    for(int i=0; i<toDelete.size(); i++)
    {
        delete toDelete[i];
    }
}

void ProfileMenu::on_SelectProfile_clicked()
{
    QList<QListWidgetItem*> selected =ui->listWidget_Profile->selectedItems();
    if(selected.size()!=0)
    {
        MainWindow *w = new MainWindow;
        w->show();
    }
    else
    {
        QMessageBox::warning(this, "SelectProfile", "Select a Profile");
    }
}
