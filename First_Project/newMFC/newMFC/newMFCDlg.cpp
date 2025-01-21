
// newMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "newMFC.h"
#include "newMFCDlg.h"
#include "afxdialogex.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CnewMFCDlg 대화 상자



CnewMFCDlg::CnewMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWMFC_DIALOG, pParent),
	m_ClickLimitCount(3), // 초기값 설정
	m_ClickCount(0),
	m_Thinkness(1),
	m_Radius(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnewMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Radius);
	DDX_Text(pDX, IDC_EDIT2, m_Thinkness);
}

BEGIN_MESSAGE_MAP(CnewMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CnewMFCDlg::OnBnReset)
	ON_BN_CLICKED(IDC_BUTTON2, &CnewMFCDlg::OnBnRandom)
	ON_BN_CLICKED(IDC_BUTTON3, &CnewMFCDlg::OnBnRandomMove)
	//ON_EN_CHANGE(IDC_EDIT1, &CnewMFCDlg::SetRadius)
	ON_EN_CHANGE(IDC_EDIT2, &CnewMFCDlg::OnSetThinkness)
	ON_LBN_SELCHANGE(IDC_LIST1, &CnewMFCDlg::OnMouseCoordsList)
	ON_MESSAGE(WM_USER + 1, &CnewMFCDlg::OnCustomUpdateUI)
END_MESSAGE_MAP()


// CnewMFCDlg 메시지 처리기

BOOL CnewMFCDlg::OnInitDialog()
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
	OnBnClickedBtnImage();

	// 초기값 설정
	m_Radius = 10;       // 기본 반지름
	m_Thinkness = 3;     // 기본 두께
	UpdateData(FALSE);   // 초기값을 UI에 반영

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CnewMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CnewMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CnewMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CnewMFCDlg::OnBnClickedBtnImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();

	// fm 필드 이미지
	unsigned char* fm = (unsigned char*)m_Image.GetBits(); // 이미지의 첫 번째 포인터 값

	memset(fm, 0xff, nWidth * nHeight); // 먼저 이미지를 흰색으로 초기화


	// 컨트롤 영역을 피해서 배경 초기화
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			CPoint point(i, j);
			fm[j * nPitch + i] = 0xff; // 흰색으로 초기화
		}
	}

	UpdateDisplay();
}


void CnewMFCDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

BOOL CnewMFCDlg::ValidImgPos(int x, int y)
{
	BOOL bRet = false;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

void CnewMFCDlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	// 원 중심 좌표
	int nCenterX = x;
	int nCenterY = y;

	// 원의 범위가 이미지 영역을 초과하지 않도록 조정
	int startX = max(0, nCenterX - nRadius);
	int endX = min(nWidth - 1, nCenterX + nRadius);
	int startY = max(0, nCenterY - nRadius);
	int endY = min(nHeight - 1, nCenterY + nRadius);

	// 원 그리기
   // 컨트롤 영역을 피해 범위 제한
	for (int j = startY; j <= endY; j++)
	{
		for (int i = startX; i <= endX; i++)
		{
			CPoint point(i, j);
			if (IsInCircle(i, j, nCenterX, nCenterY, nRadius))
			{
				fm[j * nPitch + i] = nGray;
			}
		}
	}
}


bool CnewMFCDlg::IsInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;  // 수정: y 좌표 계산
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}
	return bRet;
}


void CnewMFCDlg::OnSetThinkness()
{
	if (!::IsWindow(m_hWnd)) // 다이얼로그 창이 유효한지 확인
		return;

	// 입력 값을 가져오기 위해 UI 동기화
	UpdateData(TRUE);

	// 입력값 유효성 검사
	if (m_Thinkness < 0)
	{
		AfxMessageBox(_T("두께는 음수가 될 수 없습니다!"));
		m_Thinkness = 3; // 기본값으로 설정
		UpdateData(FALSE); // UI에 값 반영
	}
}


