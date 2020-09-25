/* This file is part of the Springlobby (GPL v2 or later), see COPYING */
#include "offlineserver.h"

#include <wx/log.h>

#include "serverevents.h"
#include "utils/conversion.h"
#include "utils/tasutil.h"

OfflineServer::OfflineServer()
    : TASServer::TASServer()
{
	m_se = new ServerEvents(*this);
}

OfflineServer::~OfflineServer()
{
	delete m_se;
	m_se = NULL;
}

void OfflineServer::Connect(const ServerLoginInfo& info)
{
	m_se->OnConnected(info.description, "", true, "", true);
	TASServer::ExecuteCommand(stdprintf("ADDUSER %s ?? 0 1", GetUserName().c_str()));
}

const int battleid = 1;

void OfflineServer::SendCmd(const std::string& command, const std::string& param, bool /*relay*/)
{
	std::string p = param;
	if (command == "OPENBATTLE") {
		const int type = GetIntParam(p);
		const int nat = GetIntParam(p);
		const std::string password = GetWordParam(p);
		const int port = GetIntParam(p);
		const int maxplayers = GetIntParam(p);
		const std::string gamehash = GetWordParam(p);
		const int rank = GetIntParam(p);
		const std::string maphash = GetWordParam(p);
		const std::string engine = GetSentenceParam(p);
		const std::string enginever = GetSentenceParam(p);
		const std::string map = GetSentenceParam(p);
		const std::string title = GetSentenceParam(p);
		const std::string game = GetSentenceParam(p);
		TASServer::ExecuteCommand(stdprintf("BATTLEOPENED %d %d %d %s %s %d %d %d %d %d %s\t%s\t%s\t%s\t%s",
						    battleid, type, nat, GetUserName().c_str(), "127.0.0.1", port, maxplayers, 0, rank,
						    maphash.c_str(), engine.c_str(), enginever.c_str(), map.c_str(), title.c_str(), game.c_str()));
		TASServer::ExecuteCommand("OPENBATTLE 1");
		TASServer::ExecuteCommand("REQUESTBATTLESTATUS");
	} else if (command == "MYBATTLESTATUS") {
		TASServer::ExecuteCommand(stdprintf("CLIENTBATTLESTATUS %s %s", GetUserName().c_str(), param.c_str()));
	} else if (command == "UPDATEBATTLEINFO") {
		TASServer::ExecuteCommand(stdprintf("UPDATEBATTLEINFO %d %s", battleid, param.c_str()));
	} else if (command == "ADDBOT") {
		const std::string name = GetWordParam(p);
		const int battlestatus = GetIntParam(p);
		const int color = GetIntParam(p);
		const std::string dll = GetSentenceParam(p);
		TASServer::ExecuteCommand(stdprintf("ADDBOT %d %s %s %d %d %s", battleid, name.c_str(), GetUserName().c_str(), battlestatus, color, dll.c_str()));
	} else if (command == "SETSCRIPTTAGS") {
		TASServer::ExecuteCommand(command + " " + param);
	} else if (command == "LEAVEBATTLE") {
		TASServer::ExecuteCommand(stdprintf("LEFTBATTLE %d %s", battleid, GetUserName().c_str()));
		TASServer::ExecuteCommand(stdprintf("BATTLECLOSED %d", battleid));
	} else if (command == "PING") {
		TASServer::ExecuteCommand("PONG " + param);
	} else if (command == "MYSTATUS") {
		TASServer::ExecuteCommand(stdprintf("CLIENTSTATUS %s %s", GetUserName().c_str(), param.c_str()));
	} else if (command == "UPDATEBOT") {
		TASServer::ExecuteCommand(stdprintf("UPDATEBOT %d %s", battleid, param.c_str()));
	} else {
		wxLogWarning("Unknown command: %s %s", command.c_str(), param.c_str());
		TASServer::ExecuteCommand(command + " " + param);
	}
}
