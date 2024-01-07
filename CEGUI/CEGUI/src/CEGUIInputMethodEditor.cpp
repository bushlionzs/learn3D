
#define UNICODE

#include "CEGUIString.h"
#include "CEGUIWindow.h"
#include "CEGUIExceptions.h"
#include "CEGUIInputMethodEditor.h"
#include "elements/CEGUIEditboxInterface.h"
#include "elements/CEGUIEditbox.h"
#include "elements/CEGUIMultiLineEditbox.h"


#include <usp10.h>
#include <dimm.h>

#include <string>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <assert.h>
#include "tchar.h"


namespace ImeModule
{

#define IMM32_DLLNAME "\\imm32.dll"
#define VER_DLLNAME "\\version.dll"

#define MAX_COMPSTRING_SIZE 256



INPUTCONTEXT* WINAPI Dummy_ImmLockIMC( HIMC ) { return NULL; }
BOOL WINAPI Dummy_ImmUnlockIMC( HIMC ) { return FALSE; }
LPVOID WINAPI Dummy_ImmLockIMCC( HIMCC ) { return NULL; }
BOOL WINAPI Dummy_ImmUnlockIMCC( HIMCC ) { return FALSE; }
BOOL WINAPI Dummy_ImmDisableTextFrameService( DWORD ) { return TRUE; }
LONG WINAPI Dummy_ImmGetCompositionStringW( HIMC, DWORD, LPVOID, DWORD ) { return IMM_ERROR_GENERAL; }
DWORD WINAPI Dummy_ImmGetCandidateListW( HIMC, DWORD, LPCANDIDATELIST, DWORD ) { return 0; }
HIMC WINAPI Dummy_ImmGetContext( HWND ) { return NULL; }
BOOL WINAPI Dummy_ImmReleaseContext( HWND, HIMC ) { return FALSE; }

HIMC WINAPI Dummy_ImmAssociateContextEx( HWND, HIMC, DWORD ) { return NULL; }

HIMC WINAPI Dummy_ImmAssociateContext( HWND, HIMC ) { return NULL; }
BOOL WINAPI Dummy_ImmGetOpenStatus( HIMC ) { return 0; }
BOOL WINAPI Dummy_ImmSetOpenStatus( HIMC, BOOL ) { return 0; }
BOOL WINAPI Dummy_ImmGetConversionStatus( HIMC, LPDWORD, LPDWORD ) { return 0; }
HWND WINAPI Dummy_ImmGetDefaultIMEWnd( HWND ) { return NULL; }
UINT WINAPI Dummy_ImmGetIMEFileNameA( HKL, LPSTR, UINT ) { return 0; }
UINT WINAPI Dummy_ImmGetVirtualKey( HWND ) { return 0; }
BOOL WINAPI Dummy_ImmNotifyIME( HIMC, DWORD, DWORD, DWORD ) { return FALSE; }
BOOL WINAPI Dummy_ImmSetConversionStatus( HIMC, DWORD, DWORD ) { return FALSE; }
BOOL WINAPI Dummy_ImmSimulateHotKey( HWND, DWORD ) { return FALSE; }
BOOL WINAPI Dummy_ImmIsIME( HKL ) { return FALSE; }
BOOL WINAPI Dummy_ImmSetCompositionWindow(HIMC, LPCOMPOSITIONFORM) { return FALSE; }
UINT WINAPI Dummy_ImmGetDescriptionW(HKL hKL, LPTSTR lpszDescription, UINT uBufLen) {if (lpszDescription) lpszDescription[0] = 0; return 0;}


UINT WINAPI Dummy_GetReadingString( HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT ) { return 0; }
BOOL WINAPI Dummy_ShowReadingWindow( HIMC, BOOL ) { return FALSE; }


BOOL APIENTRY Dummy_VerQueryValueA( const LPVOID, LPSTR, LPVOID *, PUINT ) { return 0; }
BOOL APIENTRY Dummy_GetFileVersionInfoA( LPSTR, DWORD, DWORD, LPVOID ) { return 0; }
DWORD APIENTRY Dummy_GetFileVersionInfoSizeA( LPSTR, LPDWORD ) { return 0; }



INPUTCONTEXT* (WINAPI * _ImmLockIMC)( HIMC )			= Dummy_ImmLockIMC;
BOOL (WINAPI * _ImmUnlockIMC)( HIMC )					= Dummy_ImmUnlockIMC;
LPVOID (WINAPI * _ImmLockIMCC)( HIMCC )					= Dummy_ImmLockIMCC;
BOOL (WINAPI * _ImmUnlockIMCC)( HIMCC )					= Dummy_ImmUnlockIMCC;
BOOL (WINAPI * _ImmDisableTextFrameService)( DWORD )	= Dummy_ImmDisableTextFrameService;
LONG (WINAPI * _ImmGetCompositionStringW)( HIMC, DWORD, LPVOID, DWORD ) = Dummy_ImmGetCompositionStringW;
DWORD (WINAPI * _ImmGetCandidateListW)( HIMC, DWORD, LPCANDIDATELIST, DWORD ) = Dummy_ImmGetCandidateListW;
HIMC (WINAPI * _ImmGetContext)( HWND )					= Dummy_ImmGetContext;
BOOL (WINAPI * _ImmReleaseContext)( HWND, HIMC )		= Dummy_ImmReleaseContext;
HIMC (WINAPI * _ImmAssociateContext)( HWND, HIMC )		= Dummy_ImmAssociateContext;

HIMC (WINAPI * _ImmAssociateContextEx)( HWND, HIMC, DWORD)		= Dummy_ImmAssociateContextEx;

BOOL (WINAPI * _ImmGetOpenStatus)( HIMC )				= Dummy_ImmGetOpenStatus;
BOOL (WINAPI * _ImmSetOpenStatus)( HIMC, BOOL )			= Dummy_ImmSetOpenStatus;
BOOL (WINAPI * _ImmGetConversionStatus)( HIMC, LPDWORD, LPDWORD ) = Dummy_ImmGetConversionStatus;
HWND (WINAPI * _ImmGetDefaultIMEWnd)( HWND )			= Dummy_ImmGetDefaultIMEWnd;
UINT (WINAPI * _ImmGetIMEFileNameA)( HKL, LPSTR, UINT ) = Dummy_ImmGetIMEFileNameA;
UINT (WINAPI * _ImmGetVirtualKey)( HWND )				= Dummy_ImmGetVirtualKey;
BOOL (WINAPI * _ImmNotifyIME)( HIMC, DWORD, DWORD, DWORD ) = Dummy_ImmNotifyIME;
BOOL (WINAPI * _ImmSetConversionStatus)( HIMC, DWORD, DWORD ) = Dummy_ImmSetConversionStatus;
BOOL (WINAPI * _ImmSimulateHotKey)( HWND, DWORD )		= Dummy_ImmSimulateHotKey;
BOOL (WINAPI * _ImmIsIME)( HKL )						= Dummy_ImmIsIME;
BOOL (WINAPI * _ImmSetCompositionWindow)(HIMC, LPCOMPOSITIONFORM) = Dummy_ImmSetCompositionWindow;

UINT (WINAPI * _ImmGetDescriptionW)(HKL hKL, LPTSTR lpszDescription, UINT uBufLen) = Dummy_ImmGetDescriptionW;



UINT (WINAPI * _GetReadingString)( HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT ) = Dummy_GetReadingString;
BOOL (WINAPI * _ShowReadingWindow)( HIMC, BOOL )		= Dummy_ShowReadingWindow;


BOOL (APIENTRY * _VerQueryValueA)( const LPVOID, LPSTR, LPVOID *, PUINT )	= Dummy_VerQueryValueA;
BOOL (APIENTRY * _GetFileVersionInfoA)( LPSTR, DWORD, DWORD, LPVOID )		= Dummy_GetFileVersionInfoA;
DWORD (APIENTRY * _GetFileVersionInfoSizeA)( LPSTR, LPDWORD )				= Dummy_GetFileVersionInfoSizeA;



HWND      s_hWnd;			
HINSTANCE s_hDllImm32;      
HINSTANCE s_hDllVer;        
HKL       s_hklCurrent;     
bool      s_bVerticalCand;  
HIMC      s_hImcDef;           
bool      s_bChineseIME;
IMESTATE  s_ImeState = IMEUI_STATE_OFF;
HINSTANCE s_hDllIme;           
std::multiset< WCHAR > s_hIMEHasSend;
bool	  s_bInCandidate = false;

CHAR	pDoubleChar[3] = {0};	
INT		nDoubleCharCount = 0;	


std::list< CEGUI::Window* > s_activeExitBox;

inline HWND GetHWND() { return s_hWnd; }
inline WORD GetLanguage() { return LOWORD( s_hklCurrent ); }
inline WORD GetPrimaryLanguage() { return PRIMARYLANGID( LOWORD( s_hklCurrent ) ); }
inline WORD GetSubLanguage() { return SUBLANGID( LOWORD( s_hklCurrent ) ); }
CEGUI::EditboxInterface* GetActiveIMEEditBox_Interface(void);



void CheckToggleState(void);
void SetupImeApi(void);
void CheckInputLocale(void);


void SetImeWindowPos(void);


TCHAR g_ImeMsPinyin2007Unicode[256] = {0, 0};


void InitializeImm(unsigned int hWnd)
{
	#define GETPROCADDRESS( Module, APIName, Temp ) \
		Temp = GetProcAddress( Module, #APIName ); \
		if( Temp ) \
			*(FARPROC*)&_##APIName = Temp

    FARPROC Temp;

	s_hWnd = (HWND)(UINT_PTR)hWnd;

    CHAR szPath[MAX_PATH+1];
    if( !::GetSystemDirectoryA( szPath, MAX_PATH+1 ) )
        return;
    lstrcatA( szPath, IMM32_DLLNAME );
    s_hDllImm32 = LoadLibraryA( szPath );
    if( s_hDllImm32 )
    {
        GETPROCADDRESS( s_hDllImm32, ImmLockIMC, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmUnlockIMC, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmLockIMCC, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmUnlockIMCC, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmDisableTextFrameService, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetCompositionStringW, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetCandidateListW, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetContext, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmReleaseContext, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmAssociateContext, Temp );
		GETPROCADDRESS( s_hDllImm32, ImmAssociateContextEx, Temp );
		
        GETPROCADDRESS( s_hDllImm32, ImmGetOpenStatus, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmSetOpenStatus, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetConversionStatus, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetDefaultIMEWnd, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetIMEFileNameA, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmGetVirtualKey, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmNotifyIME, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmSetConversionStatus, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmSimulateHotKey, Temp );
        GETPROCADDRESS( s_hDllImm32, ImmIsIME, Temp );
		GETPROCADDRESS( s_hDllImm32, ImmSetCompositionWindow, Temp);
		GETPROCADDRESS( s_hDllImm32, ImmGetDescriptionW, Temp);		
    }

    if( !::GetSystemDirectoryA( szPath, MAX_PATH+1 ) )
        return;
    lstrcatA( szPath, VER_DLLNAME );
    s_hDllVer = LoadLibraryA( szPath );
    if( s_hDllVer )
    {
        GETPROCADDRESS( s_hDllVer, VerQueryValueA, Temp );
        GETPROCADDRESS( s_hDllVer, GetFileVersionInfoA, Temp );
        GETPROCADDRESS( s_hDllVer, GetFileVersionInfoSizeA, Temp );
    }

	
    
    s_hImcDef = _ImmGetContext( GetHWND() );
    _ImmReleaseContext( GetHWND(), s_hImcDef );

	char * imeName = "Microsoft Pinyin IME 2007";
	::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)imeName, -1, (LPWSTR)g_ImeMsPinyin2007Unicode, 255);
}


