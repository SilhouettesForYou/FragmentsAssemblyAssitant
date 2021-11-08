
// FragmentsRestorationAssitantDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FragmentsRestorationAssitant.h"
#include "FragmentsRestorationAssitantDlg.h"
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


// CFragmentsRestorationAssitantDlg �Ի���

CString CFragmentsRestorationAssitantDlg::defaultPath = _T("");

CFragmentsRestorationAssitantDlg::CFragmentsRestorationAssitantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFragmentsRestorationAssitantDlg::IDD, pParent)
	, m_csModelDir(_T(""))
	, m_radioMajorAxis(0)
	, m_editValueOfRotate(_T(""))
	, m_editValueOfTranslate(_T(""))
	, m_editValueOfRecordOperation(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LOGO);
	m_btnRoateConfIcon = AfxGetApp()->LoadIcon(IDI_ICON_DELTA_CONF);
	m_btnTranslateConfIcon = AfxGetApp()->LoadIcon(IDI_ICON_DELTA_CONF);

	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	originalRendererWindow = vtkSmartPointer<vtkRenderWindow>::New();
	originalInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	adjustedRendererWindow = vtkSmartPointer<vtkRenderWindow>::New();
	adjustedInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

}

void CFragmentsRestorationAssitantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIRECTORY_OF_MODELS, m_csModelDir);
	DDX_Control(pDX, IDC_EDIT_DIRECTORY_OF_MODELS, m_eModelsDir);
	DDX_Radio(pDX, IDC_RADIO_MAJOR_AXIS, m_radioMajorAxis);
	DDX_Control(pDX, IDC_SPIN_TURN_ROTATE, m_spinTurnRotate);
	DDX_Control(pDX, IDC_SPIN_TURN_TRANSLATE, m_spinTurnTranslate);
	DDX_Text(pDX, IDC_EDIT_VALUE_OF_ROTATE, m_editValueOfRotate);
	DDX_Text(pDX, IDC_EDIT_VALUE_OF_TRANSLATE, m_editValueOfTranslate);
	DDX_Control(pDX, IDC_EDIT_RECORD_OPERATION, m_editRecordOperation);
	DDX_Text(pDX, IDC_EDIT_RECORD_OPERATION, m_editValueOfRecordOperation);
	DDX_Control(pDX, IDC_BUTTON_ROTATE_CONF, m_btnRotateConf);
	DDX_Control(pDX, IDC_BUTTON_TRANSLATE_CONF, m_btnTranslateConf);
}

BEGIN_MESSAGE_MAP(CFragmentsRestorationAssitantDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FRAGMENTS_AND_FRACTURES, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonOpenFragmentsAndFractures)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FIX_FRACTURE, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonChooseFixFracture)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FLOAT_FRACTURE, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonChooseFloatFracture)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_PCA, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonFirstPca)
	ON_BN_CLICKED(IDC_BUTTON_TURN_OVER, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonTurnOver)
	ON_BN_CLICKED(IDC_RADIO_MAJOR_AXIS, &CFragmentsRestorationAssitantDlg::OnBnClickedRadioMajorAxis)
	ON_BN_CLICKED(IDC_RADIO_MINOR_AXIS, &CFragmentsRestorationAssitantDlg::OnBnClickedRadioMajorAxis)
	ON_BN_CLICKED(IDC_RADIO_Z_AXIS, &CFragmentsRestorationAssitantDlg::OnBnClickedRadioMajorAxis)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TURN_ROTATE, &CFragmentsRestorationAssitantDlg::OnDeltaposSpinTurnRotate)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TURN_TRANSLATE, &CFragmentsRestorationAssitantDlg::OnDeltaposSpinTurnTranslate)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE_CONF, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonRotateConf)
	ON_BN_CLICKED(IDC_BUTTON_TRANSLATE_CONF, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonTranslateConf)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FRAGMENT, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonSaveFragment)
	ON_BN_CLICKED(IDC_BUTTON_RECHOSE, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonRechose)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_RELATION, &CFragmentsRestorationAssitantDlg::OnBnClickedButtonSaveRelation)
END_MESSAGE_MAP()


// CFragmentsRestorationAssitantDlg ��Ϣ�������

BOOL CFragmentsRestorationAssitantDlg::OnInitDialog()
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
	m_spinTurnRotate.SetBuddy(GetDlgItem(IDC_EDIT_VALUE_OF_ROTATE));
	m_spinTurnTranslate.SetBuddy(GetDlgItem(IDC_EDIT_VALUE_OF_TRANSLATE));

	m_btnRotateConf.SetIcon(m_btnRoateConfIcon);
	m_btnTranslateConf.SetIcon(m_btnTranslateConfIcon);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CFragmentsRestorationAssitantDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFragmentsRestorationAssitantDlg::OnPaint()
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
HCURSOR CFragmentsRestorationAssitantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CALLBACK  CFragmentsRestorationAssitantDlg::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:    //��ʼ����Ϣ
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)(LPTSTR)(LPCTSTR)defaultPath);   //  defaultPath Ϊ��ľ�̬����
		break;
	case BFFM_SELCHANGED:    //ѡ��·���仯
		TCHAR curr[MAX_PATH];
		SHGetPathFromIDList((LPCITEMIDLIST)lParam, curr);
		::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)curr);
	break;
	default:
		break;
	}
	return 0;
}


void CFragmentsRestorationAssitantDlg::InitFragmentsView()
{
	DisplayFragmentsAndFracturess(fragments, fracturess, renderWindow);
}


void CFragmentsRestorationAssitantDlg::RecordOperation(int op, string value = "")
{
	UpdateData(true);
	string history = Utils::UnicodeToANSI(m_editValueOfRecordOperation) + utils.LOG(op, value);
	CString message;
	message.Format(_T("%s\r\n"), CStringW(history.c_str()));
	m_editValueOfRecordOperation = message;
	UpdateData(false);
	this->SendDlgItemMessage(IDC_EDIT_RECORD_OPERATION, WM_VSCROLL, SB_BOTTOM, 0); //������ʼ���ڵײ�
}


