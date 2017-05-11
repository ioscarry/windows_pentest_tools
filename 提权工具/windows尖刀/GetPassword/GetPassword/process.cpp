#include "stdafx.h"
#include "process.h"
#include <TlHelp32.h>
#include <Shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")
using namespace std;
extern OSVERSIONINFOEX GLOB_Version;

bool getList(vector<MY_PROCESSENTRY32> *myProcessesVector,wstring *processName)
{
	HANDLE hProcessesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hProcessesSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 myProcesses;
		myProcesses.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessesSnapshot,&myProcesses))
		{
			do 
			{
				if (!processName || (_tcsicmp(processName->c_str(),myProcesses.szExeFile) == 0))
				{
					MY_PROCESSENTRY32 myProcessK = {
						myProcesses.dwSize,
						myProcesses.cntUsage,
						myProcesses.th32ProcessID,
						myProcesses.th32DefaultHeapID,
						myProcesses.th32ModuleID,
						myProcesses.cntThreads,
						myProcesses.th32ParentProcessID,
						myProcesses.pcPriClassBase,
						myProcesses.dwFlags,
						myProcesses.szExeFile
					};
					
					myProcessesVector->push_back(myProcessK);
				}
			} while (Process32Next(hProcessesSnapshot,&myProcesses));
		}

		CloseHandle(hProcessesSnapshot);
		return true;
	}
	else return false;
}

bool getProcessBasicInformation(PROCESS_BASIC_INFORMATION *Infos,HANDLE processHandle)
{
	bool success = false;
	if (processHandle == INVALID_HANDLE_VALUE)
		processHandle = GetCurrentProcess();
	if (PNT_QUERY_INFORMATION_PROCESS NtQueryInformationProcess = 
			reinterpret_cast<PNT_QUERY_INFORMATION_PROCESS>(GetProcAddress(GetModuleHandle(TEXT("ntdll")),"NtQueryInformationProcess")))
	{
		ULONG sizeReturn;
		success = NT_SUCCESS(NtQueryInformationProcess(processHandle,
													   ProcessBasicInformation,
													   Infos,
													   sizeof(PROCESS_BASIC_INFORMATION),
													   &sizeReturn)) && 
							(sizeReturn == sizeof(PROCESS_BASIC_INFORMATION));
	}
	return success;
}


bool readMemory(const PVOID BaseAddress,PVOID Destination,size_t length,HANDLE handleProcess)
{
	if (handleProcess == INVALID_HANDLE_VALUE)
	{
		return (memcpy_s(Destination,length,BaseAddress,length) == 0);
	}
	else
	{
		SIZE_T dwByteRead = 0;
		return ((ReadProcessMemory(handleProcess,BaseAddress,Destination,length,&dwByteRead)!=0) && (dwByteRead == length));
	}
}


bool getPeb(PEB *peb,HANDLE processHandle)
{
	bool success = false;
	PROCESS_BASIC_INFORMATION *Infos = new PROCESS_BASIC_INFORMATION();
	if (getProcessBasicInformation(Infos,processHandle))
	{
		success = readMemory(Infos->PebBaseAddress,peb,sizeof(PEB),processHandle);
	}
	delete Infos;
	return success;
}

bool getUnicodeStringOfProcess(UNICODE_STRING *ptrString,BYTE **Buffer,HANDLE process,PLSA_PROTECT_MEMORY unProtectFunction)
{
	bool result = false;
	if (ptrString->Buffer && (ptrString->Length > 0))
	{
		*Buffer = new BYTE[ptrString->MaximumLength];
		if (result = readMemory(ptrString->Buffer,*Buffer,ptrString->MaximumLength,process))
		{
			if (unProtectFunction)
				unProtectFunction(*Buffer,ptrString->MaximumLength);
		}
	}
	return result;
}
extern wstring stringOrHex(const BYTE myTab[], DWORD mySize, DWORD length = 32, bool line = true);