void UninitializeImm(void)
{
	#define PLACEHOLDERPROC( APIName ) \
		_##APIName = Dummy_##APIName

    if( s_hDllImm32 )
    {
        PLACEHOLDERPROC( ImmLockIMC );
        PLACEHOLDERPROC( ImmUnlockIMC );
        PLACEHOLDERPROC( ImmLockIMCC );
        PLACEHOLDERPROC( ImmUnlockIMCC );
        PLACEHOLDERPROC( ImmDisableTextFrameService );
        PLACEHOLDERPROC( ImmGetCompositionStringW );
        PLACEHOLDERPROC( ImmGetCandidateListW );
        PLACEHOLDERPROC( ImmGetContext );
        PLACEHOLDERPROC( ImmReleaseContext );
        PLACEHOLDERPROC( ImmAssociateContext );
		PLACEHOLDERPROC( ImmAssociateContextEx );
        PLACEHOLDERPROC( ImmGetOpenStatus );
        PLACEHOLDERPROC( ImmSetOpenStatus );
        PLACEHOLDERPROC( ImmGetConversionStatus );
        PLACEHOLDERPROC( ImmGetDefaultIMEWnd );
        PLACEHOLDERPROC( ImmGetIMEFileNameA );
        PLACEHOLDERPROC( ImmGetVirtualKey );
        PLACEHOLDERPROC( ImmNotifyIME );
        PLACEHOLDERPROC( ImmSetConversionStatus );
        PLACEHOLDERPROC( ImmSimulateHotKey );
        PLACEHOLDERPROC( ImmIsIME );
		PLACEHOLDERPROC( ImmSetCompositionWindow);
		PLACEHOLDERPROC( ImmGetDescriptionW);

        FreeLibrary( s_hDllImm32 );
        s_hDllImm32 = NULL;
    }
    if( s_hDllIme )
    {
        PLACEHOLDERPROC( GetReadingString );
        PLACEHOLDERPROC( ShowReadingWindow );

        FreeLibrary( s_hDllIme );
        s_hDllIme = NULL;
    }
    if( s_hDllVer )
    {
        PLACEHOLDERPROC( VerQueryValueA );
        PLACEHOLDERPROC( GetFileVersionInfoA );
        PLACEHOLDERPROC( GetFileVersionInfoSizeA );

        FreeLibrary( s_hDllVer );
        s_hDllVer = NULL;
    }
}
void OpenIME(HWND hWnd)
{
	_ImmAssociateContextEx(hWnd, NULL, IACE_DEFAULT);
	HIMC hImc = _ImmGetContext(hWnd);
	if (!_ImmGetOpenStatus(hImc))
	{
		_ImmSetOpenStatus(hImc, true);
	}
	_ImmReleaseContext(hWnd, hImc);

}