vtkSmartPointer<vtkUnsignedCharArray> CFragmentsRestorationAssitantDlg::DyeForPoint(int numOfPoints, int scheme)
{
	vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colors->SetNumberOfComponents(3);
	for (int i = 0; i < numOfPoints; i++)
	{
		colors->InsertTuple(i, COLOR_RAINBOW[scheme]);
	}
	return colors;
}


vtkSmartPointer<vtkPolyData> CFragmentsRestorationAssitantDlg::DrawPCA(vtkSmartPointer<vtkPolyData> frature, vector<vtkSmartPointer<vtkLineSource>>& lines, double* maxEigenVector, double* secEigenVector, double center[3])
{
	vtkSmartPointer<vtkDoubleArray> eigenvectors = vtkSmartPointer<vtkDoubleArray>::New();
	Registration registration(frature);
	registration.PCA(eigenvectors);
	int vectorNum = eigenvectors->GetNumberOfTuples();
	for (vtkIdType i = 0; i < vectorNum; i++)
	{
		double eigenVector[3];
		eigenvectors->GetTypedTuple(i, eigenVector);
	}

	eigenvectors->GetTypedTuple(0, maxEigenVector);
	eigenvectors->GetTypedTuple(1, secEigenVector);

	// ��ȡģ�͵����ĵ�
	frature->GetCenter(center);
	//cout << "center: " << center[0] << ", " << center[1] << ", " << center[2] << endl;

	double** endpoints = new double*[vectorNum];
	for (int i = 0; i < vectorNum; i++)
		endpoints[i] = new double[3];
	for (int i = 0; i < vectorNum; i++)
	{
		int delta;
		vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
		double eigenVector[3];
		eigenvectors->GetTypedTuple(i, eigenVector);
		if (i == 0)
			delta = 50;
		else
			delta = 25;
		// һ���˵�
		for (int j = 0; j < 3; j++)
			endpoints[i][j] = eigenVector[j] * -delta + center[j];
		line->SetPoint1(endpoints[i]);
		// ��һ���˵�
		for (int j = 0; j < 3; j++)
			endpoints[i][j] = eigenVector[j] * delta + center[j];
		line->SetPoint2(endpoints[i]);
		line->Update();
		lines.push_back(line);
	}
	return registration.ConvertToVertex();
}


