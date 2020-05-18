
// FileRedirectClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CFileRedirectClientDlg �Ի���
class CFileRedirectClientDlg : public CDialogEx
{
// ����
public:
	CFileRedirectClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILEREDIRECTCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnconnect();
	afx_msg void OnLbnSelchangeFilterlist();
//	afx_msg void OnEnChangeRedirectpath();
	CEdit m_source_path;
	CEdit m_redirect_path;
	CListCtrl m_filter_list;
	afx_msg void OnBnClickedBtnaddfilter();
	afx_msg void OnBnClickedBtnclose();
};
