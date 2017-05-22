#include <QtTest>
#include "QDiscord"

class tst_QDiscordID : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordID();
private slots:
	void testConstruction_null();
	void testConstruction_string();
	void testConstruction_int();
	void testOperators();
};

namespace data {
	QString id1 = "129827149523671712";
	QString id2 = "129865555555576712";
	QString id3 = "155954930191040513";
	quint64 iid1 = 129827149523671712ULL;
	quint64 iid2 = 129865555555576712ULL;
	quint64 iid3 = 155954930191040513ULL;

}

tst_QDiscordID::tst_QDiscordID()
{}

void tst_QDiscordID::testConstruction_null()
{
	QDiscordID id;
	QVERIFY(id.isNull());
	QCOMPARE(static_cast<bool>(id), false);
}

void tst_QDiscordID::testConstruction_string()
{
	QDiscordID id(data::id1);
	QCOMPARE(id.value(), data::iid1);
	QCOMPARE(id.toString(), data::id1);
}

void tst_QDiscordID::testConstruction_int()
{
	QDiscordID id(data::iid1);
	QCOMPARE(id.toString(), data::id1);
	QCOMPARE(id.value(), data::iid1);
}

void tst_QDiscordID::testOperators()
{
	QDiscordID nullId;
	QDiscordID id1(data::iid1);
	QDiscordID id2(data::iid2);
	QDiscordID id3(data::iid3);

	QVERIFY(nullId != nullId);
	QCOMPARE(nullId == nullId, false);

	QVERIFY(id1 != nullId);
	QCOMPARE(id1 == nullId, false);
	QVERIFY(id2 != nullId);
	QCOMPARE(id2 == nullId, false);
	QVERIFY(id3 != nullId);
	QCOMPARE(id3 == nullId, false);

	QVERIFY(id1 > nullId);
	QVERIFY(id2 > nullId);
	QVERIFY(id3 > nullId);
	QVERIFY(id1 >= nullId);
	QVERIFY(id2 >= nullId);
	QVERIFY(id3 >= nullId);
	QCOMPARE(id1 < nullId, false);
	QCOMPARE(id2 < nullId, false);
	QCOMPARE(id3 < nullId, false);
	QCOMPARE(id1 <= nullId, false);
	QCOMPARE(id2 <= nullId, false);
	QCOMPARE(id3 <= nullId, false);

	QVERIFY(nullId != id1);
	QCOMPARE(nullId == id1, false);
	QVERIFY(nullId != id2);
	QCOMPARE(nullId == id2, false);
	QVERIFY(nullId != id3);
	QCOMPARE(nullId == id3, false);

	QVERIFY(nullId < id1);
	QVERIFY(nullId < id2);
	QVERIFY(nullId < id3);
	QVERIFY(nullId <= id1);
	QVERIFY(nullId <= id2);
	QVERIFY(nullId <= id3);
	QCOMPARE(nullId > id1, false);
	QCOMPARE(nullId > id2, false);
	QCOMPARE(nullId > id3, false);
	QCOMPARE(nullId >= id1, false);
	QCOMPARE(nullId >= id2, false);
	QCOMPARE(nullId >= id3, false);

	QVERIFY(id3 > id2);
	QVERIFY(id3 >= id2);
	QVERIFY(id2 > id1);
	QVERIFY(id2 >= id1);
	QCOMPARE(id2 > id3, false);
	QCOMPARE(id2 >= id3, false);
	QCOMPARE(id1 > id2, false);
	QCOMPARE(id1 >= id2, false);

	QVERIFY(id1 == id1);
	QCOMPARE(id1 != id1, false);

	QVERIFY(id1 >= id1);
	QCOMPARE(id1 > id1, false);
	QVERIFY(id1 <= id1);
	QCOMPARE(id1 < id1, false);
}

QTEST_MAIN(tst_QDiscordID)

#include "tst_qdiscordid.moc"
