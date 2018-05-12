#include "DataManager.h"

Vector::Vector()
{
	Error = false;
	size = 0;
	Name="";
	Data.clear();
}
Vector::Vector(double num)
{
	Error = false;
	Name = "V";
	Data.push_back(num);
	size=1;
}
Vector::Vector(bool err)
{
	Error = err;
}
Vector::Vector(std::string n, std::vector<double>D)
{
	Error = false;
	Name = n;
	Data = D;
	size = D.size();
}
Vector::Vector(std::vector<double>D)
{
	Error = false;
	Name = "V";
	Data = D;
	size = D.size();
}

Vector operator +(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	std::vector<double>data;
	double ans = 0;
	for (int i = 0; i <a.Data.size(); i++)
	{
		data.push_back(a.Data[i] + b.Data[i]);
	}
	return Vector(data);
}
Vector operator -(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	std::vector<double>data;
	double ans = 0;
	for (int i = 0; i <a.Data.size(); i++)
	{
		data.push_back(a.Data[i] - b.Data[i]);
	}
	return Vector(data);
}
Vector operator /(Vector& a, double& b)
{
	
	std::vector<double>data;
	double ans = 0;
	for (int i = 0; i <a.Data.size(); i++)
	{
		data.push_back(a.Data[i] / b);
	}
	return Vector(data);
}
Vector operator *(Vector& a, Vector& b)
{
	if (a.size == 1)
	{
		std::vector<double>tmp;
		for (int i = 0; i < b.size; i++)
		{
			tmp.push_back(b.Data[i] * a.Data[0]);
		}
		return Vector(tmp);
	}
	else if (b.size == 1)
	{
		std::vector<double>tmp;
		for (int i = 0; i < a.size; i++)
		{
			tmp.push_back(a.Data[i] * b.Data[0]);
		}
		return Vector(tmp);
	}
	else if (a.size == b.size&&a.size != 1 && b.size != 1)
	{
		double ans = 0;
		for (int i = 0; i < a.Data.size(); i++)
		{
			ans += a.Data[i] * b.Data[i];
		}
		return Vector(ans);
	}
	else
		return Vector(false);
}
Vector dot(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	double ans = 0;
	for (int i = 0; i <a.Data.size(); i++)
	{
		ans += a.Data[i] * b.Data[i];
	}
	return Vector(ans);
}
Vector Vector::Norm()
{
	double ans = 0;
	for (int i = 0; i <Data.size(); i++)
	{
		ans += Data[i] * Data[i];
	}
	ans = sqrt(ans);
	return	Vector(ans);
}
Vector Vector::Normal()
{
	double nor = 0;
	for (int i = 0; i <Data.size(); i++)
	{
		nor += Data[i] * Data[i];
	}
	nor = sqrt(nor);
	std::vector<double>tmp; 
	for (int i = 0; i <Data.size(); i++)
	{
		tmp.push_back(Data[i] / nor);
	}
	return Vector(tmp);
}
Vector Cross(Vector& a, Vector& b)
{
	if (a.size != 3||b.size!=3)
	{
		return Vector(false);
	}
	std::vector<double>data;
	data.push_back(a.Data[1] * b.Data[2] - a.Data[2] * b.Data[1]);
	data.push_back(-a.Data[0] * b.Data[2] + a.Data[2] * b.Data[0]);
	data.push_back(a.Data[0] * b.Data[1] - a.Data[1] * b.Data[0]);
	return Vector(data);
}
Vector Com(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	Vector Dot = dot(a,b);
	double ans= Dot.Data[0] / b.Norm().Data[0];
	return Vector(ans);
}
Vector Proj(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	Vector DotA= dot(a, b);
	Vector DotB = dot(b, b);
	double k = DotA.Data[0] / DotB.Data[0];
	std::vector<double>data;
	for (int i = 0; i < a.Data.size(); i++)
	{
		data.push_back(b.Data[i] * k);
	}
	return Vector(data);
}
Vector Area(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}
	double nora =dot(a,a).Data[0];
	double norb =dot(b,b).Data[0];
	double dota = dot(a, b).Data[0];
	double k = nora * norb - dota*dota ;
	double area = 0.5*sqrt(k);
	return Vector(area);
}
bool isParallel(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return 0;
	}
	for (int i = 1; i< a.size; i++)
	{
		double k = a.Data[i] / a.Data[i - 1];
		if (b.Data[i] / b.Data[i - 1] != k)
			return 0;
	}
	return 1;
}
bool isOrthogonal(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return false;
	}
	double k = dot(a, b).Data[0];
	if (dot(a, b).Data[0] == 0)
		return true;
	else
		return false;
}
Vector angle(Vector& a, Vector& b)
{
	if (a.size != b.size)
	{
		return Vector(false);
	}

	double ang = acos(dot(a, b).Data[0] /( a.Norm().Data[0] * b.Norm().Data[0]))*180/M_PI;
	return Vector(ang);
}
Vector pN(Vector& a, Vector& b)
{	
	return Cross(a,b);
}
bool IsLI(std::vector<Vector>&v)
{
	Matrix A;
	A.rowCount = v[0].size;
	A.colCount = v.size();
	for (int i = 0; i < v[0].size; i++)
	{
		std::vector<double> tempDatas;
		for (int j = 0; j < v.size(); j++)
		{
			tempDatas.push_back(v[i].Data[j]);
		}
		A.Data.push_back(tempDatas);
	}
	Matrix ans = A * A.Transpose();
	bool k = 0;
	double tmp = ans.det(k);
	if (tmp == 0)
		return false;
	else
		return true;
}

std::vector<Vector> Ob(std::vector<Vector>& u)
{
	std::vector<Vector>v;
	std::vector<Vector>w;
	for (int i = 0; i < u.size();i++)
	{
		Vector ans=u[i];
		for (int j = 0; j < v.size(); j++)
		{
			double k = dot(u[i], v[j]).Data[0] / dot(v[j], v[j]).Data[0];
			Vector tmp(k);
			tmp = tmp * v[j];
			ans =ans-tmp;
		}
		v.push_back(ans);
		Vector tmp = ans / v[i].Norm().Data[0];
		tmp.size = u[0].size;
		w.push_back(tmp);
	}
	
	return w;
}
std::ostream& operator<<(std::ostream& output, Vector &a)
{
	if (a.Error)
	{
		output << "Error";
		return output;
	}
		for (int i = 0; i < a.Data.size(); i++)
		{
			if (i == a.Data.size() - 1)
				output << a.Data[i]<<"\r\n";
			else
			output << a.Data[i] <<" ";
	    }
	return output;
}
std::istream&operator >>(std::istream& input, Vector &a)
{
	input >> a.size;

	for (int count = 0; count < a.size; count++)
	{
		double value;
		input >> value;
		a.Data.push_back(value);
	}

	return input;
}
bool err(Vector&a)
{
	return a.Error;
}