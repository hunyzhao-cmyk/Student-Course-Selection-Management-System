
// DemoDlg.h: 头文件
//

#pragma once


// CMyDemoDlg 对话框
class CMyDemoDlg : public CDialogEx
{
// 构造
public:
	CMyDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString m_strOriginalSno;   // 保存选中的原始学号

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	
	CListCtrl my_list;
	void ShowData();
	
	CEdit m_edtsno;
	CEdit m_edtsname;
	CEdit m_edtssex;
	CEdit m_edtsage;
	CEdit m_edtsdept;
	afx_msg void OnNMClickList2Show(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDelete();
	CButton m_chkMath;
	CButton m_chkEnglish;
	CButton m_chkPhysics;
	CButton m_chkChemistry;
	CButton m_chkBiology;
	afx_msg void OnBnClickedButtonSelectCourse();
	afx_msg void OnBnClickedButtonReset();
};
