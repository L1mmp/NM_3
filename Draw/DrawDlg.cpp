
// DrawDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "afxdialogex.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LagrangeInterpolator.h"


// ���������� ���� CDrawDlg



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


// ����������� ��������� CDrawDlg

BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	drv.Create(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());
	//drv2.Create(GetDlgItem(IDC_PICTURE2)->GetSafeHwnd());

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//drv.Draw();
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDrawDlg::OnBnClickedOk()
{
	vector<double> F;
	vector<double> F_keys;

	LagrangeInterpolator lagrange;

	vector<double> FInterpolyant;
	vector<double> FInterpolyant_keys;
	for (int i = 0; i < 1000; i++)
	{
		double x = i * 2.0 / 1000.0;
		F.push_back(sin(pow(x, 3)));
		F_keys.push_back(x);
	}

	double arrayX[100];
	double arrayY[100];
	int n = 10;

	for (int i = 0; i < n; i++)
	{
		arrayX[i] = i * 2.0 / (n - 1);
		arrayY[i] = sin(pow(arrayX[i], 3));
	}

	for (int i = 0; i < 1000; i++)
	{
		double x = i * 2.0 / 1000.0;
		FInterpolyant_keys.push_back(x);
		FInterpolyant.push_back(lagrange.GetValue(arrayX, arrayY, x, n));
	}

	ofstream fout;
	fout.open("../result.txt");
	int k = 30;

	for (int i = 0; i < k+1; i++)
	{
		double x = i * 0.08;
		double difference = sin(pow(x, 3)) - lagrange.GetValue(arrayX, arrayY, x, n);

		fout << "X: " << x << '\t' << "f(" << x << ") - " << "F" << "(" << x << ") = " << difference << endl;
	}
	fout.close();

	drv.DrawTwoFunctions(F, FInterpolyant, F_keys, FInterpolyant_keys);
}
