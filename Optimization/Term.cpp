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
	sum += vars->calc(v)*coef;

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