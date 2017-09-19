# McLib

- 多屏窗口控制器基础版，对外接口仿照Duilib

- 用法示例：
``` C++
// 提供获取屏幕基本信息
std::vector<MONITORINFOEX> mi;
	
Monitors::GetInstance()->GetMonitors(mi);

// 获取某个屏幕上所有窗口的基本信息，入参strMonitorName是上一步获取到的屏幕信息中的屏幕名称。
CString strMonitorName = mi.szDevice;
std::map<HWND, WindowsInfoDetail> wi;
	
Monitors::GetInstance()->GetWindows(strMonitorName, wi);

// 移动窗口到指定屏幕的接口，hwnd是想要移动的窗口的句柄。
Monitors::GetInstance()->MoveWindowToSpecifyMonitor(hwnd, strMonitorName);

```