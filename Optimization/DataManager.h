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

	// 如果結果為Scalar時就回傳只有一個元素的向量-記得設定SIZE 不然PRINT不出來
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
//定義矩陣資料結構
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


class Variable
{
public:

	std::string name;
	double exp;
	Variable *next;
	Variable(std::string);
};

class Term
{
public:

	double coef;
	Variable *vars;
	Term *next;
	Term(std::vector<std::string>&);
};


class Equation
{
public:
	std::string EquationString;
	int EquationIndex;
	Equation();
	Equation(std::string, int);
	Term* EqTerms;
	int degree();
};

//定義控管資料class
class DataManager
{
private:
	//儲存方程式資料
	std::vector<Equation> Equations;
	//紀錄向量ID，用於控管
	int EquationIndex;
	//紀錄檔案路徑名稱
	std::string FileName;
public:

	//紀錄目前選擇的方法
	/*
	0:Powell’s Method
	1:Newton Method
	2:Steep Descent Algorithm
	3:Quasi-Newton Method
	4:Conjugate Gradient Methods
	*/
	int currentEq;
	//紀錄目前選擇的多項式
	int currentMethod;

	DataManager();
	//讀取向量資料
	bool LoadEquationData();
	//取得向量資料
	std::vector<Equation>& GetEquations();
	//設置檔案路徑名稱
	void SetFileName(std::string fileName);
};
