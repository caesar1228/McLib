#pragma once
#ifdef LIBMC_STATIC
#define LIBMC_API 
#else
#if defined(LIBMC_EXPORTS)
#	if defined(_MSC_VER)
#		define LIBMC_API __declspec(dllexport)
#	else
#		define LIBMC_API 
#	endif
#else
#	if defined(_MSC_VER)
#		define LIBMC_API __declspec(dllimport)
#	else
#		define LIBMC_API
#	endif
#endif
#endif

#pragma warning(disable:4251)

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <assert.h>
#include <atlstr.h>
#include <vector>
#include <map>
#include <memory>

using namespace std;

#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#include "MonitorInfo.h"
#include "WindowsInfo.h"
#include "Monitors.h"
