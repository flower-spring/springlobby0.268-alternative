/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#ifndef SPRINGLOBBY_PlaybackTab_H_INCLUDED
#define SPRINGLOBBY_PlaybackTab_H_INCLUDED

#include <wx/scrolwin.h>
#include <vector>
#include "gui/controls.h"
class Ui;
class MapCtrl;
class BattleroomListCtrl;
class wxCheckBox;
class wxCommandEvent;
class wxDataViewEvent;
class wxStaticText;
class wxComboBox;
class wxButton;
class wxBoxSizer;
class wxStaticText;
class wxStaticLine;
class wxToggleButton;
struct StoredGame;
class PlaybackLoader;
class PlaybackListFilter;
class PlaybackDataView;
class BattleroomDataViewCtrl;

class PlaybackTab : public wxPanel
{
private:
	friend class BattleListFilter; //! WTF?


public:
	//! loads all replays into list and adds them to listctrl
	PlaybackTab(wxWindow* parent, bool replay);
	~PlaybackTab();

	//! adds a single replay to listctrl
	void AddPlayback(const StoredGame& Replay, bool resortIsNeeded = true);
	void RemovePlayback(const StoredGame& Replay);
	void UpdatePlayback(const StoredGame& Replay);

	//! add all replays in m_replays to listctrl
	void AddAllPlaybacks(wxCommandEvent& evt);
	void RemoveAllPlaybacks();
	void ReloadList();

	void UpdateList();

	//! calls ui::watch which executes spring
	void OnWatch(wxCommandEvent& event);
	//! clears list and parses all replays anew
	void OnReload(wxCommandEvent& event);
	//! does nothing yet
	void OnDelete(wxCommandEvent& event);
	//! does nothing yet
	void OnFilter(wxCommandEvent& event);
	//! does nothing yet
	void OnFilterActiv(wxCommandEvent& event);

	//! sets m_sel_replay_id according to selected listitem
	void OnSelect(wxDataViewEvent& event);
	//! does nothing yet
	void SetFilterActiv(bool activ);

	void Deselect();
	void Deselected();

	void OnSpringTerminated(wxCommandEvent& data);
	void OnUnitsyncReloaded(wxCommandEvent& data);

private:
	void OnChar(wxKeyEvent& event);
	PlaybackListFilter* m_filter;
	PlaybackDataView* m_replay_dataview;
	PlaybackLoader* m_replay_loader;
	MapCtrl* m_minimap;
	wxStaticText* m_engine_lbl;
	wxStaticText* m_engine_text;
	wxStaticText* m_map_lbl;
	wxStaticText* m_map_text;
	wxStaticText* m_game_lbl;
	wxStaticText* m_game_text;
	wxStaticText* m_players_lbl;
	wxStaticText* m_players_text;

	wxStaticLine* m_buttons_sep;
	wxButton* m_watch_btn;
	wxButton* m_delete_btn;
	wxButton* m_reload_btn;

	BattleroomDataViewCtrl* m_players;

	wxCheckBox* m_filter_activ;
	bool m_isreplay;
	wxToggleOrCheck* m_filter_show;

	void AskForceWatch(StoredGame& rep) const;

	DECLARE_EVENT_TABLE()
};

enum {
	PLAYBACK_WATCH = wxID_HIGHEST,
	PLAYBACK_DELETE,
	PLAYBACK_RELOAD,
	PLAYBACK_LIST,
	PLAYBACK_LIST_FILTER_BUTTON,
	PLAYBACK_LIST_FILTER_ACTIV,
	PLAYBACK_TIMER,
	PLAYBACK_USER_LIST
};

#endif // SPRINGLOBBY_PlaybackTab_H_INCLUDED
