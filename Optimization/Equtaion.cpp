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
	////-------------------------------------------------------在負號前面加"+"方便之後運算猜解每個term
	//for (int index = 0; index < EqString.size(); index++)
	//{
	//	if (EqString[index] == '-')
	//	{
	//		EqString.insert(EqString.begin() + index, '+');
	//		index++;
	//	}
	//}
	//----------------------設定Equation的 編號 跟 字串
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
	// 用set不會重複的特性 將所有var name存起來 
	Term* currentStep = EqTerms;
	std::set<std::string> temp;
		
	// iterate 每個term
	while (currentStep)
	{

		//iterate 每個var
		Variable* currentVar = currentStep->vars;

		while (currentVar)
		{
			if (currentVar->exp != 0)
				//將變數名稱存起來
				temp.insert(currentVar->name);
			currentVar = currentVar->next;
		}

		currentStep = currentStep->next;
	}
	
	//存多少個就是有幾種變數 因為set不會重複
	return temp.size();
}

double Equation::calc(std::vector<ValueforVar> vars)
{
	return EqTerms->calc(vars);
}