void CloseIME(HWND hWnd)
{	
	HIMC hImc = _ImmGetContext(hWnd);
	if (_ImmGetOpenStatus(hImc))
	{
		_ImmSetOpenStatus(hImc, false);
	}
	_ImmReleaseContext(hWnd, hImc);
	_ImmAssociateContext(hWnd, NULL);
}

bool ImeMsgProc(unsigned int uMsg, unsigned int _wParam, unsigned int _lParam)
{
	WPARAM wParam = _wParam;
	LPARAM lParam = _lParam;
    HIMC hImc;
	

    switch( uMsg )
	{
	case WM_IME_ENDCOMPOSITION:
		{
			
			HIMC hImc;
			if( NULL != ( hImc = _ImmGetContext( GetHWND() ) ) )
			{
				
				

				
				_ImmReleaseContext( GetHWND(), hImc );
			}
		}
		break;
	case WM_CHAR:
            switch( (WCHAR)wParam )
            {
			
			case VK_TAB:
				CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Tab);
				break;

			
			case VK_BACK:
				
				if ((_lParam >> 16) == 0x23) 
					break;
				CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Backspace);
				break;

			case VK_CANCEL: 
			case 24:        
				{
					CEGUI::EditboxInterface* pEdit = GetActiveIMEEditBox_Interface();
					if(pEdit)
					{
						if(0 != pEdit->getSelectionLength() && !(pEdit->isTextMasked()))
						{
							
							CEGUI::String szSel = (GetActiveIMEEditBox())->getText().substr(pEdit->getSelectionStartIndex(), pEdit->getSelectionLength());

							size_t length = szSel.length();
							if(length > 0)
							{
								size_t pos = 0;
								wchar_t* pWtxt = new wchar_t[length+1];
								pWtxt[length] = 0;
								
								while(length--)
								{
									pWtxt[pos] = szSel.at(pos) & 0xFFFF;
									pos++;
								}

								
								if(::OpenClipboard(::GetTopWindow(NULL)))
								{
									::EmptyClipboard();
									
									int size = ::WideCharToMultiByte(CP_ACP,0,pWtxt,wcslen(pWtxt),NULL,0,NULL,FALSE);
									
									HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE,(size_t)size+1);
									char* ptxt = (char*)::GlobalLock(hglb);
									ptxt[size] = 0;
									
									::WideCharToMultiByte(CP_ACP,0,pWtxt,wcslen(pWtxt),ptxt,size,NULL,FALSE);
									::GlobalUnlock(hglb);
									
									::SetClipboardData(CF_TEXT, hglb);
									::CloseClipboard();
									
									::GlobalFree(hglb);
								}

								delete [] pWtxt;

								if((WCHAR)wParam == 24) 
								{
									CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Delete);
								}
							}
						}
					}
				}
				break;

			
			case 22:
				{
					CEGUI::EditboxInterface* pWin = GetActiveIMEEditBox_Interface();
					if(pWin)
					{
						if(::IsClipboardFormatAvailable(CF_TEXT) && ::OpenClipboard(::GetTopWindow(NULL)))
						{
							HGLOBAL hglb = ::GetClipboardData(CF_TEXT);
							if(NULL != hglb)
							{
								try
								{
									char* ptxt = (char*)::GlobalLock(hglb);
									if( NULL == ptxt )
									{
										::GlobalUnlock(hglb);
										::CloseClipboard();
										break;
									}

									int size = ::MultiByteToWideChar(CP_ACP,0,ptxt,(int)strlen(ptxt),NULL,0);
									wchar_t* pWtxt = new wchar_t[size+1];
									pWtxt[size] = 0;

									::MultiByteToWideChar(CP_ACP,0,ptxt,(int)strlen(ptxt),pWtxt,size);

									::GlobalUnlock(hglb);
									::CloseClipboard();

									int pos = 0;
									while(size--)
									{
										
										if( (pWtxt[pos] < 0X20 /*|| (pWtxt[pos] > 0X80 && pWtxt[pos] <= 0XFF)*/) 
											&& pWtxt[pos] != '\r' && pWtxt[pos] != '\n' )
										{
											CEGUI::System::getSingleton().injectChar( 0x25a1 );
										}
										else
										{
											CEGUI::System::getSingleton().injectChar((CEGUI::utf32)pWtxt[pos]);
										}
										pos++;
									}
								}
								catch( ... )
								{
									::GlobalUnlock(hglb);
									::CloseClipboard();
									break;
								}
							}
						}
					}
				}
				break;

				
			case 1:
				{
					CEGUI::EditboxInterface* pEdit = GetActiveIMEEditBox_Interface();
					if(pEdit)
					{
						pEdit->setSelection(0, pEdit->getMaxTextLength());
						pEdit->setCaratIndex(pEdit->getMaxTextLength());
					}
				}
				break;

			case VK_RETURN:
				CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Return);
				break;

				
			case 26:  
			case 2:   
			case 14:  
			case 19:  
			case 4:   
			case 6:   
			case 7:   
			case 10:  
			case 11:  
			case 12:  
			case 17:  
			case 23:  
			case 5:   
			case 18:  
			case 20:  
			case 25:  
			case 21:  

			case 15:  
			case 16:  
			case 27:  
			case 29:  
			case 28:  
				break;
			default:
				{
					WCHAR szCharW;
					CHAR szChar = (CHAR)LOWORD(wParam);
					if(szChar >= 32 && szChar <= 128 )
					{
						::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)&szChar, 1, &szCharW, 1);

						CEGUI::System::getSingleton().injectChar((CEGUI::utf32)szCharW);
					}
					
					
					else if(szChar > 128 || szChar < 0)
					{
						
						if( szCharW > 0X80 && szCharW <= 0XFF )
						{
							
							CEGUI::System::getSingleton().injectChar( 0x25a1 );
						}
						else
						{
							if(nDoubleCharCount == 2)
								nDoubleCharCount = 0;

							if(nDoubleCharCount == 0)
							{
								memset(pDoubleChar, 0, sizeof(pDoubleChar));
								pDoubleChar[nDoubleCharCount] = szChar;
								++nDoubleCharCount;
							}
							else if(nDoubleCharCount == 1)
							{
								pDoubleChar[nDoubleCharCount] = szChar;
								::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pDoubleChar, 2, &szCharW, 1);

								CEGUI::System::getSingleton().injectChar((CEGUI::utf32)szCharW);
								++nDoubleCharCount;
							}	
						}
					}
					
					else if( szCharW < 0X20 && szCharW != '\r' && szCharW != '\n' && szCharW != '\t' )
					{
						
						CEGUI::System::getSingleton().injectChar( 0x25a1 );
					}
				}
			}
			return true;

        case WM_IME_COMPOSITION:
            
            {
                LONG lRet;  
                WCHAR wszCompStr[MAX_COMPSTRING_SIZE];
				bool bRet = false;

                
                if( NULL == ( hImc = _ImmGetContext( GetHWND() ) ) )
                {
                    break;
                }

                if ( lParam & GCS_RESULTSTR )
                {
                    
                    lRet = _ImmGetCompositionStringW( hImc, GCS_RESULTSTR, wszCompStr, sizeof( wszCompStr ) );
                    if( lRet > 0 )
                    {
                        lRet /= sizeof(WCHAR);
                        wszCompStr[lRet] = 0;  
						for(int i = 0; i <lRet; ++i )
						{
							CEGUI::System::getSingleton().injectChar((WCHAR)wszCompStr[i]);
						}
                    }
					bRet = true;
                }

                _ImmReleaseContext( GetHWND(), hImc );

				
				
				return bRet;
			}
        case WM_INPUTLANGCHANGE:
            
            {
                UINT uLang = GetPrimaryLanguage();
                CheckToggleState();

                
                SetupImeApi();
            }
            break;

		case WM_IME_NOTIFY:
			
			{
				if(wParam == IMN_SETOPENSTATUS || wParam == IMN_SETCONVERSIONMODE)
				{
					CheckToggleState();
				}

				
				switch( wParam )
				{
				case IMN_SETCONVERSIONMODE:
					break;
				case IMN_OPENCANDIDATE:
				case IMN_CHANGECANDIDATE:
					s_bInCandidate = true;
					break;
				case IMN_CLOSECANDIDATE:
					s_bInCandidate = false;
					break;
				}

			}
			break;
		case WM_KEYDOWN:
			{
				switch ( wParam )
				{
				case VK_SHIFT:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::LeftShift);
					break;

				case VK_CONTROL:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::LeftControl);
					break;

				case VK_DELETE:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Delete);
					break;

				case VK_LEFT:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowLeft);
					break;

				case VK_RIGHT:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowRight);
					break;

				case VK_UP:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowUp);
					break;

				case VK_DOWN:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowDown);
					break;

				case VK_HOME:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Home);
					break;

				case VK_END:
					CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::End);
					break;
				
				case VK_F1:
					
					break;
				case VK_F2:
					
					break;
				}
			}
			break;

		case WM_KEYUP:
			{
				switch ( wParam )
				{
				case VK_SHIFT:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::LeftShift);
					break;

				case VK_CONTROL:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::LeftControl);
					break;

				case VK_DELETE:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Delete);
					break;

				case VK_LEFT:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowLeft);
					break;

				case VK_RIGHT:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowRight);
					break;

				case VK_UP:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowUp);
					break;

				case VK_DOWN:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowDown);
					break;

				case VK_HOME:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Home);
					break;

				case VK_END:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::End);
					break;
					
				case VK_TAB:
					CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Tab);
					break;
				}
			}
			break;

		default:
			break;
	}

	return false;
}

