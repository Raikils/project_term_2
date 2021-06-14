#include "profilemenu.h"
#include "ui_profilemenu.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

ProfileMenu::ProfileMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileMenu)
{
    ui->setupUi(this);
    QFile f("profiles.dat");
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    while(!in.atEnd())
    {
        Profile profile;
        in>>profile;
        ui->listWidget_Profile->addItem(QString::fromStdString(profile.name()));
        this->profile_vector.push_back(profile);
    }
    f.close();
}

ProfileMenu::~ProfileMenu()
{
    QFile f("profiles.dat");
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    for(int i=0; i<profile_vector.size(); i++)
    {
        out<<profile_vector[i];
    }
    f.close();
    delete ui;
}

void ProfileMenu::on_addProfile_clicked()
{
   if((ui->UserName->text()!="")&&(ui->UserName->text()[0]!=" "))
   {
      for(int i=0; i<profile_vector.size(); i++)
      {
          if(ui->UserName->text().toStdString()==profile_vector[i].name())
          {
              QMessageBox::warning(this, "UserName", "User name must be unique!");
              return;
          }
      }
      Profile prof;
      prof.setName(ui->UserName->text().toStdString());
      profile_vector.push_back(prof);
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
        for(int j=0; j<profile_vector.size(); j++)
        {
            if(profile_vector[j].name()==toDelete[i]->text().toStdString())
            {
                profile_vector.remove(j);
            }
        }
        delete toDelete[i];
    }
}

void ProfileMenu::on_SelectProfile_clicked()
{
    QList<QListWidgetItem*> selected =ui->listWidget_Profile->selectedItems();
    if(selected.size()!=0)
    {
        QFile f("profiles.dat");
        f.open(QIODevice::WriteOnly);
        QDataStream out(&f);
        for(int i=0; i<profile_vector.size(); i++)
        {
            out<<profile_vector[i];
        }
        f.close();
        for(int i=0; i<profile_vector.size(); i++)
        {
            if(profile_vector[i].name()==selected[0]->text().toStdString())
            {
                qDebug() << QString::fromStdString(profile_vector[i].name());
                emit sendProfile(profile_vector[i]); 
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "SelectProfile", "Select a Profile");
    }
}
