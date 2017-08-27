#include "stdafx.h"
#include "MonitorInfo.h"

namespace McLib {
	MonitorInfo::MonitorInfo()
	{
		monitorinfo = make_shared<vector<MONITORINFOEX>>();
		EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
	}

	MonitorInfo::~MonitorInfo()
	{
	}

	BOOL CALLBACK MonitorInfo::MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
	{
		MonitorInfo* pThis = reinterpret_cast<MonitorInfo*>(pData);
		MONITORINFOEX monitorinfo;
		monitorinfo.cbSize = sizeof(MONITORINFOEX);

		GetMonitorInfo(hMon, &monitorinfo);
		pThis->monitorinfo->push_back(monitorinfo);

		return TRUE;
	}
}