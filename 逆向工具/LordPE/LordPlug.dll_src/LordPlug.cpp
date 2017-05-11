/*-------------------------------------------------
   LordPlug.dll -- LordPE功能扩展
               (c)www.pediy.com by kanxue 2005.10.10 
  -------------------------------------------------*/

#include <Windows.h>
#include <commctrl.h>

#define MAXINPUTLEN 512

//(1) 给LordPE查看输入表部分加上搜索功能 
void _cdecl Searchimport(const DWORD reversed, HWND hWnd)
{
  try
  {
    
    TCHAR cSearchBuffer[MAXINPUTLEN]={0};
    TCHAR cItem[512]={0};

    int listcount,nSearchLength,iItem;
    LVITEM lvitem;
    HWND hWinList;
    POINT Point;
    
        
    nSearchLength=GetDlgItemText(hWnd,10222,cSearchBuffer,sizeof(cSearchBuffer)/sizeof(TCHAR)+1);
    if(nSearchLength==0){
      return;
    }
    
    hWinList=GetDlgItem(hWnd,2202);
    
    listcount=SendMessage(hWinList, LVM_GETITEMCOUNT, 0, 0);
    if(0==listcount)
      return;
    
    
    //iItem=SendMessage(hWinList,LVM_GETNEXTITEM,-1,LVNI_FOCUSED);  //得到所选的行
    iItem=0;
    
    do{
      iItem++;
      
      if(iItem==listcount)
        break;
      
      lvitem.cchTextMax=512;
      lvitem.iSubItem=4; 
      lvitem.pszText=cItem;
      SendMessage(hWinList, LVM_GETITEMTEXT, (WPARAM)iItem, (LPARAM)&lvitem);
    }
    while(memicmp(cSearchBuffer,cItem,nSearchLength)!=0);
    
    if(iItem!=listcount){  
      SetDlgItemText(hWnd,2203,cItem);
      //选中ListView控件中的Item
      lvitem.state=LVIS_SELECTED | LVIS_FOCUSED;
      lvitem.stateMask=LVIS_SELECTED | LVIS_FOCUSED;
      SendMessage(hWinList,LVM_SETITEMSTATE,(WPARAM)iItem, (LPARAM)&lvitem);
      //滚动窗口
      SendMessage(hWinList,LVM_GETITEMPOSITION,(WPARAM)iItem,(LPARAM) (POINT*) &Point);
      SendMessage(hWinList,LVM_SCROLL,0,Point.y-50);
    }
    else
      SetDlgItemText(hWnd,2203,"没找到指定项目");
    
    return;
    
  }
  catch (...)
  {
    return ;
  }
  
  
}

/*

0040D473   > \E9 5AAE0000         jmp     004182D2                         ;  Case 111 (WM_COMMAND) of switch 0040D2A7
0040D478      90                  nop
0040D479      90                  nop
0040D47A      90                  nop
0040D47B      90                  nop
0040D47C   .  3D 04400000         cmp     eax, 4004                        ;  Switch (cases 89C..5002)


  


004182D2      8B4424 18           mov     eax, [esp+18]
004182D6      25 FFFF0000         and     eax, 0FFFF
004182DB      3D EF270000         cmp     eax, 27EE      
004182E0      74 3E               je      short 00418320 //是否操作了搜索框
004182E2      68 7CD44000         push    0040D47C
004182E7      C3                  retn



00418320   > \E8 0E000000   call    00418333
00418325   .  4C 6F 72 64 5>ascii   "LordPlug.dll",0
00418332   .  00            ascii   0
00418333   $  FF15 C0904100 call    [<&KERNEL32.LoadLibraryA>]       ; \LoadLibraryA
00418339   .  E8 11000000   call    0041834F
0041833E   .  53 65 61 72 6>ascii   "Searchimport",0
0041834B   .  00            ascii   0
0041834C   .  00            ascii   0
0041834D   .  00            ascii   0
0041834E   .  00            ascii   0
0041834F   $  50            push    eax                              ; |hModule
00418350   .  FF15 68914100 call    [<&KERNEL32.GetProcAddress>]     ; \GetProcAddress
00418356   .  83C4 0C       add     esp, 0C
00418359   .  FFD0          call    eax                             //调用LordPlug.dll中的Searchimport()函数
0041835B   .  83EC 0C       sub     esp, 0C
0041835E   .  68 7CD44000   push    0040D47C
00418363   .  C3            retn                                     ;  RET 用来作为跳转到 0040D47C


 */