vector<vtkSmartPointer<vtkPolyData>> CFragmentsRestorationAssitantDlg::PreRegistration(vtkSmartPointer<vtkPolyData> fracture1, vtkSmartPointer<vtkPolyData> fracture2, vtkSmartPointer<vtkMatrix4x4>& matrix)
{
	bool isTurnedOverMain = false;			// �ж��Ƿ���������ת
	bool isTurnedOverSec = false;			// �ж��Ƿ��ڴη���ת
	double center1[3], center2[3];			// ������������ĵ�
	double eigenVector1[3];					// ����1��������
	double secEigenVector1[3];				// ����1�Ĵη���
	double eigenVector2[3];					// ����2��������
	double secEigenVector2[3];				// ����2�Ĵη���

	vector<vtkSmartPointer<vtkPolyData>> datas;
	vector<vtkSmartPointer<vtkLineSource>> lines;
	//DrawPCA(fractureName1, lines);
	vtkSmartPointer<vtkPolyData> fixedPolyData = DrawPCA(fracture1, lines, eigenVector1, secEigenVector1, center1);				// �任�й̶���PolyData
	vtkSmartPointer<vtkPolyData> transformedPolyData = DrawPCA(fracture2, lines, eigenVector2, secEigenVector2, center2);		// �任���ƶ���PolyData

	// ������������������ļн�
	double innerProduct = eigenVector1[0] * eigenVector2[0] + eigenVector1[1] * eigenVector2[1] + eigenVector1[2] * eigenVector2[2];
	double theta = acos(innerProduct / (vtkMath::Norm(eigenVector1) * vtkMath::Norm(eigenVector2)));

	// �����ж������ĵ���룬��Ҫ���ڵڶ���Ԥ��׼
	double distance = sqrt(square(center1[0] - center2[0]) + square(center1[1] - center2[1]) + square(center1[2] - center2[2]));
	cout << "distance between two centers: " << distance << endl;
	cout << theta << "----" << 180 * theta / vtkMath::Pi() << "��" << endl;

	// 
	Registration re;
	double delta = 50;
	double axis1[3], axis2[3];
	double endpoints1[3], endpoints2[3];
	re.GetRotateAxis(eigenVector1, secEigenVector1, axis1);
	re.GetRotateAxis(eigenVector2, secEigenVector2, axis2);
	vtkSmartPointer<vtkLineSource> lineAxis1 = vtkSmartPointer<vtkLineSource>::New();
	vtkSmartPointer<vtkLineSource> lineAxis2 = vtkSmartPointer<vtkLineSource>::New(); 
	for (int i = 0; i < 3; i++)
	{
		endpoints1[i] = axis1[i] * -delta + center1[i];
		endpoints2[i] = axis2[i] * -delta + center2[i];
	}
	lineAxis1->SetPoint1(center1);
	lineAxis1->SetPoint2(endpoints1);
	lineAxis1->Update();
	lineAxis2->SetPoint1(center2);
	lineAxis2->SetPoint2(endpoints2);
	lineAxis2->Update();

	// ��¼�������ȸ�������
	for (int i = 0; i < 3; i++)
	{
		majorAxis[i] = eigenVector1[i];
		minorAxis[i] = secEigenVector1[i];
		axis[i] = axis1[i];

		fixedCenter[i] = center1[i];
		floatCenter[i] = center2[i];

		rotateAxis = majorAxis;
	}

	// �������ĵ�
	vtkSmartPointer<vtkSphereSource> sphere1 = vtkSmartPointer<vtkSphereSource>::New();
	vtkSmartPointer<vtkSphereSource> sphere2 = vtkSmartPointer<vtkSphereSource>::New();
	sphere1->SetRadius(0.5);
	sphere2->SetRadius(0.5);
	sphere1->SetCenter(center1);
	sphere2->SetCenter(center2);
	sphere1->Update();
	sphere2->Update();

	fixedPolyData->GetPointData()->SetScalars(DyeForPoint(fixedPolyData->GetNumberOfPoints(), 2)); // ��ɫ
	transformedPolyData->GetPointData()->SetScalars(DyeForPoint(transformedPolyData->GetNumberOfPoints(), 3));
	datas.push_back(lineAxis1->GetOutput());
	datas.push_back(lineAxis2->GetOutput());
	datas.push_back(lines[0]->GetOutput());
	datas.push_back(lines[3]->GetOutput());
	datas.push_back(lines[1]->GetOutput());
	datas.push_back(lines[4]->GetOutput());
	datas.push_back(sphere1->GetOutput());
	datas.push_back(sphere2->GetOutput());

	// ������ת����
	vtkSmartPointer<vtkMatrix4x4> rotateMatrixMain = vtkSmartPointer<vtkMatrix4x4>::New();			// ʹ��������������ƽ�е���ת����
	vtkSmartPointer<vtkMatrix4x4> rotateMatrixJunior = vtkSmartPointer<vtkMatrix4x4>::New();		// ʹ�����η�������ƽ�е���ת����
	vtkSmartPointer<vtkMatrix4x4> translateMatrix = vtkSmartPointer<vtkMatrix4x4>::New();			// ƽ�ƾ���
	vtkSmartPointer<vtkMatrix4x4> turnOverMatrix = vtkSmartPointer<vtkMatrix4x4>::New();			// �������ᷭת����
	vtkSmartPointer<vtkMatrix4x4> matrixWithoutTranslate = vtkSmartPointer<vtkMatrix4x4>::New();


	Registration registration;
	registration.InstanceMatrix(matrix);
	registration.InstanceMatrix(matrixWithoutTranslate);

	// ����ʹ��������������ƽ�е���ת����
	registration.RotateByAnyAxis(eigenVector1, eigenVector2, rotateMatrixMain);
	vtkMatrix4x4::Multiply4x4(matrix, rotateMatrixMain, matrix);


	// ����ʹ��������η���ƽ�е���ת����
	double newSecEigenVector2[3];
	registration.TransformPoints(matrix, secEigenVector2, newSecEigenVector2);
	registration.RotateByAnyAxis(secEigenVector1, newSecEigenVector2, rotateMatrixJunior);
	vtkMatrix4x4::Multiply4x4(rotateMatrixJunior, matrix, matrix);
	vtkMatrix4x4::Multiply4x4(matrix, matrixWithoutTranslate, matrixWithoutTranslate);


	// ����ʹ�����������ĵ��غϵ���ת����
	double newCenter2[3];
	registration.TransformPoints(matrix, center2, newCenter2);
	registration.TranslateMatrix(center1, newCenter2, translateMatrix);
	vtkMatrix4x4::Multiply4x4(translateMatrix, matrix, matrix);


	Registration transform(transformedPolyData);
	vtkSmartPointer<vtkPolyData> afterTransformedPolyData = vtkSmartPointer<vtkPolyData>::New();
	transform.TransformPolyData(matrix, afterTransformedPolyData);

	datas.push_back(fixedPolyData);
	datas.push_back(transformedPolyData);

	return datas;
}


void CFragmentsRestorationAssitantDlg::Display(int itemId, vtkSmartPointer<vtkRenderWindow> renWin, vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
	CRect rect;
	GetDlgItem(itemId)->GetWindowRect(rect);
	CWnd* pWnd = GetDlgItem(itemId);
	HWND hwnd = pWnd->GetSafeHwnd();
	renWin->SetParentId(hwnd);
	renWin->SetSize(rect.Width(), rect.Height());

	interactor->SetRenderWindow(renWin);
	renWin->Render();
	interactor->Start();
}


