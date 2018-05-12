#include "DataManager.h"


Equation::Equation()
{
	EquationString = "";
	EquationIndex = -1;

}
Variable::Variable(std::string vars)
{	
	// 常數項
	if (vars.empty())
	{
		name = 'x';
		exp = 0;
		next = NULL;
		return;
	}
	std::stringstream temp;
	int index = 0;
	bool NameLoaded = 0;
	//-------------------------------分解多變數
	for (index = 0; (index < vars.size())&&(vars[index]!='*'); index++)
	{
		//---------------------------------變數指數不是1
		if (vars[index] == '^')
		{
			temp >> name;
			temp.clear();
			NameLoaded = 1;
		}		
		else
			temp << vars[index];
	}
	//---------------------------------------變數指數不是1
	if (NameLoaded)  //x^0.5
		temp >> exp;
	else   //x
	{
		temp >> name;
		exp=1;
	}
	//---------------------------多變亮的情形多移除一個'*'
	if (index != vars.size())
	{
		vars.erase(vars.begin(), vars.begin() + 1);
	}
	vars.erase(vars.begin(), vars.begin() + index);

	if (vars.empty())
	{
		next = NULL;
		return;
	}

	next = new Variable(vars);
}

//每次都處理第一個term再遞迴處理下一個直到terms都處理完-vector is empty
Term::Term(std::vector<std::string>& terms)
{
	//----------------------------讀去coef
	std::stringstream temp;
	int index=0;
	//在此僅限變數 x y 若之後需要可再添加
	for ( index= 0; (terms[0][index] != '*')&&(terms[0][index] != 'x')&&(terms[0][index] != 'y')&& (index<terms[0].size());index++)
	{
		temp << terms[0][index];
	}
	if (temp.str() == "")
		coef = 1;   // x^2的情況
	else if (temp.str() == "-")
		coef = -1;  // -x^2的情況
	else
	{
		temp >> coef; //-3.0*x^2的情況
		terms[0].erase(terms[0].begin(), terms[0].begin() + 1); //多erase一個'*'
	}
	//---------------------------erase coef把變數部分傳進variable
	if(!terms[0].empty())
	terms[0].erase(terms[0].begin(), terms[0].begin() + index);
	vars = new Variable(terms[0]);
	
	//-----------------------------------------------erase這個處理完term 進入下一個
	terms.erase(terms.begin(), terms.begin()+1);

	//每個Terms都pass完後不再
	if (terms.empty())
	{
		next = NULL;
		return;
	}

	next = new Term(terms);
}

Equation::Equation(std::string EqString, int Index)
{
	//----------------------設定Equation的 編號 跟 字串
	EquationIndex = Index;
	EquationString = EqString;
	//-------------------------------------------------------在減號前面加"+"方便之後運算猜解每個term
	for (int index = 0; index < EqString.size();index++)
	{
		if (EqString[index] == '-')
		{
			EqString.insert(EqString.begin() + index, '+');
			index++;
		}	
	}
	//--------------------------------------------------------根據"+"的位置將字串分成各個term並存起來
	std::vector<std::string> terms;
	std::string tempString;

	for (char c : EqString)
	{
		if (c == '+')
		{
			terms.push_back(tempString);
			tempString.clear();
		}
		else
		{
			tempString.push_back(c);
		}
	}
	terms.push_back(tempString);
	//----------------------------------------------------------	
	EqTerms = new Term(terms);
	
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