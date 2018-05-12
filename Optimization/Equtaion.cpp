#include "DataManager.h"


Equation::Equation()
{
	EquationString = "";
	EquationIndex = -1;

}
Variable::Variable(std::string vars)
{	
	// �`�ƶ�
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
	//-------------------------------���Ѧh�ܼ�
	for (index = 0; (index < vars.size())&&(vars[index]!='*'); index++)
	{
		//---------------------------------�ܼƫ��Ƥ��O1
		if (vars[index] == '^')
		{
			temp >> name;
			temp.clear();
			NameLoaded = 1;
		}		
		else
			temp << vars[index];
	}
	//---------------------------------------�ܼƫ��Ƥ��O1
	if (NameLoaded)  //x^0.5
		temp >> exp;
	else   //x
	{
		temp >> name;
		exp=1;
	}
	//---------------------------�h�ܫG�����Φh�����@��'*'
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

//�C�����B�z�Ĥ@��term�A���j�B�z�U�@�Ӫ���terms���B�z��-vector is empty
Term::Term(std::vector<std::string>& terms)
{
	//----------------------------Ū�hcoef
	std::stringstream temp;
	int index=0;
	//�b���ȭ��ܼ� x y �Y����ݭn�i�A�K�[
	for ( index= 0; (terms[0][index] != '*')&&(terms[0][index] != 'x')&&(terms[0][index] != 'y')&& (index<terms[0].size());index++)
	{
		temp << terms[0][index];
	}
	if (temp.str() == "")
		coef = 1;   // x^2�����p
	else if (temp.str() == "-")
		coef = -1;  // -x^2�����p
	else
	{
		temp >> coef; //-3.0*x^2�����p
		terms[0].erase(terms[0].begin(), terms[0].begin() + 1); //�herase�@��'*'
	}
	//---------------------------erase coef���ܼƳ����Ƕivariable
	if(!terms[0].empty())
	terms[0].erase(terms[0].begin(), terms[0].begin() + index);
	vars = new Variable(terms[0]);
	
	//-----------------------------------------------erase�o�ӳB�z��term �i�J�U�@��
	terms.erase(terms.begin(), terms.begin()+1);

	//�C��Terms��pass���ᤣ�A
	if (terms.empty())
	{
		next = NULL;
		return;
	}

	next = new Term(terms);
}

Equation::Equation(std::string EqString, int Index)
{
	//----------------------�]�wEquation�� �s�� �� �r��
	EquationIndex = Index;
	EquationString = EqString;
	//-------------------------------------------------------�b��e���["+"��K����B��q�ѨC��term
	for (int index = 0; index < EqString.size();index++)
	{
		if (EqString[index] == '-')
		{
			EqString.insert(EqString.begin() + index, '+');
			index++;
		}	
	}
	//--------------------------------------------------------�ھ�"+"����m�N�r������U��term�æs�_��
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