void CFragmentsRestorationAssitantDlg::DisplayFragmentsAndFracturess(vector<vtkSmartPointer<vtkPolyData>> fragments, vector<vector<vtkSmartPointer<vtkPolyData>>> fracturess, vtkSmartPointer<vtkRenderWindow>& renderWindow)
{
	// Setup render window, renderer, and interactor
	unsigned int n = fragments.size();
	double delta = 1.0 / n;
	vector<vector<double>> viewports;
	for (unsigned int i = 0; i < n; i++)
	{
		vector<double> viewport;
		viewport.push_back(delta * (i));
		viewport.push_back(0.5);
		viewport.push_back(delta * (i + 1));
		viewport.push_back(1);
		viewports.push_back(viewport);
	}


	for (unsigned int i = 0; i < n; i++)
	{
		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		vtkSmartPointer<vtkTextActor> textActor =
			vtkSmartPointer<vtkTextActor>::New();

		mapper->SetInputData(fragments[i]);
		actor->SetMapper(mapper);
		//actor->GetProperty()->SetOpacity(0.5);
		//actor->GetProperty()->EdgeVisibilityOn();
		//actor->GetProperty()->BackfaceCullingOn();
		//actor->SetBackfaceProperty(backfaces);
		//actor->GetProperty()->SetEdgeColor(171 / 255.0, 224 / 255.0, 255 / 255.0); 
		actor->GetProperty()->SetColor(COLOR_RAINBOW[i % 10][0] / 255.0, COLOR_RAINBOW[i % 10][1] / 255.0, COLOR_RAINBOW[i % 10][2] / 255.0);
		renderer->AddActor(actor);

		vtkSmartPointer<vtkProperty2D> textProperty = textActor->GetProperty();
		string fragmentName = "# " + fragmentNames[i].substr(0, fragmentNames[i].length() - 4);
		textActor->SetInput(fragmentName.c_str());
		/*textProperty->SetFontFamilyToArial();
		textProperty->BoldOn();
		textProperty->SetFontSize(36);
		textProperty->ShadowOn();
		textProperty->SetShadowOffset(4, 4);*/
		textProperty->SetColor(22 / 255.0, 36 / 255.0, 92 / 255.0);
		//textActor->SetDisplayPosition(20, 30);
		//textActor->SetPosition(150, 16);
		renderer->AddActor(textActor);

		renderer->SetViewport(viewports[i][0], viewports[i][1], viewports[i][2], viewports[i][3]);
		//renderer->ResetCameraClippingRange();
		//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
		renderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
		renderWindow->AddRenderer(renderer);

		// ���ö����λ��

		double delta1 = delta / fracturess[i].size();

		for (unsigned int j = 0; j < fracturess[i].size(); j++)
		{
			vector<double> viewport;
			viewport.push_back(viewports[i][0] + delta1 * (j));
			viewport.push_back(0);
			viewport.push_back(viewports[i][0] + delta1 * (j + 1));
			viewport.push_back(0.5);

			vtkSmartPointer<vtkRenderer> renderer =
				vtkSmartPointer<vtkRenderer>::New();
			vtkSmartPointer<vtkPolyDataMapper> mapper =
				vtkSmartPointer<vtkPolyDataMapper>::New();
			vtkSmartPointer<vtkActor> actor =
				vtkSmartPointer<vtkActor>::New();
			vtkSmartPointer<vtkTextActor> textActor =
				vtkSmartPointer<vtkTextActor>::New();

			mapper->SetInputData(fracturess[i][j]);
			actor->SetMapper(mapper);
			//actor->GetProperty()->SetOpacity(0.5);
			//actor->GetProperty()->EdgeVisibilityOn();
			//actor->GetProperty()->BackfaceCullingOn();
			//actor->SetBackfaceProperty(backfaces);
			//actor->GetProperty()->SetEdgeColor(171 / 255.0, 224 / 255.0, 255 / 255.0); 
			actor->GetProperty()->SetColor(COLOR_RAINBOW[i % 10][0] / 255.0, COLOR_RAINBOW[i % 10][1] / 255.0, COLOR_RAINBOW[i % 10][2] / 255.0);
			renderer->AddActor(actor);

			vtkSmartPointer<vtkProperty2D> textProperty = textActor->GetProperty();
			textActor->SetInput(("# " + string(1, (char)('a' + j))).c_str());
			/*textProperty->SetFontFamilyToArial();
			textProperty->BoldOn();
			textProperty->SetFontSize(36);
			textProperty->ShadowOn();
			textProperty->SetShadowOffset(4, 4);*/
			textProperty->SetColor(22 / 255.0, 36 / 255.0, 92 / 255.0);
			//textActor->SetDisplayPosition(20, 30);
			renderer->AddActor(textActor);

			renderer->SetViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
			//renderer->ResetCameraClippingRange();
			//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
			//renderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
			//int index = rand() % 6;
			renderer->SetBackground(COLOR_BACKGROUND_LIGHT[i % 5][0] / 255.0, COLOR_BACKGROUND_LIGHT[i % 5][1] / 255.0, COLOR_BACKGROUND_LIGHT[i % 5][2] / 255.0);
			renderWindow->AddRenderer(renderer);
		}
	}
}


void CFragmentsRestorationAssitantDlg::DisplayFragmentsAndFractures(vector<vtkSmartPointer<vtkPolyData>> fragments, vector<vtkSmartPointer<vtkPolyData>> fractures, vtkSmartPointer<vtkRenderWindow>& renderWindow, vtkSmartPointer<vtkMatrix4x4> matrix = NULL)
{
	double topViewport[4] = { 0.0, 0.5, 1.0, 1.0 };
	double bottomViewport[4] = { 0.0, 0.0, 1.0, 0.5 };
	//assert(fragments.size() == fractures.size());
	vtkSmartPointer<vtkRenderer> topRenderer =
		vtkSmartPointer<vtkRenderer>::New();

	for (unsigned int i = 0; i < fragments.size(); i++)
	{
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();

		mapper->SetInputData(fragments[i]);
		actor->SetMapper(mapper);
		//actor->GetProperty()->SetOpacity(0.5);
		//actor->GetProperty()->EdgeVisibilityOn();
		//actor->GetProperty()->BackfaceCullingOn();
		//actor->SetBackfaceProperty(backfaces);
		//actor->GetProperty()->SetEdgeColor(171 / 255.0, 224 / 255.0, 255 / 255.0); 
		actor->GetProperty()->SetColor(COLOR_RAINBOW[i % 10][0] / 255.0, COLOR_RAINBOW[i % 10][1] / 255.0, COLOR_RAINBOW[i % 10][2] / 255.0);
		//textActor->SetMapper(textMapper);
		//textActor->SetPosition(150, 16);
		//renderer->AddActor(textActor);
		topRenderer->AddActor(actor);
	}


	topRenderer->SetViewport(bottomViewport);
	
	//renderer->ResetCameraClippingRange();
	//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
	topRenderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
	renderWindow->AddRenderer(topRenderer);

	vtkSmartPointer<vtkRenderer> bottomRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkTextActor> textActor =
		vtkSmartPointer<vtkTextActor>::New();

	for (unsigned int i = 0; i < fractures.size(); i++)
	{
		
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();

		mapper->SetInputData(fractures[i]);
		actor->SetMapper(mapper);
		actor->GetProperty()->SetPointSize(3);
		actor->GetProperty()->SetLineWidth(2);
		//actor->GetProperty()->SetOpacity(0.5);
		//actor->GetProperty()->EdgeVisibilityOn();
		//actor->GetProperty()->BackfaceCullingOn();
		//actor->SetBackfaceProperty(backfaces);
		//actor->GetProperty()->SetEdgeColor(171 / 255.0, 224 / 255.0, 255 / 255.0); 
		actor->GetProperty()->SetColor(COLOR_RAINBOW[i % 10][0] / 255.0, COLOR_RAINBOW[i % 10][1] / 255.0, COLOR_RAINBOW[i % 10][2] / 255.0);
		if (i % 2 != 0 && matrix != NULL)
			actor->SetUserMatrix(matrix);
		bottomRenderer->AddActor(actor);
		//textActor->SetMapper(textMapper);
		//textActor->SetPosition(150, 16);
		
	}

	vtkSmartPointer<vtkProperty2D> textProperty = textActor->GetProperty();
	string title = "";
	if (curSelectedFractures[0] != "" && curSelectedFractures[1] != "")
	{
		string fixedName = curSelectedFractures[0];
		string floatName = curSelectedFractures[1];
		vector<string> fixedSegments = Utils::SplitString(fixedName, "\\");
		vector<string> floatSegments = Utils::SplitString(floatName, "\\");
		string fixedPost = fixedSegments[fixedSegments.size() - 1];
		string floatPost = floatSegments[floatSegments.size() - 1];
		title += fixedPost.substr(0, fixedPost.length() - 4) + " --- " + floatPost.substr(0, floatPost.length() - 4);
	}

	textActor->SetInput(title.c_str());
	/*textProperty->SetFontFamilyToArial();
	textProperty->BoldOn();
	textProperty->SetFontSize(36);
	textProperty->ShadowOn();
	textProperty->SetShadowOffset(4, 4);*/
	textProperty->SetColor(22 / 255.0, 36 / 255.0, 92 / 255.0);

	bottomRenderer->SetViewport(topViewport);
	if (curSelectedFractures[0] != "" && curSelectedFractures[1] != "")
		topRenderer->AddActor(textActor);
	//renderer->ResetCameraClippingRange();
	//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
	bottomRenderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
	renderWindow->AddRenderer(bottomRenderer);
}


