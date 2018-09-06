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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    CString strInfo( _T( "��ʾ�豸���������Ϣ���£�\n" ) );
    strInfo += _T( "==============================\n" );
    CString strTmp;

    HDC hDC = ::GetDC( GetSafeHwnd() );
    int dpiX = ::GetDeviceCaps( hDC, LOGPIXELSX );
    int dpiY = ::GetDeviceCaps( hDC, LOGPIXELSY );

    strTmp.Format( _T( "����DPI(ÿӢ�����): %d\n" ), dpiX );
    strInfo += strTmp;

    strTmp.Format( _T( "����DPI(ÿӢ�����): %d\n" ), dpiY );
    strInfo += strTmp;

    int nPixelX = ::GetDeviceCaps( hDC, HORZRES );
    int nPixelY = ::GetDeviceCaps( hDC, VERTRES );
    strTmp.Format( _T( "��Ļ�ֱ���Ϊ��%d x %d\n" ), nPixelX, nPixelY );
    strInfo += strTmp;

    int nBitsPixel = ::GetDeviceCaps( hDC, BITSPIXEL );
    strTmp.Format( _T( "��ɫ��ȣ�%d λ\n" ), nBitsPixel );
    strInfo += strTmp;

    int nDispFrequency = ::GetDeviceCaps( hDC, VREFRESH );
    strTmp.Format( _T( "ˢ��Ƶ�ʣ�%d ����\n" ), nDispFrequency );
    strInfo += strTmp;

    strTmp.Format( _T( "�Ƿ�Ϊ������ʾ�豸: %s\n" ), ( ( dpiX > 96 && dpiY > 96 ) ? _T( "��" ) : _T( "��" ) ) );
    strInfo += strTmp;

    ::ReleaseDC( NULL, hDC );

    m_stcInfo.SetWindowText( strInfo );

    //SetTimer( 0, 5000, NULL );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CBigDpiTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
                /// ������ʾ��ʡ��ģʽ
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 1 );

                Sleep( 3000 );

                /// �ر���ʾ��
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 2 );

                Sleep( 3000 );

                /// ������ʾ��
                ::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, -1 );
            }
            break;
        default:
            break;
    }
}