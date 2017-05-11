; PESniffer for PEiD (PEiD plugin) (PESniffer.dll from PETools by NEOx)
; =======================================================================================
; Author        : Slip [tPORt]
; Homepage      : http://slip.31337.pl
; EMail         : slip_2k5@pisem.net
; IDE           : FASM 1.65.25
; =======================================================================================
; Last modified : 20.05.2006

format pe gui 4.0 dll
entry DllEntryPoint

include "%fasminc%\win32a.inc"
;include "c:\fasm\include\win32a.inc"

MAX_PATH =                      260
IDD_MAIN =                      100
IDRB_EPSCAN =                   101
IDRB_SECTIONSCAN =              102
IDB_DONE =                      103
IDS_DATABASEINFORMATION =       104

PS_EPSCAN =                     0
PS_SECTIONSCAN =                1

; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
section ".slip" data readable writeable
szPluginName                    db "PESniffer for PEiD",0
szPEiDWindowClass               db "#32770",0
szPEiDWindowText                db "PEiD v0.94",0
szButton                        db "BUTTON",0
szEdit                          db "EDIT", 0
szStatic                        db "STATIC", 0
szPESnifferDll                  db "PESniffer.dll",0
szAnalyzeFile                   db "AnalyzeFile",0
szGetTotalSignatures            db "GetTotalSignatures",0
szIsDataBaseLoaded              db "IsDataBaseLoaded",0
szTotalSigns                    db "Total signatures in database:  %d",0
szPESniffer                     db "PESniffer:",0
sz_                             db ">",0
sz_ms                           db " (%d ms)",0
szError                         db "Error",0
szPESnifferDllNotFound          db "PESniffer.dll not found! Please copy it in PEiD directory.",0
szSignsTxtNotFound              db "Sign.txt not found! Please copy it in PEiD directory.",0
szKeyName                       db "Software\PEiD",0
hInstance                       dd 0
hPEiDInstance                   dd 0
hPEiDWindow                     dd 0
hEdit                           dd 0
hButton                         dd 0
hStatic                         dd 0
hFont                           dd 0
dwOldPEiDWindowProc             dd 0
szFileName                      rb MAX_PATH
szDetected                      rb MAX_PATH
szBuffer                        rb MAX_PATH
AnalyzeFile                     dd 0
GetTotalSignatures              dd 0
IsDataBaseLoaded                dd 0
dwScan                          dd 0
dwTotalSignatures               dd 0
dwScanTime                      dd 0
hKey                            dd 0
dwSize                          dd 4
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
section ".slip" code readable writeable executable
proc DllEntryPoint hinstDLL,fdwReason,lpvReserved
                push    [hinstDLL]
                pop     [hInstance]
                xor     eax, eax
                inc     eax
                ret
endp
; <------------------------------------------------------------------------------------->
proc LoadOptions
                invoke  RegCreateKeyEx, HKEY_CURRENT_USER, szKeyName, 0, 0, 0, KEY_ALL_ACCESS, 0, hKey, 0
                invoke  RegQueryValueEx, [hKey], szPluginName, 0, REG_DWORD, dwScan, dwSize
                invoke  RegCloseKey, [hKey]
                ret
endp
; <------------------------------------------------------------------------------------->
proc SaveOptions
;local   hKey:                   DWORD

                invoke  RegCreateKeyEx, HKEY_CURRENT_USER, szKeyName, 0, 0, 0, KEY_ALL_ACCESS, 0, hKey, 0
                invoke  RegSetValueEx, [hKey], szPluginName, 0, REG_DWORD, dwScan, 4
                invoke  RegCloseKey, [hKey]
                ret
endp
; <------------------------------------------------------------------------------------->
proc MainDialogProc stdcall hDlg, uMsg, wParam, lParam
                push    ebx
                push    esi
                push    edi
                cmp     [uMsg], WM_INITDIALOG
                je      .wm_initdialog
                cmp     [uMsg], WM_CLOSE
                je      .wm_close
                cmp     [uMsg], WM_COMMAND
                je      .wm_command
                jmp     .finish

        .wm_initdialog:
                stdcall [GetTotalSignatures]
                mov     [dwTotalSignatures], eax
                invoke  wvsprintf, szBuffer, szTotalSigns, dwTotalSignatures
                invoke  SetDlgItemText, [hDlg], IDS_DATABASEINFORMATION, szBuffer
                cmp     [dwScan], PS_EPSCAN
                jne     .sectionscan
                invoke  CheckDlgButton, [hDlg], IDRB_EPSCAN, BST_CHECKED
                jmp     .finish

        .sectionscan:
                invoke  CheckDlgButton, [hDlg], IDRB_SECTIONSCAN, BST_CHECKED
                jmp     .finish

        .wm_command:
                mov     ebx, [wParam]
                xor     eax, eax
                mov     ax, bx
                cmp     eax, IDB_DONE
                je      .idb_done
                jmp     .finish

        .idb_done:
                invoke  IsDlgButtonChecked, [hDlg], IDRB_EPSCAN
                cmp     eax, BST_CHECKED
                je      .checked
                push    PS_SECTIONSCAN
                pop     [dwScan]
                jmp     .wm_close

        .checked:
                push    PS_EPSCAN
                pop     [dwScan]
                jmp     .wm_close

        .wm_close:
                call    SaveOptions
                invoke  EndDialog, [hDlg], 0
                jmp     .finish

        .finish:
                xor     eax, eax
                pop     edi
                pop     esi
                pop     ebx
                ret
