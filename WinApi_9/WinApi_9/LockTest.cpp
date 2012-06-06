#include <windows.h>
#include <tchar.h>

int _tmain(int argc, LPCTSTR argv[])
{
	if (argc<3)
	{
		_tprintf(_T("Usage:\n\tlocktest -e file\n\ttlocktest -s file"));
		return 1;
	}

	HANDLE _hFile = CreateFile(argv[2], GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	if (_hFile==INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Error while opening file %s\n"), argv[2]);
		return 2;
	}

	LPCTSTR _mode = argv[1];

	OVERLAPPED _overlapped;
	_overlapped.Offset = 0;
	_overlapped.OffsetHigh = 0;
	_overlapped.hEvent = 0;

	BOOL _locked=FALSE;

	if (!_tcscmp(_mode, _T("-s")))
	{
		_locked = LockFileEx(_hFile, LOCKFILE_FAIL_IMMEDIATELY, 0, 12, 0, &_overlapped);
	}
	else
	{
		if (!_tcscmp(_mode, _T("-e")))
		{
			_locked = LockFileEx(_hFile, LOCKFILE_FAIL_IMMEDIATELY | LOCKFILE_EXCLUSIVE_LOCK, 0, 12, 0, &_overlapped);
		}
		else
		{
			_tprintf(_T("Requested invalid mode %s\n"), argv[1]);
			CloseHandle(_hFile);
			return 3;
		}
	}
	if (_locked)
	{
		_tprintf(_T("File locked\n"));
	} else
	{
		_tprintf(_T("File not locked\n"));
	}
	CloseHandle(_hFile);
	return 0;
}
