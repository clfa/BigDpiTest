#pragma once


class CBigDpiTestDlg : public CDialogEx
{
public:
	CBigDpiTestDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_BIGDPITEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer( UINT_PTR nIDEvent );

    DECLARE_MESSAGE_MAP()

private:

private:
    CStatic     m_stcInfo;
};