endp
; <------------------------------------------------------------------------------------->
proc NewPEiDWindowProc stdcall hDlg, uMsg, wParam, lParam
                push    ebx
                push    esi
                push    edi
                cmp     [uMsg], WM_COMMAND
                je      .wm_command
                jmp     .finish

        .wm_command:
                mov     ebx, [lParam]
                cmp     ebx, [hButton]
                jne     .l1
                call    DoMyJob
                jmp     .finish

        .l1:
                mov     ebx, [wParam]
                xor     eax, eax
                mov     ax, bx
                cmp     eax, 1001
                jne     .finish
                invoke  GetDlgItem, [hDlg], 1000
                invoke  GetWindowText, eax, szBuffer, MAX_PATH
                invoke  lstrcmp, szBuffer, szFileName
                or      eax, eax
                je      .finish
                invoke  lstrcpy, szFileName, szBuffer
                invoke  GetTickCount
                mov     [dwScanTime], eax
                stdcall [AnalyzeFile], szFileName, [dwScan], 0, szDetected
                invoke  GetTickCount
                sub     eax, [dwScanTime]
                ;neg     eax
                or      eax, eax
                je      .l2
                mov     [dwScanTime], eax
                invoke  wvsprintf, szBuffer, sz_ms, dwScanTime
                invoke  lstrcat, szDetected, szBuffer

        .l2:
                invoke  SetWindowText, [hEdit], szDetected

        .finish:
                invoke  CallWindowProc, [dwOldPEiDWindowProc], [hDlg], [uMsg], [wParam], [lParam]
                pop     edi
                pop     esi
                pop     ebx
                ret
endp
; <------------------------------------------------------------------------------------->
proc InitPlugin
                invoke  LoadLibrary, szPESnifferDll
                mov     edi, eax
                invoke  GetProcAddress, eax, szAnalyzeFile
                mov     [AnalyzeFile], eax
                or      eax, eax
                je      .l1
                invoke  GetProcAddress, edi, szGetTotalSignatures
                mov     [GetTotalSignatures], eax
                invoke  GetProcAddress, edi, szIsDataBaseLoaded
                mov     [IsDataBaseLoaded], eax
                stdcall [IsDataBaseLoaded]
                or      eax, eax
                je      .l1
                invoke  GetModuleHandle, NULL
                mov     [hPEiDInstance], eax
                invoke  CreateWindowEx, 0, szStatic, szPESniffer, WS_CHILD + WS_VISIBLE + SS_LEFT, 6, 126, 402, 16, [hPEiDWindow], NULL, eax
                mov     [hStatic], eax
                invoke  CreateWindowEx, WS_EX_STATICEDGE, szEdit, NULL, WS_CHILD + WS_VISIBLE + ES_READONLY, 67, 125, 312, 16, [hPEiDWindow], NULL, [hPEiDInstance]
                mov     [hEdit], eax
                invoke  CreateWindowEx, WS_EX_STATICEDGE, szButton, sz_, WS_CHILD + WS_VISIBLE, 387, 124, 21, 19, [hPEiDWindow], NULL, [hPEiDInstance]
                mov     [hButton], eax
                invoke  SendMessage, [hPEiDWindow], WM_GETFONT, 0, 0
                mov     [hFont], eax
                invoke  SendMessage, [hEdit], WM_SETFONT, eax, 0
                invoke  SendMessage, [hStatic], WM_SETFONT, [hFont], 0
                invoke  SendMessage, [hButton], WM_SETFONT, [hFont], 0
                invoke  GetWindowLong, [hPEiDWindow], GWL_WNDPROC
                mov     [dwOldPEiDWindowProc], eax
                invoke  SetWindowLong, [hPEiDWindow], GWL_WNDPROC, NewPEiDWindowProc
                call    LoadOptions
        .l1:
                ret
