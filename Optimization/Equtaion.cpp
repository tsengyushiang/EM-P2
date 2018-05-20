#include "DataManager.h"


Equation::Equation()
{
	EquationString = "";
	EquationIndex = -1;
	EqTerms = NULL;

}

Equation::Equation(std::string EqString, int Index)
{
	EquationIndex = Index;
	EquationString = EqString;		
	EqTerms = new Term(EqString);	
}

Equation::Equation(Equation* e)
{
	EquationString = e->EquationString;
	EquationIndex = e->EquationIndex;
	if (e->EqTerms != NULL)
		EqTerms = new Term(e->EquationString);
	else
		EqTerms = NULL;
	range = e->range;
	domainChange = e->domainChange;
	VariableChange = e->VariableChange;
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

double Equation::calc(std::vector<SubValueintoEq> vars)
{
	for (SubValueintoEq& v : vars)
	{
		for (SubVariableintoEq variable : VariableChange)
		{
			if (v.name == variable.name)
			{
				Equation* temp=new Equation(variable.Eq);
				v.value = temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name,v.value)});
				delete temp;
			}
		}
	}
	
	return EqTerms->calc(vars);
}

Equation& Equation::operator=(Equation& e)
{
	EquationString = e.EquationString;
	EquationIndex = e.EquationIndex;
	EqTerms = new Term(e.EqTerms);
	range=e.range;
	domainChange=e.domainChange;
	VariableChange=e.VariableChange;

	return *this;
}

std::vector<SubValueintoEq> Equation::goldenSection()
{
	int  PreventInfiniteLoop = 200;	

	const double THRESHOLD = 0.001;	
	const double RATIO = 2 - ((1 + sqrt(5.0)) / 2);
	
	std::vector<double> min;
	std::vector<double> max;

	for (Range& r : range)
	{
		for (SubVariableintoEq v : domainChange)
		{
			if (r.name == v.name)
			{
				Equation* temp = new Equation(v.Eq);	

				double m = temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, r.min)});
				double M = temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, r.max)});
				
				if(abs(m)<1E+60)
					min.push_back(m);
				if(abs(M)<1E+60)
					max.push_back(M);
				delete temp;
			}
		}
	}

	sort(min.begin(), min.end());
	sort(max.begin(), max.end());


	double a = min.back();
	double b = max.front();



	while ((abs(b - a) >= THRESHOLD)&&PreventInfiniteLoop)
	{

		double c1 = a + (b - a)*(RATIO);
		double c2 = a + (b - a)*(1-RATIO);

		double fc1 = 0;
		double fc2 = 0;
		if (degree() == 1)
		{
			fc1 = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c1)});
			fc2 = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c2)});
		}
		else if(degree()==2)
		{
			fc1 = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c1), SubValueintoEq("y", c1)});
			fc2 = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c2), SubValueintoEq("y", c2)});
		}


		if (fc1 < fc2) {
			b = c2;
		}
		else
		{
			a = c1;
		}	
		PreventInfiniteLoop--;
	}	
	
	std::vector<SubValueintoEq> result;

	for (SubVariableintoEq v : VariableChange)
	{
			Equation* temp = new Equation(v.Eq);
			
			result.push_back(SubValueintoEq(v.name, \
				temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, (b + a) / 2)})));
			
			delete temp;
	}

	return 	result;
	

}

