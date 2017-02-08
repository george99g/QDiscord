#include <QtTest>
#include "../../../src/QDiscord"

class tst_QDiscordToken: public QObject
{
	Q_OBJECT
public:
	tst_QDiscordToken();
private slots:
	void testAutoToken_data();
	void testAutoToken();
	void testTokenGeneration_data();
	void testTokenGeneration();
private:
};



tst_QDiscordToken::tst_QDiscordToken()
{

}

void tst_QDiscordToken::testAutoToken_data()
{
	QTest::addColumn<QString>("input");
	QTest::addColumn<QString>("output_fullToken");
	QTest::addColumn<QDiscordToken::Type>("output_type");

	QTest::newRow("none")
	<< "My.FanCy.ToKen"
	<< "My.FanCy.ToKen"
	<< QDiscordToken::Type::None;

	QTest::newRow("bot")
	<< "bot My.FanCy.ToKen"
	<< "Bot My.FanCy.ToKen"
	<< QDiscordToken::Type::Bot;

	QTest::newRow("bearer")
	<< "bearer My.FanCy.ToKen"
	<< "Bearer My.FanCy.ToKen"
	<< QDiscordToken::Type::Bearer;

	QTest::newRow("invalid")
	<< "mybot My.FanCy.ToKen"
	<< "Bot My.FanCy.ToKen"
	<< QDiscordToken::Type::Bot;
}

void tst_QDiscordToken::testAutoToken()
{
	QFETCH(QString, input);
	QFETCH(QString, output_fullToken);
	QFETCH(QDiscordToken::Type, output_type);

	QDiscordToken token(input, QDiscordToken::Type::Auto);

	QCOMPARE(token.fullToken(), output_fullToken);
	QCOMPARE(token.type(), output_type);
}

void tst_QDiscordToken::testTokenGeneration_data()
{
	QTest::addColumn<QString>("input");
	QTest::addColumn<QDiscordToken::Type>("type");
	QTest::addColumn<QString>("output_fullToken");

	QTest::newRow("none")
	<< "My.FanCy.ToKen"
	<< QDiscordToken::Type::None
	<< "My.FanCy.ToKen";

	QTest::newRow("bot")
	<< "My.FanCy.ToKen"
	<< QDiscordToken::Type::Bot
	<< "Bot My.FanCy.ToKen";

	QTest::newRow("bearer")
	<< "My.FanCy.ToKen"
	<< QDiscordToken::Type::Bearer
	<< "Bearer My.FanCy.ToKen";
}

void tst_QDiscordToken::testTokenGeneration()
{
	QFETCH(QString, input);
	QFETCH(QDiscordToken::Type, type);
	QFETCH(QString, output_fullToken);

	QDiscordToken token(input, type);

	QCOMPARE(token.fullToken(), output_fullToken);
}

QTEST_MAIN(tst_QDiscordToken)

#include "tst_qdiscordtoken.moc"