void CheckToggleState(void)
{	
    CheckInputLocale();
    bool bIme = _ImmIsIME( s_hklCurrent ) != 0;
    s_bChineseIME = ( GetPrimaryLanguage() == LANG_CHINESE ) && bIme;

    HIMC hImc;
    if( NULL != ( hImc = _ImmGetContext( GetHWND() ) ) )
    {
        if( s_bChineseIME )
        {
            DWORD dwConvMode, dwSentMode;
            _ImmGetConversionStatus( hImc, &dwConvMode, &dwSentMode );
            s_ImeState = ( dwConvMode & IME_CMODE_NATIVE ) ? IMEUI_STATE_ON : IMEUI_STATE_ENGLISH;
			
			static int s_Count = 0;
			if (s_Count < 5)
			{
				s_Count ++;
				if(!HasInputFocus())
				{
					_ImmSetOpenStatus(hImc, FALSE);

					
					
					
					_ImmNotifyIME(hImc, NI_CLOSECANDIDATE, CPS_CANCEL, 0);

					TCHAR buffer[ 255 ] = { 0, 0 };
					_ImmGetDescriptionW( s_hklCurrent, buffer, 255 );
					if( 0 != wcscmp( (wchar_t*)buffer,  (wchar_t*)g_ImeMsPinyin2007Unicode) )
					{
						_ImmAssociateContext(GetHWND(), NULL);
					}
				}
				s_Count --;
			}
        }
        else
        {
            s_ImeState = ( bIme && _ImmGetOpenStatus( hImc ) != 0 ) ? IMEUI_STATE_ON : IMEUI_STATE_OFF;
        }
        _ImmReleaseContext( GetHWND(), hImc );
    }
    else
        s_ImeState = IMEUI_STATE_OFF;
}




