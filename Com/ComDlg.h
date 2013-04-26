
// ComDlg.h : 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"


// CComDlg 对话框
class CComDlg : public CDialogEx
{
// 构造
public:
	CComDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_com;
	
	CString m_rdata;
	afx_msg void OnBnClickedButton2();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	
//	afx_msg void OnEnChangeEdit1();
	CEdit m_show_data;
	afx_msg void OnBnClickedButton3();
	//int m_send_data;
	CString m_send;
//	afx_msg void OnEnChangeEdit1();
	short m_port;
	int m_band;
	afx_msg void OnBnClickedButton1();
	// 由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
	int String2Hex(CString str, CByteArray & senddata);
	// 功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
	char ConvertHexChar(char ch);
	//CButton m_button2;
	CButton m_button2;
	//CComboBox m_combox;
};
