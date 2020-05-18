
// FileRedirectClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileRedirectClient.h"
#include "FileRedirectClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileRedirectClientDlg �Ի���



CFileRedirectClientDlg::CFileRedirectClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileRedirectClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileRedirectClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, SourcePath, m_source_path);
	DDX_Control(pDX, RedirectPath, m_redirect_path);
	DDX_Control(pDX, FilterList, m_filter_list);
}

BEGIN_MESSAGE_MAP(CFileRedirectClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(BtnConnect, &CFileRedirectClientDlg::OnBnClickedBtnconnect)
ON_BN_CLICKED(BtnAddFilter, &CFileRedirectClientDlg::OnBnClickedBtnaddfilter)
ON_BN_CLICKED(BtnClose, &CFileRedirectClientDlg::OnBnClickedBtnclose)
END_MESSAGE_MAP()


// CFileRedirectClientDlg ��Ϣ�������

BOOL CFileRedirectClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
   
	m_filter_list.GetClientRect(&rect);
	m_filter_list.SetExtendedStyle(m_filter_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_filter_list.InsertColumn(0, _T("Դ·��"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_filter_list.InsertColumn(1, _T("�ض���·��"), LVCFMT_CENTER, rect.Width() / 2, 1);

	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFileRedirectClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileRedirectClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFileRedirectClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileRedirectClientDlg::OnBnClickedBtnconnect()
{
	if (InitialCommunicationPort() != S_OK){
		MessageBox(L"����ʧ��", L"����", MB_OK);
		return;
	}
	isConnected = true;
}


void CFileRedirectClientDlg::OnBnClickedBtnaddfilter()
{
	if (!isConnected){
		MessageBox(L"��δ����", L"����", MB_OK);
		return;
	}

	CString source_path;
	CString redirect_path;
	TCHAR source_path_device[MAX_PATH] = { 0 };
	TCHAR redirect_path_device[MAX_PATH] = { 0 };

	m_source_path.GetWindowText(source_path);
	m_redirect_path.GetWindowText(redirect_path);

	if (source_path.IsEmpty()){
		MessageBox(L"Դ��ַ����Ϊ��", L"����", MB_OK);
		return;
	}

	if (redirect_path.IsEmpty()){
		MessageBox(L"�ض����ַ����Ϊ��", L"����", MB_OK);
		return;
	}

	COMMAND_MESSAGE data;
	data.Command = ENUM_ADD_FILTER;
	FILEFILTERITEM filter;

	QueryDosDevice(source_path.Left(2), source_path_device, MAX_PATH);
	QueryDosDevice(redirect_path.Left(2), redirect_path_device, MAX_PATH);

	source_path.Replace(source_path.Left(2), source_path_device);
	redirect_path.Replace(redirect_path.Left(2), redirect_path_device);

	filter.sourcePath = (LPWSTR)(LPCWSTR)source_path;
	filter.redirectPath = (LPWSTR)(LPCWSTR)redirect_path;

	data.filter = filter;
	SendMessageToPort(&data);

	m_filter_list.InsertItem(filterIndex, source_path);
	m_filter_list.SetItemText(filterIndex, 1, redirect_path);

	m_source_path.SetWindowText(_T(""));
	m_redirect_path.SetWindowText(_T(""));
	filterIndex++;

}


void CFileRedirectClientDlg::OnBnClickedBtnclose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (!isConnected){
		MessageBox(L"��δ����", L"����", MB_OK);
		return;
	}

	COMMAND_MESSAGE data;
	data.Command = ENUM_CLEAR_FILTER;
	SendMessageToPort(&data);
	m_filter_list.DeleteAllItems();
	filterIndex = 0;
}
