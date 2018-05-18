#include "DataManager.h"


Variable::Variable()
{
	str.clear();
	name.clear();
	exp = 0;
	next = NULL;
}

Variable::Variable(Variable* v)
{
	name = v->name;
	exp = v->exp;
	next = new Variable(v->next->str);

}
Variable::Variable(std::string vars)
{
	// �`�ƶ�
	str = vars;
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
	for (index = 0; (index < vars.size()) && (vars[index] != '*'); index++)
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
		exp = 1;
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

double Variable::calc(std::vector<ValueforVar> vars)
{
	double sum = 1;
	for (ValueforVar c : vars)
		if (name == c.name)
			sum *= powl(c.value, exp);

	if (next)
		sum *= next->calc(vars);

	return sum;
}

Variable::~Variable()
{
	if(next!=NULL)
		delete next;
	next = NULL;
}