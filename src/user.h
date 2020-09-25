/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#ifndef SPRINGLOBBY_HEADERGUARD_USER_H
#define SPRINGLOBBY_HEADERGUARD_USER_H


/**
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

TODO: remove all wx stuff & merge / move to

lsl/user/user.h

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**/


#include "utils/mixins.h"
#include <lslutils/misc.h>
#include <string>

class IServer;

const unsigned int SYNC_UNKNOWN = 0;
const unsigned int SYNC_SYNCED = 1;
const unsigned int SYNC_UNSYNCED = 2;

//! @brief Struct used to store a client's status.
struct UserStatus {
	enum RankContainer {
		RANK_1,
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8
	};

	bool in_game;
	bool away;
	RankContainer rank;
	bool moderator;
	bool bot;
	UserStatus()
	    : in_game(false)
	    , away(false)
	    , rank(RANK_1)
	    , moderator(false)
	    , bot(false)
	{
	}

	bool operator==(const UserStatus& s) const
	{
		return ((in_game == s.in_game) && (away == s.away) && (rank == s.rank) && (moderator == s.moderator) && (bot == s.bot));
	}

	std::string GetDiffString(const UserStatus& other) const;

	static int ToInt(const UserStatus& us)
	{
		int taus = 0;
		taus += (us.in_game ? 1 : 0);
		taus += (us.away ? 1 : 0) << 1;
		taus += (us.rank % 16) << 2;
		taus += (us.moderator ? 1 : 0) << 5;
		taus += (us.bot ? 1 : 0) << 6;
		return taus;
	}

	// https://springrts.com/dl/LobbyProtocol/ProtocolDescription.html#MYSTATUS:client
	static UserStatus FromInt(const int tas)
	{
		UserStatus stat;
		stat.in_game = (tas >> 0) & 1;
		stat.away = (tas >> 1) & 1;
		stat.rank = (UserStatus::RankContainer)((tas >> 2) % 8);
		stat.moderator = (tas >> 5) & 1;
		stat.bot = (tas >> 6) & 1;
		assert(ToInt(stat) == tas);
		return stat;
	}
};

struct UserPosition {
	int x;
	int y;
	UserPosition()
	    : x(-1)
	    , y(-1)
	{
	}
};

struct UserBattleStatus {
	//!!! when adding something to this struct, also modify User::UpdateBattleStatus() !!
	// total 17 members here
	int team;
	int ally;
	LSL::lslColor colour;
	int color_index;
	int handicap;
	int side;
	unsigned int sync;
	bool spectator;
	bool ready;
	bool isfromdemo;
	UserPosition pos; // for startpos = 4
	// bot-only stuff
	std::string owner;
	std::string aishortname;
	std::string airawname;
	std::string aiversion;
	int aitype;
	// for nat holepunching
	std::string ip;
	unsigned int udpport;
	std::string scriptPassword;
	bool IsBot() const
	{
		return !aishortname.empty();
	}
	UserBattleStatus()
	    : team(0)
	    , ally(0)
	    , colour(0, 0, 0)
	    , color_index(-1)
	    , handicap(0)
	    , side(0)
	    , sync(SYNC_UNKNOWN)
	    , spectator(false)
	    , ready(false)
	    , isfromdemo(false)
	    , aitype(-1)
	    , udpport(0)
	{
	}
	bool operator==(const UserBattleStatus& s) const
	{
		return ((team == s.team) && (colour == s.colour) && (handicap == s.handicap) && (side == s.side) && (sync == s.sync) && (spectator == s.spectator) && (ready == s.ready) && (owner == s.owner) && (aishortname == s.aishortname) && (isfromdemo == s.isfromdemo) && (aitype == s.aitype));
	}
	bool operator!=(const UserBattleStatus& s) const
	{
		return ((team != s.team) || (colour != s.colour) || (handicap != s.handicap) || (side != s.side) || (sync != s.sync) || (spectator != s.spectator) || (ready != s.ready) || (owner != s.owner) || (aishortname != s.aishortname) || (isfromdemo != s.isfromdemo) || (aitype != s.aitype));
	}

	// https://springrts.com/dl/LobbyProtocol/ProtocolDescription.html#MYBATTLESTATUS:client
	static UserBattleStatus FromInt(const int tas)
	{
		UserBattleStatus stat;
		stat.ready = (tas >> 1) & 1;
		stat.team = (tas >> 2) & 15;
		stat.ally = (tas >> 6) & 15;
		stat.spectator = ((tas >> 10) & 1) == 0;
		stat.handicap = ((tas >> 11) & 127) % 101;
		stat.sync = ((tas >> 22) & 3) % 3;
		stat.side = (tas >> 24) & 15;
		return stat;
	}

