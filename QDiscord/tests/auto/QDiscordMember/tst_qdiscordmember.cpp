#include <QtTest>
#include "QDiscord"

class tst_QDiscordMember : public QObject
{
	Q_OBJECT
public:
	tst_QDiscordMember();
private slots:
	void testConstruction_null();
	void testDeserialization_fields();
	void testSerialization();
	void testUpdate();
	void testOperators();
	void testMention();
private:
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
		{"bot", false},
		{"mfa_enabled", false},
		{"avatar", QJsonValue()}
	};

	const QJsonObject user3 =
	{
		{"id", "155954930191040513"},
		{"discriminator", "7480"},
		{"username", "TestBot"},
		{"bot", true},
		{"mfa_enabled", true},
		{"avatar", QJsonValue()}
	};

	const QJsonObject member1 =
	{
		{"deaf", false},
		{"joined_at", "2017-04-30T11:46:31.837710+00:00"},
		{"mute", false},
		{"nick", "testbot"},
		{"roles", QJsonArray({"234244444451867392"})},
		{"user", user1}
	};

	const QJsonObject member2 =
	{
		{"deaf", true},
		{"joined_at", "2017-04-30T11:46:31.837710+00:00"},
		{"mute", true},
		{"nick", QJsonValue()},
		{"roles", QJsonArray({"234244444451867392"})},
		{"user", user2}
	};

	const QJsonObject member3 =
	{
		{"deaf", false},
		{"joined_at", "2017-04-30T11:46:31.837710+00:00"},
		{"mute", false},
		{"nick", QJsonValue()},
		{"roles", QJsonArray({"234244444451867392"})},
		{"user", user3}
	};

	const QJsonObject guild =
	{
		{"id", "174444440191040513"}
	};
}

tst_QDiscordMember::tst_QDiscordMember()
{

}

void tst_QDiscordMember::testConstruction_null()
{
	QDiscordMember member;
	QVERIFY(member.isNull());
	QCOMPARE(static_cast<bool>(member), false);
}

void tst_QDiscordMember::testDeserialization_fields()
{
	QDiscordMember member1(data::member1);
	QCOMPARE(member1.deaf(), false);
	QCOMPARE(member1.mute(), false);
	QCOMPARE(member1.nickname().has_value(), true);
	QCOMPARE(member1.nickname().value(), QString("testbot"));
	QCOMPARE(
				member1.joinedAt(),
				QDateTime::fromString("2017-04-30T11:46:31.837710+00:00",
									  Qt::ISODateWithMs)
				);

	QDiscordMember member2(data::member2);
	QCOMPARE(member2.deaf(), true);
	QCOMPARE(member2.mute(), true);
	QCOMPARE(member2.nickname().has_value(), false);
}

void tst_QDiscordMember::testSerialization()
{
	QDiscordMember member1(data::member1);
	QJsonObject output1 =
	{
		{"deaf", false},
		{"joined_at", "2017-04-30T11:46:31.838Z"},
		{"mute", false},
		{"nick", "testbot"},
		//{"roles", QJsonArray({"234244444451867392"})},
		{"user", data::user1}
	};
	QCOMPARE(member1.serialize(), output1);

	QDiscordMember member2(data::member2);
	QJsonObject output2 =
	{
		{"deaf", true},
		{"joined_at", "2017-04-30T11:46:31.838Z"},//This shouldn't be happening
		{"mute", true},
		{"nick", QJsonValue()},
		//{"roles", QJsonArray({"234244444451867392"})},
		{"user", QJsonObject({
			 {"id", "129865555555576712"},
			 {"discriminator", "7480"},
			 {"username", "TestBot"},
			 {"avatar", QJsonValue()}
		 })}
	};
	QCOMPARE(member2.serialize(), output2);

	QDiscordMember member3(data::member3);
	QJsonObject output3 =
	{
		{"deaf", false},
		{"joined_at", "2017-04-30T11:46:31.838Z"},
		{"mute", false},
		{"nick", QJsonValue()},
		//{"roles", QJsonArray({"234244444451867392"})},
		{"user", data::user3}
	};
	QCOMPARE(member3.serialize(), output3);
}

void tst_QDiscordMember::testUpdate()
{
	QDiscordMember member1;
	member1.update(data::member3);
	QCOMPARE(member1.deaf(), false);
	QCOMPARE(member1.mute(), false);
	QCOMPARE(member1.nickname().has_value(), false);
	QCOMPARE(
				member1.joinedAt(),
				QDateTime::fromString("2017-04-30T11:46:31.837710+00:00",
									  Qt::ISODateWithMs)
				);

	QDiscordMember member2;
	member2.update(data::member1);
	QCOMPARE(member2.nickname().has_value(), true);
	QCOMPARE(member2.nickname().value(), QString("testbot"));
}

void tst_QDiscordMember::testOperators()
{
	QSharedPointer<QDiscordGuild> guild = QDiscordGuild::fromJson(data::guild);
	QDiscordMember nullMember;
	QDiscordMember member1(data::member1);
	member1.setGuild(guild);
	QDiscordMember member2(data::member2);
	member2.setGuild(guild);
	QDiscordMember member3(data::member2);

	QVERIFY(nullMember != nullMember);
	QVERIFY(nullMember != member1);
	QVERIFY(nullMember != member2);
	QVERIFY(nullMember != member3);
	QVERIFY(member1 != member2);
	QVERIFY(member1 != member3);
	QVERIFY(member3 != member3);
	QVERIFY(member1 == member1);
}

void tst_QDiscordMember::testMention()
{
	QDiscordMember member(data::member1);
	QCOMPARE(member.mentionUsername(), member.user().mention());
	QCOMPARE(member.mentionNickname(), QString("<@!129827149523671712>"));

	QDiscordMember nullMember;
	QCOMPARE(nullMember.mentionNickname(), QString("<@!invalid ID>"));
}

QTEST_MAIN(tst_QDiscordMember)

#include "tst_qdiscordmember.moc"
