/* Copyright (C) 2007 The SpringLobby Team. All rights reserved. */

#include <stdexcept>
#include <lslutils/logging.h>

#include "singleplayer.h"
#include <lsl/networking/tasserver.h>
#include <lslutils/lslconfig.h>
#include <lsl/spring/spring.h>
#include <lslutils/conversion.h>
#include <unitsync++/unitsync.h>

namespace LSL
{

SinglePlayerBattle::SinglePlayerBattle(MainSinglePlayerTab& msptab)
    : m_sptab(msptab)
    , m_me(new User(usync().IsLoaded() ? usync().GetDefaultNick() : _T("invalid")))
{
	OnUserAdded(m_me);
	m_me.BattleStatus().side = sett().GetBattleLastSideSel(GetHostGameName());
	m_me.BattleStatus().color = sett().GetBattleLastColour();
	CustomBattleOptions().setSingleOption(_T("startpostype"), wxFormat(_T("%d")) % ST_Pick, OptionsWrapper::EngineOption);
}


SinglePlayerBattle::~SinglePlayerBattle()
{
}


void SinglePlayerBattle::SendHostInfo(HostInfo update)
{
	if ((update & HI_StartType) != 0)
		m_sptab.UpdateMinimap();
	if ((update & HI_Restrictions) != 0)
		m_sptab.ReloadRestrictions();
	if ((update & HI_Map_Changed) != 0) {
		LoadMap();
		m_sptab.ReloadMapOptContrls();
		Update(wxFormat(_T("%d_%s")) % OptionsWrapper::PrivateOptions % _T("mapname"));
	}
	if ((update & HI_Mod_Changed) != 0) {
		RemoveUnfittingBots();
		LoadMod();
		std::string presetname = sett().GetModDefaultPresetName(GetHostGameName());
		if (!presetname.empty()) {
			LoadOptionsPreset(presetname);
			SendHostInfo(HI_Send_All_opts);
		}
		m_sptab.ReloadModOptContrls();
		Update(wxFormat(_T("%d_%s")) % OptionsWrapper::PrivateOptions % _T("modname"));
	}
	if ((update & HI_Send_All_opts) != 0) {
		for (int i = 0; i < (int)OptionsWrapper::LastOption; i++) {
			const std::map<std::string, std::string>& options = CustomBattleOptions().getOptionsMap((OptionsWrapper::GameOption)i);
			for (std::map<std::string, std::string>::const_iterator itor = options.begin(); itor != options.end(); ++itor) {
				Update(wxFormat(_T("%d_%s")) % i % itor->first);
			}
		}
	}
}

void SinglePlayerBattle::RemoveUnfittingBots()
{
	StringVector old_ais = usync().GetAIList(m_previous_local_mod_name);
	StringVector new_ais = usync().GetAIList(m_local_game.name);
	for (size_t i = 0; i < old_ais.GetCount(); ++i) {
		if (new_ais.Index(old_ais[i]) == wxNOT_FOUND) {
			for (size_t j = 0; j < GetNumUsers(); ++j) {
				User& u = GetUser(j);
				if (u.GetBattleStatus().airawname == old_ais[i])
					KickPlayer(u);
			}
		}
	}
}

void SinglePlayerBattle::Update(const std::string& Tag)
{
	m_sptab.UpdateTag(Tag);
}

void SinglePlayerBattle::StartSpring()
{
	spring().Run(*this);
	ui().OnSpringStarting();
}

} // namespace LSL {
