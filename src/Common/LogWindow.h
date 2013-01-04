// Log (output) window. Uses an edit control to store and display text. It can be
// assigned an output file so that output is also directed to a file. If
// you just specify a file name (rather than a handle to an already-created
// file), the file is created (and overwritten) without buffering. This is
// useful for debugging because output will be written to the file even if
// the process crashes.
// -Author: Adel Amro
// http://my.opera.com/adelamro/blog


# ifndef LOG_WINDOW_H
# define LOG_WINDOW_H



# include <windows.h>


# define WC_LOGWINDOW			TEXT("LogWindowClass")


class CLogWindow
{
public:
	CLogWindow();
	~CLogWindow();

	BOOL Create( HINSTANCE, HWND parent = NULL, BOOL topMost = FALSE, LPCTSTR captionName = NULL );
	BOOL SetOutputFile( LPCTSTR fileName, BOOL overwrite = FALSE );
	BOOL SetOutputFile( HANDLE file );

	VOID Clear();

	VOID Write( const char* msg, ... );
	VOID WriteNewLine( const char* msg, ... );
	VOID operator () ( const char* msg, ... ); // Equivalent to WriteNewLine().

# ifdef UNICODE
	VOID Write( const WCHAR* msg, ... );
	VOID WriteNewLine( const WCHAR* msg, ... );
	VOID operator () ( const WCHAR* msg, ... ); // Equivalent to WriteNewLine().
# endif

	VOID Indent()	{ indentation++; }							// Add an indentation level.
	VOID Unindent()	{ if( indentation != 0 ) indentation--; }	// Remove an indentation level.

	operator HWND() const { return hWnd; }

	HWND hWnd;
	HWND hEdit;
	HANDLE hFile;

	// Utility object for easier indentation.
	// The object will indent the log window when it's created, and unindent it when it goes out of scope.
	struct ScopeIndent
	{
		CLogWindow& logWindow;
		ScopeIndent( CLogWindow& _logWindow ) : logWindow( _logWindow ) { logWindow.Indent(); }
		~ScopeIndent() { logWindow.Unindent(); }
	};

protected:
	LRESULT MsgProc( UINT Msg, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK StaticMsgProc( HWND, UINT, WPARAM, LPARAM );
	static BOOL RegisterClass( HINSTANCE );

	UINT indentation;
	BOOL deleteFile;
};


# endif // inclusion guard