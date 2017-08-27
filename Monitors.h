#pragma once
#include "MonitorInfo.h"
#include "WindowsInfo.h"

namespace McLib {
	class LIBMC_API Monitors
	{
	public:
		static Monitors* GetInstance();
		Monitors();
		~Monitors();

	public:
		bool Init();
		void Uninit();

		void GetMonitors(std::vector<MONITORINFOEX> &mi);
		void GetWindows(const CString& name, std::map<HWND, WindowsInfoDetail> &wi);

		void MoveWindowToSpecifyMonitor(HWND hwnd, const CString& monitorname);

	private:
		void GetMonitorInfoFromMonitorName(const CString& monitorname, MONITORINFOEX &mi);
		WindowsInfoDetail GetWindowDetailFormHwnd(HWND hwnd);
		void GetMonitorInfoFromFormHwnd(HWND hwnd, MONITORINFOEX &mi);

	private:
		MonitorInfo monitor_infos_;
		WindowsInfo windows_infos_;
	};
}

