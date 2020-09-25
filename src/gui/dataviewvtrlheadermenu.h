/*
 * dataviewvtrlheadermenu.h
 *
 *  Created on: 22 ���� 2015 �.
 *      Author: ������
 */

#ifndef SRC_GUI_DATAVIEWVTRLHEADERMENU_H_
#define SRC_GUI_DATAVIEWVTRLHEADERMENU_H_

#include <wx/menu.h>
class wxDataViewCtrl;

class DataViewCtrlHeaderMenu : public wxMenu
{
public:
	DataViewCtrlHeaderMenu(wxDataViewCtrl* parentDataView, int columnIndex);
	virtual ~DataViewCtrlHeaderMenu();

private:
	void CreateMenuItems();
	void ConnectEvents();
	int CountVisibleColumns();
	void OnHideColumn(wxCommandEvent&);
	void OnShowColumns(wxCommandEvent&);

public:
	static wxEventType HIDE_COLUMN_EVT;
	static wxEventType SHOW_ALL_COLUMNS_EVT;

private:
	enum {
		HIDE_COLUMN_ID,
		SHOW_ALL_COLUMNS_ID
	};

private:
	wxDataViewCtrl* parentDataView;
	int columnIndex;
};

#endif /* SRC_GUI_DATAVIEWVTRLHEADERMENU_H_ */