void CFragmentsRestorationAssitantDlg::DisplayModel(vtkSmartPointer<vtkPolyData> data, vtkSmartPointer<vtkRenderWindow>& renWin)
{
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(data);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(COLOR_RAINBOW[2][0] / 255.0, COLOR_RAINBOW[2][1] / 255.0, COLOR_RAINBOW[2][2] / 255.0);
	renderer->AddActor(actor);
	//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
	renderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
	renWin->AddRenderer(renderer);

}


void CFragmentsRestorationAssitantDlg::DisplayMoreModels(vector<vtkSmartPointer<vtkPolyData>> datas, vtkSmartPointer<vtkRenderWindow>& renWin)
{
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		vtkSmartPointer<vtkPolyData> data = datas[i];
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(data);

		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetPointSize(5);
		actor->GetProperty()->SetLineWidth(2);
		//actor->GetProperty()->SetOpacity(0.5);
		//actor->GetProperty()->EdgeVisibilityOn();
		//actor->GetProperty()->BackfaceCullingOn();
		actor->GetProperty()->SetColor(COLOR_RAINBOW[i % 10][0] / 255.0, COLOR_RAINBOW[i % 10][1] / 255.0, COLOR_RAINBOW[i % 10][2] / 255.0);

		renderer->AddActor(actor);
	}

	//renderer->SetBackground(238 / 255.0, 255 / 255.0, 198 / 255.0);
	renderer->SetBackground(255 / 255.0, 255 / 255.0, 255 / 255.0);
	renWin->AddRenderer(renderer);
}


void CFragmentsRestorationAssitantDlg::TransformFracturesOnFragment(vtkSmartPointer<vtkPolyData>& fragment, vector<vtkSmartPointer<vtkPolyData>>& fractures, vtkSmartPointer<vtkMatrix4x4> matrix)
{
	Registration registration;
	vtkSmartPointer<vtkPolyData> fragmentTemp = vtkSmartPointer<vtkPolyData>::New();
	registration.TransformPolyData(matrix, fragment, fragmentTemp);
	fragment->DeepCopy(fragmentTemp);

	for (unsigned int i = 0; i < fractures.size(); i++)
	{
		vtkSmartPointer<vtkPolyData> temp = vtkSmartPointer<vtkPolyData>::New();
		registration.TransformPolyData(matrix, fractures[i], temp);
		fractures[i]->DeepCopy(temp);
	}
}


void CFragmentsRestorationAssitantDlg::TransformFracturesOnTheSameFragment(vector<pair<vtkSmartPointer<vtkPolyData>, string>>& fractures, vtkSmartPointer<vtkMatrix4x4> matrix)
{
	Registration registration;
	for (auto fracture : fractures)
	{
		vtkSmartPointer<vtkPolyData> temp = vtkSmartPointer<vtkPolyData>::New();
		registration.TransformPolyData(matrix, fracture.first, temp);
		fracture.first->DeepCopy(temp);
	}
}


void CFragmentsRestorationAssitantDlg::TransformDatas(vtkSmartPointer<vtkPolyData>& data, vtkSmartPointer<vtkMatrix4x4> matrix)
{
	Registration registration;

	vtkSmartPointer<vtkPolyData> temp = vtkSmartPointer<vtkPolyData>::New();
	registration.TransformPolyData(matrix, data, temp);
	data->DeepCopy(temp);
}


void CFragmentsRestorationAssitantDlg::TransformDatas(vector<vtkSmartPointer<vtkPolyData>>& datas, vtkSmartPointer<vtkMatrix4x4> matrix)
{
	Registration registration;

	for (unsigned int i = 0; i < datas.size(); i++)
	{
		if (i % 2 != 0)
		{
			vtkSmartPointer<vtkPolyData> fractureTemp = vtkSmartPointer<vtkPolyData>::New();
			registration.TransformPolyData(matrix, datas[i], fractureTemp);
			datas[i]->DeepCopy(fractureTemp);
		}
	}
}


