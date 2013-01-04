// Author: Adel Amro
// Last updated: 15/9/2012


# include "LogWindow.h"
# include <tchar.h>
# include <stdio.h>
//# include <strsafe.h>




# define MAX_LINE 2048
static TCHAR buff[ MAX_LINE ];

# ifdef UNICODE
static WCHAR conversionBuffer[ MAX_LINE ];
# endif





// Disable "conversion from LONG to ptr of different size" warnings.
# pragma warning( push )
# pragma warning( disable: 4311 )
# pragma warning( disable: 4312 )

CLogWindow* GetClassPointer( HWND hWnd )				{ return (CLogWindow*)GetWindowLongPtr( hWnd, 0 ); }
VOID SetClassPointer( HWND hWnd, CLogWindow* pLW )		{ SetWindowLongPtr( hWnd, 0, (LONG)pLW ); }

# pragma warning( pop )



CLogWindow* pAttachInstance = NULL; // The instance that needs to be attached to the window.


// Marshal messages to the message handler method in the CLogWindow class.
LRESULT CALLBACK CLogWindow::StaticMsgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	if( Msg == WM_NCCREATE )
	{
		SetClassPointer( hWnd, pAttachInstance );
		pAttachInstance->hWnd = hWnd;
	}
	CLogWindow* pLogWindow = GetClassPointer( hWnd );
	if( pLogWindow )
		return pLogWindow->MsgProc( Msg, wParam, lParam );
	return DefWindowProc( hWnd, Msg, wParam, lParam );
}



ATOM LogWindowAtom = NULL;
BOOL LogWindowInited = FALSE;


BOOL CLogWindow::RegisterClass( HINSTANCE hInstance )
{
	if( LogWindowInited )
		return LogWindowAtom != NULL;
	LogWindowInited = TRUE;

	WNDCLASSEX wc;
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= 0;
	wc.lpfnWndProc		= CLogWindow::StaticMsgProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= sizeof( CLogWindow* );
	wc.hInstance		= hInstance;
	wc.hIcon			= 0;
	wc.hIconSm			= 0;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= WC_LOGWINDOW;

	LogWindowAtom = RegisterClassEx(&wc);
	if( !LogWindowAtom )
		return FALSE;

	ZeroMemory( buff, MAX_LINE * sizeof(TCHAR) );

	return TRUE;
}






CLogWindow::CLogWindow()
{
	hWnd = hEdit = NULL;
	hFile = INVALID_HANDLE_VALUE;
	indentation = 0;
	deleteFile = FALSE;
}


CLogWindow::~CLogWindow()
{
	if( hWnd )
		DestroyWindow( hWnd );
	if( deleteFile && hFile != INVALID_HANDLE_VALUE )
		CloseHandle( hFile );
	hFile = INVALID_HANDLE_VALUE;
}





BOOL CLogWindow::Create( HINSTANCE hInst, HWND parent, BOOL topMost, LPCTSTR captionName )
{
	if( FALSE == RegisterClass( hInst ) )
		return FALSE;

	pAttachInstance = this;

	hWnd = CreateWindowEx( WS_EX_TOOLWINDOW | (topMost ? WS_EX_TOPMOST : 0),
		WC_LOGWINDOW, captionName,
      WS_VISIBLE | WS_POPUPWINDOW | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
		parent, NULL, hInst, NULL );

	if( !hWnd )
		return FALSE;

	DWORD style = WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_READONLY |
		/*ES_AUTOHSCROLL |*/ ES_AUTOVSCROLL /*| WS_HSCROLL*/ | WS_VSCROLL | ES_WANTRETURN;

	hEdit = CreateWindowEx( 0, TEXT("Edit"), NULL,
      style, 0, 0, 100, 100, hWnd, (HMENU)1000, hInst, NULL );

	SendMessage( hEdit, WM_SETFONT, (WPARAM)GetStockObject( DEFAULT_GUI_FONT), 0L );
	UINT tabStops = 16;
	SendMessage( hEdit, EM_SETTABSTOPS, 1, (LPARAM)&tabStops );

	SendMessage( hWnd, WM_SIZE, 0, 0 );

	return TRUE;
}






BOOL CLogWindow::SetOutputFile( HANDLE hNewFile )
{
	if( hFile != INVALID_HANDLE_VALUE )
	{
		if( deleteFile )
		{
			CloseHandle( hFile );
			hFile = INVALID_HANDLE_VALUE;
		}
	}
	deleteFile = FALSE;
	hFile = hNewFile;
	return TRUE;
}





