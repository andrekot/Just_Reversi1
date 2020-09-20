
#pragma once
#include "stdafx.h"
#include "New_Dll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

bool turn;//если тру тогда ход белых
int steps2[8];
int steps[8];
static B_turn Best;
NEW_DLL_API B_turn best_t;
 //если фишка бела€, функци€ возвращает yes
three IfWhite(HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){//провер€ю черна€ фишка или бела€
//см. макрос IFWHITE
LONG gethbtm;
gethbtm=SendDlgItemMessage(hwnd,id,BM_GETIMAGE,IMAGE_BITMAP,NULL);
LONG sethbtm1=(LONG)hbtm2;
LONG sethbtm2=(LONG)hbtm;
LONG sethbtm=(LONG)hbtm1;
	if (sethbtm==gethbtm) 
	{return (no);}
	if (sethbtm1==gethbtm){return (yes);}
	if (sethbtm2==gethbtm){ return (undefined);}

}
//в области ли id?
bool IsOut(int id){
	if ((id>=1063)&&(id<=1000)) {return(true);}
	else return (false);
}


//‘ункци€ вставл€ет мои битмапы в кнопки 1-бела€ кнопка,2-черна€
//см. макросы WHITE_B BLACK_B
NEW_DLL_API void DrawBitmap(bool f,HWND hwnd,int id,HBITMAP hbtm1,HBITMAP hbtm2){

	switch (f){
  case 0:SendDlgItemMessage(hwnd,id,BM_SETIMAGE,IMAGE_BITMAP,(LONG)hbtm2);
	  f=1;
	  break;
  case 1:SendDlgItemMessage(hwnd,id,  // dialog box window handle 
             BM_SETIMAGE,IMAGE_BITMAP,          // message to send 
             (LONG) hbtm1);
	  f=0;
	  break;
	} 

};

//вычисл€ем id по направлени€м 
int local_id(int id,myways ways) {
	int lid;
	switch (ways){
		case LL:lid=id-8;break;
		case RR:lid=id+8;break;
		case TT:lid=id-1;break;
		case BB:lid=id+1;break;
		case LT:lid=id-9;break;
		case RT:lid=id+7;break;
		case RB:lid=id+9;break;
		case LB:lid=id-7;break;
	default:lid=0;break;
	}
	if (IsOut(lid)) {return (0);}
	else return (lid);
}
//–екурсивна€ функци€ считает сколько в одном направлении одного цвета кнопок
//возвращает первую не закрашеную кнопку
int Recourse(HWND hwnd,int id,myways ways,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
	id=local_id(id,ways);
	three z=IFWHITE;
	if ((z==yes)&&(turn==false))
	{Recourse(hwnd,id,ways,hbtm,hbtm1,hbtm2);}
	else if ((z==undefined)&&(turn==0)){return(id);}
	else if ((z==no)&&(turn==true)){Recourse(hwnd,id,ways,hbtm,hbtm1,hbtm2);}
	else if ((z==yes)&&(turn==true)){return(id);}
	else return (0);
}

int Recourse2(HWND hwnd,int id,myways ways,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
	id=local_id(id,ways);three z=IFWHITE;
	if (z==yes){Recourse2(hwnd,id,ways,hbtm,hbtm1,hbtm2);}
	else if (z==no) return (id);
	else return (0);
}

//прорисовка хода
void PaintTurn(HWND hwnd,B_turn best_t,HBITMAP hbtm1,HBITMAP hbtm2){
	int i=0,cid,id;bool f=false;
	cid=best_t.id;
	while (f!=true){
		id=local_id(cid,(myways)best_t.way);
			if ((id==best_t.step)|(i>6)){f=true;}
			else {if((turn==true)){BLACK_B;}
					else {WHITE_B;}
	cid=id;}
	i=i+1;
	}

}
// переворачивание фишек
void GetNextStep(int* step,HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
 	myways w;three z1,z2;
	int* step1;
	z2=IFWHITE;
	int cid=id;
	for (int i=1;i<=8;i++){//8 направлений
		step1=step;
		w=(myways)i;
		id=local_id(cid,w);
		z1=IFWHITE;
		if ((id!=0)&&(id!=999)) {
		if ((z1==yes)&&(turn==false))
		{step1=step+i-1;*step1=Recourse(hwnd,cid,w,hbtm,hbtm1,hbtm2);}
		else if ((z1==no)&&(turn==true)){step1=step+i-1;*step1=Recourse(hwnd,cid,w,hbtm,hbtm1,hbtm2);}
		else { step1=step+i-1;*step1=0;}
		}		
	
	}

}
//функци€ определ€ет критические точки на сторонах
myways Region(int id)
{
	myways cid=net,rid=net;	
	float f=((float)id-1000)/8,f1=((float)id-999)/8;
	for (int k=1;k<=8;k++){
	switch (k) {
	case 1:if ((id>=1000)&&(id<=1007)){cid=LL;}
	break;
	case 2:if ((id>=1056)&&(id<=1063)){cid=RR;}
	break;
	case 3:if ((f-(int)(f))==0)
	{cid=TT;}
	break;
	case 4:if ((f1-(int)(f1))==0)
	{cid=BB;}
	break;
	case 5:if (((id>=1000)&&(id<=1007))&&((f-(int)(f))==0)){cid=LT;}
	break;
	case 6:if (((id>=1056)&&(id<=1063))&&((f1-(int)(f1))==0)){cid=RB;}
	break;
	case 7:if (((id>=1056)&&(id<=1063))&&((f-(int)(f))==0)){cid=RT;}
	break;
	case 8:if (((id>=1000)&&(id<=1007))&&((f1-(int)(f1))==0)){cid=LB;}
	break;
	
	}
	if (cid!=net){rid=cid;}
	}
	return rid;
}

