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
	return int(temp.size());
}

double Equation::calc(std::vector<SubValueintoEq> vars)
{
	if (EqTerms == NULL) return 0;
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

double Equation::goldenSection()
{
	int  PreventInfiniteLoop = 200;	

	const long double THRESHOLD = 1E-06;
	const double gr = (sqrt(5.0) + 1) / 2;
	
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
				
				if(abs(m)<1E+66)
					min.push_back(m);
				if (abs(M)<1E+66)
					max.push_back(M);
				delete temp;
			}
		}
	}
	sort(min.begin(), min.end());
	sort(max.begin(), max.end());

	if (min.empty() || max.empty())
		return 0;

	double a = min.back();
	double b = max.front();

	double c = b - (b - a) / gr;
	double d = a + (b - a) / gr;

	while ((abs(c - d) >= THRESHOLD)&&PreventInfiniteLoop)
	{
		double fc = 0;
		double fd = 0;
		if (degree() == 1)
		{
			fc = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c)});
			fd = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", d)});
		}
		else if(degree()==2)
		{
			fc = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", c), SubValueintoEq("y", c)});
			fd = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", d), SubValueintoEq("y", d)});
		}


		if (fc < fd) 
		{
			b = d;
		}
		else
		{
			a = c;
		}	

		c = b - (b - a) / gr;
		d = a + (b - a) / gr;

		PreventInfiniteLoop--;
	}	

	return (b + a) / 2;

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

			double alpha = Eq.goldenSection();


			for (SubVariableintoEq v : Eq.VariableChange)
			{
				Equation* temp = new Equation(v.Eq);
				
				newPoints.push_back(SubValueintoEq(v.name, \
					temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, alpha)})));

					delete temp;
			}	

			result << "x0 = " << Points[0][0].value << "\r\n";
			result << "x1 = " << newPoints[0].value << "\r\n";
			result << "aplha= " << alpha << "\r\n";
			result << "S = " << (newPoints[0].value - Points[0][0].value) << "\r\n\r\n";		
			
			if (abs((newPoints[0].value - Points[0][0].value)) < THRESHOLD)	break;

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
				double alpha = Eq.goldenSection();


				for (SubVariableintoEq v : Eq.VariableChange)
				{
					Equation* temp = new Equation(v.Eq);

					newPoints.push_back(SubValueintoEq(v.name, \
						temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, alpha)})));

					delete temp;
				}

				//--------------------------------------------------Print
				result << "x"<<count+1<<" = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
				//-------------------------------
				Points.push_back(newPoints);
				result << "x" << count + 2 << " = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n";
				result << "aplha= " << alpha << "\r\n";
				result << "S"<<count<<"= " << direction[count][0] << "\t" << direction[count][1] << "\r\n\r\n";
				//----------------------------------------------------------RESET
				newPoints.clear();
				Eq.VariableChange.clear();
				Eq.domainChange.clear();	
	
				if ((powl(Points[1][0].value - Points[0][0].value, 2) + powl(Points[1][1].value - Points[0][1].value, 2)) < THRESHOLD)
				{
					result << "[x,y] = [" << Points[1][0].value << "\t" << Points[1][1].value << "]\r\n";
					result << "min = " << Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)}) << "\r\n";
					return result.str();
				}
			}			

			direction.push_back(std::vector<double>{Points.back()[0].value - Points.front()[0].value, Points.back()[1].value - Points.front()[1].value});
			direction.erase(direction.begin(), direction.begin() + 1);
			Points.erase(Points.begin(), Points.begin() + 2);
			
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
			double alpha = Eq.goldenSection();


			for (SubVariableintoEq v : Eq.VariableChange)
			{
				Equation* temp = new Equation(v.Eq);

				newPoints.push_back(SubValueintoEq(v.name, \
					temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, alpha)})));

				delete temp;
			}

			//--------------------------------------------------Print
			Points.push_back(newPoints);		

			if ((powl(Points[1][0].value - Points[0][0].value, 2) + powl(Points[1][1].value - Points[0][1].value, 2)) < THRESHOLD)
			{
				result << "[x,y] = [" << Points[1][0].value << "\t" << Points[1][1].value << "]\r\n";
				result << "min = " << Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)}) << "\r\n";
				return result.str();
			}

			result << "aplha= " << alpha << "\r\n";
			result << "S= " << direction.back()[0] << "\t" << direction.back()[1] << "\r\n";
			result << "x4 = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n\r\n";
			//----------------------------------------------------------RESET			
			newPoints.clear();
			Eq.VariableChange.clear();
			Eq.domainChange.clear();		
			Points.erase(Points.begin(), Points.begin() + 1);
		}

	

	}
	return result.str();
}