void SetupImeApi(void)
{
    char szImeFile[MAX_PATH + 1];

    _GetReadingString = NULL;
    _ShowReadingWindow = NULL;
    if( _ImmGetIMEFileNameA( s_hklCurrent, szImeFile, sizeof(szImeFile)/sizeof(szImeFile[0]) - 1 ) == 0 )
        return;

    if( s_hDllIme ) FreeLibrary( s_hDllIme );
    s_hDllIme = LoadLibraryA( szImeFile );
    if ( !s_hDllIme )
        return;
    _GetReadingString = (UINT (WINAPI*)(HIMC, UINT, LPWSTR, PINT, BOOL*, PUINT))
        ( GetProcAddress( s_hDllIme, "GetReadingString" ) );
    _ShowReadingWindow =(BOOL (WINAPI*)(HIMC, BOOL))
        ( GetProcAddress( s_hDllIme, "ShowReadingWindow" ) );
}

void CheckInputLocale(void)
{
    s_hklCurrent = GetKeyboardLayout( 0 );
}

void SetImeWindowPos(void)
{
	
	CEGUI::EditboxInterface* pEdit = GetActiveIMEEditBox_Interface();
	if(NULL == pEdit) return;

	CEGUI::Window* pWnd = GetActiveIMEEditBox();
	if(NULL == pWnd) return;

	CEGUI::Rect ceguiRect = pWnd->getPixelRect();
	POINT pt;
	pt.x = (long)ceguiRect.d_left;
	pt.y = (long)ceguiRect.d_bottom;

	HIMC hImc = _ImmGetContext(GetHWND());
	if(NULL == hImc) return;

	COMPOSITIONFORM imeForm;
	imeForm.dwStyle = CFS_POINT;
	imeForm.ptCurrentPos = pt;

	_ImmSetCompositionWindow(hImc,&imeForm);
	_ImmReleaseContext(GetHWND(),hImc);
}