wstring getUnicodeStringOfProcess(UNICODE_STRING *ptrString,HANDLE process,PLSA_PROTECT_MEMORY unProtectFunction)
{
	wstring Chain;
	BYTE *Buffer = NULL;
	if (getUnicodeStringOfProcess(ptrString,&Buffer,process,unProtectFunction))
	{
		Chain.assign(stringOrHex(Buffer,ptrString->Length));
	}
	if (Buffer)
		delete[] Buffer;
	return Chain;
}

bool getBasicModulesListOfProcess(vector<BASIC_MODULEENTRY> *ModuleVector,HANDLE processHandle)
{
	bool success = false;
	PEB *Peb = new PEB();
	if (getPeb(Peb,processHandle))
	{
		PEB_LDR_DATA *Loader = new PEB_LDR_DATA();
		if (readMemory(Peb->LoaderData,Loader,sizeof(PEB_LDR_DATA),processHandle))
		{
			PBYTE read,end;
			LDR_DATA_TABLE_ENTRY Entry;
			for (read = PBYTE(Loader->InMemoryOrderModulevector.Flink) - FIELD_OFFSET(LDR_DATA_TABLE_ENTRY,InMemoryOrderLinks),
				 end = (PBYTE)(Peb->LoaderData) + FIELD_OFFSET(PEB_LDR_DATA,InLoadOrderModulevector);
				 read != end;
				 read = (PBYTE)Entry.InMemoryOrderLinks.Flink - FIELD_OFFSET(LDR_DATA_TABLE_ENTRY,InMemoryOrderLinks))
			{
				if (success = readMemory(read,&Entry,sizeof(Entry),processHandle))
				{
					BASIC_MODULEENTRY Module = {
						reinterpret_cast<PBYTE>(Entry.DllBase),
						Entry.SizeOfImage,
						getUnicodeStringOfProcess(&Entry.BaseDllName,processHandle)
					};
					ModuleVector->push_back(Module);
				}
			}
		}
		delete Loader;
	}
	delete Peb;
	return success;
}


bool getUniqueFromName(MY_PROCESSENTRY32 *myProcess,wstring *processName)
{
	bool result = false;
	vector<MY_PROCESSENTRY32> *myProcesses = new vector<MY_PROCESSENTRY32>();

	if (getList(myProcesses,processName))
	{
		if (result = (myProcesses->size() == 1))
		{
			*myProcess = myProcesses->front();
		}
	}
	delete myProcesses;
	return result;
}

bool getCurrentDirectory(wstring *myDirectory)
{
	bool result = false;
	DWORD DirSize = GetCurrentDirectory(0,NULL);
	TCHAR *myBuffer = new TCHAR[DirSize];
	if (DirSize > 0 && GetCurrentDirectory(DirSize,myBuffer) == DirSize - 1)
	{
		myDirectory->assign(myBuffer);
		result = true;
	}
	delete myBuffer;
	return result;
}

bool getAbsolutePathOf(wstring &thisData,wstring *response)
{
	bool result = false;
	TCHAR myBuffer[MAX_PATH];

	if (PathIsRelative(thisData.c_str()))
	{
		wstring Rep = TEXT("");
		if (result = getCurrentDirectory(&Rep))
		{
			PathCombine(myBuffer,Rep.c_str(),thisData.c_str());
			response->assign(myBuffer);
		}
	}
	else
	{
		if (result = (PathCanonicalize(myBuffer,thisData.c_str()) != 0))
		{
			response->assign(myBuffer);
		}
	}
	return result;
}

bool isFileExist(wstring &file,bool *result)
{
	bool success = false;
	HANDLE hFile = CreateFile(file.c_str(),0,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);

	if (success = (hFile && hFile != INVALID_HANDLE_VALUE))
	{
		CloseHandle(hFile);
		*result = true;
	}
	else if (success = (GetLastError() == ERROR_FILE_NOT_FOUND))
		*result = false;
	return success;
}