void CFragmentsRestorationAssitantDlg::TransformCenter(double* center, vtkSmartPointer<vtkMatrix4x4> matrix)
{
	Registration registration;

	double newCenter[3];

	for (int i = 0; i < 3; i++)
	{
		newCenter[i] = center[i];
	}
	registration.TransformPoints(matrix, newCenter, center);
}


void CFragmentsRestorationAssitantDlg::Translate(vtkSmartPointer<vtkMatrix4x4>& matrix, double* axis, double distance)
{
	// �ֽ���������ת�ᷭת���ڽ���ת��Ķ��������ƽ�Ƶ��̶���������
	double* start = fixedCenter;
	double end[3];
	end[0] = start[0] + axis[0] * distance;
	end[1] = start[1] + axis[1] * distance;
	end[2] = start[2] + axis[2] * distance;
	vtkSmartPointer<vtkMatrix4x4> translateMatrix = vtkSmartPointer<vtkMatrix4x4>::New();			// ƽ�ƾ���
	registration.TranslateMatrix(start, end, translateMatrix);
	TransformCenter(floatCenter, translateMatrix);
	vtkMatrix4x4::Multiply4x4(translateMatrix, matrix, matrix);
}


void CFragmentsRestorationAssitantDlg::RotateAndTranslate(vtkSmartPointer<vtkMatrix4x4>& matrix, double* axis, double theta)
{
	// �ֽ���������ת�ᷭת���ڽ���ת��Ķ��������ƽ�Ƶ��̶���������
	vtkSmartPointer<vtkMatrix4x4> turnOverMatrix = vtkSmartPointer<vtkMatrix4x4>::New();			// �������ᷭת����
	registration.RotateByAnyAngle(axis, theta, turnOverMatrix);
	vtkMatrix4x4::Multiply4x4(turnOverMatrix, matrix, matrix);
	TransformCenter(floatCenter, turnOverMatrix);
	vtkSmartPointer<vtkMatrix4x4> translateMatrix = vtkSmartPointer<vtkMatrix4x4>::New();			// ƽ�ƾ���
	registration.TranslateMatrix(fixedCenter, floatCenter, translateMatrix);
	TransformCenter(floatCenter, translateMatrix);
	vtkMatrix4x4::Multiply4x4(translateMatrix, matrix, matrix);
}