afx_msg void CnewMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	// 에딧 컨트롤에서 반지름 값 가져오기
	UpdateData(TRUE); // 에딧 컨트롤 값 동기화
	if (m_Radius < 0) // 반지름 유효성 검사
	{
		AfxMessageBox(_T("반지름은 음수가 될 수 없습니다! 기본값으로 설정합니다."));
		m_Radius = 10;
	}

	// 드래그 시작 여부 확인
	m_DraggedCircleIndex = -1; // 초기값
	for (int i = 0; i < m_Circles.size(); ++i)
	{
		if (IsPointInCircle(point, m_Circles[i]))
		{
			m_DraggedCircleIndex = i; // 드래그 대상 원 인덱스
			m_IsDragging = true;
			return; // 드래그 이벤트 시작
		}
	}

	// 클릭한 점 추가 (원 개수 제한을 검사)
	if (m_Circles.size() < 3) // 원이 3개 미만일 경우에만 추가
	{
		CircleInfo circle = { point, m_Radius }; // 반지름은 10으로 기본 설정
		m_Circles.push_back(circle);

		// fm 필드 이미지 가져오기
		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		memset(fm, 0xff, m_Image.GetWidth() * m_Image.GetHeight()); // 기존 화면 초기화

		// 기존 원과 클릭된 점들 그리기
		for (const auto& c : m_Circles)
		{
			DrawCircle(fm, c.point.x, c.point.y, c.radius, 0); // 원 그리기
		}

		// 원의 개수가 3개가 되면 외접원을 계산
		if (m_Circles.size() == 3)
		{
			CPoint center;
			double radius;

			// 외접원 계산
			CalculateCircumcircle(m_Circles[0].point, m_Circles[1].point, m_Circles[2].point, center, radius);

			if (radius > 0) // 유효한 외접원일 경우
			{
				// 외접원 그리기
				DrawCircleOutline(fm, center.x, center.y, static_cast<int>(radius), 0, m_Thinkness);
			}
		}

		// 화면 갱신
		UpdateDisplay();
		OnMouseCoordsList();
	}
}


afx_msg void CnewMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_IsDragging)
	{
		m_IsDragging = false; // 드래그 종료
		m_DraggedCircleIndex = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

afx_msg void CnewMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_IsDragging && m_DraggedCircleIndex >= 0 && (nFlags & MK_LBUTTON))
	{
		// 원의 좌표를 마우스 위치로 업데이트
		m_Circles[m_DraggedCircleIndex].point = point;

		// 화면 갱신
		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		memset(fm, 0xff, m_Image.GetWidth() * m_Image.GetHeight()); // 배경 초기화

		for (const auto& circle : m_Circles)
		{
			DrawCircle(fm, circle.point.x, circle.point.y, circle.radius, 10);
		}

		// 원의 개수가 3개가 되면 외접원을 계산
		if (m_Circles.size() == 3)
		{
			CPoint center;
			double radius;

			// 외접원 계산
			CalculateCircumcircle(m_Circles[0].point, m_Circles[1].point, m_Circles[2].point, center, radius);

			if (radius > 0) // 유효한 외접원일 경우
			{
				// 외접원 그리기
				DrawCircleOutline(fm, center.x, center.y, static_cast<int>(radius), 0, m_Thinkness);
			}
		}
		UpdateDisplay();
		OnMouseCoordsList();
	}
}

void CnewMFCDlg::OnBnRandom()
{
	if (m_Circles.empty())
	{
		AfxMessageBox(_T("저장된 좌표가 없습니다."));
		return;
	}

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, m_Image.GetWidth() * m_Image.GetHeight()); // 배경 초기화

	// 랜덤 좌표 재배치
	srand((unsigned)time(nullptr)); // 랜덤 시드 설정
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	for (auto& circle : m_Circles)
	{
		circle.point.x = rand() % nWidth;
		circle.point.y = rand() % nHeight;

		// 새 위치에 원 그리기
		DrawCircle(fm, circle.point.x, circle.point.y, circle.radius, 10);
	}

	// 원의 개수가 3개가 되면 외접원을 계산
	if (m_Circles.size() == 3)
	{
		CPoint center;
		double radius;

		// 외접원 계산
		CalculateCircumcircle(m_Circles[0].point, m_Circles[1].point, m_Circles[2].point, center, radius);

		if (radius > 0) // 유효한 외접원일 경우
		{
			// 외접원 그리기
			DrawCircleOutline(fm, center.x, center.y, static_cast<int>(radius), 0, m_Thinkness);
		}
	}

	// 화면 갱신
	UpdateDisplay();
	OnMouseCoordsList();
}


void CnewMFCDlg::OnBnReset()
{
	m_Circles.clear(); // 모든 원 정보 초기화

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, m_Image.GetWidth() * m_Image.GetHeight()); // 배경 초기화

	// 화면 갱신
	UpdateDisplay();
	OnMouseCoordsList();
	m_ClickCount = 0;
}


void CnewMFCDlg::OnMouseCoordsList()
{
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST1); // 리스트박스 핸들 가져오기
	if (!pListBox)
		return;

	pListBox->ResetContent(); // 리스트박스 초기화

	CString strCoord;
	int Circle_size = m_Circles.size();

	for (int i = 0; i < Circle_size; i++)
	{
		strCoord.Format(_T("X: %d, Y: %d, R: %d"), m_Circles.at(i).point.x , m_Circles.at(i).point.y, m_Radius);
		pListBox->AddString(strCoord); // 중심 좌표와 반지름 정보 추가
	}
}


