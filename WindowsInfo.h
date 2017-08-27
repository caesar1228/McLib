#pragma once

namespace McLib {
	typedef struct LIBMC_API tag_WindowsInfoDetail {
		CString strWindowText;		//窗口标题	
		RECT winRect;				//窗口的位置
		CString strWindowStatus;	//窗口状态
		CString strClassName;		//窗口类名

		tag_WindowsInfoDetail() {
			this->strWindowText = _T("");
			this->winRect = { 0, 0, 0, 0 };
			this->strWindowStatus = _T("");
			this->strClassName = _T("");
		}
	}WindowsInfoDetail;

	class LIBMC_API WindowsInfo
	{
	public:
		WindowsInfo();
		~WindowsInfo();

		WindowsInfo(const WindowsInfo& mi) = delete;
		WindowsInfo& operator= (const WindowsInfo& mi) = delete;

		shared_ptr<map<HWND, WindowsInfoDetail>> getWindowsInfo() {
			return windowsinfo;
		}
		void Reload();

	private:
		static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	private:
		shared_ptr<map<HWND, WindowsInfoDetail>> windowsinfo;
		HWND pDesktopWnd;
	};
}