// Just_Reversi1.cpp : Defines the entry point for the application.

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "windowsx.h"
#include "process.h"
#include "C:\MyProjects\NEW_Dll\NEW_Dll.h"
HBITMAP hbtm;
HBITMAP hbtm1;
HBITMAP hbtm2;
HANDLE thread, Even;
bool End=false;
bool turn1=true;//åñëè òðó òîãäà õîä áåëûõ

class Fishka {
public:
	Fishka();
	~Fishka();
	short number;
	three color;
	HBITMAP bmpComp;
	HBITMAP bmpHuman;
	HBITMAP bmp;
	bool IfUsed();
	void Paint();
}
;
Fishka::Fishka()
{
};
Fishka::~Fishka()
{
};
bool Fishka::IfUsed()
{
return (0);
}
void Paint()
{
}
class Pole
{
public:
	Pole();
	~Pole();
	void Paint();
	void Init();
	void Save();
	void Load();
	Fishka* fptr;
	short size;
	bool IsOutPole(short id);
}
;
Pole::Pole()
{
	
	this->fptr=new Fishka[64];
}
;
Pole::~Pole()
{
	delete fptr;
};
void Pole::Init()
{
};
void Pole::Paint()
{
};
bool Pole::IsOutPole(short id)
{
	return(0);
}
;
class Game
{
public:
	Game();
	~Game();
	void StartGame();
	bool CompTurn();
	bool HumanTurn();
	bool End();
	bool SavePole();
	bool LoadPole();
	void REWTurn();
	void FFTurn();
	Pole Pole1;
	bool turn;
}
;
void Start(HWND hwnd){
	int id;turn1=1;
 
	for (int i=1000;i<=1063;i++) {
	  id=i;SendDlgItemMessage(hwnd,id,  // dialog box window handle 
             BM_SETIMAGE,IMAGE_BITMAP,          // message to send 
             (LONG) hbtm);
  }
id=1027;WHITE_B;
id=1028;BLACK_B;
id=1035;BLACK_B;
id=1036;WHITE_B;
SetDlgItemInt(hwnd,IDC_EDIT1,2,NULL);	
SetDlgItemInt(hwnd,IDC_EDIT2,2,NULL);
}

//Ôóíêöèÿ ïîòîêà
unsigned int Thread1(PVOID pvParam){
bool f=false,fz;LONG gethbtm;
DWORD black=0,white=0,neutral=0;three z;
SetDlgItemInt((HWND)pvParam,IDC_EDIT1,0,NULL);	
SetDlgItemInt((HWND)pvParam,IDC_EDIT2,0,NULL);	
	
	while (f==false){
	WaitForSingleObject(Even,INFINITE);
		black=0,white=0,neutral=0;fz=false;
	    for (int id=1000;id<=1063;id++){

gethbtm=SendDlgItemMessage((HWND)pvParam,id,BM_GETIMAGE,IMAGE_BITMAP,NULL);
LONG sethbtm1=(LONG)hbtm2;
LONG sethbtm2=(LONG)hbtm;
LONG sethbtm=(LONG)hbtm1;
	if (sethbtm==gethbtm) {z=no;}
	if (sethbtm1==gethbtm){z=yes;}
	if (sethbtm2==gethbtm){ z=undefined;}
	
		switch (z){
		case yes:white=white+1;			
		break;
		case no:black=black+1;
		break;
		case undefined:{neutral=neutral+1;
			if((Thread_Ht((HWND)pvParam,id,hbtm,hbtm1,hbtm2)==true)&&(turn1==true))
			{

				fz=true;
			}
		
					   }
			break; 
		}

	}
	
SetDlgItemInt((HWND)pvParam,IDC_EDIT1,white,NULL);	
SetDlgItemInt((HWND)pvParam,IDC_EDIT2,black,NULL);	
if ((neutral==0)|(fz==false)){End=true;}
if (End==true)	{
	
	if (white>black){MessageBox((HWND)pvParam,"ÂÛ ÂÛÈÃÐÀËÈ!","ÐÅÂÅÐÑÈ",MB_OK);}
	else {
	if (black>white){MessageBox((HWND)pvParam,"ÂÛ ÏÐÎÈÃÐÀËÈ!","ÐÅÂÅÐÑÈ",MB_OK);}
	else {MessageBox((HWND)pvParam,"ÍÈ×Üß!","ÐÅÂÅÐÑÈ",MB_OK);}

	}
Start((HWND) pvParam);
End=false;	
}

	}
	return(0);
}

bool InitDialog(HWND hwnd){
		
  LONG hInst=GetWindowLong(hwnd,GWL_HINSTANCE);
  hbtm=LoadBitmap((HINSTANCE)hInst,MAKEINTRESOURCE(IDB_BITMAP3));
  hbtm1=LoadBitmap((HINSTANCE)hInst,MAKEINTRESOURCE(IDB_BITMAP4));
  hbtm2=LoadBitmap((HINSTANCE)hInst,MAKEINTRESOURCE(IDB_BITMAP5));
  DWORD q;
	thread=chBEGINTHREADEX(NULL,NULL,Thread1,hwnd,0,&q);//ñòàðò ïîòîêà
	Even=CreateEvent(NULL,false,false,false);
  Start(hwnd);
 
  return true;
}
BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	chSETDLGICONS(hwnd, IDI_ICON1);
  InitDialog(hwnd);
  return(TRUE);
}

void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	


	if ((id!=IDOK)&&(id!=IDCANCEL)&&(id!=ID_START)&&(id!=IDC_SAVE)&&
		(id!=IDC_LOAD)&&(id!=IDC_ABOUT)&&(id!=WM_CLOSE))
	{if (!((id>=1000)&&(id<=1063))) id=0;}
	switch (id) {

	case 0:
		break;
	case IDC_ABOUT:
		MessageBox(hwnd,"Ïðîãðàììà íàïèñàíà Ìàðòûíåö Àíäðååì. Êðàñíîäàð2003. andrews-answer@narod.ru","Î ïðîãðàììå",MB_OK);
		
		break;
	case IDC_SAVE:
		Save(hwnd,hbtm,hbtm1,hbtm2);
		 
		break;
	case IDC_LOAD:
		Load(hwnd,hbtm,hbtm1,hbtm2);
		SetEvent(Even);
		break;
	case ID_START:
		Start(hwnd);
		break;
	case IDCANCEL:
     
		break;
	case WM_CLOSE:
		EndDialog(hwnd,id);
		break;
   case IDOK:
  EndDialog(hwnd, id);
	   break;
   
   default:
	
	switch (turn1){
		
	case 1:
		
		SetEvent(Even);
		bool cv=Ht(hwnd,id,hbtm,hbtm1,hbtm2);
		if (cv==true){
		turn1=!turn1;
		Comp_turn(hwnd,hbtm,hbtm1,hbtm2);
		id=best_t.step;
		if (id!=0) {	
		turn1=!turn1;}
		else {End=true;}
		

		}
		}
		
		break;

	}
	}


INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {
   
  chHANDLE_DLGMSG(hwnd, WM_COMMAND,Dlg_OnCommand);
  chHANDLE_DLGMSG(hwnd, WM_INITDIALOG,Dlg_OnInitDialog); 
 
     
   }
   return(FALSE);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD_FORMVIEW), 
         NULL,(DLGPROC) Dlg_Proc,NULL);
	CloseHandle(thread);	   
	CloseHandle(Even);
	return (0);
}