std::string Equation::SteepDescent(std::vector<SubValueintoEq>& InitialPoints)
{
	const double THRESHOLD = 1.0E-04;
	const int MAXIMUMLOOPCOUNT = 500;
	std::stringstream result;

	if (InitialPoints.size() == 1)
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };

		Equation gradient(this);
		gradient.gradient("x");		
		std::vector<std::vector<double>> direction{ std::vector<double>{(-1)*gradient.calc(InitialPoints)} };
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
				Eq.VariableChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
				temp.str("");

				double t = 1.0 / direction[0][varcount];

				temp << t << "*";
				temp << Points[0][varcount].name;

				if ((Points[0][varcount].value<0) ^ (t< 0))
					temp << "+";
				else
					temp << "-";
				temp << abs(Points[0][varcount].value*t);

				Eq.domainChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
			}

			double alpha = Eq.goldenSection();


			for (SubVariableintoEq v : Eq.VariableChange)
			{
				Equation* temp = new Equation(v.Eq);

				newPoints.push_back(SubValueintoEq(v.name, \
					temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, alpha)})));

				delete temp;
			}

			result << "h = " << direction[0][0] << "\r\n\r\n";
			result << "aplha= " << alpha << "\r\n";
			result << "X = " << newPoints[0].value << "\r\n";
			
			
			
			Points[0] = newPoints;
			direction[0][0] = (-1)*gradient.calc(std::vector<SubValueintoEq>{SubValueintoEq(Points[0][0].name, Points[0][0].value)});
			std::cout << direction[0][0] <<std::endl;

			if (abs(direction[0][0]) < THRESHOLD)	break;

			Eq.VariableChange.clear();
			Eq.domainChange.clear();
		}
		result << "[x] = [" << newPoints[0].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value)}) << "\r\n";
	}
	else
	{
		Equation gradientX(this);
		Equation gradientY(this);
		gradientX.gradient("x");
		gradientY.gradient("y");

		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };

		std::vector<std::vector<double>> direction{ std::vector<double>{
			(-1)*gradientX.calc(InitialPoints),	(-1)*gradientY.calc(InitialPoints)
		}};

		std::vector<SubValueintoEq> newPoints;

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			Equation Eq(this);
			
			for (int varcount = 0; varcount < InitialPoints.size(); varcount++)
			{
					std::stringstream temp;
					temp << Points.back()[varcount].value;
					if (direction[0][varcount] > 0)
						temp << "+";
					else
						temp << "-";
					temp << abs(direction[0][varcount]);
					temp << "*";
					temp << Points.back()[varcount].name;
					Eq.VariableChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
					temp.str("");

					double t = 1.0 / direction[0][varcount];

					temp << t << "*";
					temp << Points.back()[varcount].name;

					if ((Points.back()[varcount].value < 0) ^ (t < 0))
						temp << "+";
					else
						temp << "-";
					temp << abs(Points.back()[varcount].value*t);

				Eq.domainChange.push_back(SubVariableintoEq(InitialPoints[varcount].name, temp.str()));
			}
			double alpha = Eq.goldenSection();


			for (SubVariableintoEq v : Eq.VariableChange)
			{
				Equation* temp = new Equation(v.Eq);

				newPoints.push_back(SubValueintoEq(v.name, \
					temp->calc(std::vector<SubValueintoEq>{SubValueintoEq(v.name, alpha)})));

				delete temp;
			}

			//--------------------------------------------------Print
			result << "h = " << direction[0][0] << "\t" << direction[0][1] << "\r\n";	
			result << "lambda= " << alpha << "\r\n";
			Points.push_back(newPoints);
			result << "X = " << Points.back()[0].value << "\t" << Points.back()[1].value << "\r\n\r\n";			
			//----------------------------------------------------------RESET
			newPoints.clear();
			Eq.VariableChange.clear();
			Eq.domainChange.clear();
		
			direction[0] = std::vector<double>{(-1)*gradientX.calc({SubValueintoEq(Points[1][0].name,Points[1][0].value), SubValueintoEq(Points[1][1].name,Points[1][1].value) })\
							, (-1)*gradientY.calc({ SubValueintoEq(Points[1][1].name,Points[1][1].value),SubValueintoEq(Points[1][0].name,Points[1][0].value) })};
			
			if (((powl(Points[1][0].value - Points[0][0].value, 2) + powl(Points[1][1].value - Points[0][1].value, 2)) < THRESHOLD))
			{
				result << "[x,y] = [" << Points[1][0].value << "\t" << Points[1][1].value << "]\r\n";
				result << "min = " << Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)}) << "\r\n";
				break;
			}
			else if (abs((Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)})\
				) - (Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[0][0].value), SubValueintoEq("y", Points[0][1].value)})))<THRESHOLD)
			{
				result << "[x,y] = [" << Points[1][0].value << "\t" << Points[1][1].value << "]\r\n";
				result << "min = " << Eq.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", Points[1][0].value), SubValueintoEq("y", Points[1][1].value)}) << "\r\n";
				break;
			}
			Points.erase(Points.begin(), Points.begin() + 1);
		}

	}
	return result.str();
}

