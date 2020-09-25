/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H


#include <lslutils/globalsmanager.h>
#include <wx/event.h>
#include <wx/timer.h>
#include <vector>
#include "utils/mixins.h"
#include "utils/uievents.h"
class INotification;

class NotificationManager : public SL::NonCopyable, public wxEvtHandler
{
public:
	NotificationManager();
	virtual ~NotificationManager();

	void OnShowNotification(UiEvents::NotficationData data);

	void OnQuit(wxCommandEvent& data);

private:
	INotification* m_notification_wrapper;

	wxTimer m_rate_limit_timer;
	const unsigned int m_rate_limit_ms;
	typedef std::vector<UiEvents::NotficationData>
	    EventDataBuffer;
	EventDataBuffer m_eventDataBuffer;

	void OnTimer(wxTimerEvent& /*event*/);
	void ShowNotification(const UiEvents::NotficationData& data);

	EventReceiverFunc<NotificationManager, UiEvents::NotficationData, &NotificationManager::OnShowNotification> m_showNotificationSink;

	DECLARE_EVENT_TABLE()
};

NotificationManager& notificationManager();

#endif // NOTIFICATIONMANAGER_H