bool CheckInputFocus(void)
{	
	bool isReadOnly = false;

	
	CEGUI::Window* pWin = ImeModule::GetActiveIMEEditBox();
	if( pWin && pWin->testClassName( (CEGUI::utf8*)"MultiLineEditbox") )
	{
		isReadOnly = ((CEGUI::MultiLineEditbox*)pWin)->isReadOnly();
	}
	else if( pWin && pWin->testClassName((CEGUI::utf8*)"Editbox") )
	{
		isReadOnly = ((CEGUI::Editbox*)pWin)->isReadOnly();
	}
	return !isReadOnly;
}



void SetActiveIMEEditBox(CEGUI::Window* imeEditBox, bool set)
{
	if(!imeEditBox) return;
	
	CheckInputLocale();
	HIMC hImc = _ImmGetContext(GetHWND());

	TCHAR buffer[ 255 ] = { 0, 0 };
	_ImmGetDescriptionW( s_hklCurrent, buffer, 255 );
	if( 0 != wcscmp( (wchar_t*)buffer,  (wchar_t*)g_ImeMsPinyin2007Unicode) || hImc == 0)
	{
		_ImmAssociateContextEx(GetHWND(), NULL, IACE_DEFAULT);
		hImc = _ImmGetContext(GetHWND());
	}

	if(set)
	{
		if(GetActiveIMEEditBox() != imeEditBox)
			s_activeExitBox.push_front(imeEditBox);
		
		if(hImc)
		{
			bool bIme = _ImmIsIME( s_hklCurrent ) != 0;
			bool s_bChineseIME = ( GetPrimaryLanguage() == LANG_CHINESE ) && bIme;
			
			if(s_bChineseIME && CheckInputFocus())			
			{				
				_ImmSetOpenStatus(hImc, TRUE);
			}
			_ImmReleaseContext(GetHWND(),hImc);
		}
	}
	else
	{
		s_activeExitBox.remove(imeEditBox);
		if(s_activeExitBox.empty())
		{
			s_activeExitBox.push_front(imeEditBox);
		}
		
		if(hImc)
		{
			CheckInputLocale();
			bool bIme = _ImmIsIME( s_hklCurrent ) != 0;
			bool s_bChineseIME = ( GetPrimaryLanguage() == LANG_CHINESE ) && bIme;
			
			if(s_bChineseIME && !CheckInputFocus())
			{
				_ImmSetOpenStatus(hImc, FALSE);
				
				
				
				_ImmNotifyIME(hImc, NI_CLOSECANDIDATE, CPS_CANCEL, 0);
				
				if( 0 != wcscmp( (wchar_t*)buffer,  (wchar_t*)g_ImeMsPinyin2007Unicode) )
				{
					_ImmAssociateContext(GetHWND(), NULL);
				}
			}
			_ImmReleaseContext(GetHWND(),hImc);
		}
	}
	
}