std::string Equation::Powell(std::vector<SubValueintoEq>& InitialPoints)
{
	const double THRESHOLD = 1.0E-04;
	const int MAXIMUMLOOPCOUNT = 500;
	std::stringstream result;	

	if (InitialPoints.size() == 1)
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };
		std::vector<std::vector<double>> direction{ std::vector<double>{1.0}};
		std::vector<SubValueintoEq> newPoints;

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			Equation Eq(this);
			for (int varcount = 0; varcount < InitialPoints.size(); varcount++)
			{
				std::stringstream temp;
				temp << Points[0][varcount].value;
				if (direction[0][varcount] > 0)
					temp << "+";
				else
					temp << "-";
				temp << abs(direction[0][varcount]);
				temp << "*";
				temp << Points[0][varcount].name;
				Eq.VariableChange.push_back(SubVariableintoEq(InitialPoints[varcount].name,temp.str()));
				temp.str("");

				double t = 1.0 / direction[0][varcount];

				temp << t << "*";
				temp << Points[0][varcount].name;

				if ((Points[0][varcount].value<0)^(t< 0))
					temp << "+";
				else
					temp << "-";
				temp << abs(Points[0][varcount].value*t);

				Eq.	domainChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
			}

			newPoints = Eq.goldenSection();			

			result << "x0 = " << Points[0][0].value << "\r\n";
			result << "x1 = " << newPoints[0].value << "\r\n";
			result << "aplha= " << (newPoints[0].value- Points[0][0].value)/direction[0][0] << "\r\n";
			result << "S = " << (newPoints[0].value - Points[0][0].value) << "\r\n\r\n";

			if (abs((newPoints[0].value - Points[0][0].value)) < THRESHOLD)
				break;

			direction[0][0] = (newPoints[0].value - Points[0][0].value);
			Points[0]= newPoints;
			Eq.VariableChange.clear();
			Eq.domainChange.clear();
		}

		result << "[x] = [" << newPoints[0].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value)}) << "\r\n";
	}
	else
	{
		std::vector<std::vector<SubValueintoEq>> Points{std::vector<SubValueintoEq>{InitialPoints}};
		std::vector<std::vector<double>> direction{ std::vector<double>{1,0},std::vector<double>{0,1}};
		std::vector<SubValueintoEq> newPoints;

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			Equation Eq(this);
			for (int count = 0; count < InitialPoints.size(); count++)
			{
				for (int varcount = 0; varcount < InitialPoints.size(); varcount++)
				{
					std::stringstream temp;
					temp << Points.back()[varcount].value;
					if (direction[count][varcount] > 0)
						temp << "+";
					else
						temp << "-";
					temp << abs(direction[count][varcount]);
					temp << "*";
					temp << Points.back()[varcount].name;
					Eq.VariableChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
					temp.str("");

					double t = 1.0 / direction[count][varcount];

					temp << t << "*";
					temp << Points.back()[varcount].name;

					if ((Points.back()[varcount].value < 0) ^ (t < 0))
						temp << "+";
					else
						temp << "-";
					temp << abs(Points.back()[varcount].value*t);

					Eq.domainChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
				}
				newPoints = Eq.goldenSection();

				//--------------------------------------------------Print
				result << "x0 = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
				//-------------------------------
				Points.push_back(newPoints);
				result << "x1 = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
				//----------------------------------------------------------RESET
				newPoints.clear();
				Eq.VariableChange.clear();
				Eq.domainChange.clear();
			}

			direction.push_back(std::vector<double>{Points.back()[0].value - Points.front()[0].value, Points.back()[1].value - Points.front()[1].value});
			direction.erase(direction.begin(), direction.begin() + 1);
			Points.erase(Points.begin(), Points.begin() + 2);
			result << "S3= " << direction.back()[0] << "\t" << direction.back()[1] << "\r\n\r\n";
			for (int varcount = 0; varcount < InitialPoints.size(); varcount++)
			{
				std::stringstream temp;
				temp << Points.back()[varcount].value;
				if (direction.back()[varcount] > 0)
					temp << "+";
				else
					temp << "-";
				temp << abs(direction.back()[varcount]);
				temp << "*";
				temp << Points.back()[varcount].name;
				Eq.VariableChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
				temp.str("");

				double t = 1.0 / direction.back()[varcount];

				temp << t << "*";
				temp << Points.back()[varcount].name;

				if ((Points.back()[varcount].value < 0) ^ (t < 0))
					temp << "+";
				else
					temp << "-";
				temp << abs(Points.back()[varcount].value*t);

				Eq.domainChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
			}
			newPoints = Eq.goldenSection();

			//--------------------------------------------------Print
			result << "x0 = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
			//-------------------------------
			Points.push_back(newPoints);
			result << "x1 = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
			//----------------------------------------------------------RESET			
			newPoints.clear();
			Eq.VariableChange.clear();
			Eq.domainChange.clear();
		
			if ((abs(Points[1][0].value - Points[0][0].value) < THRESHOLD) && (abs(Points[1][1].value - Points[0][1].value) < THRESHOLD))
			{
				result << "[x,y] = [" << Points[1][0].value<<"\t"<< Points[1][1].value << "]\r\n";
				result << "min = " << Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)}) << "\r\n";
				break;
			}
			Points.erase(Points.begin(), Points.begin() + 1);
		}

	

	}
	return result.str();
}

std::string Equation::SteepDescent(std::vector<SubValueintoEq>& a)
{
	std::string result;








	return result;
}