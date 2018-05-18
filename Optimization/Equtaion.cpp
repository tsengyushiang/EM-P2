#include "DataManager.h"


Equation::Equation()
{
	EquationString = "";
	EquationIndex = -1;
	EqTerms = NULL;

}
ValueforVar::ValueforVar(std::string n, double v, double m, double M)
	:name(n), value(v), min(m), max(M){}

Equation::Equation(std::string EqString, int Index)
{
	////-------------------------------------------------------�b�t���e���["+"��K����B��q�ѨC��term
	//for (int index = 0; index < EqString.size(); index++)
	//{
	//	if (EqString[index] == '-')
	//	{
	//		EqString.insert(EqString.begin() + index, '+');
	//		index++;
	//	}
	//}
	//----------------------�]�wEquation�� �s�� �� �r��
	EquationIndex = Index;
	EquationString = EqString;		
	EqTerms = new Term(EqString);	
}

Equation::Equation(Equation* e)
{
	EquationString = e->EquationString;
	EquationIndex = e->EquationIndex;
	EqTerms = new Term(e->EqTerms);
}

Equation::~Equation()
{
	EquationString.clear();
	EquationIndex = -1;
	if (EqTerms != NULL)
		delete EqTerms;
	EqTerms = NULL;
}


int Equation::degree()
{
	// ��set���|���ƪ��S�� �N�Ҧ�var name�s�_�� 
	Term* currentStep = EqTerms;
	std::set<std::string> temp;
		
	// iterate �C��term
	while (currentStep)
	{

		//iterate �C��var
		Variable* currentVar = currentStep->vars;

		while (currentVar)
		{
			if (currentVar->exp != 0)
				//�N�ܼƦW�٦s�_��
				temp.insert(currentVar->name);
			currentVar = currentVar->next;
		}

		currentStep = currentStep->next;
	}
	
	//�s�h�֭ӴN�O���X���ܼ� �]��set���|����
	return temp.size();
}

double Equation::calc(std::vector<ValueforVar> vars)
{
	return EqTerms->calc(vars);
}