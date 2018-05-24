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
	str = v->str;
	name = v->name;
	exp = v->exp;
	if (v->next != NULL)
		next = new Variable(v->next->str);
	else
		next = NULL;
}
Variable::Variable(std::string vars)
{
	str = vars;
	std::stringstream temp;
	int index = 0;
	bool NameLoaded = 0;
	//-------------------------------分解多變數
	for (index = 0; (index < vars.size()) && (vars[index] != '*'); index++)
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
		exp = 1;
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

double Variable::calc(std::vector<SubValueintoEq> vars)
{
	double sum = 1;
	for (SubValueintoEq c : vars)
		if ((name == c.name))
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

Variable& Variable::operator=(Variable& v)
{
	name = v.name;
	exp = v.exp;
	next = new Variable(v.next);
	return *this;
}

double Variable::gradient(std::string name)
{
	Variable* var=this;
	double coef = 0;

	if (var->name == name)
	{
		coef = var->exp;
		var->exp -= 1;
	}

	if((!coef)&&(next!=NULL))
		coef = next->gradient(name);

	return coef;

}