void CFragmentsRestorationAssitantDlg::WriteModel(vtkSmartPointer<vtkPolyData> data, string path)
{
	vtkSmartPointer<vtkSTLWriter> writer =
		vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(path.c_str());
	writer->SetInputData(data);
	writer->Write();
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonOpenFragmentsAndFractures()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd = GetSafeHwnd();   //�õ����ھ��
	CString filePath = _T("");	//�õ��ļ�·��
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)	//ȡ��IMalloc�������ӿ�
	{
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;
		bi.hwndOwner = hwnd;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ���ļ���"); //ѡ��Ŀ¼�Ի�����ϲ��ֵı���
		//����½��ļ��а�ť BIF_NEWDIALOGSTYLE
		bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = BrowseCallbackProc;
		bi.lParam = 0;
		bi.iImage = 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //ȡ��IMalloc�������ӿ�
		{
			if (::SHGetPathFromIDList(pidl, pszBuffer)) //���һ���ļ�ϵͳ·��
			{
				filePath = pszBuffer;
				dir = filePath;
			}
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			m_eModelsDir.SetWindowTextW(filePath);
			if (filePath)
			{
				string format = ".stl";
				vector<string> files;

				utils.GetAllFormatFilesWithDirectory(Utils::UnicodeToANSI(filePath), files, format);
				
				fragmentNames = files;
	
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
	}
	defaultPath = filePath;
	if (!filePath.Compare(_T(""))) 
	{
		MessageBox(_T("���ļ�����"), _T("��ʾ"), MB_OK);
		return;
	}

	fragments = utils.ReadDatas(Utils::UnicodeToANSI(filePath) + "\\", fragmentNames);
	fracturess = utils.ReadFracturesWithPrefix(Utils::UnicodeToANSI(filePath) + "\\", fracturesDir, fractureNames, prefix);

	vector<string> splitted = utils.SplitString(Utils::UnicodeToANSI(filePath), "\\");
	for (unsigned int i = 0; i < splitted.size() - 2; i++)
		matchPairFileName += splitted[i] + "\\";
	matchPairFileName += "match-pair\\fragment-" + prefix + ".txt";
	if (_access(matchPairFileName.c_str(), 0) != -1)
		remove(matchPairFileName.c_str());

	for (unsigned int i = 0; i < fractureNames.size(); i++)
	{
		vector<int> v;
		for (unsigned int j = 0; j < fractureNames[i].size(); j++)
		{
			v.push_back(0);
		}
		visited.push_back(v);
	}

	if (fragments.size() != 0)
	{
		InitFragmentsView();

		RecordOperation(9);

		Display(IDC_STATIC_DISPLAY_FRAGMENTS, renderWindow, renderWindowInteractor);
	}
	else
	{
		MessageBox(_T("�ļ�����û��.stl�ļ�"), _T("��ʾ"), MB_OK);
	}
}


BOOL CFragmentsRestorationAssitantDlg::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���
	return CDialogEx::DestroyWindow();
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonChooseFixFracture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (fracturess.size() != 0)
	{
		CSelectFracturesDlg dlg;
		dlg.SetNames(Utils::UnicodeToANSI(dir), fragmentNames, fractureNames);
		dlg.SetVisited(visited);
		dlg.SetFixedFractureId(true);
		if (dlg.DoModal() == IDOK)
		{
			int i = dlg.GetId()[0];
			int j = dlg.GetId()[1];
			if (pairOfFractures.size() != 0 && pairOfFragments.size() != 0)
			{
				vector<vtkSmartPointer<vtkPolyData>> tmp1;
				vector<vtkSmartPointer<vtkPolyData>> tmp2;
				pairOfFractures.swap(tmp1);
				pairOfFragments.swap(tmp2);
			}
			curSelectedFractures[0] = fractureNames[i][j];
			visited[i][j] = 1;
			fixedFracture = fracturess[i][j];
			fixedFragment = fragments[i];
			pairOfFractures.push_back(fixedFracture);
			pairOfFragments.push_back(fixedFragment);
			DisplayFragmentsAndFractures(pairOfFragments, pairOfFractures, originalRendererWindow);
			RecordOperation(10);
			Display(IDC_STATIC_ORIGINAL_VIEW, originalRendererWindow, originalInteractor);
		}
		
		
	}
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonChooseFloatFracture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (fracturess.size() != 0 && fixedFracture != NULL)
	{
		CSelectFracturesDlg dlg;
		dlg.SetNames(Utils::UnicodeToANSI(dir), fragmentNames, fractureNames);
		dlg.SetVisited(visited);
		dlg.SetFixedFractureId(false);
		if (dlg.DoModal() == IDOK)
		{
			int i = dlg.GetId()[0];
			int j = dlg.GetId()[1];
			if (pairOfFractures.size() != 0 && pairOfFragments.size() != 0 && originalPairOfFragments.size() != 0)
			{
				utils.ClearVector<vtkSmartPointer<vtkPolyData>>(pairOfFractures);
				utils.ClearVector<vtkSmartPointer<vtkPolyData>>(pairOfFragments);
				utils.ClearVector<vtkSmartPointer<vtkPolyData>>(originalPairOfFragments);
			}
			curSelectedFractures[1] = fractureNames[i][j];
			visited[i][j] = 1;
			floatFracture = fracturess[i][j];
			// �洢ͬһ��Ƭ�ϵ���������
			for (unsigned int k = 0; k < fracturess[i].size(); k++)
			{
				string title = fracturesDir + prefix + "-" + to_string(i + 1) + "-";
				title.push_back(char('a' + k));
				floatFractures.push_back(make_pair(fracturess[i][k], title + ".stl"));
			}
			floatFragment = fragments[i];
			pairOfFractures.push_back(fixedFracture);
			pairOfFragments.push_back(fixedFragment);
			pairOfFractures.push_back(floatFracture);
			pairOfFragments.push_back(floatFragment);

			vtkSmartPointer<vtkPolyData> floatOriginalFragment = vtkSmartPointer<vtkPolyData>::New();
			floatOriginalFragment->DeepCopy(fragments[i]);
			originalPairOfFragments.push_back(fixedFragment);
			originalPairOfFragments.push_back(floatOriginalFragment);
			DisplayFragmentsAndFractures(originalPairOfFragments, pairOfFractures, originalRendererWindow);
			RecordOperation(11);
			//originalRendererWindow->Render();
			Display(IDC_STATIC_ORIGINAL_VIEW, originalRendererWindow, originalInteractor);
		}
		
	}
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonFirstPca()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pairOfFragments.size() != 0)
	{
		pairOfFragments.clear();
	}
	IS_TUNE = true;
	vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();					// ����任����
	transformedDatas = PreRegistration(fixedFracture, floatFracture, matrix);
	TransformDatas(floatFragment, matrix);		// ������ͨ������任����һ��λ��
	TransformDatas(transformedDatas, matrix);		// ������ͨ������任����һ��λ��
	TransformCenter(floatCenter, matrix);			// �����������ĵ�ͨ������任����һ��λ��
	TransformFracturesOnTheSameFragment(floatFractures, matrix);	// ��ͬһ��Ƭ�ϵ���������ͨ������任����һ��λ��
	pairOfFragments.push_back(fixedFragment);
	pairOfFragments.push_back(floatFragment);
	DisplayFragmentsAndFractures(pairOfFragments, transformedDatas, adjustedRendererWindow);
	RecordOperation(12);
	Display(IDC_STATIC_ADJUSTED_VIEW, adjustedRendererWindow, adjustedInteractor);
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonTurnOver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (rotateAxis != NULL && IS_TUNE)
	{
		if (pairOfFragments.size() != 0)
		{
			pairOfFragments.clear();
		}
		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		RotateAndTranslate(matrix, rotateAxis, vtkMath::Pi());
		TransformDatas(floatFragment, matrix);
		TransformDatas(transformedDatas, matrix);		// ������ͨ������任����һ��λ��
		TransformFracturesOnTheSameFragment(floatFractures, matrix);	// ��ͬһ��Ƭ�ϵ���������ͨ������任����һ��λ��
		//TransformCenter(floatCenter, matrix);			// �����������ĵ�ͨ������任����һ��λ��
		pairOfFragments.push_back(fixedFragment);
		pairOfFragments.push_back(floatFragment);
		DisplayFragmentsAndFractures(pairOfFragments, transformedDatas, adjustedRendererWindow);
		RecordOperation(AXIS);
		adjustedRendererWindow->Render();
		//Display(IDC_STATIC_ADJUSTED_VIEW, adjustedRendererWindow, adjustedInteractor);
	}
	
}


void CFragmentsRestorationAssitantDlg::OnBnClickedRadioMajorAxis()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	switch (m_radioMajorAxis)
	{
	case 0:
		rotateAxis = majorAxis;
		AXIS = 0;

		break;
	case 1:
		rotateAxis = minorAxis;
		AXIS = 1;
		break;
	case 2:
		rotateAxis = axis;
		AXIS = 2;
		break;
	}
}


