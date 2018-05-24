#include "DataManager.h"

Term::Term()
{
	str.clear();
	coef = 0;
	vars = NULL;
	next = NULL;
}

Term::Term(std::string EqString)
{	
	//--------------------------------------------------------
	std::string firstTerm;

	for (int index=0;index<EqString.size();index++)
	{
		if (((EqString[index] == '+') || (EqString[index] == '-'))&&index)
		{			
			break;
		}
		else
		{
			firstTerm.push_back(EqString[index]);
		}
	}
	EqString.erase(EqString.begin(), EqString.begin() + firstTerm.size());
	//----------------------------------------------------------
	str = firstTerm;
	//----------------------------Ū�hcoef
	std::stringstream temp;
	int index = 0;
	//�b���ȭ��ܼ� x y �Y����ݭn�i�A�K�[
	for (index = 0; (firstTerm[index] != '*') && (firstTerm[index] != 'x') && (firstTerm[index] != 'y') && (index<firstTerm.size()); index++)
	{
		temp << firstTerm[index];
	}
	if ((temp.str() == "+")||(temp.str() == ""))
		coef = 1;   // x^2�����p
	else if (temp.str() == "-")
		coef = -1;  // -x^2�����p
	else
	{
		temp >> coef; //-3.0*x^2�����p

		if (index<firstTerm.size())
			firstTerm.erase(firstTerm.begin(), firstTerm.begin() + 1); //�herase�@��'*'
	}
	//---------------------------erase coef���ܼƳ����Ƕivariable
	if (!firstTerm.empty())
		firstTerm.erase(firstTerm.begin(), firstTerm.begin() + index);
	
	if (firstTerm.empty())
		vars = NULL;
	else
	    vars = new Variable(firstTerm);	

	//�Ҧ�Term��pass����
	if (EqString.empty())
	{
		next = NULL;
		return;
	}

	next = new Term(EqString);
}

Term::~Term()
{
	str.clear();
	coef = 0;
	if (vars != NULL)
		delete vars;
	vars = NULL;
	if (next != NULL)
		delete next;
	next = NULL;
}

Term::Term(Term* t)
{
	str = t->str;
	coef = t->coef;
	if (t->vars != NULL)
		vars = new Variable(t->vars->str);
	else
		vars = NULL;
	if (t->next != NULL)
		next = new Term(t->next->str);
	else
		next = NULL;
}

double Term::calc(std::vector<SubValueintoEq> v)
{
	double sum = 0;

	if (coef == 0)
		sum += 0;
	else if(vars!=NULL)
		sum += vars->calc(v)*coef;
	else
		sum += coef;

	if (next)
		sum += next->calc(v);

	return sum;
}

Term& Term::operator=(Term& t)
{
	str = t.str;
	coef = t.coef;
	vars = new Variable(t.vars);
	next = new Term(t.str);
	return *this;
}

void Term::gradient(std::string name)
{
	if (vars != NULL)
	{
		coef *= vars->gradient(name);

		//-------------------------------------�ˬd�L������O�_���`��x^0
		std::vector<Variable*> everyVar;
		
		//��Ҧ��ܼƦs�_��
		Variable* iter = vars;
		while (iter!=NULL)
		{
			everyVar.push_back(iter);
			iter = iter->next;
		}

		//��exp==0�� delete�����ܼ�
		for (int index=1;index<everyVar.size();index++)
		{
			if (everyVar[index]->exp == 0)
			{
				everyVar[index - 1]->next = everyVar[index]->next;
				everyVar[index]->next = NULL;
				delete everyVar[index];
			} 
		}
				
		if (vars->exp == 0)
		{
			Variable* t = vars->next;
			vars->next = NULL;
			delete vars;
			vars = t;
		}
	}
	else
		coef = 0;

	if (next != NULL)
		next->gradient(name);	
	
}