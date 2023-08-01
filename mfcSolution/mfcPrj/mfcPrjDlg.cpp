
// mfcPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcPrj.h"
#include "mfcPrjDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcPrjDlg 대화 상자

CmfcPrjDlg::CmfcPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EDIT, &CmfcPrjDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DATA, &CmfcPrjDlg::OnBnClickedBtnData)
END_MESSAGE_MAP()


// CmfcPrjDlg 메시지 처리기

BOOL CmfcPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 800, 650); //사이즈 지정
	m_pDlgImage = new CDlgImg; 
	m_pDlgImage->Create(IDD_DlgImg, this); 
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 800, 500);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

HCURSOR CmfcPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmfcPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pDlgImage) delete m_pDlgImage;
}


void CmfcPrjDlg::OnBnClickedBtnEdit()
{
	// 정보가져오기
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch(); 
	//memset(fm, 0, nWidth * nHeight);  // 초기화 되어 무게중심 못구함 주석 필요
	
	// 랜덤 좌표 생성
	int x = rand() % nWidth;
	int y = rand() % nHeight;
	CRect rect;
	m_pDlgImage->GetClientRect(&rect);

	//자식Dlg 좌표 전달
	m_pDlgImage->m_nDataCount = 1;
	m_pDlgImage->m_ptData[0] = CPoint(x, y);

	// 랜덤 원형의 중심 좌표 저장
	m_ptRandomCircleCenter = CPoint(x, y);

	//무게중심 빨간점 표시
	m_pDlgImage->m_ptCenter = CPoint(x, y);


	m_pDlgImage->m_bDrawCircle = true; 
	m_pDlgImage->Invalidate();
}


void CmfcPrjDlg::OnBnClickedBtnData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();


	//랜덤 원형 좌표 가져오기
	CPoint center = m_ptRandomCircleCenter;

	int nTh = 0x80;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) { // 중심값 구하기
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount; //int*int= int -> 하나를 double 형변환 
	double dCenterY = (double)nSumY / nCount;


	cout << dCenterX << "\t" << dCenterY << endl;
}
	




