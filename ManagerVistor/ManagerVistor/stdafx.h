// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <objbase.h>
#include <zmouse.h>
#include "../UiLib/UiLib/UIlib.h"
using namespace UiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "../UiLib/Lib/UiLib_ud.lib")
#   else
#       pragma comment(lib, "../UiLib/Lib/UiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "../UiLib/Lib/UiLib_u.lib")
#   else
#       pragma comment(lib, "../lib/DuiLib_u.lib")
#   endif
#endif
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