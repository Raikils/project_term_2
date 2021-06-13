#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "profilemenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //std::vector<std::string> a = {"tt0944947", "tt0944947"};

}

void MainWindow::setProfile(const Profile &profile)
{
    this->profile=profile;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::film_search()
{
    std::vector<std::string> films_title = profile.recommendation();
    for (const auto &title : films_title) {
        QPair<Film,FilmForm*> pair;
        pair.first = Film(title);
        QListWidgetItem * elem = new QListWidgetItem;
        elem->setSizeHint(QSize(200,250));
        Profile *pr= new Profile;
        FilmForm *filmform = new FilmForm(pr);
        filmform->SetImageFilm( QString::fromStdString(pair.first.main_picture()));
        filmform->SetTitleFilm( QString::fromStdString(pair.first.title()));
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
    //film_search();
    QListWidgetItem * elem = new QListWidgetItem;
    elem->setSizeHint(QSize(200,250));
    Film f("tt1270797");
    Profile *pr= new Profile;
    FilmForm *filmform = new FilmForm(pr,f);
    ui->listWidget_recommended_movie->addItem(elem);
    ui->listWidget_recommended_movie->setItemWidget(elem,filmform);
}

void MainWindow::on_pushButton_toProfile_clicked()
{
<<<<<<< Updated upstream
    this->profilemenu = new ProfileMenu;
    profilemenu->show();
    this->hide();
=======
//    this->profilemenu = new ProfileMenu;
//    w->show();
//    this->hide();
>>>>>>> Stashed changes
}
