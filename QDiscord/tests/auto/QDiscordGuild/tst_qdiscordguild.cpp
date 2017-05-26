#include <QtTest>
#include "QDiscord"

class tst_QDiscordGuild : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordGuild();
private slots:
	void testConstruction_null();
	void testConstruction_fields();
	void testSerialization();
	void testOperators();
};

namespace data {
	const QJsonObject user1 =
	{
		{"id", "129827149523671712"},
		{"discriminator", "7480"},
		{"username", "TestBot"},
		{"avatar", QJsonValue()}
	};

	const QJsonObject user2 =
	{
		{"id", "129865555555576712"},
		{"discriminator", "7480"},
		{"username", "TestBot"},
		{"bot", true},
		{"mfa_enabled", true},
		{"avatar", QJsonValue()}
	};

	const QJsonObject member1 =
	{
		{"deaf", false},
		{"joined_at", "2014-03-31T18:56:51.227Z"},
		{"mute", false},
		{"nick", "testbot"},
		{"user", user1}
	};

	const QJsonObject member2 =
	{
		{"deaf", true},
		{"joined_at", "2017-04-30T11:46:31.838Z"},
		{"mute", true},
		{"nick", QJsonValue()},
		{"user", user2}
	};

	const QJsonObject textChannel =
	{
		{"id", "169867030833333333"},
		{"is_private", false},
		{"last_message_id", "333333333333603755"},
		{"name", "test"},
		{"position", 2},
		{"topic", "Test"},
		{"type", "text"}
	};

	const QJsonObject voiceChannel =
	{
		{"bitrate", 64000},
		{"id", "177777777641315777"},
		{"is_private", false},
		{"name", "Test"},
		{"position", 3},
		{"type", "voice"},
		{"user_limit", 0}
	};

	const QJsonObject unavailableGuild = {
		{"id", "155954930191040513"},
		{"unavailable", true}
	};

	const QJsonObject guild1 = {
		{"id", "129827149523671712"},
		{"unavailable", false},
		{"afk_channel_id", QJsonValue()},
		{"afk_timeout", 300},
		{"embed_enabled", true},
		{"embed_channel_id", "169867030833333333"},
		{"application_id", QJsonValue()},
		{"channels", QJsonArray({textChannel})},
		{"default_message_notifications", 1},
		{"explicit_content_filter", 2},
		{"features", QJsonArray({"EXAMPLE_FEATURE"})},
		{"icon", "cc777ccc333777aaabbcc43d319b98c9"},
		{"joined_at", "2014-03-31T18:56:51.227317+00:00"},
		{"large", true},
		{"member_count", 1},
		{"members", QJsonArray({member1})},
		{"mfa_level", 1},
		{"name", "Test server"},
		{"owner_id", "129827149523671712"},
		{"region", "us-west"},
		{"splash", QJsonValue()},
		{"verification_level", 3}
	};

	const QJsonObject guild2 = {
		{"id", "129865555555576712"},
		{"unavailable", false},
		{"afk_channel_id", "169867030833333333"},
		{"afk_timeout", 400},
		{"embed_enabled", false},
		{"embed_channel_id", "177777777641315777"},
		{"application_id", "155954930191040513"},
		{"channels", QJsonArray({voiceChannel})},
		{"default_message_notifications", 0},
		{"explicit_content_filter", 0},
		{"features", QJsonArray()},
		{"icon", QJsonValue()},
		{"joined_at", "2015-03-31T18:56:51.227317+00:00"},
		{"large", false},
		{"member_count", 1},
		{"members", QJsonArray({member2})},
		{"mfa_level", 0},
		{"name", "Test server 2"},
		{"owner_id", "129865555555576712"},
		{"region", "us-east"},
		{"splash", "cc777ccc333777aaabbcc43d319b98c9"},
		{"verification_level", 0}
	};
}

tst_QDiscordGuild::tst_QDiscordGuild()
{}

void tst_QDiscordGuild::testConstruction_null()
{
	QDiscordGuild guild;
	QVERIFY(guild.isNull());
	QCOMPARE(static_cast<bool>(guild), false);
}

