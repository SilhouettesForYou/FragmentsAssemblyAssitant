#pragma once


// CTuneDelta �Ի���

class CTuneDelta : public CDialogEx
{
	DECLARE_DYNAMIC(CTuneDelta)

public:
	CTuneDelta(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTuneDelta();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELTA_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_editValueOfDelta;
	afx_msg void OnBnClickedButtonConfConfirm();
	double GetDelta();
};
