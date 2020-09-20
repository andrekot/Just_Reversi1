
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NEW_DLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NEW_DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef NEW_DLL_EXPORTS
#define NEW_DLL_API __declspec(dllexport)
#else
#define NEW_DLL_API __declspec(dllimport)
#endif

// This class is exported from the New_Dll.dll
class NEW_DLL_API CNew_Dll {
public:
	CNew_Dll(void);
	// TODO: add your methods here.
};

extern NEW_DLL_API int nNew_Dll;

extern NEW_DLL_API int fnNew_Dll(void);
enum three{yes=1,no=2,undefined=3};
enum myways{net=0,LL=1,RR=2,TT=3,BB=4,LT=5,RB=6,RT=7,LB=8};
enum priority{none=0,minus=1,low=2,medium=3,high=4};
struct B_turn {
	int id;
	int step;
	priority pr;
	int forced;
	int way;
};
extern NEW_DLL_API B_turn best_t;
extern NEW_DLL_API bool Ht(HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2);
extern NEW_DLL_API bool Thread_Ht(HWND hwnd,int id,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2);
extern NEW_DLL_API void Comp_turn(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2);
extern NEW_DLL_API void Save(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2);
extern NEW_DLL_API void Load(HWND hwnd,HBITMAP hbtm,HBITMAP hbtm1,HBITMAP hbtm2);
extern NEW_DLL_API void DrawBitmap(bool f,HWND hwnd,int id,HBITMAP hbtm1,HBITMAP hbtm2);


