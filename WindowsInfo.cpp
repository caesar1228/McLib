#include "stdafx.h"
#include "WindowsInfo.h"

namespace McLib {
	WindowsInfo::WindowsInfo()
	{
		windowsinfo = make_shared<map<HWND, WindowsInfoDetail>>();
		pDesktopWnd = GetDesktopWindow();
		EnumChildWindows(pDesktopWnd, EnumWindowsProc, (LPARAM)this);
	}

	WindowsInfo::~WindowsInfo()
	{
	}

	BOOL CALLBACK WindowsInfo::EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		WindowsInfo* pThis = reinterpret_cast<WindowsInfo*>(lParam);
		if (hwnd == NULL || pThis == NULL)
		{
			return  FALSE;
		}

		if (::IsWindow(hwnd) && ::IsWindowVisible(hwnd) && \
			((GetWindowLong(hwnd, GWL_EXSTYLE)&WS_EX_TOOLWINDOW) != WS_EX_TOOLWINDOW) && \
			(GetWindowLong(hwnd, GWL_HWNDPARENT) == 0))
		{
			WindowsInfoDetail wininfodetail;

			//��ô��ڱ���
			CString strWindowText = _T("");
			::GetWindowText(hwnd, strWindowText.GetBuffer(256), 256);
			wininfodetail.strWindowText = strWindowText;

			BOOL is_max_ = FALSE;
			//�жϴ���״̬
			if (::IsZoomed(hwnd))
			{
				wininfodetail.strWindowStatus = _T("���");
				is_max_ = TRUE;
				
			}
			else if (::IsIconic(hwnd))
				wininfodetail.strWindowStatus = _T("��С��");
			else
				wininfodetail.strWindowStatus = _T("��ͨ����");

			//���ڵ�λ��
			if (is_max_)
			{
				RECT winRect;
				GetWindowRect(hwnd, &winRect);
				wininfodetail.winRect = winRect;
			} 
			else
			{
				WINDOWPLACEMENT wndpl;
				GetWindowPlacement(hwnd, &wndpl);
				wininfodetail.winRect = wndpl.rcNormalPosition;
			}

			//��ô�������
			CString strClassName = _T("");
			::GetClassName(hwnd, strClassName.GetBuffer(256), 256);
			wininfodetail.strClassName = strClassName;

			pThis->windowsinfo->insert(make_pair(hwnd, wininfodetail));
		}

		return TRUE;
	}

	void WindowsInfo::Reload()
	{
		windowsinfo->erase(windowsinfo->begin(), windowsinfo->end());
		EnumChildWindows(pDesktopWnd, EnumWindowsProc, (LPARAM)this);
	}
}