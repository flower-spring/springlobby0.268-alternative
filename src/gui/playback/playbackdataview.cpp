/* This file is part of the Springlobby (GPL v2 or later), see COPYING */
#include "playbackdataview.h"

#include <wx/dataview.h>
#include <wx/menu.h>

#include "exception.h"
#include "gui/basedataviewmodel.h"
#include "gui/customdialogs.h"
#include "gui/ui.h"
#include "iplaybacklist.h"
#include "log.h"
#include "playbackdatamodel.h"
#include "replaylist.h"
#include "servermanager.h"
#include "storedgame.h"

BEGIN_EVENT_TABLE(PlaybackDataView, BaseDataViewCtrl)
EVT_DATAVIEW_ITEM_CONTEXT_MENU(REPLAY_DATAVIEW_ID, PlaybackDataView::OnContextMenu)
EVT_MENU(REPLAY_DATAVIEW_DLMAP_ID, PlaybackDataView::OnDLMap)
EVT_MENU(REPLAY_DATAVIEW_DLMOD_ID, PlaybackDataView::OnDLMod)
EVT_CHAR(PlaybackDataView::OnKeyDown)
END_EVENT_TABLE()

PlaybackDataView::PlaybackDataView(const wxString& dataViewName, wxWindow* parent)
    : BaseDataViewCtrl(dataViewName, parent, REPLAY_DATAVIEW_ID)
{
	m_Parent = parent;

	PlaybackDataModel* m_PlaybackDataModel = new PlaybackDataModel();
	AssociateModel(m_PlaybackDataModel);

	const int DEFAULT_SIZE = wxCOL_WIDTH_AUTOSIZE;
	AppendIconTextColumn(_("Date"), DATE, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Game"), GAME, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Map"), MAP, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Players"), PLAYERS, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Duration"), DURATION, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Engine"), ENGINE, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("Filesize"), FILESIZE, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
	AppendTextColumn(_("File"), FILENAME, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);

	m_ContextMenu = new wxMenu(wxEmptyString);
	m_ContextMenu->Append(REPLAY_DATAVIEW_DLMAP_ID, _("Download &map"));
	m_ContextMenu->Append(REPLAY_DATAVIEW_DLMOD_ID, _("Download &game"));

	LoadColumnProperties();
}

PlaybackDataView::~PlaybackDataView()
{
}

void PlaybackDataView::AddPlayback(const StoredGame& replay, bool resortIsNeeded)
{
	AddItem(replay, resortIsNeeded);

	Refresh();
}

void PlaybackDataView::RemovePlayback(const StoredGame& replay)
{
	RemoveItem(replay);

	Refresh();
}

void PlaybackDataView::OnContextMenu(wxDataViewEvent& /*event*/)
{
	const StoredGame* storedGame = GetSelectedItem();

	if (storedGame == nullptr) {
		return;
	}
	PopupMenu(m_ContextMenu);
}

void PlaybackDataView::OnDLMap(wxCommandEvent& /*event*/)
{
	const StoredGame* storedGame = GetSelectedItem();
	if (storedGame == nullptr) {
		return;
	}
	ui().NeedsDownload(&storedGame->battle);
}

void PlaybackDataView::OnDLMod(wxCommandEvent& /*event*/)
{
	const StoredGame* storedGame = GetSelectedItem();

	if (storedGame == nullptr) {
		return;
	}

	ui().NeedsDownload(&storedGame->battle);
}

void PlaybackDataView::DeletePlayback()
{
	const StoredGame* storedGame = GetSelectedItem();

	if (storedGame == nullptr) {
		return;
	}

	try {
		const int m_sel_replay_id = storedGame->id;
		if (!replaylist().DeletePlayback(m_sel_replay_id)) {
			wxString pn(storedGame->battle.GetPlayBackFilePath());
			customMessageBoxModal(SL_MAIN_ICON, _("Could not delete Replay: ") + pn, _("Error"));
		} else {
			RemovePlayback(*storedGame);
		}
	} catch (std::runtime_error&) {
		//Do nothing
	}
}

void PlaybackDataView::SetTipWindowText(const long /*item_hit*/,
					const wxPoint& /*position*/)
{
	//TODO: Implement
}

void PlaybackDataView::HighlightItem(long /*longInt*/)
{
	//TODO: Implement
}

//React on DEL key, resend event to parent
void PlaybackDataView::OnKeyDown(wxKeyEvent& event)
{
	const int keyCode = event.GetKeyCode();
	if ((keyCode == WXK_DELETE) && (m_Parent != NULL)) {
		wxPostEvent(m_Parent, event);
		return;
	}
	event.Skip();
}
