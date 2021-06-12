#include <QtTest>
#include <QCoreApplication>
#include "film.h"
#include "profile.h"
#include <QFile>
#include <iostream>
#include <chrono>
#include <thread>

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void test_film_class();
    void test_profile_class();
};

Test::Test()
{

}

Test::~Test()
{

}

void Test::test_film_class()
{
    Film f("tt0944947");
    QVERIFY(f.title() == "Game of Thrones");
    QVERIFY(f.getDescription() == "In the mythical continent of Westeros, several powerful families fight for control of the Seven Kingdoms. As conflict erupts in the kingdoms of men, an ancient enemy rises once again to threaten them all. Meanwhile, the last heirs of a recently usurped dynasty plot to take back their homeland from across the Narrow Sea.");
    QVERIFY(f.main_picture() == "https://m.media-amazon.com/images/M/MV5BYTRiNDQwYzAtMzVlZS00NTI5LWJjYjUtMzkwNTUzMWMxZTllXkEyXkFqcGdeQXVyNDIzMzcwNjc@._V1_.jpg");
    QVERIFY(f.id() == "tt0944947");
    QVERIFY(f.genre()[0] == "Action");
    QVERIFY(f.genre()[1] == "Adventure");
    QVERIFY(f.genre()[2] == "Drama");
    QVERIFY(f.genre()[3] == "Fantasy");

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::map<std::string, std::string> a = f.get_full_info();
    for (const auto& k : a) {
        std::cout << k.first << " " << k.second << std::endl;
    }
}

void Test::test_profile_class()
{
    /*Profile p;
    std::vector<std::string> films = p.search_films(4, "drama");
    for (const auto &k : films) {
        std::cout << k << std::endl;
    }*/
    Profile p;
    p.setName("name");
    p.setLiked_films({"ret"});
    QFile f("testprof.dat");
        f.open(QIODevice::WriteOnly);
        QDataStream out(&f);
        out << p;
        f.close();
    QFile g("testprof.dat");
        g.open(QIODevice::ReadOnly);
        QDataStream in(&g);
        in >> p;
        g.close();
    QVERIFY(p.liked_films()[0] == "ret");
    QVERIFY(p.name() == "name");
    QVERIFY(p.genre()["drama"] > 0);
    QVERIFY(true);
}

QTEST_MAIN(Test)

#include "tst_test.moc"