void CnewMFCDlg::CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3, CPoint& center, double& radius)
{
	double x1 = p1.x, y1 = p1.y;
	double x2 = p2.x, y2 = p2.y;
	double x3 = p3.x, y3 = p3.y;

	// 외접원 계산
	double dA = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

	if (fabs(dA) < 1e-6) // 세 점이 일직선 상에 있는 경우 처리
	{
		AfxMessageBox(_T("세 점이 일직선 상에 있습니다. 외접원을 계산할 수 없습니다."));
		center = CPoint(0, 0);
		radius = 0;
		return;
	}

	double A = x1 * x1 + y1 * y1;
	double B = x2 * x2 + y2 * y2;
	double C = x3 * x3 + y3 * y3;

	// 외접원의 중심
	double x_c = (A * (y2 - y3) + B * (y3 - y1) + C * (y1 - y2)) / (2 * dA);
	double y_c = (A * (x3 - x2) + B * (x1 - x3) + C * (x2 - x1)) / (2 * dA);

	center = CPoint(static_cast<int>(x_c), static_cast<int>(y_c));

	// 외접원의 반지름
	radius = sqrt(pow(x_c - x1, 2) + pow(y_c - y1, 2));
}


void CnewMFCDlg::DrawCircleOutline(unsigned char* fm, int x, int y, int nRadius, int nGray, int thickness)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	for (int angle = 0; angle < 360; angle++)
	{
		double radian = angle * 3.141592 / 180.0; // 각도를 라디안으로 변환
		int px = static_cast<int>(x + nRadius * cos(radian));
		int py = static_cast<int>(y + nRadius * sin(radian));

		for (int t = 0; t < thickness; t++) // 두께 조절 루프
		{
			double offset = t - thickness / 2.0; // 두께의 중앙을 기준으로 픽셀 배치
			int px_offset = static_cast<int>(px + offset * cos(radian + 3.141592 / 2.0)); // 수직 방향 오프셋 추가
			int py_offset = static_cast<int>(py + offset * sin(radian + 3.141592 / 2.0));

			if (px_offset >= 0 && px_offset < nWidth && py_offset >= 0 && py_offset < nHeight) // 유효한 이미지 영역 확인
			{
				fm[py_offset * nPitch + px_offset] = nGray; // 테두리 픽셀 값 설정
			}
		}
	}
}

bool CnewMFCDlg::IsPointInCircle(CPoint point, const CircleInfo& circle)
{
	double dX = point.x - circle.point.x;
	double dY = point.y - circle.point.y;
	double distanceSquared = dX * dX + dY * dY;

	return distanceSquared <= circle.radius * circle.radius;
}

// 랜덤 원 이동 및 그리기 동작 함수
void CnewMFCDlg::OnBnRandomMove()
{
	// 쓰레드 실행
	std::thread([this]() {
		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		int nWidth = m_Image.GetWidth();
		int nHeight = m_Image.GetHeight();

		for (int i = 0; i < 10; i++) // 총 10번 반복
		{
			// 랜덤 위치 갱신
			srand((unsigned)time(nullptr) + i); // 랜덤 시드 변경
			for (auto& circle : m_Circles)
			{
				circle.point.x = rand() % nWidth;
				circle.point.y = rand() % nHeight;
			}

			// 화면 갱신
			memset(fm, 0xff, nWidth * nHeight); // 배경 초기화
			for (const auto& circle : m_Circles)
			{
				DrawCircle(fm, circle.point.x, circle.point.y, circle.radius, 10); // 원 그리기
			}

			// 외접원 그리기 (원이 3개일 경우)
			if (m_Circles.size() == 3)
			{
				CPoint center;
				double radius;
				CalculateCircumcircle(m_Circles[0].point, m_Circles[1].point, m_Circles[2].point, center, radius);

				if (radius > 0)
				{
					DrawCircleOutline(fm, center.x, center.y, static_cast<int>(radius), 0, m_Thinkness);
				}
			}

			// UI 갱신 (메인 스레드에서 실행해야 함)
			PostMessage(WM_USER + 1); // 커스텀 메시지로 UI 업데이트 요청

			std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 0.5초 대기
		}
		}).detach(); // 별도 쓰레드로 실행
}

// WM_USER 메시지 핸들러
LRESULT CnewMFCDlg::OnCustomUpdateUI(WPARAM wParam, LPARAM lParam)
{
	UpdateDisplay(); // UI 업데이트
	return 0;
}