/**************************************************************************************************************/
//(2) 给LordPE查看输入表部分加右键菜单(仅复制ThunkRVA/FirstThunk列)


 void _cdecl  PopMenuCopy(const DWORD reversed, HWND hWnd)
 {
   try
   {
     
     int iItem;
     LVITEM lvitem;
       TCHAR cItem[512]={0};
     HWND hWinList;
     HGLOBAL clipbuffer; 
     char * buffer=0; 
     
          
     hWinList=GetDlgItem(hWnd,2202);
     
     iItem=SendMessage(hWinList,LVM_GETNEXTITEM,-1,LVNI_FOCUSED);  //得到所选的行
     if(-1==iItem)
       return;
     
     lvitem.cchTextMax=512;
     lvitem.iSubItem=0; 
     lvitem.pszText=cItem;
     SendMessage(hWinList, LVM_GETITEMTEXT, (WPARAM)iItem, (LPARAM)&lvitem);
     
     
     //将取得文本放到剪贴簿  
     
     if(OpenClipboard(NULL)) 
     { 
       EmptyClipboard(); 
       clipbuffer = GlobalAlloc(GMEM_DDESHARE,lstrlen(cItem)+1); 
       if(clipbuffer==NULL) return;
       
       buffer = (char*)GlobalLock(clipbuffer); 
       strcpy(buffer, LPCSTR(cItem)); 
       GlobalUnlock(clipbuffer); 
       if(SetClipboardData(CF_TEXT,clipbuffer)!=0)
         clipbuffer = NULL;
       CloseClipboard(); 
       if (clipbuffer) GlobalFree(clipbuffer);
       
     } 
     
     
      return;
   }
   catch (...)
   {
     
     return ;
   }
   
   
 }
  