CEGUI::Window* GetActiveIMEEditBox(void)
{
	if(s_activeExitBox.empty()) return 0;

	return *(s_activeExitBox.begin());
}

CEGUI::EditboxInterface* GetActiveIMEEditBox_Interface(void)
{
	CEGUI::Window* pWin = GetActiveIMEEditBox();

	if(pWin && pWin->testClassName((CEGUI::utf8*)"MultiLineEditbox"))
	{
		return (CEGUI::EditboxInterface*)(CEGUI::MultiLineEditbox*)pWin;
	}
	else if(pWin && pWin->testClassName((CEGUI::utf8*)"Editbox"))
	{
		return (CEGUI::EditboxInterface*)(CEGUI::Editbox*)pWin;
	}
	return 0;
}


bool HasInputFocus(void)
{	
	bool isReadOnly = false;

	
	CEGUI::Window* pWin = ImeModule::GetActiveIMEEditBox();
	if( pWin && pWin->testClassName( (CEGUI::utf8*)"MultiLineEditbox") )
	{
		isReadOnly = ((CEGUI::MultiLineEditbox*)pWin)->isReadOnly();
	}
	else if( pWin && pWin->testClassName((CEGUI::utf8*)"Editbox") )
	{
		isReadOnly = ((CEGUI::Editbox*)pWin)->isReadOnly();
	}
	
	HIMC hImc = _ImmGetContext(GetHWND());
	if(hImc)
	{
		bool bIme = _ImmIsIME( s_hklCurrent ) != 0;
		bool s_bChineseIME = ( GetPrimaryLanguage() == LANG_CHINESE ) && bIme;

		

		{
			if(s_bChineseIME && (BOOL)isReadOnly == _ImmGetOpenStatus(hImc))
			{
				static int s_Count = 0;
				
				{
					s_Count ++;					

					_ImmSetOpenStatus(hImc, FALSE);
					
					
					
					_ImmNotifyIME(hImc, NI_CLOSECANDIDATE, CPS_CANCEL, 0);

					TCHAR buffer[ 255 ] = { 0, 0 };
					_ImmGetDescriptionW( s_hklCurrent, buffer, 255 );
					if( 0 != wcscmp( (wchar_t*)buffer,  (wchar_t*)g_ImeMsPinyin2007Unicode) )
					{
						_ImmAssociateContext(GetHWND(), NULL);

					}					
					s_Count --;
				}
			}
		}
		_ImmReleaseContext(GetHWND(),hImc);
	}

	return !isReadOnly;
}

bool HasForbidInput(void)
{
	bool isForbidInput = false;

	CEGUI::Window* pWin = ImeModule::GetActiveIMEEditBox();
	if( pWin && pWin->testClassName((CEGUI::utf8*)"Editbox") )
	{
		isForbidInput = ((CEGUI::Editbox*)pWin)->isForbidInput();
	}

	return isForbidInput;
}


bool HasInCandidate(void)
{
	return s_bInCandidate;
}

void ClearImeStat(void)
{
	s_bInCandidate = false;
}

unsigned int GetCaretBlinkTime(void)
{
	return ::GetCaretBlinkTime();
}

IMESTATE GetState(void)
{
	return s_ImeState;
}

}