//определ€ю не выходит ли за границы ход?
bool InRegion(B_turn best_t){
	int rid,cid,local;
	if ((best_t.step<1000)|(best_t.step>1063)){return false;}
	local=best_t.id;
//	rid=(int)Region(best_t.id);
	cid=best_t.way;
	for (int j=1;j<=7;j++){
	rid=Region(local);
	if (rid!=net){
	
	switch (rid) {
	case 1:if (cid==RR){return true;}
		break;
	case 2:if (cid==LL){return true;}
		break;
	case 3:
		if ((cid==LT)|(cid==RT)|(cid==TT)){
			return false;}
		break;
	case 4:
		if ((cid==LB)|(cid==RB)|(cid==BB)){
			return false;}
		break;
	case 5:
		if ((cid==LT)|(cid==TT)|(cid==LL)|(cid==RT)|(cid==LB)){
			return false;}
		break;
	case 6:
		if ((cid==RR)|(cid==BB)|(cid==RB)|(cid==LB)|(cid==RT)){
			return false;}
		break;
	case 7:
		if ((cid==RR)|(cid==TT)|(cid==RT)|(cid==RB)|(cid==LT)){
			return false;}
		break;
	case 8:
		if ((cid==LL)|(cid==BB)|(cid==LB)|(cid==RB)|(cid==LT)){
			return false;}
		break;
	}}
	local=local_id(local,(myways)cid);
	if (local==best_t.step){j=8;}
	}
return true;}
// переворачивание фишек
bool Forcing(HWND hwnd,B_turn best_t,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2)
{	
	int id,id1;B_turn c_turn;three z;
	c_turn.id=best_t.step;
	for (int i=1;i<=8;i++){
	id=local_id(c_turn.id,(myways)i);
	if (((best_t.way-i)==1)|((best_t.way-i)==-1)){;}
	else {
	z=IFWHITE;
	if (z==yes){id1=Recourse2(hwnd,id,(myways)i,hbtm,hbtm1,hbtm2);
	if ((id1!=0)){ c_turn.step=id1;c_turn.way=i;
	if (InRegion(c_turn)){PaintTurn(hwnd,c_turn,hbtm1,hbtm2);return (true);}}}
	}	
	}
return(false);
}
NEW_DLL_API bool Ht(HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
B_turn hturn;bool flag=false;turn=true;
	int hsteps[8];
	for (int i=1;i<=8;i++){
		hsteps[i]=0;}
	three z=IFWHITE;
	if (z==undefined){
	for (i=1;i<=8;i++){
		GetNextStep(&hsteps[1],hwnd,id,hbtm,hbtm1,hbtm2);}
	for ( i=1;i<=8;i++){
		if (hsteps[i]!=0){hturn.way=i;
		hturn.step=hsteps[i];
		hturn.id=id;
		if (InRegion(hturn)){
			BLACK_B;
		PaintTurn(hwnd,hturn,hbtm1,hbtm2);
		flag=true;

		}
	
	}}
			
				}
return flag;	
}
NEW_DLL_API bool Thread_Ht(HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
B_turn hturn;bool flag1=false;turn=true;
	int hsteps[8];
	for (int i=1;i<=8;i++){
		hsteps[i]=0;}
	three z=IFWHITE;
	if (z==undefined){
	for (i=1;i<=8;i++){
		GetNextStep(&hsteps[1],hwnd,id,hbtm,hbtm1,hbtm2);}
	for ( i=1;i<=8;i++){
		if (hsteps[i]!=0){hturn.way=i;
		hturn.step=hsteps[i];
		hturn.id=id;
		if (InRegion(hturn)){
		flag1=true;
		}
	
	}}
			
				}
return flag1;	
}

