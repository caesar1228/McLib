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

		for each (const auto& monitor_info in *monitor_infos_.getMonitorInfo())
		{
			if (name.Compare(monitor_info.szDevice) == 0)
			{
				for each (const auto& window_info in *windows_infos_.getWindowsInfo())
				{
					RECT tempRect;
					if (::IntersectRect(&tempRect, &monitor_info.rcMonitor, &window_info.second.winRect))
					{
						double intersect_area = (tempRect.bottom - tempRect.top) * (tempRect.right - tempRect.left);
						double window_area = (window_info.second.winRect.bottom - window_info.second.winRect.top) * (window_info.second.winRect.right - window_info.second.winRect.left);
						// 交集大于整体面积50%确定在该屏幕
						if (intersect_area / window_area > 0.5)
							wi[window_info.first] = window_info.second;
					}
				}
			}
		}
	}

	void Monitors::MoveWindowToSpecifyMonitor(HWND hwnd, const CString & monitorname)
	{
		WindowsInfoDetail windows_info_detail = Monitors::GetInstance()->GetWindowDetailFormHwnd(hwnd);
		MONITORINFOEX specify_mi;
		Monitors::GetInstance()->GetMonitorInfoFromMonitorName(monitorname, specify_mi);
		MONITORINFOEX my_mi;
		Monitors::GetInstance()->GetMonitorInfoFromFormHwnd(hwnd, my_mi);

		RECT tempRect;
		::IntersectRect(&tempRect, &specify_mi.rcMonitor, &windows_info_detail.winRect);
		double intersect_area = (tempRect.bottom - tempRect.top) * (tempRect.right - tempRect.left);
		double window_area = (windows_info_detail.winRect.bottom - windows_info_detail.winRect.top) * (windows_info_detail.winRect.right - windows_info_detail.winRect.left);
		// 交集小于整体面积50%确定不在该屏幕
		if (intersect_area / window_area < 0.5)
		{
			long rel_dis_x = my_mi.rcMonitor.left - specify_mi.rcMonitor.left;
			long rel_dis_y = my_mi.rcMonitor.top - specify_mi.rcMonitor.top;

			SetWindowPos(hwnd, HWND_TOP, windows_info_detail.winRect.left - rel_dis_x, windows_info_detail.winRect.top - rel_dis_y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
		}
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
		WindowsInfoDetail windows_info_detail = Monitors::GetInstance()->GetWindowDetailFormHwnd(hwnd);
		for each (const auto& monitor_info in *monitor_infos_.getMonitorInfo())
		{
			RECT tempRect;
			if (::IntersectRect(&tempRect, &monitor_info.rcMonitor, &windows_info_detail.winRect))
			{
				double intersect_area = (tempRect.bottom - tempRect.top) * (tempRect.right - tempRect.left);
				double window_area = (windows_info_detail.winRect.bottom - windows_info_detail.winRect.top) * (windows_info_detail.winRect.right - windows_info_detail.winRect.left);
				// 交集大于整体面积50%确定在该屏幕
				if (intersect_area / window_area > 0.5)
					mi = monitor_info;
			}
		}
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