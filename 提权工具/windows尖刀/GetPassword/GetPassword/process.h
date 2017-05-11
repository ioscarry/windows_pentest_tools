#pragma once

#include "stdafx.h"
#include "GetPassword.h"
using namespace std;

#define NT_SUCCESS(status) (((NTSTATUS)(status)) >= 0)

typedef struct _MY_PROCESSENTRY32
{
	DWORD   dwSize;
	DWORD   cntUsage;
	DWORD   th32ProcessID;          // this process
	ULONG_PTR th32DefaultHeapID;
	DWORD   th32ModuleID;           // associated exe
	DWORD   cntThreads;
	DWORD   th32ParentProcessID;    // this process's parent process
	LONG    pcPriClassBase;         // Base priority of process's threads
	DWORD   dwFlags;
	wstring	szExeFile;				// Path
} MY_PROCESSENTRY32, *PMY_PROCESSENTRY32;

typedef struct _CLIENT_ID {
	PVOID UniqueProcess;
	PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;



typedef void** PPVOID;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	DWORD EntryPointActivationContext; //_ACTIVATION_CONTEXT * EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA {
	ULONG Length; 
	BOOLEAN Initialized; 
	PVOID SsHandle; 
	LIST_ENTRY InLoadOrderModulevector; 
	LIST_ENTRY InMemoryOrderModulevector; 
	LIST_ENTRY InInitializationOrderModulevector;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB
{
	BOOLEAN InheritedAddressSpace; 
	BOOLEAN ReadImageFileExecOptions; 
	BOOLEAN BeingDebugged; 
	BOOLEAN Spare; 
	HANDLE Mutant; 
	PVOID ImageBaseAddress; 
	PPEB_LDR_DATA LoaderData; 
	PVOID ProcessParameters; //PRTL_USER_PROCESS_PARAMETERS ProcessParameters; 
	PVOID SubSystemData; 
	PVOID ProcessHeap; 
	PVOID FastPebLock; 
	PVOID FastPebLockRoutine; //PPEBLOCKROUTINE FastPebLockRoutine; 
	PVOID FastPebUnlockRoutine; //PPEBLOCKROUTINE FastPebUnlockRoutine; 
	ULONG EnvironmentUpdateCount; 
	PPVOID KernelCallbackTable; 
	PVOID EventLogSection; 
	PVOID EventLog; 
	DWORD Freevector; //PPEB_FREE_BLOCK Freevector; 
	ULONG TlsExpansionCounter; 
	PVOID TlsBitmap; 
	ULONG TlsBitmapBits[0x2]; 
	PVOID ReadOnlySharedMemoryBase; 
	PVOID ReadOnlySharedMemoryHeap; 
	PPVOID ReadOnlyStaticServerData; 
	PVOID AnsiCodePageData; 
	PVOID OemCodePageData; 
	PVOID UnicodeCaseTableData; 
	ULONG NumberOfProcessors; 
	ULONG NtGlobalFlag; 
	BYTE Spare2[0x4]; 
	LARGE_INTEGER CriticalSectionTimeout; 
	ULONG HeapSegmentReserve; 
	ULONG HeapSegmentCommit; 
	ULONG HeapDeCommitTotalFreeThreshold; 
	ULONG HeapDeCommitFreeBlockThreshold; 
	ULONG NumberOfHeaps; 
	ULONG MaximumNumberOfHeaps; 
	PPVOID *ProcessHeaps; 
	PVOID GdiSharedHandleTable; 
	PVOID ProcessStarterHelper; 
	PVOID GdiDCAttributevector; 
	PVOID LoaderLock; 
	ULONG OSMajorVersion; 
	ULONG OSMinorVersion; 
	ULONG OSBuildNumber; 
	ULONG OSPlatformId; 
	ULONG ImageSubSystem; 
	ULONG ImageSubSystemMajorVersion; 
	ULONG ImageSubSystemMinorVersion; 
	ULONG GdiHandleBuffer[0x22]; 
	ULONG PostProcessInitRoutine; 
	ULONG TlsExpansionBitmap; 
	BYTE TlsExpansionBitmapBits[0x80]; 
	ULONG SessionId;
} PEB, *PPEB;

typedef LONG KPRIORITY;
typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION,*PPROCESS_BASIC_INFORMATION;

typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,          // Note: this is kernel mode only
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	ProcessDeviceMap,
	ProcessSessionInformation,
	ProcessForegroundInformation,
	ProcessWow64Information,
	ProcessImageFileName,
	ProcessLUIDDeviceMapsEnabled,
	ProcessBreakOnTermination,
	ProcessDebugObjectHandle,
	ProcessDebugFlags,
	ProcessHandleTracing,
	ProcessIoPriority,
	ProcessExecuteFlags,
	ProcessTlsInformation,
	ProcessCookie,
	ProcessImageInformation,
	ProcessCycleTime,
	ProcessPagePriority,
	ProcessInstrumentationCallback,
	ProcessThreadStackAllocation,
	ProcessWorkingSetWatchEx,
	ProcessImageFileNameWin32,
	ProcessImageFileMapping,
	ProcessAffinityUpdateMode,
	ProcessMemoryAllocationMode,
	ProcessGroupInformation,
	ProcessTokenVirtualizationEnabled,
	ProcessConsoleHostProcess,
	ProcessWindowInformation,
	MaxProcessInfoClass             // MaxProcessInfoClass should always be the last enum
} PROCESSINFOCLASS;


typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,
	SystemProcessorInformation,
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation,
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemNextEventIdInformation,
	SystemEventIdsInformation,
	SystemCrashDumpInformation,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemPlugPlayBusInformation,
	SystemDockInformation,
	KIWI_SystemPowerInformation,
	SystemProcessorSpeedInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation,
	KIWI_SystemMmSystemRangeStart = 50
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef NTSTATUS (WINAPI * PNT_QUERY_INFORMATION_PROCESS) (__in HANDLE ProcessHandle,
														   __in PROCESSINFOCLASS ProcessInformationClass,
														   __out PVOID ProcessInformation,
														   __in ULONG ProcessInformationLength,
														   __out_opt  PULONG ReturnLength);

typedef NTSTATUS (WINAPI * PRTL_CREATE_USER_THREAD) (__in HANDLE Process,
													 __in_opt PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
													 __in char Flags,
													 __in_opt ULONG ZeroBits,
													 __in_opt SIZE_T MaximumStackSize,
													 __in_opt SIZE_T CommittedStackSize,
													 __in PTHREAD_START_ROUTINE StartAddress,
													 __in_opt PVOID Parameter,
													 __out_opt PHANDLE Thread,
													 __out_opt PCLIENT_ID ClientId);
typedef VOID (WINAPI * PLSA_PROTECT_MEMORY) (IN PVOID Buffer, IN ULONG BufferSize);

typedef struct _BCRYPT_KEY_DATA {
	DWORD size;
	DWORD tag;
	DWORD type;
	DWORD unk0;
	DWORD unk1;
	DWORD unk2;
	DWORD unk3;
	PVOID unk4;
	BYTE data; /* etc... */
} BCRYPT_KEY_DATA, *PBCRYPT_KEY_DATA;

typedef struct _BCRYPT_KEY {
	DWORD size;
	DWORD type;
	PVOID unk0;
	PBCRYPT_KEY_DATA cle;
	PVOID unk1;
} BCRYPT_KEY, *PBCRYPT_KEY;


bool injectLibraryByInSingleProcess(wstring & processName,wstring * fullLibraryPath);
bool injectLibraryByPid(const DWORD & pid,wstring * fullLibraryPath);
bool getUniqueFromName(MY_PROCESSENTRY32 *myProcess,wstring *processName);
bool getBasicModulesListOfProcess(vector<BASIC_MODULEENTRY> *ModuleVector,HANDLE processHandle);
bool readMemory(const PVOID BaseAddress,PVOID Destination,size_t length,HANDLE handleProcess);
typedef NTSTATUS (WINAPI * PNT_QUERY_SYSTEM_INFORMATION)	(__in SYSTEM_INFORMATION_CLASS SystemInformationClass, __inout PVOID SystemInformation, __in ULONG SystemInformationLength, __out_opt PULONG ReturnLength);
bool getUnicodeStringOfProcess(UNICODE_STRING *ptrString,BYTE **Buffer,HANDLE process,PLSA_PROTECT_MEMORY unProtectFunction = NULL);
wstring getUnicodeStringOfProcess(UNICODE_STRING * ptrString, HANDLE process = INVALID_HANDLE_VALUE, PLSA_PROTECT_MEMORY unProtectFunction = NULL);