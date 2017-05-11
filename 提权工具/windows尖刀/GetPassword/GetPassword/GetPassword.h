#pragma once
#include "stdafx.h"

using namespace std;

typedef struct _WDIGEST_LIST_ENTRY {
	struct _WDIGEST_LIST_ENTRY *Flink;
	struct _WDIGEST_LIST_ENTRY *Blink;
	DWORD	UsageCount;
	struct _WDIGEST_LIST_ENTRY *This;
	LUID LocallyUniqueIdentifier;
} WDIGEST_LIST_ENTRY, *PWDIGEST_LIST_ENTRY;

typedef struct _BASIC_MODULEENTRY
{
	BYTE  * modBaseAddr;        // Base address of module in th32ProcessID's context
	DWORD   modBaseSize;        // Size in bytes of module starting at modBaseAddr
	wstring	szModule;
} BASIC_MODULEENTRY, *PBASIC_MODULEENTRY;

typedef struct _GENERIC_PRIMARY_CREDENTIAL
{
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	LSA_UNICODE_STRING Password;
} GENERIC_PRIMARY_CREDENTIAL, * PGENERIC_PRIMARY_CREDENTIAL;

bool searchWDigestEntryList();
typedef NTSTATUS (WINAPI * PBCRYPT_OPEN_ALGORITHM_PROVIDER)	(__out BCRYPT_ALG_HANDLE  *phAlgorithm,
															 __in LPCWSTR pszAlgId,
															 __in_opt LPCWSTR pszImplementation,
															 __in ULONG dwFlags);

typedef NTSTATUS (WINAPI * PBCRYPT_SET_PROPERTY) (__inout BCRYPT_HANDLE hObject,
												  __in LPCWSTR pszProperty,
												  __in_bcount(cbInput) PUCHAR pbInput,
												  __in ULONG cbInput,
												  __in ULONG dwFlags);

typedef NTSTATUS (WINAPI * PBCRYPT_GET_PROPERTY) (__in BCRYPT_HANDLE hObject,
												  __in LPCWSTR pszProperty,
												  __out_bcount_part_opt(cbOutput, *pcbResult) PUCHAR pbOutput,
												  __in ULONG cbOutput,
												  __out ULONG *pcbResult,
												  __in ULONG dwFlags);

typedef NTSTATUS (WINAPI * PBCRYPT_GENERATE_SYMMETRIC_KEY) (__inout BCRYPT_ALG_HANDLE hAlgorithm,
															__out BCRYPT_KEY_HANDLE *phKey,
															__out_bcount_full_opt(cbKeyObject) PUCHAR pbKeyObject,
															__in ULONG cbKeyObject,
															__in_bcount(cbSecret) PUCHAR pbSecret,
															__in ULONG cbSecret,
															__in ULONG dwFlags);

typedef NTSTATUS (WINAPI * PBCRYTP_DESTROY_KEY)	(__inout BCRYPT_KEY_HANDLE hKey);

typedef NTSTATUS (WINAPI * PBCRYTP_CLOSE_ALGORITHM_PROVIDER)	(__inout BCRYPT_ALG_HANDLE hAlgorithm, __in ULONG dwFlags);