std::string Equation::Newton(std::vector<SubValueintoEq>& InitialPoints)
{
	const double THRESHOLD = 1.0E-04;
	const int MAXIMUMLOOPCOUNT = 500;
	std::stringstream result;

	if (InitialPoints.size() == 1)
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };

		Equation gradient1(this);
		Equation gradient2(this);
		gradient1.gradient("x");
		gradient2.gradient("x");
		gradient2.gradient("x");		

		std::vector<Matrix> direction{};
		std::vector<SubValueintoEq> newPoints;

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{		
			Matrix hessian;
			Matrix gradient;
			std::stringstream t;

			t << 1 << " " << 1 << " " << gradient2.calc(Points[0]) << std::endl;
			t << 1 << " " << 1 << " " << gradient1.calc(Points[0]) << std::endl;
			t >> hessian >> gradient;
			result <<"Hessian=\r\n "<<hessian << "\r\n";
			result << "Hessian Inverse=\r\n " << hessian.Inverse() << "\r\n";	

			direction.push_back((-0.5)*hessian.Inverse()*gradient);

			newPoints.push_back(SubValueintoEq("x",Points[0][0].value + direction[0].Data[0][0]));			
			
			result << "x= " << newPoints[0].value << "\r\n\r\n";

			if (abs(newPoints[0].value - Points[0][0].value) < THRESHOLD)break;

			Points[0] = newPoints;
			direction.clear();
			newPoints.clear();
			t.str(""); t.clear();
		
		}
		result << "[x] = [" << newPoints[0].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value)}) << "\r\n";
	}
	else
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };

		Equation gradientX(this); gradientX.gradient("x");
		Equation gradientY(this); gradientY.gradient("y");
		Equation gradientXX(this); gradientXX.gradient("x"); gradientXX.gradient("x");
		Equation gradientXY(this); gradientXY.gradient("x"); gradientXY.gradient("y");
		Equation gradientYY(this); gradientYY.gradient("y"); gradientYY.gradient("y");		

		std::vector<Matrix> direction{};
		std::vector<SubValueintoEq> newPoints;

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			Matrix hessian;
			Matrix gradient;
			std::stringstream t;

			t << 2 << " " << 2 << " " << gradientXX.calc(Points[0]) << " " << gradientXY.calc(Points[0]) << " "\
				<< gradientXY.calc(Points[0]) << " " << gradientYY.calc(Points[0]) << std::endl;

			t << 2 << " " << 1 << " " << gradientX.calc(Points[0]) << " " << gradientY.calc(Points[0]) << std::endl;

			t >> hessian >> gradient;
			result << "Hessian=\r\n " << hessian << "\r\n";
			result << "Hessian Inverse=\r\n " << hessian.Inverse() << "\r\n";

			direction.push_back((-1)*hessian.Inverse()*gradient);

			newPoints = std::vector<SubValueintoEq>{ SubValueintoEq("x", Points[0][0].value + direction[0].Data[0][0]), \
														SubValueintoEq("y", Points[0][1].value + direction[0].Data[1][0]) };

			result << "x= " << newPoints[0].value<<" " << newPoints[1].value << "\r\n\r\n";

			if ((powl(newPoints[0].value - Points[0][0].value, 2) + powl(newPoints[1].value - Points[0][1].value, 2)) < THRESHOLD)
			{
				break;
			}

			Points[0] = newPoints;
			direction.clear();
			newPoints.clear();
			t.str(""); t.clear();

		}
		result << "[x,y] = [" << newPoints[0].value << "\t" << newPoints[1].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value), SubValueintoEq("y", newPoints[1].value)}) << "\r\n";
	}
	return result.str();
}