/*
 0040D6C4  |.  68 01500000   push    5001                             ; |ItemID = 5001 (20481.)
0040D6C9  |.  6A 00         push    0                                ; |Flags = MF_BYCOMMAND|MF_ENABLED|MF_STRING
0040D6CB  |.  50            push    eax                              ; |hMenu
0040D6CC  |.  A3 34E14100   mov     [41E134], eax                    ; |
0040D6D1  |.  FFD6          call    esi                              ; \AppendMenuA
0040D6D3  |.  A1 34E14100   mov     eax, [41E134]
0040D6D8  |.  68 7CBE4100   push    0041BE7C                         ; /pItem = "refresh"
0040D6DD  |.  68 02500000   push    5002                             ; |ItemID = 5002 (20482.)
0040D6E2  |.  6A 00         push    0                                ; |Flags = MF_BYCOMMAND|MF_ENABLED|MF_STRING
0040D6E4  |.  50            push    eax                              ; |hMenu => 002E0C87
0040D6E5  |.  FFD6          call    esi                              ; \AppendMenuA

00418370      68 80A64100   push    0041A680                         ;  ASCII "copy..."
00418375      68 00500000   push    5000
0041837A      6A 00         push    0
0041837C      50            push    eax
0041837D      A3 34E14100   mov     [41E134], eax
00418382      FFD6          call    esi
00418384      A1 34E14100   mov     eax, [41E134]
00418389      68 ECC84100   push    0041C8EC                         ;  ASCII "edit..."
0041838E      68 C4D64000   push    0040D6C4
00418393      C3            retn
00418394      0000          add     [eax], al
00418396      0000          add     [eax], al



CASE
0040D559   > \2D 05400000   sub     eax, 4005
0040D55E   .  74 6B         je      short 0040D5CB
0040D560   .  2D FC0F0000   sub     eax, 0FFC
0040D565   .  74 3D         je      short 0040D5A4
0040D567   .  48            dec     eax
0040D568   .  74 09         je      short 0040D573
0040D56A   >  33C0          xor     eax, eax                         ;  Default case of switch 0040D47C


0040D559   > \E9 46AE0000   jmp     004183A4
0040D55E   >  74 6B         je      short 0040D5CB
0040D560   .  2D FC0F0000   sub     eax, 0FFC                        ;  Switch (cases FFC..FFD)
0040D565   .  74 3D         je      short 0040D5A4
0040D567   .  48            dec     eax
0040D568   .  74 09         je      short 0040D573
0040D56A   >  33C0          xor     eax, eax                         ;  Default case of switch 0040D560



004183B6      68 25834100   push    00418325
004183BB      FF15 C0904100 call    [<&KERNEL32.LoadLibraryA>]       ;  kernel32.LoadLibraryA
004183C1      E8 0D000000   call    004183D3
004183C6      50            push    eax
004183C7      6F            outs    dx, dword ptr es:[edi]
004183C8      70 4D         jo      short 00418417
004183CA      65:6E         outs    dx, byte ptr es:[edi]
004183CC      75 43         jnz     short 00418411
004183CE      6F            outs    dx, dword ptr es:[edi]
004183CF      70 79         jo      short 0041844A
004183D1      0000          add     [eax], al
004183D3      50            push    eax
004183D4      FF15 68914100 call    [<&KERNEL32.GetProcAddress>]     ;  kernel32.GetProcAddress
004183DA      83C4 0C       add     esp, 0C
004183DD      FFD0          call    eax   //调用PopMenuCopy
004183DF      83EC 0C       sub     esp, 0C
004183E2      B8 01000000   mov     eax, 1
004183E7      5E            pop     esi
004183E8      83C4 08       add     esp, 8
004183EB      C2 1000       retn    10
*/

 /**************************************************************************************************************/

 //(3)当点击LordPE查看输入表部分中"View always FirstThunk",保持当前光条所在行在原来位置附件.(LordPE默认会将光条置到0行)

 int _cdecl  GetNextitem(const DWORD reversed, HWND hWnd)
 {
   try
   {
     
     
     int iItem;
     HWND hWinList;
     
          
     hWinList=GetDlgItem(hWnd,2202);
     
     iItem=SendMessage(hWinList,LVM_GETNEXTITEM,-1,LVNI_FOCUSED);  //得到所选的行
     if(-1==iItem)
       return 0;
     
     return iItem;
     
   }
   catch (...)
   {
     
     return FALSE;
   }
   
 }
 
 
 void  CALLBACK  SetCursortoItem(HWND hWnd,INT iItem)
 {
   try
   {
     
       LVITEM lvitem;
     HWND hWinList;
     POINT Point; 
     
     
     hWinList=GetDlgItem(hWnd,2202);
     
     if(0==SendMessage(hWinList, LVM_GETITEMCOUNT, 0, 0))
       return;
     
     //选中ListView控件中的Item
     lvitem.state=LVIS_SELECTED | LVIS_FOCUSED;
     lvitem.stateMask=LVIS_SELECTED | LVIS_FOCUSED;
     SendMessage(hWinList,LVM_SETITEMSTATE,(WPARAM)iItem, (LPARAM)&lvitem);
     //滚动窗口
     SendMessage(hWinList,LVM_GETITEMPOSITION,(WPARAM)iItem,(LPARAM) (POINT*)&Point);
     SendMessage(hWinList,LVM_SCROLL,0,Point.y-50);
     SetFocus(hWinList);
     
     
     return;
     
   }
   catch (...)
   {
     
     return;
   }
   
   
 }
 
