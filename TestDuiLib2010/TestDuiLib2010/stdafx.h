// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
/*#define _CRT_SECURE_NO_DEPRECATE*/
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <objbase.h>
#include <zmouse.h>
#include <UIlib.h>
using namespace DuiLib;
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif
//TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
/*
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN	
//#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include <zmouse.h>

#include <UIlib.h>

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)

*/