std::string Equation::Qusai_Newton(std::vector<SubValueintoEq>& InitialPoints)
{
	const double THRESHOLD = 1.0E-04;
	const int MAXIMUMLOOPCOUNT = 500;
	std::stringstream result;

	if (InitialPoints.size() == 1)
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };
		std::vector<Matrix> direction{};
		std::vector<SubValueintoEq> newPoints;

		Equation gradientX(this);
		gradientX.gradient("x");		

		Matrix F({1});

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			
			Matrix gradient({ gradientX.calc(Points[0]) });
			std::stringstream t;	

			result << "F= " << F ;

			direction.push_back((-1)*F.Inverse()*gradient);

			newPoints.push_back(SubValueintoEq("x", Points[0][0].value + (0.1)*direction[0].Data[0][0]));

			
			Matrix deltaX = Matrix({ newPoints[0].value - Points[0][0].value });
			Matrix deltaGradient = Matrix({ gradientX.calc({newPoints[0]}) - gradientX.calc(Points[0])});

			F = F + ((deltaX - F * deltaGradient)/deltaGradient);	
		
			result << "x= " << newPoints[0].value << "\r\n\r\n";	

			if (abs(newPoints[0].value - Points[0][0].value) < THRESHOLD)break;

			Points[0] = newPoints;
			direction.clear();
			newPoints.clear();
			t.str(""); t.clear();

		}
		result << "[x] = [" << newPoints[0].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value)}) << "\r\n";
	}
	else
	{
		std::vector<std::vector<SubValueintoEq>> Points{ std::vector<SubValueintoEq>{InitialPoints} };
		std::vector<Matrix> direction{};
		std::vector<SubValueintoEq> newPoints;

		Equation gradientX(this);
		Equation gradientY(this);
		gradientX.gradient("x");
		gradientY.gradient("y");

		Matrix F({ 1,0,0,1 });

		for (int i = 0; i < MAXIMUMLOOPCOUNT; i++)
		{
			Matrix gradient({ gradientX.calc(Points[0]),gradientY.calc(Points[0]) });
			std::stringstream t;
		
			result << "F= \r\n" << F;

			direction.push_back((-0.5)*F*gradient);

			newPoints.push_back(SubValueintoEq("x", Points[0][0].value + direction[0].Data[0][0]));
			newPoints.push_back(SubValueintoEq("y", Points[0][1].value + direction[0].Data[1][0]));

			Matrix deltaX = Matrix({ newPoints[0].value - Points[0][0].value, newPoints[1].value - Points[0][1].value });
			Matrix deltaGradient = Matrix({ gradientX.calc(newPoints) - gradientX.calc(Points[0]),gradientY.calc(newPoints) - gradientY.calc(Points[0]) });

			F = F + ((deltaX - F * deltaGradient)*(deltaX - F * deltaGradient).Transpose())/
				((deltaX - F * deltaGradient).Transpose()*deltaGradient);
			
			result << "x= " << newPoints[0].value<<"\t"<< newPoints[1].value << "\r\n\r\n";

			if ((powl(newPoints[0].value - Points[0][0].value, 2) + powl(newPoints[1].value - Points[0][1].value, 2)) < THRESHOLD)
			{
				break;
			}
			
			Points[0] = newPoints;
			direction.clear();
			newPoints.clear();
			t.str(""); t.clear();

		}
		result << "[x,y] = [" << newPoints[0].value << "\t" << newPoints[1].value << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", newPoints[0].value), SubValueintoEq("y", newPoints[1].value)}) << "\r\n";
	}
	return result.str();
}

