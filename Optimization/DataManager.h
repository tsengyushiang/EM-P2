#pragma once
#define _USE_MATH_DEFINES
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <set>
#include<algorithm>
class Vector
{
public:
	bool Error;
	int size;
	std::vector<double>Data;
	std::string Name;
	Vector();
	Vector(std::string n, std::vector<double>Data);
	Vector(std::vector<double>Data);
	Vector(double Num);
	Vector(bool err);
	friend std::ostream& operator <<(std::ostream&, Vector&);
	friend std::istream& operator >>(std::istream&, Vector&);

	// �p�G���G��Scalar�ɴN�^�ǥu���@�Ӥ������V�q-�O�o�]�wSIZE ���MPRINT���X��
	friend Vector operator +(Vector&, Vector&);
	friend Vector operator -(Vector&, Vector&);
	friend Vector operator *(Vector&, Vector&); // Scalar Multi
	friend Vector operator /(Vector&, double&);
	friend Vector dot(Vector&, Vector&);
	Vector Norm();
	Vector Normal();
	friend Vector Cross(Vector&, Vector&);
	friend Vector Com(Vector&, Vector&);
	friend Vector Proj(Vector&, Vector&);
	friend Vector Area(Vector&, Vector&);
	friend bool isParallel(Vector&, Vector&);
	friend bool isOrthogonal(Vector&, Vector&);
	friend Vector angle(Vector&, Vector&);
	friend Vector pN(Vector&, Vector&);
	friend bool IsLI(std::vector<Vector>&);
	friend bool err(Vector&);
	friend std::vector<Vector> Ob(std::vector<Vector>&);
};
//�w�q�x�}��Ƶ��c
class Matrix
{
	// return change of det
	double sort();
	double LeadingOne();
public:
	int rowCount, colCount;
	Matrix();
	bool Error;
	std::string Name;
	std::vector<std::vector<double>> Data;
	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator-(const Matrix&, const Matrix&);
	friend Matrix operator*(const Matrix&, const Matrix&);
	friend Matrix operator*(double, const Matrix&);
	friend bool operator==(const Matrix&, const Matrix&);
	friend std::istream& operator>>(std::istream&, Matrix&);
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	int Rank();
	double det(bool&);
	Matrix eigen();
	Matrix PowerMethod();
	Matrix Transpose();
	Matrix RowReduction();
	Matrix Adjoint();
	Matrix Inverse();
	friend Matrix SolveLinarSystem(const Matrix&, const Matrix&);
	friend Matrix LeastSquare(Matrix&, Matrix&);
};

class SubValueintoEq
{
public:
	// variable name
	std::string name;
	// value
	double value;

	SubValueintoEq() :name(""), value(0) {}
	SubValueintoEq(std::string n, double v) :name(n), value(v) {}
};

class SubVariableintoEq
{
public:
	// variable name
	std::string name;
	// value
	std::string Eq;

	SubVariableintoEq() :name(""), Eq("") {}
	SubVariableintoEq(std::string n,std::string e) :name(n), Eq(e) {}

};

class Range
{
public:
	// variable name
	std::string name;
	// interval
	double min;
	double max;

	Range() :name(""), min(0), max(0) {}
	Range(std::string n, double m, double M) :name(n), min(m), max(M) {}
};

class Variable
{
public:
	std::string str;
	std::string name;
	double exp;
	Variable *next;

	Variable();
	Variable(std::string);
	Variable(Variable*);
	~Variable();
	Variable& operator=(Variable&);
	
	double gradient(std::string name);
	double calc(std::vector<SubValueintoEq> vars);
};

class Term
{
public:

	std::string str;
	double coef;
	Variable *vars;
	Term *next;

	Term();
	Term(std::string );
	Term(Term*);
	~Term();
	Term& operator =(Term&);

	void gradient(std::string name);
	double calc(std::vector<SubValueintoEq> vars);
};

class Equation
{
public:
	std::string EquationString;
	int EquationIndex;
	Term* EqTerms;
	std::vector<Range> range;
	std::vector<SubVariableintoEq> domainChange;
	std::vector<SubVariableintoEq> VariableChange;

	Equation();
	Equation(std::string, int=-1);
	Equation(Equation*);
	~Equation();
	Equation& operator=(Equation&);

	int degree();
	double calc(std::vector<SubValueintoEq> vars);
	double goldenSection();
	std::string Powell(std::vector<SubValueintoEq>&);
	std::string SteepDescent(std::vector<SubValueintoEq>&);
	void gradient(std::string name);


};

//�w�q���޸��class
class DataManager
{
private:
	//�����ɮ׸��|�W��
	std::string FileName;
public:

	//�����ثe��ܪ���k
	/*
	0:Powell��s Method
	1:Newton Method
	2:Steep Descent Algorithm
	3:Quasi-Newton Method
	4:Conjugate Gradient Methods
	*/
	int currentEq;
	//�����ثe��ܪ��h����
	int currentMethod;

	std::vector<SubValueintoEq> VarInfo;
	
	//�x�s�h�������
	std::vector<Equation*> Equations;
	//�����h����ID�A�Ω󱱺�
	int EquationIndex;

	DataManager();
	//Ū���h�������
	bool LoadEquationData();
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);

	 
};
