#include <QtTest>
#include "QDiscord"

class tst_QDiscordMessage : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordMessage();
private slots:
	void testConstruction_null();
	void testDeserialization_fields();
	void testSerialization();
	void testOperators();
private:
};

namespace data {
	const QJsonObject author =
	{
		{"id", "129827149523671712"},
		{"discriminator", "7480"},
		{"username", "TestBot"},
		{"avatar", QJsonValue()}
	};
	const QJsonObject message1 =
	{
		{"author", author},
		{"channel_id", "200000000025117696"},
		{"content", "Test."},
		{"id", "274444499999953408"},
		{"mention_everyone", false},
		{"mentions", QJsonArray()},
		{"nonce", QJsonValue()},
		{"pinned", false},
		{"timestamp", "2017-01-28T17:18:18.077000+00:00"},
		{"edited_timestamp", QJsonValue()},
		{"tts", false}
	};
	const QJsonObject message2 =
	{
		{"author", author},
		{"channel_id", "200000000025117696"},
		{"content", "Test2."},
		{"id", "374444499999953408"},
		{"mention_everyone", true},
		{"mentions", QJsonArray()},
		{"nonce", QJsonValue()},
		{"pinned", true},
		{"timestamp", "2017-01-28T17:18:18.077000+00:00"},
		{"edited_timestamp", "2017-01-28T17:30:10.077000+00:00"},
		{"tts", true}
	};
}

tst_QDiscordMessage::tst_QDiscordMessage()
{

}

void tst_QDiscordMessage::testConstruction_null()
{
	QDiscordMessage message;
	QVERIFY(message.isNull());
	QCOMPARE(static_cast<bool>(message), false);
}

void tst_QDiscordMessage::testDeserialization_fields()
{
	QDiscordMessage message(data::message1);
	QCOMPARE(message.channelId(), QDiscordID(200000000025117696ULL));
	QCOMPARE(message.content(), QString("Test."));
	QCOMPARE(message.id(), QDiscordID(274444499999953408ULL));
	QCOMPARE(message.mentionEveryone(), false);
	QCOMPARE(message.mentions(), QList<QDiscordUser>());
	QCOMPARE(message.nonce().isNull(), true);
	QCOMPARE(message.pinned(), false);
	//Skipping timestamp check
	QCOMPARE(message.editedTimestamp().has_value(), false);
	QCOMPARE(message.tts(), false);

	QDiscordMessage message2(data::message2);
	QCOMPARE(message2.channelId(), QDiscordID(200000000025117696ULL));
	QCOMPARE(message2.content(), QString("Test2."));
	QCOMPARE(message2.id(), QDiscordID(374444499999953408ULL));
	QCOMPARE(message2.mentionEveryone(), true);
	QCOMPARE(message2.mentions(), QList<QDiscordUser>());
	QCOMPARE(message2.nonce().value(), QDiscordID().value());
	QCOMPARE(message2.pinned(), true);
	//Skipping timestamp check
	QCOMPARE(message2.editedTimestamp().has_value(), true);
	//Skipping edited_timestamp check
	QCOMPARE(message2.tts(), true);
}

void tst_QDiscordMessage::testSerialization()
{
	QDiscordMessage message1(data::message1);
	QJsonObject output =
	{
		{"author", data::author},
		{"channel_id", "200000000025117696"},
		{"content", "Test."},
		{"id", "274444499999953408"},
		{"mention_everyone", false},
		{"mentions", QJsonArray()},
		{"nonce", QJsonValue()},
		{"pinned", false},
		{"timestamp", "2017-01-28T17:18:18.077Z"}, //This is still broken
		{"edited_timestamp", QJsonValue()},
		{"tts", false}
	};
	QCOMPARE(message1.serialize(), output);

	QDiscordMessage message2(data::message2);
	QJsonObject output2 =
	{
		{"author", data::author},
		{"channel_id", "200000000025117696"},
		{"content", "Test2."},
		{"id", "374444499999953408"},
		{"mention_everyone", true},
		{"mentions", QJsonArray()},
		{"nonce", QJsonValue()},
		{"pinned", true},
		{"timestamp", "2017-01-28T17:18:18.077Z"},
		{"edited_timestamp", "2017-01-28T17:30:10.077Z"},
		{"tts", true}
	};
	QCOMPARE(message2.serialize(), output2);
}

void tst_QDiscordMessage::testOperators()
{
	QDiscordMessage message1(data::message1);
	QDiscordMessage message2(data::message2);

	QCOMPARE(message1 <  message2, message1.id() <  message2.id());
	QCOMPARE(message1 <= message2, message1.id() <= message2.id());
	QCOMPARE(message1 >  message2, message1.id() >  message2.id());
	QCOMPARE(message1 >= message2, message1.id() >= message2.id());
	QCOMPARE(message1 == message2, message1.id() == message2.id());
	QCOMPARE(message1 != message2, message1.id() != message2.id());
}

QTEST_MAIN(tst_QDiscordMessage)

#include "tst_qdiscordmessage.moc"
