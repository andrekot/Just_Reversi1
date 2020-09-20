// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A5AC47F4_92F0_446A_9582_AA5931CE101D__INCLUDED_)
#define AFX_STDAFX_H__A5AC47F4_92F0_446A_9582_AA5931CE101D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#define ISOUT IsOut(id)
#define COUNT if (flag==true) {forced++;}
#define IFWHITE IfWhite(hwnd,id,hbtm,hbtm1,hbtm2)
#define LEFT LRTB(0,hwnd,id)
#define RIGHT LRTB(1,hwnd,id)
#define TOP LRTB(2,hwnd,id)
#define BOTTOM LRTB(3,hwnd,id)
#define LEFT_TOP LRTB(4,hwnd,id)
#define LEFT_BOTTOM LRTB(5,hwnd,id)
#define RIGHT_TOP LRTB(6,hwnd,id)
#define RIGHT_BOTTOM LRTB(7,hwnd,id)
#define WHITE_B DrawBitmap(1,hwnd,id,hbtm1,hbtm2)
#define BLACK_B DrawBitmap(0,hwnd,id,hbtm1,hbtm2) 

// This macro returns TRUE if a number is between two others
#define chINRANGE(low, Num, High) (((low) <= (Num)) && ((Num) <= (High)))


//////////////////////////////// chDIMOF Macro ////////////////////////////////


// This macro evaluates to the number of elements in an array. 
#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))


///////////////////////////// chBEGINTHREADEX Macro ///////////////////////////


// This macro function calls the C runtime's _beginthreadex function. 
// The C runtime library doesn't want to have any reliance on Windows' data 
// types such as HANDLE. This means that a Windows programmer needs to cast
// values when using _beginthreadex. Since this is terribly inconvenient, 
// I created this macro to perform the casting.
typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStack, pfnStartAddr, \
   pvParam, fdwCreate, pdwThreadId)                 \
      ((HANDLE)_beginthreadex(                      \
         (void *)        (psa),                     \
         (unsigned)      (cbStack),                 \
         (PTHREAD_START) (pfnStartAddr),            \
         (void *)        (pvParam),                 \
         (unsigned)      (fdwCreate),               \
         (unsigned *)    (pdwThreadId)))


////////////////// DebugBreak Improvement for x86 platforms ///////////////////


#ifdef _X86_
#define DebugBreak()    _asm { int 3 }
#endif


/////////////////////////// Software Exception Macro //////////////////////////
#define chHANDLE_DLGMSG(hwnd, message, fn)  \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,  \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))

// Useful macro for creating your own software exception codes
#define MAKESOFTWAREEXCEPTION(Severity, Facility, Exception) \
   ((DWORD) ( \
   /* Severity code    */  (Severity       ) |     \
   /* MS(0) or Cust(1) */  (1         << 29) |     \
   /* Reserved(0)      */  (0         << 28) |     \
   /* Facility code    */  (Facility  << 16) |     \
   /* Exception code   */  (Exception <<  0)))


/////////////////////////// Quick MessageBox Macro ////////////////////////////


inline void chMB(PCSTR s) {
   char szTMP[128];
   GetModuleFileNameA(NULL, szTMP, chDIMOF(szTMP));
   MessageBoxA(GetActiveWindow(), s, szTMP, MB_OK);
}


//////////////////////////// Assert/Verify Macros /////////////////////////////


inline void chFAIL(PSTR szMsg) {
   chMB(szMsg);
   DebugBreak();
}


// Put up an assertion failure message box.
inline void chASSERTFAIL(LPCSTR file, int line, PCSTR expr) {
   char sz[128];
   wsprintfA(sz, "File %s, line %d : %s", file, line, expr);
   chFAIL(sz);
}


// Put up a message box if an assertion fails in a debug build.
#ifdef _DEBUG
#define chASSERT(x) if (!(x)) chASSERTFAIL(__FILE__, __LINE__, #x)
#else
#define chASSERT(x)
#endif


// Assert in debug builds, but don't remove the code in retail builds.
#ifdef _DEBUG
#define chVERIFY(x) chASSERT(x)
#else
#define chVERIFY(x) (x)
#endif


/////////////////////////// chHANDLE_DLGMSG Macro /////////////////////////////


// The normal HANDLE_MSG macro in WindowsX.h does not work properly for dialog
// boxes because DlgProc return a BOOL instead of an LRESULT (like
// WndProcs). This chHANDLE_DLGMSG macro corrects the problem:
#define chHANDLE_DLGMSG(hwnd, message, fn)                 \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,     \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


//////////////////////// Dialog Box Icon Setting Macro ////////////////////////


// Sets the dialog box icons
inline void chSETDLGICONS(HWND hwnd, int idi) {
   SendMessage(hwnd, WM_SETICON, TRUE,  (LPARAM) 
      LoadIcon((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
         MAKEINTRESOURCE(idi)));
   SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM) 
      LoadIcon((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
      MAKEINTRESOURCE(idi)));
}
    

/////////////////////////// OS Version Check Macros ///////////////////////////


inline void chWindows9xNotAllowed() {
   OSVERSIONINFO vi = { sizeof(vi) };
   GetVersionEx(&vi);
   if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
      chMB("This application requires features not present in Windows 9x.");
      ExitProcess(0);
   }
}


inline void chWindows2000Required() {
   OSVERSIONINFO vi = { sizeof(vi) };
   GetVersionEx(&vi);
   if ((vi.dwPlatformId != VER_PLATFORM_WIN32_NT) && (vi.dwMajorVersion < 5)) {
      chMB("This application requires features present in Windows 2000.");
      ExitProcess(0);
   }
}


///////////////////////////// UNICODE Check Macro /////////////////////////////


// Since Windows 98 does not support Unicode, issue an error and terminate
// the process if this is a native Unicode build running on Windows 98

// This is accomplished by creating a global C++ object. Its constructor is 
// executed before WinMain.

#ifdef UNICODE

class CUnicodeSupported {
public:
   CUnicodeSupported() {
      if (GetWindowsDirectoryW(NULL, 0) <= 0) {
         chMB("This application requires an OS that supports Unicode.");
         ExitProcess(0);
      }
   }
};

// "static" stops the linker from complaining that multiple instances of the
// object exist when a single project contains multiple source files.
static CUnicodeSupported g_UnicodeSupported;

#endif


/////////////////////////// Force Windows subsystem ///////////////////////////


#pragma comment(linker, "/subsystem:Windows")

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A5AC47F4_92F0_446A_9582_AA5931CE101D__INCLUDED_)
