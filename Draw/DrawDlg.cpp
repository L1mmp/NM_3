
// DrawDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LagrangeInterpolator.h"


// диалоговое окно CDrawDlg



CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDrawDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CDrawDlg

BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	drv.Create(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());
	drv2.Create(GetDlgItem(IDC_PICTURE2)->GetSafeHwnd());

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//drv.Draw();
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDrawDlg::OnBnClickedOk()
{
	vector<double> F;

	double arrayX[26];
	double arrayY[26];

	for (int i = 0; i < 26; i++)
	{
		arrayX[i] = i * 0.08;
		arrayY[i] = sin(pow(arrayX[i], 3));
	}

	LagrangeInterpolator lagrange;

	vector<double> FInterpolyant;
	for (int i = 0; i < 1000; i++)
	{
		F.push_back(sin(pow(i, 3) * 3.14 / 2e5));
	}

	for (double i = 30; i < 1000; i+=0.6)
	{
		FInterpolyant.push_back(lagrange.GetValue(arrayX, arrayY, pow(i, 3) * 3.14 / 5e5/*pow(i, 3) / 100000, 26*/, 26));
	}

	drv.DrawTwoFunctions(F, FInterpolyant);
}
