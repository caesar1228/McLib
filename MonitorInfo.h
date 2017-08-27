#pragma once

namespace McLib {
	class LIBMC_API MonitorInfo
	{
	public:
		MonitorInfo();
		~MonitorInfo();

		MonitorInfo(const MonitorInfo& mi) = delete;
		MonitorInfo& operator= (const MonitorInfo& mi) = delete;

		shared_ptr<vector<MONITORINFOEX>> getMonitorInfo() {
			return monitorinfo;
		}

	private:
		static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData);

	private:
		shared_ptr<vector<MONITORINFOEX>> monitorinfo;
	};
}