bool writeMemory(void *BaseAddress,const void * SourceAddress,size_t length,HANDLE handleProcess)
{
	bool success = false;
	DWORD oldProtect,oldProtect2;
	if (handleProcess == INVALID_HANDLE_VALUE)
	{
		if (VirtualProtect(BaseAddress,length,PAGE_EXECUTE_READWRITE,&oldProtect) != 0)
		{
			success = (memcpy_s(BaseAddress,length,SourceAddress,length) == 0);
			VirtualProtect(BaseAddress,length,oldProtect,&oldProtect2);
		}
	}
	else
	{
		if (VirtualProtectEx(handleProcess,BaseAddress,length,PAGE_EXECUTE_READWRITE,&oldProtect) != 0)
		{
			SIZE_T dwByteWrite = 0;
			success = ((WriteProcessMemory(handleProcess,BaseAddress,SourceAddress,length,&dwByteWrite) != 0) && (dwByteWrite == length));
			VirtualProtectEx(handleProcess,BaseAddress,length,oldProtect,&oldProtect2);
		}
	}

	return success;
}

bool injectLibraryByHandle(const HANDLE & handleProcess,wstring * fullLibraryPath)
{
	bool success = false;

	wstring LibComplete = TEXT("");
	if (getAbsolutePathOf(*fullLibraryPath,&LibComplete))
	{
		bool fileExist = false;
		if (isFileExist(LibComplete,&fileExist) && fileExist)
		{
			SIZE_T szFullLibraryPath = static_cast<SIZE_T>((LibComplete.size() + 1) * sizeof(TCHAR));

			if (LPVOID remoteVM = VirtualAllocEx(handleProcess,NULL,szFullLibraryPath,MEM_COMMIT,PAGE_EXECUTE_READWRITE))
			{
				if (writeMemory(remoteVM,LibComplete.c_str(),szFullLibraryPath,handleProcess))
				{
					PTHREAD_START_ROUTINE pThreadStart = reinterpret_cast<PTHREAD_START_ROUTINE>(GetProcAddress(GetModuleHandle(TEXT("kernel32")),"LoadLibraryW"));
					HANDLE hRemoteThread = INVALID_HANDLE_VALUE;

					if (GLOB_Version.dwMajorVersion > 5)
					{
						PRTL_CREATE_USER_THREAD RtlCreateUserThread = reinterpret_cast<PRTL_CREATE_USER_THREAD>(GetProcAddress(GetModuleHandle(TEXT("ntdll")),"RtlCreateUserThread"));
						SetLastError(RtlCreateUserThread(handleProcess,NULL,0,0,0,0,pThreadStart,remoteVM,&hRemoteThread,NULL));
					}
					else
					{
						hRemoteThread = CreateRemoteThread(handleProcess,NULL,0,pThreadStart,remoteVM,0,NULL);
					}

					if (hRemoteThread && hRemoteThread != INVALID_HANDLE_VALUE)
					{
						WaitForSingleObject(hRemoteThread,INFINITE);
						success = true;
						CloseHandle(hRemoteThread);
					}
				}
				VirtualFreeEx(handleProcess,remoteVM,0,MEM_RELEASE);
			}
		}
	}
	return success;
}

bool injectLibraryByPid(const DWORD & pid,wstring * fullLibraryPath)
{
	bool result = false;
	if (HANDLE processHandle = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,false,pid))
	{
		result = injectLibraryByHandle(processHandle,fullLibraryPath);
		CloseHandle(processHandle);
	}
	return result;
}

bool injectLibraryByInSingleProcess(wstring & processName,wstring * fullLibraryPath)
{
	bool result = false;

	MY_PROCESSENTRY32 myProcess;
	if (getUniqueFromName(&myProcess,&processName))
	{
		result = injectLibraryByPid(myProcess.th32ProcessID,fullLibraryPath);
	}
	return result;
}