void tst_QDiscordGuild::testConstruction_fields()
{
	QSharedPointer<QDiscordGuild> unavailableGuild =
			QDiscordGuild::fromJson(data::unavailableGuild);
	QCOMPARE(unavailableGuild->id(), QDiscordID(155954930191040513ULL));
	QVERIFY(unavailableGuild->unavailable());
	QCOMPARE(unavailableGuild->afkTimeout(), -1);
	QCOMPARE(unavailableGuild->embedEnabled(), false);
	QCOMPARE(unavailableGuild->verificationLevel(),
			 QDiscordGuild::VerificationLevel::Unknown);
	QCOMPARE(unavailableGuild->defaultMessageNotifications(),
			 QDiscordGuild::NotificationLevel::Unknown);
	QCOMPARE(unavailableGuild->explicitContentFilter(),
			 QDiscordGuild::ExplicitContentFilterLevel::Unknown);
	QCOMPARE(unavailableGuild->mfaLevel(), -1);
	QCOMPARE(unavailableGuild->memberCount(), -1);

	QSharedPointer<QDiscordGuild> guild1 =
			QDiscordGuild::fromJson(data::guild1);
	QCOMPARE(guild1->id(), QDiscordID(129827149523671712ULL));
	QVERIFY(guild1->afkChannelId().isNull());
	QCOMPARE(guild1->afkTimeout(), 300);
	QCOMPARE(guild1->embedEnabled(), true);
	QCOMPARE(guild1->embedChannelId(), QDiscordID(169867030833333333ULL));
	QVERIFY(guild1->applicationId().isNull());
	QCOMPARE(guild1->channels().length(), 1);
	QCOMPARE(guild1->channels()[0]->id(), QDiscordID(169867030833333333ULL));
	QCOMPARE(guild1->channels()[0]->type(), QDiscordChannel::ChannelType::Text);
	QCOMPARE(guild1->defaultMessageNotifications(),
			 QDiscordGuild::NotificationLevel::OnlyMentions);
	QCOMPARE(guild1->explicitContentFilter(),
			 QDiscordGuild::ExplicitContentFilterLevel::All);
	QCOMPARE(guild1->features().length(), 1);
	QCOMPARE(guild1->features()[0], QString("EXAMPLE_FEATURE"));
	QCOMPARE(guild1->icon(), QString("cc777ccc333777aaabbcc43d319b98c9"));
	//Skipping `joined_at` check
	QCOMPARE(guild1->large(), true);
	QCOMPARE(guild1->memberCount(), 1);
	QCOMPARE(guild1->members().length(), 1);
	QCOMPARE(guild1->members()[0]->user().id(),
			QDiscordID(129827149523671712ULL));
	QCOMPARE(guild1->mfaLevel(), 1);
	QCOMPARE(guild1->name(), QString("Test server"));
	QCOMPARE(guild1->ownerId(), QDiscordID(129827149523671712ULL));
	QCOMPARE(guild1->region(), QString("us-west"));
	QVERIFY(guild1->splash().isEmpty());
	QCOMPARE(guild1->verificationLevel(),
			 QDiscordGuild::VerificationLevel::High);

	QSharedPointer<QDiscordGuild> guild2 =
			QDiscordGuild::fromJson(data::guild2);
	QCOMPARE(guild2->id(), QDiscordID(129865555555576712ULL));
	QCOMPARE(guild2->afkChannelId(), QDiscordID(169867030833333333ULL));
	QCOMPARE(guild2->afkTimeout(), 400);
	QCOMPARE(guild2->embedEnabled(), false);
	QCOMPARE(guild2->embedChannelId(), QDiscordID(177777777641315777ULL));
	QCOMPARE(guild2->applicationId(), QDiscordID(155954930191040513ULL));
	QCOMPARE(guild2->channels().length(), 1);
	QCOMPARE(guild2->channels()[0]->id(), QDiscordID(177777777641315777ULL));
	QCOMPARE(guild2->channels()[0]->type(),
			QDiscordChannel::ChannelType::Voice);
	QCOMPARE(guild2->defaultMessageNotifications(),
			 QDiscordGuild::NotificationLevel::AllMessages);
	QCOMPARE(guild2->explicitContentFilter(),
			 QDiscordGuild::ExplicitContentFilterLevel::None);
	QCOMPARE(guild2->features().length(), 0);
	QVERIFY(guild2->icon().isEmpty());
	//Skipping `joined_at` check
	QCOMPARE(guild2->large(), false);
	QCOMPARE(guild2->memberCount(), 1);
	QCOMPARE(guild2->members().length(), 1);
	QCOMPARE(guild2->members()[0]->user().id(),
			QDiscordID(129865555555576712ULL));
	QCOMPARE(guild2->mfaLevel(), 0);
	QCOMPARE(guild2->name(), QString("Test server 2"));
	QCOMPARE(guild2->ownerId(), QDiscordID(129865555555576712ULL));
	QCOMPARE(guild2->region(), QString("us-east"));
	QCOMPARE(guild2->splash(), QString("cc777ccc333777aaabbcc43d319b98c9"));
	QCOMPARE(guild2->verificationLevel(),
			 QDiscordGuild::VerificationLevel::None);
}

