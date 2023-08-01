#pragma once
#include "afxdialogex.h"
#define MAX_POINT 1000

// CDlgImg 대화 상자
class CDlgImg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImg)

public:
	CDlgImg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImg();

	CImage m_image;
	int m_nDataCount = 0; //몇개 그릴것인지
	CPoint m_ptData[MAX_POINT]; //좌표

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgImg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	void InitImage(); //그림판 size
	void drawData(CDC* pDC);

public:
	afx_msg void OnPaint();
};


