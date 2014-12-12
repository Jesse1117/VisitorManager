#pragma once
#include <string.h>
using namespace std;
/*
ע��:Ϊ�˽�ʡ����ʱ����ļ��ķ�װֻ�ǲ��ü򵥵ķ�װ��û�в����쳣���ƣ�
������ڴ�������Դ��롣
������ʱ�佫�����쳣���ơ�
*/
class CDoFile
{
public:
	CDoFile(void);
	~CDoFile(void);
	int MyCreateDirectory(const std::wstring& path);
	BOOL MyIsFileExit(const std::wstring& pathname);
	std::wstring MyParentPath(const std::wstring& path);
	BOOL MyDeleteDirectory(const std::wstring& path);

	std::wstring MyGetExeFullFilePath();
	BOOL MyOpenFile(std::wstring fileName,UINT nOpenFlags);
	BOOL MyCloseFile();
	UINT MyReadFile(void* lpBuf,UINT nCount);
	BOOL MyWriteFile(const void* lpBuf,UINT nCount);
	ULONGLONG MySeekFile(LONGLONG lOff, UINT nFrom);
	ULONGLONG MyFileGetPosition()const;
	BOOL MyFileFlush();
	ULONGLONG MyFileGetLength()const;
	BOOL MyFileSetLength(ULONGLONG newLength);
	void MyFileSeekToEnd();
	void MyFileSeekToBegin();
private:
	std::wstring m_strPath;
public:
	static enum OpenFlags {
		modeRead =         (int) 0x00000,
		modeWrite =        (int) 0x00001,
		modeReadWrite =    (int) 0x00002,
		shareCompat =      (int) 0x00000,
		shareExclusive =   (int) 0x00010,
		shareDenyWrite =   (int) 0x00020,
		shareDenyRead =    (int) 0x00030,
		shareDenyNone =    (int) 0x00040,
		modeNoInherit =    (int) 0x00080,
		modeCreate =       (int) 0x01000,
		modeNoTruncate =   (int) 0x02000,
		typeText =         (int) 0x04000, // typeText and typeBinary are
		typeBinary =       (int) 0x08000, // used in derived classes only
		osNoBuffer =       (int) 0x10000,
		osWriteThrough =   (int) 0x20000,
		osRandomAccess =   (int) 0x40000,
		osSequentialScan = (int) 0x80000,
	};//openflags
	static enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
	};
	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
public:
	HANDLE m_hFile;//�ļ����
	std::wstring m_strFileName;//�ļ�����
};
