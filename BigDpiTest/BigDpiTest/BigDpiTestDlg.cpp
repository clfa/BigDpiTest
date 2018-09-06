#include "stdafx.h"
#include "BigDpiTest.h"
#include "BigDpiTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CBigDpiTestDlg::CBigDpiTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBigDpiTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBigDpiTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control( pDX, IDC_STATIC_INFO, m_stcInfo );
}

BEGIN_MESSAGE_MAP(CBigDpiTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CBigDpiTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    CString strInfo( _T( "显示设备物理参数信息如下：\n" ) );
    strInfo += _T( "==============================\n" );
    CString strTmp;

    HDC hDC = ::GetDC( GetSafeHwnd() );
    int dpiX = ::GetDeviceCaps( hDC, LOGPIXELSX );
    int dpiY = ::GetDeviceCaps( hDC, LOGPIXELSY );

    strTmp.Format( _T( "横向DPI(每英寸点数): %d\n" ), dpiX );
    strInfo += strTmp;

    strTmp.Format( _T( "纵向DPI(每英寸点数): %d\n" ), dpiY );
    strInfo += strTmp;

    int nPixelX = ::GetDeviceCaps( hDC, HORZRES );
    int nPixelY = ::GetDeviceCaps( hDC, VERTRES );
    strTmp.Format( _T( "屏幕分辨率为：%d x %d\n" ), nPixelX, nPixelY );
    strInfo += strTmp;

    int nBitsPixel = ::GetDeviceCaps( hDC, BITSPIXEL );
    strTmp.Format( _T( "颜色深度：%d 位\n" ), nBitsPixel );
    strInfo += strTmp;

    int nDispFrequency = ::GetDeviceCaps( hDC, VREFRESH );
    strTmp.Format( _T( "刷新频率：%d 赫兹\n" ), nDispFrequency );
    strInfo += strTmp;

    strTmp.Format( _T( "是否为大屏显示设备: %s\n" ), ( ( dpiX > 96 && dpiY > 96 ) ? _T( "是" ) : _T( "否" ) ) );
    strInfo += strTmp;

    ::ReleaseDC( NULL, hDC );

    m_stcInfo.SetWindowText( strInfo );

    //SetTimer( 0, 5000, NULL );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBigDpiTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CBigDpiTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBigDpiTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBigDpiTestDlg::OnTimer( UINT_PTR nIDEvent )
{
    KillTimer( nIDEvent );

    switch ( nIDEvent )
    {
        case 0:
            {
                /// 设置显示器省电模式
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 1 );

                Sleep( 3000 );

                /// 关闭显示器
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 2 );

                Sleep( 3000 );

                /// 开启显示器
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, -1 );
            }
            break;
        default:
            break;
    }
}