/*




0040D496   .  3D 9C080000   cmp     eax, 89C
0040D49B      0F84 47AE0000 je      004182E8
0040D4A1   .  3D 01400000   cmp     eax, 4001

004182E8      68 25834100   push    00418325
004182ED      FF15 C0904100 call    [<&KERNEL32.LoadLibraryA>]       ;  kernel32.LoadLibraryA
004182F3      E8 0D000000   call    00418305
004182F8      47            inc     edi
004182F9      65:74 4E      je      short 0041834A
004182FC      65:78 74      js      short 00418373
004182FF      697465 6D 000>imul    esi, [ebp+6D], FF500000
00418307      15 68914100   adc     eax, <&KERNEL32.GetProcAddress>
0041830C      83C4 0C       add     esp, 0C
0041830F      FFD0          call    eax
00418311      83EC 0C       sub     esp, 0C
00418314      A3 D0EB4100   mov     [41EBD0], eax //返回值放全局变量中
00418319      68 39D54000   push    0040D539
0041831E      C3            retn




0040D539   > \8B4424 10     mov     eax, [esp+10]                    ;  Cases 89C,4004 of switch 0040D47C
0040D53D   .  6A 00         push    0                                ; /lParam = 0
0040D53F   .  6A 00         push    0                                ; |wParam = 0
0040D541   .  68 00340000   push    3400                             ; |Message = MSG(3400)
0040D546   .  50            push    eax                              ; |hWnd
0040D547   .  FF15 AC924100 call    [<&USER32.SendMessageA>]         ; \SendMessageA
0040D54D      90            nop
0040D54E    - E9 36D10000   jmp     0041A689
0040D553      90            nop





.rdata段
0041A689    68 25834100     push    00418325
0041A68E    FF15 C0904100   call    [<&KERNEL32.LoadLibraryA>]       ; kernel32.LoadLibraryA
0041A694    E8 11000000     call    0041A6AA
0041A699    53              push    ebx
0041A69A    65:74 43        je      short 0041A6E0
0041A69D    75 72           jnz     short 0041A711
0041A69F    73 6F           jnb     short 0041A710
0041A6A1    72 74           jb      short 0041A717
0041A6A3    6F              outs    dx, dword ptr es:[edi]
0041A6A4    49              dec     ecx
0041A6A5    74 65           je      short 0041A70C
0041A6A7    6D              ins     dword ptr es:[edi], dx
0041A6A8    0000            add     [eax], al
0041A6AA    50              push    eax
0041A6AB    FF15 68914100   call    [<&KERNEL32.GetProcAddress>]     ; kernel32.GetProcAddress
0041A6B1    FF35 D0EB4100   push    dword ptr [41EBD0]
0041A6B7    FF7424 14       push    dword ptr [esp+14]
0041A6BB    FFD0            call    eax
0041A6BD    B8 01000000     mov     eax, 1
0041A6C2    5E              pop     esi
0041A6C3    83C4 08         add     esp, 8
0041A6C6    C2 1000         retn    10




 */
/*
 (4)
修改FLC(File Location Calulator)窗口,各个文本框(VA,RVA,Offset)为只读属性,此时可以用鼠标复制里面的文本.(LordPE原来是将文本框禁止变灰,此时不可复制)

SendMessage(hWnd,EM_SETREADONLY,(WPARAM) bEnable,0);

0040C918    - E9 B4DD0000   jmp     0041A6D1
0040C91D      90            nop
0040C91E   .  55            push    ebp                              ; |hWnd
0040C91F   .  FFD3          call    ebx                              ; \EnableWindow
0040C921   .  A1 C0B14100   mov     eax, [41B1C0]



0041A6D1    BB DCA64100     mov     ebx, 0041A6DC
0041A6D6    68 1EC94000     push    0040C91E
0041A6DB    C3              retn
0041A6DC    8B4424 08       mov     eax, [esp+8]
0041A6E0    8B4C24 04       mov     ecx, [esp+4]
0041A6E4    34 01           xor     al, 1
0041A6E6    6A 00           push    0
0041A6E8    50              push    eax
0041A6E9    68 CF000000     push    0CF
0041A6EE    51              push    ecx
0041A6EF    FF15 AC924100   call    [<&USER32.SendMessageA>]         ; USER32.SendMessageA
0041A6F5    C2 0800         retn    8
0041A6F8    0000            add     [eax], al
 */

