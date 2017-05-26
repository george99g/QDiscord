#include <QtTest>
#include "QDiscord"

class tst_QDiscordDiscriminator : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordDiscriminator();
private slots:
	void testConstruction_null();
	void testConstruction_string();
	void testConstruction_int();
	void testOperators();
};

namespace data {
	const QString d1 = "1234";
	const QString d2 = "2345";
	const QString d3 = "3456";
	const qint16 id1 = 1234;
	const qint16 id2 = 2345;
	const qint16 id3 = 3456;
}

tst_QDiscordDiscriminator::tst_QDiscordDiscriminator()
{}

void tst_QDiscordDiscriminator::testConstruction_null()
{
	QDiscordDiscriminator discriminator;
	QVERIFY(discriminator.isNull());
	QCOMPARE(static_cast<bool>(discriminator), false);
}

void tst_QDiscordDiscriminator::testConstruction_string()
{
	QDiscordDiscriminator discriminator(data::d1);
	QCOMPARE(discriminator.value(), data::id1);
	QCOMPARE(discriminator.toString(), data::d1);
}

void tst_QDiscordDiscriminator::testConstruction_int()
{
	QDiscordDiscriminator discriminator(data::id1);
	QCOMPARE(discriminator.toString(), data::d1);
	QCOMPARE(discriminator.value(), data::id1);
}

void tst_QDiscordDiscriminator::testOperators()
{
	QDiscordDiscriminator nullDiscriminator;
	QDiscordDiscriminator d1(data::id1);
	QDiscordDiscriminator d2(data::id2);
	QDiscordDiscriminator d3(data::id3);

	QVERIFY(nullDiscriminator != nullDiscriminator);
	QCOMPARE(nullDiscriminator == nullDiscriminator, false);

	QVERIFY(d1 != nullDiscriminator);
	QCOMPARE(d1 == nullDiscriminator, false);
	QVERIFY(d2 != nullDiscriminator);
	QCOMPARE(d2 == nullDiscriminator, false);
	QVERIFY(d3 != nullDiscriminator);
	QCOMPARE(d3 == nullDiscriminator, false);

	QVERIFY(d1 > nullDiscriminator);
	QVERIFY(d2 > nullDiscriminator);
	QVERIFY(d3 > nullDiscriminator);
	QVERIFY(d1 >= nullDiscriminator);
	QVERIFY(d2 >= nullDiscriminator);
	QVERIFY(d3 >= nullDiscriminator);
	QCOMPARE(d1 < nullDiscriminator, false);
	QCOMPARE(d2 < nullDiscriminator, false);
	QCOMPARE(d3 < nullDiscriminator, false);
	QCOMPARE(d1 <= nullDiscriminator, false);
	QCOMPARE(d2 <= nullDiscriminator, false);
	QCOMPARE(d3 <= nullDiscriminator, false);

	QVERIFY(nullDiscriminator != d1);
	QCOMPARE(nullDiscriminator == d1, false);
	QVERIFY(nullDiscriminator != d2);
	QCOMPARE(nullDiscriminator == d2, false);
	QVERIFY(nullDiscriminator != d3);
	QCOMPARE(nullDiscriminator == d3, false);

	QVERIFY(nullDiscriminator < d1);
	QVERIFY(nullDiscriminator < d2);
	QVERIFY(nullDiscriminator < d3);
	QVERIFY(nullDiscriminator <= d1);
	QVERIFY(nullDiscriminator <= d2);
	QVERIFY(nullDiscriminator <= d3);
	QCOMPARE(nullDiscriminator > d1, false);
	QCOMPARE(nullDiscriminator > d2, false);
	QCOMPARE(nullDiscriminator > d3, false);
	QCOMPARE(nullDiscriminator >= d1, false);
	QCOMPARE(nullDiscriminator >= d2, false);
	QCOMPARE(nullDiscriminator >= d3, false);

	QVERIFY(d3 > d2);
	QVERIFY(d3 >= d2);
	QVERIFY(d2 > d1);
	QVERIFY(d2 >= d1);
	QCOMPARE(d2 > d3, false);
	QCOMPARE(d2 >= d3, false);
	QCOMPARE(d1 > d2, false);
	QCOMPARE(d1 >= d2, false);

	QVERIFY(d1 == d1);
	QCOMPARE(d1 != d1, false);

	QVERIFY(d1 >= d1);
	QCOMPARE(d1 > d1, false);
	QVERIFY(d1 <= d1);
	QCOMPARE(d1 < d1, false);
}

QTEST_MAIN(tst_QDiscordDiscriminator)

#include "tst_qdiscorddiscriminator.moc"
