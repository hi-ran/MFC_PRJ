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


// CDlgImg 메시지 처리기
void CDlgImg::InitImage()
{
	int nWidth = 1000;
	int nHeight = 1000;
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


BOOL CDlgImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, 640, 480);
	InitImage();
	
	return TRUE;  
}


void CDlgImg::OnPaint()
{
	CPaintDC dc(this); 

	if (m_image)
		m_image.Draw(dc, 0, 0);

	drawData(&dc);
}

#define COLOR_RED   RGB(0xff,0,0) 
void CDlgImg::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]); 
		rect.InflateRect(2, 2); 
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);
}