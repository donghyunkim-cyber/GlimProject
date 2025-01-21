
// newMFCDlg.h: 헤더 파일
//

#pragma once
#include <vector> // std::vector 사용

using namespace std;

// CnewMFCDlg 대화 상자
class CnewMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CnewMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	struct CircleInfo
	{
		CPoint point; // Circle center
		int radius;   // Circle radius
	};

	vector<CircleInfo> m_Circles; // Vector to store all circles

public:
	void OnBnClickedBtnImage();
	void UpdateDisplay();
	void DrawCircle(unsigned char* fm , int i ,int j , int nRadius , int nGray);
	bool IsInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void OnSetThinkness();
	void SetRadius();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnBnReset();
	void OnBnRandom();
	void CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3, CPoint& center, double& radius);
	void DrawCircleOutline(unsigned char* fm, int x, int y, int nRadius, int nGray , int thickness);
	bool IsPointInCircle(CPoint point, const CircleInfo& circle);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void OnBnRandomMove();
	LRESULT OnCustomUpdateUI(WPARAM wParam, LPARAM lParam);
private:
	CImage m_Image;
	BOOL ValidImgPos(int x, int y);
	int m_ClickLimitCount;
	int m_ClickCount;
	int m_Radius;
	int m_Thinkness;
	vector<CPoint> m_MouseCoords;
	CPoint m_Circumcenter; // 외접원의 중심
	double m_Circumradius; // 외접원의 반지름

	bool m_IsDragging = false; // 드래그 중 여부
	int m_DraggedCircleIndex = -1; // 드래그 중인 원의 인덱스
public:
	afx_msg void OnMouseCoordsList();

};
