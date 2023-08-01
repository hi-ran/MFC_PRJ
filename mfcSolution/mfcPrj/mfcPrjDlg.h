
// mfcPrjDlg.h: 헤더 파일
//

#pragma once
#include "DlgImg.h"


// CmfcPrjDlg 대화 상자
class CmfcPrjDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfcPrjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImg * m_pDlgImage;
	CImage m_image;
	int m_nDataCount = 0; //몇개 그릴것인지
	CPoint m_ptData[MAX_POINT]; //좌표
	CPoint m_ptRandomCircleCenter; //랜덤 원형 좌표 
	CPoint m_ptCenter; //무게중심 점 

// 대화 상자 데이터입니다.	
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnData();
};
