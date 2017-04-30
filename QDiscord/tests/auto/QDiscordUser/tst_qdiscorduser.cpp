#include <QtTest>
#include "QDiscord"

class tst_QDiscordUser: public QObject
{
	Q_OBJECT
public:
	tst_QDiscordUser();
private slots:
	void testConstruction_null();
	void testDeserialization_avatar();
	void testDeserialization_optionals();
	void testDeserialization_fields();
	void testSerialization();
	void testUpdate();
	void testOperators();
	void testMention();
};

namespace data{
	const QJsonObject user1 =
	{
		{"avatar", QJsonValue()},
		{"bot", true},
		{"discriminator", "8701"},
		{"id", "129827149523671712"},
		{"username", "TestBot"}
	};

	const QJsonObject user2 =
	{
		{"avatar", "f2facc666667b92beb581bb98bf69892"},
		{"bot", true},
		{"discriminator", "8701"},
		{"email", "testbot@example.org"},
		{"id", "129865555555576712"},
		{"mfa_enabled", true},
		{"username", "TestBot"},
		{"verified", true}
	};

	const QJsonObject user3 =
	{
		{"avatar", "f2facc666667b92beb581bb98bf69892"},
		{"discriminator", "7525"},
		{"id", "155954930191040513"},
		{"username", "TestBot"}
	};
}

tst_QDiscordUser::tst_QDiscordUser()
{

}

void tst_QDiscordUser::testConstruction_null()
{
	QDiscordUser user;
	QVERIFY(user.isNull());
	QCOMPARE(static_cast<bool>(user), false);
}

void tst_QDiscordUser::testDeserialization_avatar()
{
	QDiscordUser noAvatar(data::user1);
	QVERIFY(noAvatar.avatar().isEmpty());

	QDiscordUser withAvatar(data::user2);
	QCOMPARE(withAvatar.avatar(), QString("f2facc666667b92beb581bb98bf69892"));
}

void tst_QDiscordUser::testDeserialization_optionals()
{
	QDiscordUser noOptionals(data::user1);
	QCOMPARE(noOptionals.email().has_value(), false);
	QCOMPARE(noOptionals.verified().has_value(), false);

	QDiscordUser withOptionals(data::user2);
	QCOMPARE(withOptionals.email().has_value(), true);
	QCOMPARE(withOptionals.verified().has_value(), true);
	QCOMPARE(withOptionals.email().value(), QString("testbot@example.org"));
	QCOMPARE(withOptionals.verified().value(), true);
}

void tst_QDiscordUser::testDeserialization_fields()
{
	QDiscordUser user1(data::user1);
	QCOMPARE(user1.avatar(), QString());
	QCOMPARE(user1.bot(), true);
	QCOMPARE(user1.discriminator(), QDiscordDiscriminator(8701));
	QCOMPARE(user1.id(), QDiscordID(129827149523671712ULL));
	QCOMPARE(user1.username(), QString("TestBot"));
	QCOMPARE(user1.email().has_value(), false);
	QCOMPARE(user1.verified().has_value(), false);
	QCOMPARE(user1.mfaEnabled(), false);

	QDiscordUser user2(data::user2);
	QCOMPARE(user2.avatar(), QString("f2facc666667b92beb581bb98bf69892"));
	QCOMPARE(user2.bot(), true);
	QCOMPARE(user2.discriminator(), QDiscordDiscriminator(8701));
	QCOMPARE(user2.id(), QDiscordID(129865555555576712ULL));
	QCOMPARE(user2.username(), QString("TestBot"));
	QCOMPARE(user2.email().has_value(), true);
	QCOMPARE(user2.email().value(), QString("testbot@example.org"));
	QCOMPARE(user2.verified().has_value(), true);
	QCOMPARE(user2.verified().value(), true);
	QCOMPARE(user2.mfaEnabled(), true);

	QDiscordUser user3(data::user3);
	QCOMPARE(user3.avatar(), QString("f2facc666667b92beb581bb98bf69892"));
	QCOMPARE(user3.bot(), false);
	QCOMPARE(user3.discriminator(), QDiscordDiscriminator(7525));
	QCOMPARE(user3.id(), QDiscordID(155954930191040513ULL));
	QCOMPARE(user3.username(), QString("TestBot"));
	QCOMPARE(user3.email().has_value(), false);
	QCOMPARE(user3.verified().has_value(), false);
	QCOMPARE(user3.mfaEnabled(), false);
}

