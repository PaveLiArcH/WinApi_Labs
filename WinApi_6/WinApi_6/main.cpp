#include <Windows.h>
#include <tchar.h>

#include "..\..\FilesCPP\EvryThng.h"

typedef void (*fileDirFunc)(int argC, LPCTSTR *argV);

struct sVariant
{
	LPCTSTR sf_name;
	fileDirFunc sf_func;
};

BOOL notExistFile(LPCTSTR file)
{
	return _taccess(file, 0);
}

void createDirectory(int argC, LPCTSTR *argV)
{
	if (argC>=2)
	{
		BOOL _res=CreateDirectory(argV[1], NULL);
		if (!_res)
		{
			ReportError(_T("При создании каталога возникли ошибки. "), 0, TRUE);
		}
	}
}

void removeDirectory(int argC, LPCTSTR *argV)
{
	if (argC>=2)
	{
		BOOL _res=RemoveDirectory(argV[1]);
		if (!_res)
		{
			ReportError(_T("При удалении каталога возникли ошибки. "), 0, TRUE);
		}
	}
}

void createFile(int argC, LPCTSTR *argV)
{
	if (argC>=2)
	{
		HANDLE _handle=CreateFile(argV[1], GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (_handle==INVALID_HANDLE_VALUE)
		{
			ReportError(_T("При создании файла возникли ошибки. "), 0, TRUE);
		}
		CloseHandle(_handle);
	}
}

void removeFile(int argC, LPCTSTR *argV)
{
	if (argC>=2)
	{
		BOOL _res=DeleteFile(argV[1]);
		if (!_res)
		{
			ReportError(_T("При удалении файла возникли ошибки. "), 0, TRUE);
		}
	}
}

void setCurrentDirectory(int argC, LPCTSTR *argV)
{
	if (argC>=2)
	{
		BOOL _res=SetCurrentDirectory(argV[1]);
		if (!_res)
		{
			ReportError(_T("При установке текущего каталога возникли ошибки. "), 0, TRUE);
		}
	}
}

void getCurrentDirectory(int argC, LPCTSTR *argV)
{
	TCHAR _buffer[MAX_PATH];
	DWORD _size=GetCurrentDirectory(MAX_PATH, _buffer);
	_tprintf(_T("Current directory: %s\n"), _buffer);
}

void copyFile(int argC, LPCTSTR *argV)
{
	if (argC>=3)
	{
		//if (notExistFile(argV[2]))
		BOOL _res=CopyFile(argV[1], argV[2], FALSE);
		if (!_res)
		{
			ReportError(_T("При копировании файла возникли ошибки. "), 0, TRUE);
		}
	}
}

void moveFile(int argC, LPCTSTR *argV)
{
	if (argC>=3)
	{
		BOOL _res=MoveFile(argV[1], argV[2]);
		if (!_res)
		{
			ReportError(_T("При перемещении файла возникли ошибки. "), 0, TRUE);
		}
	}
}

void copyDirectory(int argC, LPCTSTR *argV)
{
	ReportError(_T("Not implemented"), 0, TRUE);
}

void moveDirectory(int argC, LPCTSTR *argV)
{
	if (argC>=3)
	{
		BOOL _res=MoveFile(argV[1], argV[2]);
		if (!_res)
		{
			ReportError(_T("При перемещении каталога возникли ошибки. "), 0, TRUE);
		}
	}
}

sVariant variantsForOne[]={
	{_T("Create file"), createFile},
	{_T("Remove file"), removeFile},
	{_T("Create directory"), createDirectory},
	{_T("Remove directory"), removeDirectory},
	{_T("Set current directory"), setCurrentDirectory},
	{_T("Get current directory"), getCurrentDirectory},
};

sVariant variantsForTwo[]={
	{_T("Copy file"), copyFile},
	{_T("Move file"), moveFile},
	{_T("Copy directory"), copyDirectory},
	{_T("Move directory"), moveDirectory},
};

void printHelp()
{
	_tprintf(_T("Usage: TestFileDir Name1 [Name2]\n"));
	_tprintf(_T("For help: TestFileDir /?\n"));
}

int _tmain(int argC, LPCTSTR *argV)
{
	for (int i=0; i<argC; i++)
	{
		if (lstrcmp(argV[i],_T("/?"))==NULL)
		{
			printHelp();
			return 0;
		}
	}
	BOOL _exit=FALSE;
	int _forOneCount=sizeof(variantsForOne)/(sizeof(sVariant));
	int _forTwoCount=sizeof(variantsForTwo)/(sizeof(sVariant));
	int _allTwoCount=_forOneCount+_forTwoCount;
	do
	{
		int i;
		switch(argC)
		{
		default:
		case 1:
			printHelp();
			return 1;
		case 2:
			for(i=0; i<_forOneCount; i++)
			{
				_tprintf(_T("%d. %s\n"), i, variantsForOne[i].sf_name);
			}
			_tprintf(_T("%d. %s\n"), ++i, _T("Exit"));
			break;
		case 3:
			_tprintf(_T("Options for first arg:\n"));
			for(i=0; i<_forOneCount; i++)
			{
				_tprintf(_T("%d. %s\n"), i, variantsForOne[i].sf_name);
			}
			_tprintf(_T("Options for src dest:\n"));
			for(int j=0; j<_forTwoCount; i++, j++)
			{
				_tprintf(_T("%d. %s\n"), i, variantsForTwo[j].sf_name);
			}
			_tprintf(_T("%d. %s\n"), ++i, _T("Exit"));
			break;
		}
		TCHAR _optionS[MAX_PATH];
		_tprintf(_T("Choose option: "));
		_getts_s(_optionS, MAX_PATH);
		
		int _option=_ttoi(_optionS);
		switch(argC)
		{
		default:
		case 1:
			break;
		case 2:
			if (_option>=0)
			{
				if (_option<_forOneCount)
				{
					variantsForOne[_option].sf_func(argC, argV);
					break;
				}
				if (_option=_forOneCount)
				{
					_exit=TRUE;
				}
			}
			ReportError(_T("Некорректный вариант"), 0, TRUE);
			break;
		case 3:
			if (_option>=0)
			{
				if (_option<_forOneCount)
				{
					variantsForOne[_option].sf_func(argC, argV);
				} else
				{
					if (_option<_allTwoCount)
					{
						variantsForTwo[_option-_forOneCount].sf_func(argC, argV);
					} else
					{
						if (_option=_allTwoCount)
						{
							_exit=TRUE;
						} else
						{
							ReportError(_T("Некорректный вариант"), 0, TRUE);
						}
					}
				}
			} else
			{
				ReportError(_T("Некорректный вариант"), 0, TRUE);
			}
			break;
		}
	} while(_exit==FALSE);
}