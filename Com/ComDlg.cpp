
// ComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Com.h"
#include "ComDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComDlg 对话框




CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComDlg::IDD, pParent)

	, m_rdata(_T(""))

	//, m_send_data(0)
	, m_send(_T(""))
	, m_port(6)
	, m_band(19200)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_com);

	DDX_Text(pDX, IDC_EDIT2, m_rdata);

	DDX_Control(pDX, IDC_EDIT2, m_show_data);
	//DDX_Text(pDX, IDC_EDIT4, m_send_data);
	DDX_Text(pDX, IDC_EDIT4, m_send);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxShort(pDX, m_port, 0, 30);
	DDX_Text(pDX, IDC_EDIT3, m_band);
	//DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	//DDX_Control(pDX, IDC_COMBO2, m_combox);
}

BEGIN_MESSAGE_MAP(CComDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CComDlg::OnBnClickedButton2)
	//	ON_WM_CREATE()
	//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CComDlg::OnBnClickedButton3)
	//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CComDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CComDlg 消息处理程序

BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CBitmap   m_Nextmap;
	//m_Nextmap.LoadBitmap(IDB_BITMAP3);
	//HBITMAP   hBitmap   =   (HBITMAP)   m_Nextmap.GetSafeHandle(); 
	// m_button2.SetBitmap(hBitmap); 


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_band0;
	UpdateData(TRUE);
	m_band0.Format(_T("%d,n,8,1"),m_band);

	if(!m_com.get_PortOpen())
	{

		m_com.put_Settings(m_band0);
		m_com.put_CommPort(m_port);
		m_com.put_PortOpen(TRUE);  //打开串口
		m_button2.SetWindowTextW(_T("关闭串口"));
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP1)));
		//UpdateData(FALSE);
	}
	else
	{
		m_com.put_PortOpen(FALSE);//打开串口
		m_button2.SetWindowTextW(_T("打开串口"));
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP2)));

	}
}


//int CComDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}
BEGIN_EVENTSINK_MAP(CComDlg, CDialogEx)
	ON_EVENT(CComDlg, IDC_MSCOMM1, 1, CComDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CComDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp;//
	//if(m_com.get_CommEvent()==2) //事件值为2表示接收缓冲区内有字符
	//{
	variant_inp=m_com.get_Input(); //读缓冲区
	safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
	len=safearray_inp.GetOneDimSize(); //得到有效数据长度
	for(k=0;k <len;k++)
		safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
	for(k=0;k <len;k++) //将数组转换为Cstring型变量
	{
		BYTE bt=*(char*)(rxdata+k); //字符型
		strtemp.Format(_T("%02x"),bt);//将字符送入临时变量strtemp存放

		//m_strRXData+=strtemp; //加入接收编辑框对应字符串

		//	}
	}

	UpdateData(TRUE); //更新编辑框内容 
	m_rdata+=" ";
	m_rdata+=strtemp;
	UpdateData(FALSE);
	m_show_data.LineScroll(m_show_data.GetLineCount());

}


//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CComDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //读取编辑框内容

	CByteArray hexdata;
	String2Hex(m_send,hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
	m_com.put_Output(COleVariant(hexdata)); //发送十六进制数据



}



/*   UpdateData(TRUE);

CByteArray sendArr; 
WORD Length;

Length=m_send.GetLength();
sendArr.SetSize(Length);
for(int i =0; i<Length; i++)
{
sendArr.SetAt(i, m_send.GetAt(i));
}
m_com.put_Output(COleVariant(sendArr));
*/



//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CComDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString xx("221");
	m_rdata.Empty();
	UpdateData(FALSE);
	//m_combox.ShowDropDown( TRUE);
}


// 由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
int CComDlg::String2Hex(CString str, CByteArray & senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}


// 功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
char CComDlg::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}