void tst_QDiscordUser::testSerialization()
{
	QDiscordUser user1(data::user1);
	QJsonObject output1 =
	{
		{"avatar", QJsonValue()},
		{"bot", true},
		{"discriminator", "8701"},
		{"id", "129827149523671712"},
		{"username", "TestBot"},
		{"mfa_enabled", false}
	};
	QCOMPARE(user1.serialize(), output1);

	QDiscordUser user2(data::user2);
	QJsonObject output2 =
	{
		{"avatar", "f2facc666667b92beb581bb98bf69892"},
		{"bot", true},
		{"discriminator", "8701"},
		{"email", "testbot@example.org"},
		{"id", "129865555555576712"},
		{"mfa_enabled", true},
		{"username", "TestBot"},
		{"verified", true}
	};
	QCOMPARE(user2.serialize(), output2);

	QDiscordUser user3(data::user3);
	QJsonObject output3 =
	{
		{"avatar", "f2facc666667b92beb581bb98bf69892"},
		{"discriminator", "7525"},
		{"id", "155954930191040513"},
		{"username", "TestBot"},
		{"bot", false},
		{"mfa_enabled", false}
	};
	QCOMPARE(user3.serialize(), output3);
}

void tst_QDiscordUser::testUpdate()
{
	QDiscordUser user;
	user.update(data::user2);
	QCOMPARE(user.avatar(), QString("f2facc666667b92beb581bb98bf69892"));
	QCOMPARE(user.bot(), true);
	QCOMPARE(user.discriminator(), QDiscordDiscriminator(8701));
	QCOMPARE(user.id(), QDiscordID(129865555555576712ULL));
	QCOMPARE(user.username(), QString("TestBot"));
	QCOMPARE(user.email().has_value(), true);
	QCOMPARE(user.email().value(), QString("testbot@example.org"));
	QCOMPARE(user.verified().has_value(), true);
	QCOMPARE(user.verified().value(), true);
	QCOMPARE(user.mfaEnabled(), true);
}

void tst_QDiscordUser::testOperators()
{
	QDiscordUser nullUser;
	QDiscordUser user1(data::user1);
	QDiscordUser user2(data::user2);
	QDiscordUser user3(data::user3);

	// A null user should never be equal to itself
	QVERIFY(nullUser != nullUser);
	QCOMPARE(nullUser == nullUser, false);

	QVERIFY(user1 != nullUser);
	QCOMPARE(user1 == nullUser, false);
	QVERIFY(user2 != nullUser);
	QCOMPARE(user2 == nullUser, false);
	QVERIFY(user3 != nullUser);
	QCOMPARE(user3 == nullUser, false);

	// A null user should be smaller than anything, due to being 0 internally
	QVERIFY(user1 > nullUser);
	QVERIFY(user2 > nullUser);
	QVERIFY(user3 > nullUser);
	QVERIFY(user1 >= nullUser);
	QVERIFY(user2 >= nullUser);
	QVERIFY(user3 >= nullUser);
	QCOMPARE(user1 < nullUser, false);
	QCOMPARE(user2 < nullUser, false);
	QCOMPARE(user3 < nullUser, false);
	QCOMPARE(user1 <= nullUser, false);
	QCOMPARE(user2 <= nullUser, false);
	QCOMPARE(user3 <= nullUser, false);

	// A null user should never be equal to anything
	QVERIFY(nullUser != user1);
	QCOMPARE(nullUser == user1, false);
	QVERIFY(nullUser != user2);
	QCOMPARE(nullUser == user2, false);
	QVERIFY(nullUser != user3);
	QCOMPARE(nullUser == user3, false);

	// The comparisons should be the same both ways
	QVERIFY(nullUser < user1);
	QVERIFY(nullUser < user2);
	QVERIFY(nullUser < user3);
	QVERIFY(nullUser <= user1);
	QVERIFY(nullUser <= user2);
	QVERIFY(nullUser <= user3);
	QCOMPARE(nullUser > user1, false);
	QCOMPARE(nullUser > user2, false);
	QCOMPARE(nullUser > user3, false);
	QCOMPARE(nullUser >= user1, false);
	QCOMPARE(nullUser >= user2, false);
	QCOMPARE(nullUser >= user3, false);

	// Users should be sorted by comparing their IDs
	QVERIFY(user3 > user2);
	QVERIFY(user3 >= user2);
	QVERIFY(user2 > user1);
	QVERIFY(user2 >= user1);
	QCOMPARE(user2 > user3, false);
	QCOMPARE(user2 >= user3, false);
	QCOMPARE(user1 > user2, false);
	QCOMPARE(user1 >= user2, false);

	// Two users with the same ID should be equal
	QVERIFY(user1 == user1);
	QCOMPARE(user1 != user1, false);

	// Even when the operation is less than or euqals or more than or equals
	QVERIFY(user1 >= user1);
	QCOMPARE(user1 > user1, false);
	QVERIFY(user1 <= user1);
	QCOMPARE(user1 < user1, false);
}

void tst_QDiscordUser::testMention()
{
	QDiscordUser nullUser;
	QCOMPARE(nullUser.mention(), QString("<@invalid ID>"));

	QDiscordUser user(data::user1);
	QCOMPARE(user.mention(), QString("<@129827149523671712>"));
}

QTEST_MAIN(tst_QDiscordUser)

#include "tst_qdiscorduser.moc"
