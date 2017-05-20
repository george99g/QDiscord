#include <QtTest>
#include "QDiscord"

class tst_QDiscordChannel : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordChannel();
private slots:
	void testConstruction_null();
	void testDeserialization_privateChannel();
	void testDeserialization_textChannel();
	void testDeserialization_voiceChannel();
	void testSerialization_privateChannel();
	void testSerialization_textChannel();
	void testSerialization_voiceChannel();
	void testOperators();
};

namespace data {
	QJsonObject recipient =
	{
		{"avatar", "51e0235cb2e58f2ce09e72406fe3ccef"},
		{"discriminator", "7480"},
		{"id", "122222222213014222"},
		{"username", "TestBot"}
	};

	QJsonObject privateChannel =
	{
		{"id", "173333333338476533"},
		{"is_private", true},
		{"last_message_id", "247016666766663446"},
		{"recipient", recipient},
		{"type", "text"}
	};


	QJsonObject textChannel =
	{
		{"id", "169867030833333333"},
		{"is_private", false},
		{"last_message_id", "333333333333603755"},
		{"name", "test"},
		{"position", 2},
		{"topic", "Test"},
		{"type", "text"}
	};

	QJsonObject voiceChannel =
	{
		{"bitrate", 64000},
		{"id", "177777777641315777"},
		{"is_private", false},
		{"name", "Test"},
		{"position", 3},
		{"type", "voice"},
		{"user_limit", 0}
	};
}

tst_QDiscordChannel::tst_QDiscordChannel()
{

}

void tst_QDiscordChannel::testConstruction_null()
{
	QDiscordChannel nullChannel;
	QVERIFY(nullChannel.isNull());
	QCOMPARE(static_cast<bool>(nullChannel), false);
}

void tst_QDiscordChannel::testDeserialization_privateChannel()
{
	QDiscordChannel privateChannel(data::privateChannel);
	QVERIFY(privateChannel.isPrivate());
	QCOMPARE(privateChannel.id(), QDiscordID(173333333338476533ULL));
	QCOMPARE(privateChannel.type(), QDiscordChannel::ChannelType::Text);
}

void tst_QDiscordChannel::testDeserialization_textChannel()
{
	QDiscordChannel channel(data::textChannel);
	QVERIFY(channel.isPrivate() == false);
	QCOMPARE(channel.id(), QDiscordID(169867030833333333ULL));
	QCOMPARE(channel.lastMessageId(), QDiscordID(333333333333603755ULL));
	QCOMPARE(channel.name(), QString("test"));
	QCOMPARE(channel.position(), 2);
	QCOMPARE(channel.topic(), QString("Test"));
	QCOMPARE(channel.type(), QDiscordChannel::ChannelType::Text);
}

void tst_QDiscordChannel::testDeserialization_voiceChannel()
{
	QDiscordChannel channel(data::voiceChannel);
	QVERIFY(channel.isPrivate() == false);
	QCOMPARE(channel.id(), QDiscordID(177777777641315777ULL));
	QCOMPARE(channel.name(), QString("Test"));
	QCOMPARE(channel.bitrate(), 64000);
	QCOMPARE(channel.position(), 3);
	QCOMPARE(channel.userLimit(), 0);
	QCOMPARE(channel.type(), QDiscordChannel::ChannelType::Voice);
}

void tst_QDiscordChannel::testSerialization_privateChannel()
{
	QDiscordChannel channel(data::privateChannel);
	QJsonObject recipient =
	{
		{"avatar", "51e0235cb2e58f2ce09e72406fe3ccef"},
		{"discriminator", "7480"},
		{"id", "122222222213014222"},
		{"username", "TestBot"},
		{"bot", false},
		{"mfa_enabled", false}
	};
	QJsonObject output =
	{
		{"id", "173333333338476533"},
		{"is_private", true},
		{"last_message_id", "247016666766663446"},
		{"recipient", recipient},
		{"type", "text"}
	};
	QCOMPARE(channel.serialize(), output);
}

void tst_QDiscordChannel::testSerialization_textChannel()
{
	QDiscordChannel channel(data::textChannel);
	QJsonObject output =
	{
		{"id", "169867030833333333"},
		{"is_private", false},
		{"last_message_id", "333333333333603755"},
		{"name", "test"},
		{"position", 2},
		{"topic", "Test"},
		{"type", "text"}
	};
	QCOMPARE(channel.serialize(), output);
}

void tst_QDiscordChannel::testSerialization_voiceChannel()
{
	QDiscordChannel channel(data::voiceChannel);
	QJsonObject output =
	{
		{"bitrate", 64000},
		{"id", "177777777641315777"},
		{"is_private", false},
		{"name", "Test"},
		{"position", 3},
		{"type", "voice"},
		{"user_limit", 0}
	};
	QCOMPARE(channel.serialize(), output);
}

void tst_QDiscordChannel::testOperators()
{
	QDiscordChannel channel1(data::privateChannel), channel2(data::textChannel);

	QCOMPARE(channel1 < channel2, channel1.id() < channel2.id());
	QCOMPARE(channel1 > channel2, channel1.id() > channel2.id());
	QCOMPARE(channel1 <= channel2, channel1.id() <= channel2.id());
	QCOMPARE(channel1 >= channel2, channel1.id() >= channel2.id());
	QCOMPARE(channel1 == channel2, channel1.id() == channel2.id());
	QCOMPARE(channel1 != channel2, channel1.id() != channel2.id());

	QCOMPARE(channel1 < channel1, channel1.id() < channel1.id());
	QCOMPARE(channel1 > channel1, channel1.id() > channel1.id());
	QCOMPARE(channel1 <= channel1, channel1.id() <= channel1.id());
	QCOMPARE(channel1 >= channel1, channel1.id() >= channel1.id());
	QCOMPARE(channel1 == channel1, channel1.id() == channel1.id());
	QCOMPARE(channel1 != channel1, channel1.id() != channel1.id());
}

QTEST_MAIN(tst_QDiscordChannel)

#include "tst_qdiscordchannel.moc"