B_turn AnalyseTurn(HWND hwnd,int id,int* step2,bool flag,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
	int* step1=step2;
	if (flag==true){Best.pr=none;Best.step=0;Best.id=0;
	Best.way=0;//сброс лучшего хода дл€ другой кнопки
	return Best;}
	priority pr;//уровень приоритета
	three color;
	for (int i=1;i<=8;i++) {
		step1=step2+i-1;
		
		switch (*step1) {
		case 1000:pr=high;break;
		case 1007:pr=high;break;
		case 1056:pr=high;break;
		case 1063:pr=high;break;
		case 1001:pr=minus;break;
		case 1006:pr=minus;break;
		case 1008:pr=minus;break;
		case 1009:pr=minus;break;
		case 1014:pr=minus;break;
		case 1015:pr=minus;break;
		case 1048:pr=minus;break;
		case 1049:pr=minus;break;
		case 1054:pr=minus;break;
		case 1055:pr=minus;break;
		case 1057:pr=minus;break;
		case 1062:pr=minus;break;
		case 0:pr=none;break;
		default:
		if ((((float)*step1-1000)/8)==((int)((*step1-1000)/8))&&(*step1!=0)){pr=medium;}
		if ((((float)*step1-999)/8)==((int)((*step1-999)/8))&&(*step1!=0)){pr=medium;}
		if ((*step1>=1002)&&(*step1<=1007)){pr=medium;}
		if ((*step1>=1057)&&(*step1<=1063)){pr=medium;}
		else {pr=low;}
		break;
		}
		color=IfWhite(hwnd,*step1,hbtm,hbtm1,hbtm2);
		if ((pr>Best.pr)&&(color==undefined)) {
		Best.id=id;Best.pr=pr;
		Best.way=(i);
		Best.step=*step1;}
		
	}

return Best;
}
NEW_DLL_API void Comp_turn(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2) {
	// функци€ - ход компьютера
	turn=false;
		B_turn curr_t;int id;three color;
		best_t.pr=none;
		best_t.id=0;best_t.step=0;
		best_t.forced=0;
		for (int i=1;i<=8;i++){
		steps2[i]=0;}
		for (int j=1;j<=64;j++) {
		id=999+j;
		color=IFWHITE;	
		if (color==no){
				
				GetNextStep(&steps2[1],hwnd,id,hbtm,hbtm1,hbtm2);
				AnalyseTurn(hwnd,NULL,&steps2[1],true,hbtm,hbtm1,hbtm2);
				curr_t=AnalyseTurn(hwnd,id,&steps2[1],false,hbtm,hbtm1,hbtm2);
				if (InRegion(curr_t)){
				if ((curr_t.pr!=0)&&(curr_t.pr>best_t.pr)){
				best_t.pr=curr_t.pr;
				best_t.id=curr_t.id;best_t.step=curr_t.step;
				best_t.forced=curr_t.forced;best_t.way=curr_t.way;
				}
				}
				}
		
		}
		 if ((best_t.step>=1000)&&(best_t.step<=1063)){
			 DrawBitmap(1,hwnd,best_t.step,hbtm1,hbtm2);
			 PaintTurn(hwnd,best_t,hbtm1,hbtm2);
		Forcing(hwnd,best_t,hbtm,hbtm1,hbtm2);}

		}
//‘ункци€ сохранени€ игры
NEW_DLL_API void Save(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2){
	HANDLE hfile=CreateFile("Just_Reversi.dat",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|
			FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		HANDLE FMAP=CreateFileMapping(hfile,NULL,PAGE_READWRITE,0,64,NULL);
		PBYTE pvd=(PBYTE)MapViewOfFile(FMAP,FILE_MAP_WRITE,0,0,64);
		for (int i=1;i<=64;i++){
		int id=999+i;
		pvd[i]=(int)IFWHITE;
		}
		UnmapViewOfFile(pvd);
		CloseHandle(hfile);
		CloseHandle(FMAP);
		
}
//функци€ загрузки игры
NEW_DLL_API void Load(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2)
{
	HANDLE hfile=CreateFile("Just_Reversi.dat",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|
			FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		HANDLE FMAP=CreateFileMapping(hfile,NULL,PAGE_READONLY,0,0,NULL);
		PBYTE pvd=(PBYTE)MapViewOfFile(FMAP,FILE_MAP_COPY,0,0,0);
		for (int i=1;i<=64;i++){
		int id=999+i;
		switch (pvd[i]){
		case 1:BLACK_B;
			break;
		case 2:WHITE_B;
			break;
		case 3:SendDlgItemMessage(hwnd,id,  
             BM_SETIMAGE,IMAGE_BITMAP,           
             (LONG) hbtm);
			break;
		
		}
		}
		UnmapViewOfFile(pvd);
		CloseHandle(hfile);
		CloseHandle(FMAP);
}