void CFragmentsRestorationAssitantDlg::OnDeltaposSpinTurnRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(true);
	CString value;
	char message[10];
	double theta = 0;
	double alpha = 0;
	if (pNMUpDown->iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����ҵļ�ͷ
	{
		theta = wcstod(m_editValueOfRotate, NULL) + THETA_DELTA;
		value.Format(_T("%.1f��"), theta);
		sprintf(message, "%.1f", THETA_DELTA);
		alpha = THETA_DELTA;
	}
	else if (pNMUpDown->iDelta == 1) // �����ֵΪ1, ˵�������Spin������ļ�ͷ
	{
		theta = wcstod(m_editValueOfRotate, NULL) - THETA_DELTA;
		value.Format(_T("%.1f��"), theta);
		sprintf(message, "%.1f", -THETA_DELTA);
		alpha = -THETA_DELTA;
	}
	RecordOperation(AXIS + 3, string(message) + "��");
	m_editValueOfRotate = value;
	UpdateData(false);

	if (IS_TUNE)
	{
		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		RotateAndTranslate(matrix, rotateAxis, alpha * vtkMath::Pi() / 180);
		//TransformDatas(floatFragment, matrix);
		TransformDatas(transformedDatas, matrix);		// ������ͨ������任����һ��λ��
		//TransformCenter(floatCenter, matrix);			// �����������ĵ�ͨ������任����һ��λ��
		TransformDatas(pairOfFragments, matrix);
		//DisplayFragmentsAndFractures(pairOfFragments, transformedDatas, adjustedRendererWindow);
		adjustedRendererWindow->Render();
		//Display(IDC_STATIC_ADJUSTED_VIEW, adjustedRendererWindow, adjustedInteractor);
	}

	*pResult = 0;

}


void CFragmentsRestorationAssitantDlg::OnDeltaposSpinTurnTranslate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(true);
	CString value;
	char message[10];
	double distance = 0;
	double beta = 0;
	if (pNMUpDown->iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����ҵļ�ͷ
	{
		distance = wcstod(m_editValueOfTranslate, NULL) + DISTANCE_DELTA;
		value.Format(_T("%.1f"), distance);
		sprintf(message, "%.1f", DISTANCE_DELTA);
		beta = DISTANCE_DELTA;
	}
	else if (pNMUpDown->iDelta == 1) // �����ֵΪ1, ˵�������Spin������ļ�ͷ
	{
		distance = wcstod(m_editValueOfTranslate, NULL) - DISTANCE_DELTA;
		value.Format(_T("%.1f"), distance);
		sprintf(message, "%.1f", -DISTANCE_DELTA);
		beta = -DISTANCE_DELTA;
	}
	RecordOperation(AXIS + 6, string(message));
	m_editValueOfTranslate = value;
	UpdateData(false);

	if (IS_TUNE)
	{
		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		Translate(matrix, rotateAxis, beta);
		TransformDatas(floatFragment, matrix);
		TransformDatas(transformedDatas, matrix);		// ������ͨ������任����һ��λ��
		//TransformCenter(floatCenter, matrix);			// �����������ĵ�ͨ������任����һ��λ��
		TransformDatas(pairOfFragments, matrix);
		//DisplayFragmentsAndFractures(pairOfFragments, transformedDatas, adjustedRendererWindow);
		adjustedRendererWindow->Render();
		//Display(IDC_STATIC_ADJUSTED_VIEW, adjustedRendererWindow, adjustedInteractor);
	}
	

	*pResult = 0;
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonRotateConf()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CTuneDelta dlg;
	dlg.DoModal();
	double delta = dlg.GetDelta();
	if (delta != 0)
		THETA_DELTA = delta;
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonTranslateConf()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CTuneDelta dlg;
	dlg.DoModal();
	if (dlg.GetDelta() != 0)
		DISTANCE_DELTA = dlg.GetDelta();
}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonSaveFragment()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������������Ĭ�Ϲ��������ֵ��������£�
	//ʹ�ù��캯���޸ĶԻ����ʼ״̬���ܸ��ã���������϶�
	if (floatFragment != NULL)
	{
		BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
		CString defaultDir = dir + "\\";	//Ĭ�ϴ򿪵��ļ�·��
		CString fileName = L"";			//Ĭ�ϴ򿪵��ļ���
		CString filter = L"�ļ� (*.stl)|*.stl||";	//�ļ����ǵ�����
		CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);

		if (IDOK == openFileDlg.DoModal())
		{
			string name = Utils::UnicodeToANSI(openFileDlg.GetPathName());
			WriteModel(floatFragment, name);
			for (auto fracture : floatFractures)
				WriteModel(fracture.first, fracture.second);
		}
	}
	

}



void CFragmentsRestorationAssitantDlg::OnBnClickedButtonRechose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	utils.ClearVector<vtkSmartPointer<vtkPolyData>>(pairOfFractures);
	utils.ClearVector<vtkSmartPointer<vtkPolyData>>(pairOfFragments);

	for (auto & row : visited) 
	{
		for (auto col : row)
			col = 0;
	}

}


void CFragmentsRestorationAssitantDlg::OnBnClickedButtonSaveRelation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (curSelectedFractures[0] != "" && curSelectedFractures[1] != "")
	{
		ofstream file(matchPairFileName, ios::app);
		string content = "";
		string fixedName = curSelectedFractures[0];
		string floatName = curSelectedFractures[1];
		vector<string> fixedSegments = Utils::SplitString(fixedName, "\\");
		vector<string> floatSegments = Utils::SplitString(floatName, "\\");
		string fixedPost = fixedSegments[fixedSegments.size() - 1];
		string floatPost = floatSegments[floatSegments.size() - 1];
		content += fixedPost.substr(0, fixedPost.length() - 4) + "&" + floatPost.substr(0, floatPost.length() - 4);
		file << content << endl;
		file.close();
		MessageBox(_T("����ɹ���"), _T("��ʾ"), MB_OK);
	}
}
