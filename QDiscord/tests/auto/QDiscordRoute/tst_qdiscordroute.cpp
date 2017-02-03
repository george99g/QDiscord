#include <QtTest>
#include "../../../src/qdiscord.d/qdiscordroute.hpp"

class tst_QDiscordRoute: public QObject
{
	Q_OBJECT
public:
	tst_QDiscordRoute();
private slots:
	void testNoParams();
	void testNoParamsDiffMethod();
	void testSingleMajorParam();
	void testMultipleMajorParams();
	void testMajorMinorParams();
	void testSingleMinorParam();
	void testMultipleMinorParams();
};

tst_QDiscordRoute::tst_QDiscordRoute()
{}

void tst_QDiscordRoute::testNoParams()
{
	QDiscordRoute route(QDiscordRoute::Method::GET,"/gateway");
	QCOMPARE(route.fullUrl(), QString("/gateway"));
	QCOMPARE(route.bucketUrl(), QString("/gateway"));
}

void tst_QDiscordRoute::testNoParamsDiffMethod()
{
	QDiscordRoute route(QDiscordRoute::Method::POST, "/gateway");
	QCOMPARE(route.method(), QDiscordRoute::Method::POST);
	QCOMPARE(route.fullUrl(), QString("/gateway"));
	QCOMPARE(route.bucketUrl(), QString("/gateway"));
}

void tst_QDiscordRoute::testSingleMajorParam()
{
	QDiscordRoute route(QDiscordRoute::Method::GET, "/guilds/{guild}", "123");
	QCOMPARE(route.method(), QDiscordRoute::Method::GET);
	QCOMPARE(route.fullUrl(), QString("/guilds/123"));
	QCOMPARE(route.bucketUrl(), QString("/guilds/123"));
}

void tst_QDiscordRoute::testMultipleMajorParams()
{
	QDiscordRoute route(
				QDiscordRoute::Method::GET,
				"/guilds/{guild}/channels/{channel}",
				"123",
				"456"
	);
	QCOMPARE(route.method(), QDiscordRoute::Method::GET);
	QCOMPARE(route.fullUrl(), QString("/guilds/123/channels/456"));
	QCOMPARE(route.bucketUrl(), QString("/guilds/123/channels/456"));
}

void tst_QDiscordRoute::testMajorMinorParams()
{
	QDiscordRoute route(
				QDiscordRoute::Method::GET,
				"/guilds/{guild}/emojis/{emoji}",
				"123",
				"456"
	);
	QCOMPARE(route.method(), QDiscordRoute::Method::GET);
	QCOMPARE(route.fullUrl(), QString("/guilds/123/emojis/456"));
	QCOMPARE(route.bucketUrl(), QString("/guilds/123/emojis/{emoji}"));
}

void tst_QDiscordRoute::testSingleMinorParam()
{
	QDiscordRoute route(QDiscordRoute::Method::GET, "/emojis/{emoji}", "123");
	QCOMPARE(route.method(), QDiscordRoute::Method::GET);
	QCOMPARE(route.fullUrl(), QString("/emojis/123"));
	QCOMPARE(route.bucketUrl(), QString("/emojis/{emoji}"));
}

void tst_QDiscordRoute::testMultipleMinorParams()
{
	QDiscordRoute route(
				QDiscordRoute::Method::GET,
				"/roles/{role}/emojis/{emoji}",
				"123",
				"456"
	);
	QCOMPARE(route.method(), QDiscordRoute::Method::GET);
	QCOMPARE(route.fullUrl(), QString("/roles/123/emojis/456"));
	QCOMPARE(route.bucketUrl(), QString("/roles/{role}/emojis/{emoji}"));
}

QTEST_MAIN(tst_QDiscordRoute)

#include "tst_qdiscordroute.moc"
