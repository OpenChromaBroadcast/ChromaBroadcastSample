
// ChromaBroadcastSampleDlg.h : header file
//

#pragma once


// CChromaBroadcastSampleDlg dialog
class CChromaBroadcastSampleDlg : public CDialogEx
{
// Construction
public:
	CChromaBroadcastSampleDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHROMABROADCASTSAMPLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	void setColors(COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, COLORREF color5);

// Implementation
protected:
	HICON m_hIcon;
	CMFCColorButton m_ColorButton1;
	CMFCColorButton m_ColorButton2;
	CMFCColorButton m_ColorButton3;
	CMFCColorButton m_ColorButton4;
	CMFCColorButton m_ColorButton5;

	COLORREF m_Color1;
	COLORREF m_Color2;
	COLORREF m_Color3;
	COLORREF m_Color4;
	COLORREF m_Color5;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
