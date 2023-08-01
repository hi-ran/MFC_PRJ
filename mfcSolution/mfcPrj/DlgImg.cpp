// DlgImg.cpp: 구현 파일
//

#include "pch.h"
#include "mfcPrj.h"
#include "afxdialogex.h"
#include "DlgImg.h"


// CDlgImg 대화 상자

IMPLEMENT_DYNAMIC(CDlgImg, CDialogEx)

CDlgImg::CDlgImg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgImg, pParent)
{

}

CDlgImg::~CDlgImg()
{
}

void CDlgImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


/*이미지 설정*/
void CDlgImg::InitImage()
{
	//img defult 크기  
	int nWidth = 800;
	int nHeight = 500;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

/*이미지 초기화*/
BOOL CDlgImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, 800, 500);
	InitImage();
	
	m_bDrawCircle = false; 

	return TRUE;  
}

 /*그림판 설정*/
#define COLOR_YELLOW   RGB(255, 255, 0) 
void CDlgImg::OnPaint()
{
	CPaintDC dc(this); 

	if (m_image)
		m_image.Draw(dc, 0, 0);

	//초기화면에 원형이 안나오려면 false 상태인 OnPaint 함수에 draw 넣기 
	if (m_bDrawCircle) 
	{
		CRect rect;
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW); 
		CPen* pOldPen = dc.SelectObject(&pen);

		for (int i = 0; i < m_nDataCount; i++) {
			rect.SetRect(m_ptData[i], m_ptData[i]);
			rect.InflateRect(50, 50);
			dc.Ellipse(rect);
		}
		dc.SelectObject(pOldPen);
	}
}

 /*노란 원형 그리기*/
//void CDlgImg::drawData(CDC* pDC)
//{
//	CRect rect;
//	CPen pen;
//	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW); //색상
//	CPen* pOldPen = pDC->SelectObject(&pen);
//
//	for (int i = 0; i < m_nDataCount; i++) {
//		rect.SetRect(m_ptData[i], m_ptData[i]); 
//		rect.InflateRect(50, 50);  
//		pDC->Ellipse(rect);
//	}
//	pDC->SelectObject(pOldPen);
//}