std::string Equation::Conjugate_Gradient(std::vector<SubValueintoEq>& InitialPoints)
{
	const double THRESHOLD = 1.0E-04;
	const int MAXIMUMLOOPCOUNT = 500;
	std::stringstream result;

	if (InitialPoints.size() == 1)
	{
		double x1 = InitialPoints[0].value;
		double B;
		double direction;
		double x2;
		double REdir;

		for (int i = 0; ; i++)
		{
			Equation equ(this);
			Equation DF(this);
			DF.gradient("x");

			if (i == 0)
			{
				direction = -1.0 * DF.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1)});
			}
			else
			{
				REdir = direction;
				direction = -1.0 * DF.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1)});
				B = (direction * direction) / (REdir * REdir);
				direction = direction + B * REdir;
			}
			std::stringstream temp;
			temp << x1;
			if (direction > 0)
				temp << "+";
			else
				temp << "-";
			temp << abs(direction) << "*";
			temp << InitialPoints[0].name;
			equ.VariableChange.push_back(SubVariableintoEq(InitialPoints[0].name, temp.str()));

			temp.str("");
			double t = 1.0 / direction;
			temp << t << "*";
			temp << "x";
			if ((x1< 0) ^ (t < 0))
				temp << "+";
			else
				temp << "-";
			temp << abs(x1*t);
			equ.domainChange.push_back(SubVariableintoEq(InitialPoints[0].name, temp.str()));
			double alpha = equ.goldenSection();

			x2 = x1 + direction * alpha;

			if (x2 > equ.range[0].max)
				x2 = equ.range[0].max;
			if (x2 < equ.range[0].min)
				x2 = equ.range[0].min;

			//print......................................................................
			result << "Xi = [ " << x1 << " ]\r\n";
			if (i != 0)
			{
				result << "BETA = " << B << "\r\n";
			}
			result << "Si = " << direction << "\r\n" << "Alpha = " << alpha << "\r\n" << "Xi = [ " << x2 << " ]\r\n\r\n";
			double value = calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x2)});
			if (abs(calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x2)}) - calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x1)})) < THRESHOLD || abs(x2 - x1) < THRESHOLD || i == MAXIMUMLOOPCOUNT - 1){break;}
			
			x1 = x2;
		}
		result << "[x] = [" << x2 << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x2)}) << "\r\n";
	}
	else
	{
		double x1 = InitialPoints[0].value;
		double y1 = InitialPoints[1].value;
		double B;
		double directionX;
		double directionY;
		double x2;
		double y2;
		double REdirX;
		double REdirY;
		Equation equ(this);
		Equation DFx(this);
		Equation DFy(this);
		DFx.gradient("x");
		DFy.gradient("y");

		for (int i = 0; ; i++)
		{			
			if (i == 0)
			{
				directionX = -1.0 * DFx.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1), SubValueintoEq(InitialPoints[1].name, y1)});
				directionY = -1.0 * DFy.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1), SubValueintoEq(InitialPoints[1].name, y1)});
			}			
			//..........................enter x1+direction*x
			std::stringstream temp;
			temp << x1;
			if (directionX > 0)
				temp << "+";
			else
				temp << "-";
			temp << abs(directionX) << "*";
			temp << "x";
			equ.VariableChange.push_back(SubVariableintoEq(InitialPoints[0].name, temp.str()));
			temp.str("");
			//..........................change domain to  X/direction-x1/direction
			double t = 1.0 / directionX;
			temp << t << "*";
			temp << "x";
			if ((x1 < 0) ^ (t < 0))
				temp << "+";
			else
				temp << "-";
			temp << abs(x1*t);
			equ.domainChange.push_back(SubVariableintoEq(InitialPoints[0].name, temp.str()));
			temp.str("");

			//..........................enter x1+direction*alpha
			temp << y1;
			if (directionY > 0)
				temp << "+";
			else
				temp << "-";
			temp << abs(directionY) << "*";
			temp << "y";
			equ.VariableChange.push_back(SubVariableintoEq(InitialPoints[1].name, temp.str()));
			temp.str("");
			//..........................change domain to  Y/direction-y1/direction
			t = 1.0 / directionY;
			temp << t << "*";
			temp << "y";
			if ((y1 < 0) ^ (t < 0))
				temp << "+";
			else
				temp << "-";
			temp << abs(y1*t);
			equ.domainChange.push_back(SubVariableintoEq(InitialPoints[1].name, temp.str()));
			temp.str("");
			//.....................................................................................................
			double alpha = equ.goldenSection();
			
			x2 = x1 + directionX * alpha;
			y2 = y1 + directionY * alpha;
			if (x2 > equ.range[0].max)
				x2 = equ.range[0].max;
			if (x2 < equ.range[0].min)
				x2 = equ.range[0].min;
			if (y2 > equ.range[1].max)
				y2 = equ.range[1].max;
			if (y2 < equ.range[1].min)
				y2 = equ.range[1].min;

			//print......................................................................
			result << "Xi = [ " << x1 << " , " << y1 << " ]\r\n";
			if (i != 0)
			{
				result << "BETA = " << B << "\r\n";
			}
			result << "Si = " << "[" << directionX << " , " << directionY << "]" << "\r\n" << "Alpha = " << alpha << "\r\n" << "Xi = [ " << x2 << " , " << y2 << " ]\r\n\r\n";
			//
			if (abs(equ.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x2), SubValueintoEq("y", y2)}) - equ.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x1), SubValueintoEq("y", y1)})) < THRESHOLD || powl(x2 - x1, 2) + powl(y2 - y1, 2)< THRESHOLD || i == MAXIMUMLOOPCOUNT - 1) { break; }
			
			
			double gx1= DFx.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1), SubValueintoEq(InitialPoints[1].name, y1)});
			double gy1= DFy.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x1), SubValueintoEq(InitialPoints[1].name, y1)});
			double gx2= DFx.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x2), SubValueintoEq(InitialPoints[1].name, y2)});
			double gy2= DFy.calc(std::vector<SubValueintoEq>{SubValueintoEq(InitialPoints[0].name, x2), SubValueintoEq(InitialPoints[1].name, y2)});

			B = (gx2 * gx2 + gy2 * gy2) / (gx1 * gx1 + gy1 * gy1);
						
			if (abs(B) < THRESHOLD) break;

			directionX = -gx2 + B * directionX;
			directionY = -gy2 + B * directionY;

			x1 = x2;
			y1 = y2;

			equ.domainChange.clear();
			equ.VariableChange.clear();

		}
		result << "[x,y] = [" << x2 << " , " << y2 << "]\r\n";
		result << "min = " << calc(std::vector<SubValueintoEq>{SubValueintoEq("x", x2), SubValueintoEq("y", y2)}) << "\r\n";

	}
	return result.str();
}

void Equation::gradient(std::string name)
{
	EqTerms->gradient(name);

	std::vector<Term*> everyTerm;

	//把所有變數存起來
	Term* iter = EqTerms;
	while (iter != NULL)
	{
		everyTerm.push_back(iter);
		iter = iter->next;
	}

	//當exp==0時 delete那個變數
	for (int index = 1; index<everyTerm.size();)
	{
		if (everyTerm[index]->coef == 0)
		{
			everyTerm[index - 1]->next = everyTerm[index]->next;
			everyTerm[index]->next = NULL;
			delete everyTerm[index];
			everyTerm.erase(everyTerm.begin() + index, everyTerm.begin() + index + 1);
		}
		else
			index++;
	}

	if ((EqTerms->coef == 0))
	{
		Term* t = EqTerms->next;
		EqTerms->next = NULL;
		delete EqTerms;
		EqTerms = t;
	}

}