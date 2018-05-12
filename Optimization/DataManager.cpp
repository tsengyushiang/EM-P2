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
			Equation tempEq(tempString,EquationIndex);
			//解析到向量標記"V"
			Equations.push_back(tempEq);
			//遞增EquationIndex，標記到當前讀取向量ID
			EquationIndex++;

		}
		return true;
	}
}

std::vector<Equation>& DataManager::GetEquations()
{
	return Equations;
}

void DataManager::SetFileName(std::string fileName)
{
	EquationIndex = 0;
	Equations.clear();
	FileName = fileName;
}

