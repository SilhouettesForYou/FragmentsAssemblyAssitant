#pragma once

#include <vtkSmartPointer.h>
#include <vtkPCAStatistics.h>

#include <vtkLine.h>
#include <vtkLineSource.h>
#include <vtkTransform.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkTable.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkMatrix3x3.h>
#include <vtkMatrix4x4.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkLandmarkTransform.h>

#include <list>
#include <map>
#include <direct.h>

#define square(a) (a) * (a)
#define MAXMUMMEANDISTENCE 0.002 
#define MAXITERATIONS 80

using namespace std;

class Registration
{
private:
	int fragmentsSize, fracturesSize;
	int** fractures;
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> source;

	vtkSmartPointer<vtkMatrix4x4> rotateX; // ��X����ת����
	vtkSmartPointer<vtkMatrix4x4> rotateY; // ��Y����ת����
	vtkSmartPointer<vtkMatrix4x4> rotateZ; // ��Z����ת����

	double Multiply(double* a, double* b);
	double Norm(double* a);
	void Normalize(double* a, double* b);

	/********************************
	* ��������GetRotateXXX

	* ����������Ƹ�����������ת�ľ���

	* ���ߣ�С��

	* ���ڣ�2018-4-9 21:34:56

	********************************/
	vtkSmartPointer<vtkMatrix4x4> GetRotateX(double theta);
	vtkSmartPointer<vtkMatrix4x4> GetRotateY(double theta);
	vtkSmartPointer<vtkMatrix4x4> GetRotateZ(double theta);


public:
	Registration();
	Registration(int fragmentsSize, int fracturesSize);
	Registration(vtkSmartPointer<vtkPolyData> source);
	~Registration();


	vector<string> SplitPair(string str, string pattern);
	vector<string> SplitString(const string str, const string pattern);
	vector<int> GetNextFracture(int fragmentId, vector<pair<string, string>> pairs);
	/********************************
	* ��������MatchStrategy

	* ���������룺һ������ģ�͵�������Ƭ���Լ�һ����Ƭ�ϵ����ɶ��棻���ж�����ƥ����

	�����ƥ�������


	* ���ߣ�С��

	* ���ڣ�2018-5-16 15:56:21

	********************************/
	void MatchStrategy(vector<pair<string, string>> pairs, vector<int>& sequences);

	/********************************
	* ��������InstanceMatrix

	* ��������ʼ����ת����

	* ���ߣ�С��

	* ���ڣ�2018-4-10 09:32:51

	********************************/
	void InstanceMatrix(vtkSmartPointer<vtkMatrix4x4>& matrix);


	/********************************
	* ��������PCA

	* ������������������

	* ���ߣ�С��

	* ���ڣ�2018-4-8 09:17:43

	********************************/
	void PCA(vtkSmartPointer<vtkDoubleArray>& eigenvectors);



	/********************************
	* ��������RotateByAnyAxis

	* ��������һ����������������ת
	��ת����vecʹ����axisƽ��
	��Ϊ��������ת��������ת��ѡ��Ϊ���������ĺϳɣ��ٽ�ĳһ�����Ƹúϳɵ�������ת180�㼴��
	https://blog.csdn.net/swety_gxy/article/details/73087848

	* ���ߣ�С��

	* ���ڣ�2018-4-8 12:27:16

	********************************/
	void RotateByAnyAxis(double* axis, double* vec, vtkSmartPointer<vtkMatrix4x4>& rotateMatrix);

	/********************************
	* ��������RotateByAnyAngle

	* ��������ת����vecʹ����axisƽ��

	* ���ߣ�С��

	* ���ڣ�2018-4-8 12:27:16

	********************************/
	void RotateByAnyAngle(double* axis, double theta, vtkSmartPointer<vtkMatrix4x4>& rotateMatrix);


	/********************************
	* ��������TranslateMatrix

	* ������ƽ��һ������

	* ���ߣ�С��

	* ���ڣ�2018-4-9 16:30:27

	********************************/
	void TranslateMatrix(double* start, double* end, vtkSmartPointer<vtkMatrix4x4>& translateMatrix);


	/********************************
	* ��������TransformPoints

	* ���������任����Ӧ���ڵ���

	* ���ߣ�С��

	* ���ڣ�2018-4-10 10:05:22

	********************************/
	void TransformPoints(vtkSmartPointer<vtkMatrix4x4> matrix, vtkSmartPointer<vtkPoints> primitivePoints, vtkSmartPointer<vtkPoints>& transformedPoints);
	void TransformPoints(vtkSmartPointer<vtkMatrix4x4> matrix, double* primitivePoint, double* transformedPoint);


	/********************************
	* ��������TransformPolyData

	* ��������PolyData��Ӧ�ñ任���󣬽�source������ת������ת��target

	* ���ߣ�С��

	* ���ڣ�2018-4-10 14:11:57

	********************************/
	void TransformPolyData(vtkSmartPointer<vtkMatrix4x4> matrix, vtkSmartPointer<vtkPolyData>& target);
	void TransformPolyData(vtkSmartPointer<vtkMatrix4x4> matrix, vtkSmartPointer<vtkPolyData> source, vtkSmartPointer<vtkPolyData>& target);


	/********************************
	* ��������IterativeClosestPointsTransform

	* ������ICP������sourceΪ��Ҫ�ƶ���PolyData��targetΪ�̶�����PolyData

	* ���ߣ�С��

	* ���ڣ�2018-4-10 11:58:36

	********************************/
	void IterativeClosestPointsTransform(vtkSmartPointer<vtkPolyData> target, vtkSmartPointer<vtkMatrix4x4>& matrix, int maxIterations);

	/********************************
	* ��������ConvertToVertex

	* �������Ե㼯��ʽ��ʾģ��

	* ���ߣ�С��

	* ���ڣ�2018-4-9 10:17:52

	********************************/
	vtkSmartPointer<vtkPolyData> ConvertToVertex();



	/********************************
	* ��������GetRotateAxis

	* �������������������������������Ϊ��ת��

	* ���ߣ�С��

	* ���ڣ�2018-7-13 17:08:03

	********************************/
	void GetRotateAxis(double* axis1, double* axis2, double* axis);
};