BOOL CLogWindow::SetOutputFile( LPCTSTR fileName, BOOL overwrite )
{
	if( fileName == NULL || fileName[0] == 0 )
		return FALSE;

	SetOutputFile( INVALID_HANDLE_VALUE );
	hFile = CreateFile( fileName, GENERIC_WRITE,
		0, // Do not share
		NULL, // Default security
		overwrite ? CREATE_ALWAYS : OPEN_ALWAYS, // Overwrite existing
		//FILE_FLAG_WRITE_THROUGH, // Write directly to file (we don't want to lose output if process crashes)
		//FILE_FLAG_NO_BUFFERING,
		0,
		NULL ); // No attribute template (0.o)??!!
	if( hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	deleteFile = TRUE;
	return TRUE;
}




VOID CLogWindow::Clear()
{
	if( !hEdit )
		return;
	SendMessage( hEdit, WM_SETTEXT, 0, 0 );
	//SendMessage( hEdit, EM_SETSEL, 0, -1 );
	//SendMessage( hEdit, WM_CLEAR, 0, 0 );
}



VOID InternalWriteText( HWND hEdit, HANDLE hFile, LPCTSTR text, INT len )
{
	if( !text || len == 0 || text[0] == 0 )
		return;

	if( hEdit )
	{
		INT start, end;
		SendMessage( hEdit, EM_GETSEL, (WPARAM)&start, (LPARAM)&end );
		INT length = (INT)SendMessage( hEdit, WM_GETTEXTLENGTH, 0L, 0L );
		SendMessage( hEdit, EM_SETSEL, length, length );
		SendMessage( hEdit, EM_REPLACESEL, FALSE, (LPARAM)text );
		SendMessage( hEdit, EM_SETSEL, start, end );
	}

	if( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD bytes;
		WriteFile( hFile, text, len * sizeof(TCHAR), &bytes, NULL );
	}
}





VOID CLogWindow::Write( const char* msg, ... )
{
	if( msg == NULL || msg[0] == 0 ) return;
	va_list vList;
	va_start( vList, msg );
# ifdef UNICODE
	MultiByteToWideChar( CP_ACP, 0, msg, -1, conversionBuffer, MAX_LINE );
	msg = (LPCSTR)conversionBuffer;
# endif
	//INT len = _vsntprintf( buff, MAX_LINE, (TCHAR*)msg, vList );
   INT len = _vsntprintf_s( buff, MAX_LINE, (TCHAR*)msg, vList );
	InternalWriteText( hEdit, hFile, buff, len );
}




VOID CLogWindow::WriteNewLine( const char* msg, ... )
{
	va_list vList;
	va_start( vList, msg );
# ifdef UNICODE
	MultiByteToWideChar( CP_ACP, 0, msg, -1, conversionBuffer, MAX_LINE );
	msg = (LPCSTR)conversionBuffer;
# endif
	if( 0 == SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 ) )
	{
      INT len = _vsntprintf_s( buff, MAX_LINE, (TCHAR*)msg, vList );
		InternalWriteText( hEdit, hFile, buff, len );
		return;
	}
	INT len = _vsntprintf( buff + 2 + indentation, MAX_LINE, (TCHAR*)msg, vList );
	buff[0] = _T('\r');
	buff[1] = _T('\n');
	for( UINT i=0; i<indentation; i++ )
		buff[ 2 + i ] = _T('\t');
	InternalWriteText( hEdit, hFile, buff, len + 2 + indentation );
}





VOID CLogWindow::operator () ( const char* msg, ... )
{
	va_list vList;
	va_start( vList, msg );
# ifdef UNICODE
	MultiByteToWideChar( CP_ACP, 0, msg, -1, conversionBuffer, MAX_LINE );
	msg = (LPCSTR)conversionBuffer;
# endif
	if( hEdit && 0 == SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 ) )
	{
		INT len = _vsntprintf_s( buff, MAX_LINE, (TCHAR*)msg, vList );
		InternalWriteText( hEdit, hFile, buff, len );
		return;
	}
	INT len = _vsntprintf( buff + 2 + indentation, MAX_LINE, (TCHAR*)msg, vList );
	buff[0] = _T('\r');
	buff[1] = _T('\n');
	for( UINT i=0; i<indentation; i++ )
		buff[ 2 + i ] = _T('\t');
	InternalWriteText( hEdit, hFile, buff, len + 2 + indentation );
}



# ifdef UNICODE
VOID CLogWindow::Write( const WCHAR* msg, ... )
{
	if( msg == NULL ) return;
	va_list vList;
	va_start( vList, msg );
	INT len = _vsntprintf( buff, MAX_LINE, msg, vList );
	InternalWriteText( hEdit, hFile, buff, len );
}




VOID CLogWindow::WriteNewLine( const WCHAR* msg, ... )
{
	va_list vList;
	va_start( vList, msg );
	if( hEdit && 0 == SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 ) )
	{
		INT len = _vsntprintf( buff, MAX_LINE, msg, vList );
		InternalWriteText( hEdit, hFile, buff, len );
		return;
	}
	INT len = _vsntprintf( buff + 2 + indentation, MAX_LINE, msg, vList );
	buff[0] = _T('\r');
	buff[1] = _T('\n');
	for( UINT i=0; i<indentation; i++ )
		buff[ 2 + i ] = _T('\t');
	InternalWriteText( hEdit, hFile, buff, len + 2 + indentation );
}




VOID CLogWindow::operator () ( const WCHAR* msg, ... )
{
	va_list vList;
	va_start( vList, msg );
	if( hEdit && 0 == SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 ) )
	{
		INT len = _vsntprintf( buff, MAX_LINE, msg, vList );
		InternalWriteText( hEdit, hFile, buff, len );
		return;
	}
	INT len = _vsntprintf( buff + 2 + indentation, MAX_LINE, msg, vList );
	buff[0] = _T('\r');
	buff[1] = _T('\n');
	for( UINT i=0; i<indentation; i++ )
		buff[ 2 + i ] = _T('\t');
	InternalWriteText( hEdit, hFile, buff, len + 2 + indentation );
}
# endif // ifdef UNICODE





LRESULT CLogWindow::MsgProc( UINT Msg, WPARAM wParam, LPARAM lParam )
{
	switch( Msg )
	{

	case WM_CLOSE:
		ShowWindow( hWnd, SW_HIDE );
		return 0;


	case WM_DESTROY:
		hWnd = NULL;
		hEdit = NULL;
		break;

	case WM_SIZE:
		if( hEdit )
		{
			RECT rClient;
			GetClientRect( hWnd, &rClient );
			MoveWindow( hEdit, 0, 0, rClient.right - rClient.left, rClient.bottom - rClient.top, TRUE );
		}
		break;
	}
	return DefWindowProc( hWnd, Msg, wParam, lParam );
}