void tst_QDiscordGuild::testSerialization()
{
	QSharedPointer<QDiscordGuild> unavailableGuild =
			QDiscordGuild::fromJson(data::unavailableGuild);
	QCOMPARE(unavailableGuild->serialize(), data::unavailableGuild);

	QSharedPointer<QDiscordGuild> guild1 =
			QDiscordGuild::fromJson(data::guild1);
	QJsonObject output1 =
	{
		{"id", "129827149523671712"},
		{"unavailable", false},
		{"afk_channel_id", QJsonValue()},
		{"afk_timeout", 300},
		{"embed_enabled", true},
		{"embed_channel_id", "169867030833333333"},
		{"application_id", QJsonValue()},
		{"channels", QJsonArray({data::textChannel})},
		{"default_message_notifications", 1},
		{"explicit_content_filter", 2},
		{"features", QJsonArray({"EXAMPLE_FEATURE"})},
		{"icon", "cc777ccc333777aaabbcc43d319b98c9"},
		{"joined_at", "2014-03-31T18:56:51.227Z"}, //Still broken
		{"large", true},
		{"member_count", 1},
		{"members", QJsonArray({data::member1})},
		{"mfa_level", 1},
		{"name", "Test server"},
		{"owner_id", "129827149523671712"},
		{"region", "us-west"},
		{"splash", QJsonValue()},
		{"verification_level", 3}
	};
	QCOMPARE(guild1->serialize(), output1);

	QSharedPointer<QDiscordGuild> guild2 =
			QDiscordGuild::fromJson(data::guild2);
	QJsonObject output2 =
	{
		{"id", "129865555555576712"},
		{"unavailable", false},
		{"afk_channel_id", "169867030833333333"},
		{"afk_timeout", 400},
		{"embed_enabled", false},
		{"embed_channel_id", "177777777641315777"},
		{"application_id", "155954930191040513"},
		{"channels", QJsonArray({data::voiceChannel})},
		{"default_message_notifications", 0},
		{"explicit_content_filter", 0},
		{"features", QJsonArray()},
		{"icon", QJsonValue()},
		{"joined_at", "2015-03-31T18:56:51.227Z"}, //Still broken
		{"large", false},
		{"member_count", 1},
		{"members", QJsonArray({data::member2})},
		{"mfa_level", 0},
		{"name", "Test server 2"},
		{"owner_id", "129865555555576712"},
		{"region", "us-east"},
		{"splash", "cc777ccc333777aaabbcc43d319b98c9"},
		{"verification_level", 0}
	};
	QCOMPARE(guild2->serialize(), output2);
}

void tst_QDiscordGuild::testOperators()
{
	QSharedPointer<QDiscordGuild> guild1 =
			QDiscordGuild::fromJson(data::guild1);
	QSharedPointer<QDiscordGuild> guild2 =
			QDiscordGuild::fromJson(data::guild2);

	QCOMPARE(*guild1 <  *guild2, guild1->id() <  guild2->id());
	QCOMPARE(*guild1 <= *guild2, guild1->id() <= guild2->id());
	QCOMPARE(*guild1 >  *guild2, guild1->id() >  guild2->id());
	QCOMPARE(*guild1 >= *guild2, guild1->id() >= guild2->id());
	QCOMPARE(*guild1 == *guild2, guild1->id() == guild2->id());
	QCOMPARE(*guild1 != *guild2, guild1->id() != guild2->id());
}

QTEST_MAIN(tst_QDiscordGuild)

#include "tst_qdiscordguild.moc"
