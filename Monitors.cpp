#include "stdafx.h"
#include "Monitors.h"

namespace McLib {
	namespace {

		Monitors* g_monitors = nullptr;

	} // namespace

	Monitors* Monitors::GetInstance() {
		if (!g_monitors) {
			g_monitors = new Monitors();
		}
		return g_monitors;
	}

	void Monitors::Uninit() {
		if (g_monitors) {
			delete g_monitors;
			g_monitors = nullptr;
		}
	}

	void Monitors::GetMonitors(std::vector<MONITORINFOEX> & mi)
	{
		if (monitor_infos_.getMonitorInfo()->size() > 0)
			mi = *monitor_infos_.getMonitorInfo();
	}

	void Monitors::GetWindows(const CString& name, std::map<HWND, WindowsInfoDetail>& wi)
	{
		windows_infos_.Reload();

		for each (const auto& window_info in *windows_infos_.getWindowsInfo())
		{

			HMONITOR hMon = MonitorFromWindow(window_info.first, MONITOR_DEFAULTTONEAREST);
			MONITORINFOEX monitorinfo;
			monitorinfo.cbSize = sizeof(MONITORINFOEX);

			GetMonitorInfo(hMon, &monitorinfo);
			if (name.Compare(monitorinfo.szDevice) == 0)
				wi[window_info.first] = window_info.second;
		}
	}

	void Monitors::MoveWindowToSpecifyMonitor(HWND hwnd, const CString & monitorname)
	{
		WindowsInfoDetail windows_info_detail = Monitors::GetInstance()->GetWindowDetailFormHwnd(hwnd);
		MONITORINFOEX specify_mi;
		specify_mi.cbSize = sizeof(MONITORINFOEX);
		Monitors::GetInstance()->GetMonitorInfoFromMonitorName(monitorname, specify_mi);
		MONITORINFOEX my_mi;
		my_mi.cbSize = sizeof(MONITORINFOEX);
		Monitors::GetInstance()->GetMonitorInfoFromFormHwnd(hwnd, my_mi);

		long rel_dis_x = my_mi.rcMonitor.left - specify_mi.rcMonitor.left;
		long rel_dis_y = my_mi.rcMonitor.top - specify_mi.rcMonitor.top;

		SetWindowPos(hwnd, HWND_TOP, windows_info_detail.winRect.left - rel_dis_x, windows_info_detail.winRect.top - rel_dis_y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
	}

	void  Monitors::GetMonitorInfoFromMonitorName(const CString& monitorname, MONITORINFOEX &mi)
	{
		for each (const auto& monitor_info in *monitor_infos_.getMonitorInfo())
		{
			if (monitorname.Compare(monitor_info.szDevice) == 0)
			{
				mi = monitor_info;
			}
		}
	}

	WindowsInfoDetail Monitors::GetWindowDetailFormHwnd(HWND hwnd)
	{
		WindowsInfoDetail windows_info_detail;
		auto it = windows_infos_.getWindowsInfo()->find(hwnd);
		if (it != windows_infos_.getWindowsInfo()->end())
			return it->second;
		else
			return windows_info_detail;
	}

	void Monitors::GetMonitorInfoFromFormHwnd(HWND hwnd, MONITORINFOEX & mi)
	{
		HMONITOR hMon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
		GetMonitorInfo(hMon, &mi);
	}

	Monitors::Monitors() {

	}

	Monitors::~Monitors() {
	}

	bool Monitors::Init() {

		int dspNum = monitor_infos_.getMonitorInfo()->size();
		int winNum = windows_infos_.getWindowsInfo()->size();

		return true;
	}
}