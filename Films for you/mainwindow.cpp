#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "profilemenu.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile f("Curentprofil.dat");
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    in >> profile;
    f.close();
    qDebug() << QString::fromStdString(profile.name());
}

void MainWindow::setProfile(const Profile &profile)
{
    this->profile=profile;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_Profile_from_Profilemenu(Profile prof)
{
    qDebug() << "fasdfwe";
    profile = prof;
    this->show();
    delete profilemenu;
    QFile f("Curentprofil.dat");
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    out << profile;
    f.close();
    qDebug() << QString::fromStdString(profile.name());
}


void MainWindow::film_search()
{
    std::vector<std::string> films_title = profile.recommendation();
    for (const auto& e : films_title) {
        qDebug() << QString::fromStdString(e);
    }
    qDebug() << "Dasdsadas";
    for (const auto &title : films_title) {
        QPair<Film,FilmForm*> pair;
        pair.first = Film(title);
        QListWidgetItem * elem = new QListWidgetItem;
        elem->setSizeHint(QSize(200,250));
        Profile *pr= new Profile;
        FilmForm *filmform = new FilmForm(pr);
        filmform->SetImageFilm( QString::fromStdString(pair.first.main_picture()));
        filmform->SetTitleFilm( QString::fromStdString(pair.first.title()));
        filmform->SetFilm(pair.first);
        QTextBrowser* description = new QTextBrowser();
        description->setText(QString::fromStdString(pair.first.getDescription()));
        filmform->SetDescription(description);
        ui->listWidget_recommended_movie->addItem(elem);
        ui->listWidget_recommended_movie->setItemWidget(elem,filmform);
        pair.second = filmform;
        films.push_back(pair);
    }
}


void MainWindow::on_pushButton_clicked()
{
    film_search();
}

void MainWindow::on_pushButton_toProfile_clicked()
{

    profilemenu = new ProfileMenu;
    connect(profilemenu, SIGNAL(sendProfile(Profile)), this, SLOT(get_Profile_from_Profilemenu(Profile)));
    profilemenu->show();
    this->hide();
}
