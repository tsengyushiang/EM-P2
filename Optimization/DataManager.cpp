#include "DataManager.h"

DataManager::DataManager()
{
	EquationIndex = 0;
	currentEq=-1;
	currentMethod=-1;
}

bool DataManager::LoadEquationData()
{
	std::fstream fin;
	//開啟檔案，傳入open函數的參數有兩個，欲開起的檔案名稱，開啟檔案的模式參數(這邊std::ios::in為讀取(輸入)狀態)
	fin.open(FileName, std::ios::in);
	//讀取失敗回傳false
	if (!fin)
	{
		return false;
	}
	else
	{
		//定義讀取檔案字串暫存變數
		std::string tempString;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempString;

			Equation temp(tempString, EquationIndex);

			//解析到向量標記"V"
			Equations.push_back(temp);
			//遞增EquationIndex，標記到當前讀取向量ID
			EquationIndex++;

		}
		return true;
	}
}

void DataManager::SetFileName(std::string fileName)
{	
	FileName = fileName;
}

double goldenSection(double a,double b, double c,Equation& Eq)
{	
	static int  PreventInfiniteLoop = 0;
	PreventInfiniteLoop++;

	if (PreventInfiniteLoop == 200)return (c+a)/2;

	const double THRESHOLD = 0.001;
	const double RATIO = 2-((1+sqrt(5.0))/2);

	double x;

	if (c - b > b - a)
		x = b + RATIO * (c - b);
	else
		x = b - RATIO * (b - a);
	
	
	if (abs(c - a) < THRESHOLD*(abs(b) + abs(x)))
		return (c + a) / 2;

	
	double fx = Eq.calc(std::vector<ValueforVar>{ValueforVar("x", x , a, b)});
	double fb = Eq.calc(std::vector<ValueforVar>{ValueforVar("x", b, a, b)});
		

	if (fx < fb) {
		if (c - b > b - a) return goldenSection(b, x, c, Eq);
		else return goldenSection(a, x, b, Eq);
	}
	else
	{
		if (c - b > b - a) return goldenSection(a,b, x, Eq);
		else return goldenSection(x, b,c, Eq);
	}

	
	
}
std::string Powell(std::vector<ValueforVar>& InitialPoints, Equation& Eq)
{
	const double THRESHOLD = 1.0E-03;
	const int MAXIMUMLOOPCOUNT = 500;
	std::string result;
	
	if (InitialPoints.size() == 1)
	{
		std::vector<double> x{InitialPoints[0].value};
		std::vector<double> direction{1};
		
		for (int iteration = 0; iteration < MAXIMUMLOOPCOUNT; iteration++)
		{
				std::stringstream str;

				double r = 1.0 / direction[0];

				str << r;
				str << "*x";
				if ((r < 0) ^ (x[0] < 0))
					str << "+";
				else
					str << "-";
				str << abs(r*x[0]);				
				Equation preOperateX(str.str(),0);
				
				double a = InitialPoints[0].min;
				double b = x[0];
				double c = InitialPoints[0].max;

				double alpha = goldenSection(a,b,c,Eq);
				alpha = preOperateX.calc(std::vector<ValueforVar>{ValueforVar("x", alpha, a, b)});
				double x1 = x[0]+alpha*direction[0];

				x.push_back(x1);

				if (iteration)
				direction.push_back(x[1] - x[0]);

				std::cout <<std::fixed<<std::setprecision(10);
				std::cout << "X0 = " << x[0] << std::endl;
				std::cout << "S0 = " << direction[0] << std::endl;
				std::cout <<"alpha = "<< alpha << std::endl;
				std::cout << "X1 = " << x1 << std::endl << std::endl;
		
				if (abs(x1 - x[0]) < THRESHOLD) break;
				
				if(iteration)
					direction.erase(direction.begin(), direction.begin() + 1);

				x.erase(x.begin(), x.begin() + 1);
		}

	}
	else//-------------未完成
	{
		std::vector<double> x{ InitialPoints[0].value};
		std::vector<double> y{ InitialPoints[1].value};
		std::vector<double> directionX{ 1,0 };
		std::vector<double> directionY{ 0,1 };

		for (int iteration = 0; iteration < MAXIMUMLOOPCOUNT; iteration++)
		{
			std::stringstream str;
			//--------------------------------------
			double r = 1.0 / directionX[0];

			str << r;
			str << "*x";
			if ((r < 0) ^ (x[0] < 0))
				str << "+";
			else
				str << "-";
			str << abs(r*x[0]);
			Equation preOperateX(str.str(), 0);

			double a = InitialPoints[0].min;
			double b = x[0];
			double c = InitialPoints[0].max;

			double alpha = goldenSection(a, b, c, Eq);
			alpha = preOperateX.calc(std::vector<ValueforVar>{ValueforVar("x", alpha, a, b)});
			
			
			double x1 = x[0] + alpha * directionX[0];
			double y1 = y[0] + alpha * directionY[0];


			x.push_back(x1);
			y.push_back(y1);

			if (iteration)
				directionX.push_back(x[1] - x[0]);

			std::cout << std::fixed << std::setprecision(10);
			std::cout << "X0 = " << x[0]<<" "<<y[0] << std::endl;
			std::cout << "S0 = " << directionX[0]<<" "<<directionY[0] << std::endl;
			std::cout << "alpha = " << alpha << std::endl;
			std::cout << "X1 = " << x1<<" "<<y1 << std::endl << std::endl;

			if (abs(x1 - x[0]) < THRESHOLD) break;

			if (iteration)
			{
				directionX.erase(directionX.begin(), directionX.begin() + 1);
				directionY.erase(directionY.begin(), directionY.begin() + 1);
			}
			x.erase(x.begin(), x.begin() + 1);
			y.erase(y.begin(), y.begin() + 1);
		}

	}
	
	return result;
}
std::string SteepDescent(std::vector<ValueforVar>&, Equation&)
{
	std::string result;








	return result;
}