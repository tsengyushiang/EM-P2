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
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempString;

		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempString;

			//�ѪR��V�q�аO"V"
			Equations.push_back(new Equation(tempString, EquationIndex));
			//���WEquationIndex�A�аO���eŪ���V�qID
			EquationIndex++;

		}
		return true;
	}
}

void DataManager::SetFileName(std::string fileName)
{	
	FileName = fileName;
}

