#include <QtTest>
#include "QDiscord"

class tst_QDiscordGame : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordGame();
private slots:
	void testConstruction_null();
	void testConstruction_game();
	void testConstruction_streaming();
	void testSerialization();
	void testOperators();
};

namespace data {
	const QJsonObject game =
	{
		{"name", "Game."},
		{"type", 0}
	};

	const QJsonObject streaming =
	{
		{"name", "A game."},
		{"url", "https://example.org"},
		{"type", 1}
	};
}

tst_QDiscordGame::tst_QDiscordGame()
{}

void tst_QDiscordGame::testConstruction_null()
{
	QDiscordGame game;
	QVERIFY(game.isNull());
	QCOMPARE(static_cast<bool>(game), false);
}

void tst_QDiscordGame::testConstruction_game()
{
	QDiscordGame game(data::game);
	QCOMPARE(game.name(), QString("Game."));
	QVERIFY(game.url().isEmpty());
	QCOMPARE(game.type(), QDiscordGame::GameType::Default);
}

void tst_QDiscordGame::testConstruction_streaming()
{
	QDiscordGame game(data::streaming);
	QCOMPARE(game.name(), QString("A game."));
	QCOMPARE(game.url(), QString("https://example.org"));
	QCOMPARE(game.type(), QDiscordGame::GameType::Streaming);
}

void tst_QDiscordGame::testSerialization()
{
	QDiscordGame game(data::game);
	QCOMPARE(game.serialize(), data::game);

	QDiscordGame streaming(data::streaming);
	QCOMPARE(streaming.serialize(), data::streaming);
}

void tst_QDiscordGame::testOperators()
{
	QDiscordGame game1(data::game);
	QDiscordGame game2(data::streaming);

	QCOMPARE(game1 <  game2, game1.name() <  game2.name());
	QCOMPARE(game1 <= game2, game1.name() <= game2.name());
	QCOMPARE(game1 >  game2, game1.name() >  game2.name());
	QCOMPARE(game1 >= game2, game1.name() >= game2.name());
	QCOMPARE(game1 == game2, game1.name() == game2.name());
	QCOMPARE(game1 != game2, game1.name() != game2.name());

}

QTEST_MAIN(tst_QDiscordGame)

#include "tst_qdiscordgame.moc"
