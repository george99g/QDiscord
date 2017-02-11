#include <QtTest>
#include "../../../src/QDiscord"

class tst_QDiscordChannel : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordChannel();
private slots:
	void testConstructor_data();
	void testConstructor();
private:
	QJsonObject _nullChannel;
	QJsonObject _testChannel;
	QJsonObject _voiceChannel;
	QJsonObject _privateChannel;
	QSharedPointer<QDiscordGuild> _guild;
};

tst_QDiscordChannel::tst_QDiscordChannel()
:_nullChannel(),
  _testChannel({
			{"id", "74711963333122947"},
			{"is_private", false},
			{"last_message_id", "74711923333222247"},
			{"last_pin_timestamp", "2017-01-07T00:47:14.897527+00:00"},
			{"name", "test_channel"},
			{"position", 3},
			{"topic", "A channel to test them all."},
			{"type", "text"},
	  }),
  _voiceChannel({
			{"bitrate", 64000},
			{"id", "74721463333122947"},
			{"is_private", false},
			{"name", "test_channel"},
			{"position", 2},
			{"type", "voice"},
			{"user_limit", 0}
	  }),
  _privateChannel({
			{"id", "14721463333122947"},
			{"is_private", true},
			{"recipient", QJsonObject({{"id", "12721463333526927"}})},
			{"type", "text"},
	  }),
  _guild(QDiscordGuild::create({{"id", "74721953363722943"}}))
{

}

void tst_QDiscordChannel::testConstructor_data()
{
	QTest::addColumn<QJsonObject>("inputObject");
	QTest::addColumn<QString>("output_id");
	QTest::addColumn<bool>("output_isPrivate");
	QTest::addColumn<QString>("output_lastMessageId");
	QTest::addColumn<QDateTime>("output_lastPinTimestamp");
	QTest::addColumn<QString>("output_name");
	QTest::addColumn<int>("output_position");
	QTest::addColumn<QString>("output_topic");
	QTest::addColumn<QDiscordChannel::ChannelType>("output_type");
	QTest::addColumn<int>("output_bitrate");
	QTest::addColumn<int>("output_userLimit");
	QTest::addColumn<QString>("output_recipientId");

	QTest::newRow("nullChannel")
	<< _nullChannel
	<< "0"
	<< false
	<< "0"
	<< QDateTime()
	<< QString()
	<< -1
	<< QString()
	<< QDiscordChannel::ChannelType::UnknownType
	<< -1
	<< -1
	<< QString();

	QTest::newRow("testChannel")
	<< _testChannel
	<< "74711963333122947"
	<< false
	<< "74711923333222247"
	<< QDateTime::fromString("2017-01-07T00:47:14.897527+00:00", Qt::ISODate)
	<< "test_channel"
	<< 3
	<< "A channel to test them all."
	<< QDiscordChannel::ChannelType::Text
	<< -1
	<< -1
	<< QString();

	QTest::newRow("voiceChannel")
	<< _voiceChannel
	<< "74721463333122947"
	<< false
	<< "0"
	<< QDateTime()
	<< "test_channel"
	<< 2
	<< QString()
	<< QDiscordChannel::ChannelType::Voice
	<< 64000
	<< 0
	<< QString();

	QTest::newRow("nullChannel")
	<< _privateChannel
	<< "14721463333122947"
	<< true
	<< "0"
	<< QDateTime()
	<< QString()
	<< -1
	<< QString()
	<< QDiscordChannel::ChannelType::Text
	<< -1
	<< -1
	<< "12721463333526927";
}

void tst_QDiscordChannel::testConstructor()
{
	QFETCH(QJsonObject, inputObject);
	QFETCH(QString, output_id);
	QFETCH(bool, output_isPrivate);
	QFETCH(QString, output_lastMessageId);
	QFETCH(QDateTime, output_lastPinTimestamp);
	QFETCH(QString, output_name);
	QFETCH(int, output_position);
	QFETCH(QString, output_topic);
	QFETCH(QDiscordChannel::ChannelType, output_type);
	QFETCH(int, output_bitrate);
	QFETCH(int, output_userLimit);
	QFETCH(QString, output_recipientId);

	QBENCHMARK
	{
		QDiscordChannel channel(inputObject, QWeakPointer<QDiscordGuild>());
		Q_UNUSED(channel);
	}

	QDiscordChannel channel(inputObject, QWeakPointer<QDiscordGuild>());

	QCOMPARE(channel.id().toString(), output_id);
	QCOMPARE(channel.isPrivate(), output_isPrivate);
	QCOMPARE(channel.lastMessageId().toString(), output_lastMessageId);
	QCOMPARE(channel.lastPinTimestamp(), output_lastPinTimestamp);
	QCOMPARE(channel.name(), output_name);
	QCOMPARE(channel.position(), output_position);
	QCOMPARE(channel.topic(), output_topic);
	QCOMPARE(channel.type(), output_type);
	QCOMPARE(channel.bitrate(), output_bitrate);
	QCOMPARE(channel.userLimit(), output_userLimit);
	if(output_recipientId != QString())
		QCOMPARE(channel.recipient()->id().toString(), output_recipientId);
}

QTEST_MAIN(tst_QDiscordChannel)

#include "tst_qdiscordchannel.moc"