endp
; <------------------------------------------------------------------------------------->
proc TimerProc stdcall hWnd, uMsg, wParam, lParam
                cmp     [hPEiDWindow], 0
                jne     .l1
                invoke  FindWindow, szPEiDWindowClass, szPEiDWindowText
                test    eax, eax
                jz      .l1
                mov     [hPEiDWindow], eax
                call    InitPlugin
        .l1:
                ret
endp
; <------------------------------------------------------------------------------------->
proc LoadDll
                invoke  SetTimer, 0, 1, 1, TimerProc
                mov     eax, szPluginName
                ret
endp
; <------------------------------------------------------------------------------------->
proc DoMyJob
                cmp     [AnalyzeFile], 0
                je      .l1
                stdcall [IsDataBaseLoaded]
                or      eax, eax
                je      .l3
                invoke  DialogBoxParam, [hInstance], IDD_MAIN, [hPEiDWindow], MainDialogProc, 0
                jmp     .l2

        .l1:
                invoke  MessageBox, [hPEiDWindow], szPESnifferDllNotFound, szError, MB_ICONERROR
                jmp     .l2

        .l3:
                invoke  MessageBox, [hPEiDWindow], szSignsTxtNotFound, szError, MB_ICONERROR

        .l2:
                ret
endp
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
section ".slip" import data readable
        library kernel, "KERNEL32",\
                user, "USER32",\
                advapi, "ADVAPI32"

        import  kernel,\
                GetModuleHandle, "GetModuleHandleA",\
                lstrcmp, "lstrcmpA",\
                lstrcpy, "lstrcpyA",\
                LoadLibrary, "LoadLibraryA",\
                GetProcAddress, "GetProcAddress",\
                GetTickCount, "GetTickCount",\
                lstrcat, "lstrcatA"

        import  user,\
                SetTimer, "SetTimer",\
                FindWindow, "FindWindowA",\
                MessageBox, "MessageBoxA",\
                CreateWindowEx, "CreateWindowExA",\
                SendMessage, "SendMessageA",\
                CallWindowProc, "CallWindowProcA",\
                GetWindowLong, "GetWindowLongA",\
                SetWindowLong, "SetWindowLongA",\
                GetDlgItem, "GetDlgItem",\
                GetWindowText, "GetWindowTextA",\
                SetWindowText, "SetWindowTextA",\
                DialogBoxParam, "DialogBoxParamA",\
                EndDialog, "EndDialog",\
                IsDlgButtonChecked, "IsDlgButtonChecked",\
                CheckDlgButton, "CheckDlgButton",\
                SetDlgItemText, "SetDlgItemTextA",\
                wvsprintf, "wvsprintfA"

        import  advapi,\
                RegCreateKeyEx, "RegCreateKeyExA",\
                RegSetValueEx, "RegSetValueExA",\
                RegQueryValueEx, "RegQueryValueExA",\
                RegCloseKey, "RegCloseKey"
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
section ".slip" resource readable
        directory RT_DIALOG, dialogs

        resource dialogs, IDD_MAIN, LANG_ENGLISH + SUBLANG_DEFAULT, main_dialog

        dialog main_dialog, "PESniffer for PEiD", -1, -1, 200, 72, WS_CAPTION + WS_POPUP + WS_SYSMENU + DS_MODALFRAME + DS_CENTER, 0, 0, "TAHOMA", 8
                dialogitem "BUTTON", "Scan metod:", 0, 2, 0, 196, 35, WS_VISIBLE + BS_GROUPBOX
                dialogitem "BUTTON", "EP Scan", IDRB_EPSCAN, 5, 10, 100, 10, WS_VISIBLE + BS_AUTORADIOBUTTON
                dialogitem "BUTTON", "Section Scan", IDRB_SECTIONSCAN, 5, 20, 100, 10, WS_VISIBLE + BS_AUTORADIOBUTTON
                dialogitem "BUTTON", "Done", IDB_DONE, 80, 57, 40, 12, WS_VISIBLE, WS_EX_STATICEDGE
                dialogitem "BUTTON", "Database information:", 0, 2, 35, 196, 20, WS_VISIBLE + BS_GROUPBOX
                dialogitem "STATIC", "", IDS_DATABASEINFORMATION, 5, 43, 180, 10, WS_VISIBLE
        enddialog
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
; <------------------------------------------------------------------------------------->
section ".slip" export data readable
        export "PESniffer4PEiD.DLL",\
               LoadDll,"LoadDll",\
               DoMyJob,"DoMyJob"

section '.slip' fixups data discardable