	static int ToInt(UserBattleStatus bs)
	{
		int ret = 0;			     // b0 is reserved
		ret += (bs.ready ? 1 : 0) << 1;      // b1
		ret += (bs.team % 16) << 2;	  //b2..b5
		ret += (bs.ally % 16) << 6;	  //b6..b9
		ret += (bs.spectator ? 0 : 1) << 10; //b10
		ret += (bs.handicap % 101) << 11;    //b11..b17
		//b18..b21 reserverd
		ret += (bs.sync % 3) << 22;  //b22..b23
		ret += (bs.side % 16) << 24; //b24..b27
		//b28..31 is unused
		return ret;
	}
};

class ChatPanel;
class IBattle;

namespace LSL
{
class lslColor;
}
//! parent class leaving out server related functionality
class CommonUser
{
public:
	CommonUser(const std::string& nick, const std::string& country)
	    : m_nick(std::string(nick))
	    , m_is_bridged(nick.find(':') != std::string::npos)
	    , m_country(std::string(country))
	    , m_id(0)
	    , m_trueSkill(0.0f)
	{
	}

	virtual ~CommonUser()
	{
	}

	const std::string& GetNick() const
	{
		return m_nick;
	}
	virtual void SetNick(const std::string& nick)
	{
		m_nick = nick;
	}
	bool IsBridged() const
	{
		return m_is_bridged;
	}


	const std::string& GetClientAgent() const
	{
		return m_client_agent;
	}
	const std::string& GetCountry() const
	{
		return m_country;
	}
	void SetClientAgent(const std::string& ca)
	{
		m_client_agent = ca;
	}
	virtual void SetCountry(const std::string& country)
	{
		m_country = country;
	}

	int GetID() const
	{
		return m_id;
	}
	void SetID(int id)
	{
		m_id = id;
	}

	double GetTrueSkill() const
	{
		return m_trueSkill;
	}

	void SetTrueSkill(double newSkill)
	{
		m_trueSkill = newSkill;
	}

	UserStatus& Status()
	{
		return m_status;
	}

	UserStatus GetStatus() const
	{
		return m_status;
	}
	virtual void SetStatus(const UserStatus& status);

	UserBattleStatus& BattleStatus()
	{
		return m_bstatus;
	}

	UserBattleStatus GetBattleStatus() const
	{
		return m_bstatus;
	}

	/** Read-only variant of BattleStatus() above.
		 */
	const UserBattleStatus&
	BattleStatus() const
	{
		return m_bstatus;
	}

	//void SetBattleStatus( const UserBattleStatus& status );/// dont use this to avoid overwriting data like ip and port, use following method.
	void UpdateBattleStatus(const UserBattleStatus& status);

	/*	  void SetUserData( void* userdata ) { m_data = userdata; }
		void* GetUserData() { return m_data; }*/

	bool operator==(const CommonUser& other) const
	{
		return (m_nick == other.GetNick());
	}


private:
	std::string m_nick;
	bool m_is_bridged;
	std::string m_client_agent;
	std::string m_country;
	int m_id;
	double m_trueSkill; //This data is not included into UserStatus because it is not part of MYSTATUS or MYBATTLESTATUS commands
	UserStatus m_status;
	UserBattleStatus m_bstatus;

	//void* m_data;
};

//! Class containing all the information about a user
class User : public CommonUser
{
public:
	ChatPanel* panel; //FIXME: privatize

	explicit User(IServer& serv);
	explicit User(const std::string& nick);
	User(const std::string& nick, IServer& serv);
	User(const std::string& nick, const std::string& country, IServer& serv);
	User(const std::string& nick, const std::string& country);
	User();

	virtual ~User();

	// User interface

	IServer& GetServer() const
	{
		return *m_serv;
	}

	void Said(const std::string& message) const;
	void Say(const std::string& message) const;
	void DoAction(const std::string& message) const;

	IBattle* GetBattle() const;
	void SetBattle(IBattle* battle);

	void SendMyUserStatus() const;
	void SetStatus(const UserStatus& status);
	void SetCountry(const std::string& country);

	bool ExecuteSayCommand(const std::string& cmd) const;

	static std::string GetRankName(UserStatus::RankContainer rank);

	float GetBalanceRank();
	UserStatus::RankContainer GetRank() const;
	std::string GetClan();

	bool IsHuman() const;
	bool IsBot() const;

	int GetFlagIconIndex() const
	{
		return m_flagicon_idx;
	}
	int GetRankIconIndex() const
	{
		return m_rankicon_idx;
	}
	int GetStatusIconIndex() const
	{
		return m_statusicon_idx;
	}
	//bool operator< ( const User& other ) const { return m_nick < other.GetNick() ; }
	//User& operator= ( const User& other );

	int GetSideiconIndex() const
	{
		return m_sideicon_idx;
	}
	void SetSideiconIndex(const int idx)
	{
		m_sideicon_idx = idx;
	}

	LSL::lslColor GetColor() const;

private:
	// User variables

	IServer* m_serv;
	IBattle* m_battle;
	int m_flagicon_idx;
	int m_rankicon_idx;
	int m_statusicon_idx;
	int m_sideicon_idx;

	//! copy-semantics?
};

#endif // SPRINGLOBBY_HEADERGUARD_USER_H
