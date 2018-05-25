#include"DataManager.h"
#define EQUALZERO(x) (((x<0.00001)&&(x>-0.00001))?true:false)
double Matrix::sort()
{
	double det = 1;
	// sort by zero count
	for (int row = 0; row < rowCount; row++)
	{
		int ZeroCount = 0;
		while ((ZeroCount < colCount) && EQUALZERO(Data[row][ZeroCount]))
				ZeroCount++;
		

		for (int i = row + 1; i< rowCount; i++)
		{
			int tempZeroCount = 0;
			while ((tempZeroCount<colCount) && EQUALZERO(Data[i][tempZeroCount]))
				tempZeroCount++;

			if (ZeroCount > tempZeroCount)
			{
				std::vector<double> temp;
				temp = Data[row];
				Data[row] = Data[i];
				Data[i] = temp;

				det *= -1;

				ZeroCount = tempZeroCount;
			}
		}
	}

	return det;

}

double Matrix::LeadingOne()
{
	double det = 1;
	for (int row = 0; row < rowCount; row++)
	{
		int col = 0;
		while ((col < colCount) && EQUALZERO(Data[row][col]))
			col++;

		for (int k = col + 1; k < colCount; k++)
		{
			Data[row][k] /= Data[row][col];						

		}
		if (col < colCount)
		{
			det *= Data[row][col];
			Data[row][col] = 1;
		}
		
	}

	return det;
	
}

Matrix::Matrix()
{
	Error = 0;
	rowCount = 0;
	colCount = 0;
	Name = "";
	Data.clear();
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix result;

	//維度判斷 不同則回傳Error
	if ((a.colCount != b.colCount) || (a.Error) || (b.Error) || (a.rowCount != b.rowCount))
	{
		result.Error = 1;
		return result;
	}

	result.colCount = a.colCount;
	result.rowCount = a.rowCount;

	for (int i = 0; i < result.rowCount; i++)
	{
		std::vector<double> tempData;
		for (int j = 0; j < result.colCount; j++)
		{
			double value = a.Data[i][j] - b.Data[i][j];
			tempData.push_back(value);

		}
		result.Data.push_back(tempData);
		tempData.clear();
	}

	return result;


}
Matrix operator+(const Matrix& a,const Matrix& b)
{
	Matrix result;

   //維度判斷 不同則回傳Error
	if ((a.colCount != b.colCount)||(a.Error)||(b.Error)||(a.rowCount!=b.rowCount))
	{
		result.Error = 1;
		return result;
	}

	result.colCount = a.colCount;
	result.rowCount = a.rowCount;

	for (int i = 0; i < result.rowCount; i++)
	{
		std::vector<double> tempData;
		for (int j = 0; j < result.colCount; j++)
		{
			double value = a.Data[i][j] + b.Data[i][j];
			tempData.push_back(value);

		}
		result.Data.push_back(tempData);
		tempData.clear();
	}

	return result;
}

bool operator==(const Matrix& a, const Matrix& b)
{
	if (a.rowCount != b.rowCount) return false;
	if (a.colCount != b.colCount) return false;

	for (int row =0; row < a.rowCount; row++)
	{
		for (int col = 0; col < a.colCount; col++)
		{
			if (abs(a.Data[row][col] -b.Data[row][col]) >0.00001)return false;
		}		
	}	

	return true;
}

std::istream& operator>>(std::istream& input, Matrix& Data)
{
	//讀取矩陣資料
   input >> Data.rowCount >> Data.colCount;

	for (int row = 0; row < Data.rowCount; row++)
	{
		std::vector<double> tempDatas;
		for (int col = 0; col < Data.colCount; col++)
		{
			double value;
			input >> value;
			tempDatas.push_back(value);
		}
		Data.Data.push_back(tempDatas);
		tempDatas.clear();
	}

	return input;

}


std::ostream& operator<<(std::ostream& output,const Matrix& Data)
{
	if (Data.Error)
	{
		output << "Error\r\n";
		return output;
	}
	output << std::fixed << std::showpoint;
	output << std::setprecision(5);
	for (int row = 0; row < Data.rowCount; row++)
	{
		for (int col = 0; col < Data.colCount; col++)
		{
			output << Data.Data[row][col];
			if (col != Data.colCount - 1)
					output << " ";
			
				
		}
		output <<"\r\n";
	}

	return output;
}


int Matrix::Rank()
{
	Matrix temp=RowReduction();	
	int rankCount = temp.rowCount;
	for (int row = 0; row < temp.rowCount; row++)
	{
		int col = 0;
		while ((col < colCount) && EQUALZERO(temp.Data[row][col]))col++;

		if (col==colCount)rankCount--;
	}

	return rankCount;
}

Matrix Matrix::RowReduction()
{
	Matrix result=*this;	

	//Gaussian Elimination
	for (int row = 0,col=0;(row < rowCount)&&(col<colCount);row++,col++)
	{		
		result.sort();
		result.LeadingOne();
		
		
		if (result.Data[row][col]==0)
		{
			col++;
			if (col < colCount)break;
		}
		for (int i = row + 1; (i<rowCount)&&(result.Data[i][col]==1); i++)
		{
			for (int j =col; j < colCount; j++)
			{
				result.Data[i][j] -= result.Data[row][j];
			}
		}
	}

	//REDUCED ROW ECHELON FORM
	int lastElement = result.rowCount > result.colCount ? result.colCount-1 : result.rowCount-1;

	for (int row = lastElement; row >= 0; row--)
	{
		if (result.Data[row][row] != 1)continue;
		for (int iterativeRow = row - 1; iterativeRow >= 0; iterativeRow--)
		{
			if (EQUALZERO(result.Data[iterativeRow][row]))continue;

			for (int col = row + 1; col < colCount; col++)
				result.Data[iterativeRow][col] -= result.Data[row][col] * result.Data[iterativeRow][row];
						
			result.Data[iterativeRow][row] = 0;
		}
	}	

	return result;

}

Matrix Matrix::Transpose()
{
	Matrix result;
	result.rowCount = colCount;
	result.colCount = rowCount;

	for (int row = 0; row < colCount; row++)
	{
		std::vector<double> temp;
		for (int col = 0; col <rowCount; col++)
		{
			temp.push_back(Data[col][row]);
		}
		result.Data.push_back(temp);
		temp.clear();
	}

	return result;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	Matrix result;
	result.rowCount = a.rowCount;
	result.colCount = b.colCount;

	if (a.colCount != b.rowCount)
	{
		result.Error = true;
		return result;
	}

	for (int row = 0; row < result.rowCount; row++)
	{
		std::vector<double> temp;
		for (int col = 0; col < result.colCount; col++)
		{
			double accumulator=0;
			for (int index = 0; index < a.colCount; index++)
			{				
				accumulator += a.Data[row][index] * b.Data[index][col];				
			}			
			temp.push_back(accumulator);
			
		}				
		result.Data.push_back(temp);
		temp.clear();
	}

	return result;
}

Matrix operator*(double a, const Matrix& b)
{
	Matrix result=b;
	
	for (int row = 0; row < result.rowCount; row++)
	{
		for (int col = 0; col < result.colCount; col++)
		{		
			result.Data[row][col] *= a;
		}
	}

	return result;
}

Matrix SolveLinarSystem(const Matrix& a,const Matrix& b)
{
	Matrix AugmentedMatrix;
	Matrix result;

	AugmentedMatrix.rowCount = result.rowCount= a.rowCount;
	AugmentedMatrix.colCount = result.colCount= a.colCount + 1;	

	if ((a.colCount != b.rowCount) || (b.colCount != 1))
	{
		result.Error = true;
		return result;
	}

	for (int row = 0; row < AugmentedMatrix.rowCount; row++)
	{
		std::vector<double> temp;
		temp = a.Data[row];
		temp.push_back(b.Data[row][0]);
		AugmentedMatrix.Data.push_back(temp);
		temp.clear();
	}
	AugmentedMatrix=AugmentedMatrix.RowReduction();

	int ZeroCount = AugmentedMatrix.rowCount-AugmentedMatrix.Rank();
	
	for (int i = 0; i < AugmentedMatrix.rowCount; i++)
	{
		bool AllZero = 1;
		for (int col = 0; col < AugmentedMatrix.rowCount; col++)
		{
			if (AugmentedMatrix.Data[i][col] != 0)AllZero = 0;
		}

		if (AugmentedMatrix.Data[i][i] == 0 && !AllZero)
		{
			AugmentedMatrix.Data.insert(AugmentedMatrix.Data.begin()+i, AugmentedMatrix.Data.back());
			AugmentedMatrix.Data.pop_back();
			ZeroCount--;
		}
		if (!ZeroCount)break;
	}



	for (int row = 0; row < AugmentedMatrix.rowCount; row++)
	{
		std::vector<double> temp;
		for (int col = 0; col < AugmentedMatrix.colCount; col++)
		{					
			if (row == col)
			{
				if (AugmentedMatrix.Data[row][col] != 1)
					temp.push_back(1);
				else
					temp.push_back(0);
			}			
			else if(col<row)
			{
				temp.push_back(0);
			}
			else if(col==AugmentedMatrix.colCount-1)
			{
				temp.push_back(AugmentedMatrix.Data[row][col]);
			}
			else
			{
				temp.push_back(-AugmentedMatrix.Data[row][col]);
			}
		}
		result.Data.push_back(temp);
		temp.clear();
	}	
	result=result.Transpose();

	for (int row = 0; row <result.Data.size(); row++)
	{
		bool Allzero = 1;
		for(int col=0;col<result.colCount;col++)
		{
			if (result.Data[row][col] != 0)Allzero = 0;
		}
		if (Allzero)
		{
			result.Data.erase(result.Data.begin()+row);
			row--;
		}
	}
	result.rowCount = result.Data.size();
	result.colCount = result.Data[0].size();

	return result;
}

double Matrix::det(bool& error)
{
	if (rowCount != colCount)
	{
		error = true;
		return 0;
	}

	Matrix result = *this;
	double det = 1;
	//Gaussian Elimination
	for (int row = 0, col = 0; (row < rowCount) && (col<colCount); row++, col++)
	{
		det*=result.sort();
		det*=result.LeadingOne();

		if (result.Data[row][col] == 0)
		{
			col++;
			if (col < colCount)break;
		}
		for (int i = row + 1; (i<rowCount) && (result.Data[i][col] == 1); i++)
		{
			for (int j = col; j < colCount; j++)
			{
				result.Data[i][j] -= result.Data[row][j];
			}
		}
	}	

	for (int index = 0; index < rowCount; index++)
	{
		det *= result.Data[index][index];
	}

	return det;

}

Matrix Matrix::Adjoint()
{
	Matrix result;
	bool error = 0;
	result.rowCount = rowCount;
	result.colCount = colCount;

	for (int col = 0; col < colCount; col++)
	{
		std::vector<double> tempArray;
		for (int row = 0; row < rowCount; row++)
		{
			Matrix temp;
			temp.rowCount = rowCount - 1;
			temp.colCount = colCount - 1;
			//-------------------------------------填要計算det的矩陣
			for (int i = 0; i < rowCount; i++)
			{
				std::vector<double> tempArray2;
				for (int j = 0; j < colCount; j++)
				{
					//矩陣為row列col行不填
					if ((i != row) && (j != col))
					{
						tempArray2.push_back(Data[i][j]);
					}
				}
				if (!tempArray2.empty())
				{
					temp.Data.push_back(tempArray2);
					tempArray2.clear();	
				}			
			}
			//算出det後填入結果矩陣
			tempArray.push_back(temp.det(error)*std::pow(-1,row+col));
		}
		result.Data.push_back(tempArray);
		tempArray.clear();
	}

	return result;
}

Matrix Matrix::Inverse()
{
	double zero = 0;

	Matrix result;
	result.rowCount = rowCount;
	result.colCount = colCount;

	if (rowCount != colCount)
	{
		result.Error = true;
		return result;
	}
	if (Rank() != rowCount)
	{
		result = *this;
		for (int row = 0; row < rowCount; row++)
		{
			for (int col = 0; col < colCount; col++)
			{
				result.Data[row][col] = double(1.0/zero);
			}
		}
		return result;
	}

	Matrix AugmentedMatrix;

	AugmentedMatrix.rowCount = rowCount;
	AugmentedMatrix.colCount = colCount*2;

	for (int row = 0; row < rowCount; row++)
	{	
		std::vector<double> tempArray;
		int col = 0;
		for (; col < colCount; col++)
		{
			tempArray.push_back(Data[row][col]);

		}

		for (; col < AugmentedMatrix.colCount; col++)
		{
			tempArray.push_back(col-colCount==row?1:0);
		}
		AugmentedMatrix.Data.push_back(tempArray);
		tempArray.clear();
	}
	AugmentedMatrix = AugmentedMatrix.RowReduction();
	
	for (int row = 0; row < rowCount; row++)
	{
		std::vector<double> tempArray;	
		for (int col = 0; col < colCount; col++)
		{
			tempArray.push_back(AugmentedMatrix.Data[row][col+colCount]);
		}		
		result.Data.push_back(tempArray);
		tempArray.clear();
	}

	return result;
}


//解一元三次式
double f(double x,double a, double b, double c, double d)
{
	double temp;
	temp = ((a*x + b)*x + c)*x + d;
	return temp;
}
std::vector<double> solveEquation(double a, double b, double c, double d)
{			
		std::vector<double> x;
		int t = -1;
		int i = 0;
		double u=0, v = 0;
		
		for (i = -10000; i <= 10000; i++)
		{
			u = double(i);
			v = u + 0.99999;
			if (fabs(f(u,a,b,c,d))<0.00001 || f(u,a,b,c,d)*f(v,a,b,c,d) <= 0)
			{
				t++;
				if (fabs(f(u,a,b,c,d))<0.00001)
					x.push_back( u);
				else
				{
					while ((u + 0.001<v) && fabs(f((u + v) / 2,a,b,c,d)) >= 0.00001)
					{
						if (f(u,a,b,c,d)*f((u + v) / 2,a,b,c,d)<0)
							v = (u + v) / 2;
						else
							u = (u + v) / 2;
					}
					x[t] = (u + v) / 2;
				}
			}
		}

		return x;
}
Matrix Matrix::eigen()
{
	Matrix result;

	if (rowCount != colCount)
	{
		result.Error = true;
		return result;
	}

	/*
	
	a-x b 
	c  d-x
	 (a-x)(d-x)-b*c =(a*d-b*c)+(-a-d)x+(1)x^2
	 
	 a=1
	 b=-a-d
	 c=a*d-b*c
	
	*/

	if (rowCount == 2)
	{
		result.rowCount = 4;
		result.colCount = 2;

		//-----------------------------------------------------------------------count eigen value
		double a = 1;
		double b = -(Data[0][0] + Data[1][1]);
		double c = Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
		double delta = std::pow(b, 2) - 4 * a*c;

		if (delta < 0)
		{
			result.Error = true;
			return result;
		}

		std::vector<double> values;
		values.push_back((-b + std::pow(delta, 0.5)) / (2 * a));
		values.push_back((-b - std::pow(delta, 0.5)) / (2 * a));
		//-----------------------------------------------------------------------sovle ax=0		
		//create 0
		Matrix allZeroMatrix;
		allZeroMatrix.rowCount = rowCount;
		allZeroMatrix.colCount = 1;
		allZeroMatrix.Data = std::vector<std::vector<double>>{ {0,0},{0,0}};

		Matrix eigenVectors;
		Matrix eigenValues;
		for (int index = 0, valueCount = 0, valuecount; index < values.size(); index++)
		{
			Matrix temp = *this;
			temp.Data[0][0] -= values[index];
			temp.Data[1][1] -= values[index];	

			Matrix tempEigenVector;
			tempEigenVector = SolveLinarSystem(temp, allZeroMatrix);

			// push_back eigenvector
			for (int i = 0; i < tempEigenVector.Data.size(); i++)
			{
				std::vector<double> temp;
				for (int c = 0; c < valueCount; c++)
				{
					temp.push_back(0);
				}
				temp.push_back(values[index]);
				valueCount++;
				for (int c = valueCount; c < tempEigenVector.colCount; c++)
				{
					temp.push_back(0);
				}
				eigenValues.Data.push_back(temp);
				temp.clear();
			}

			//push_back eigenvalue
			for (std::vector<double> v : tempEigenVector.Data)
			{
				eigenVectors.Data.push_back(v);
			}
		}
		eigenVectors.rowCount = eigenVectors.Data.size();
		eigenVectors.colCount = eigenVectors.Data[0].size();
		//------------------------------------------------------------------------	
		for (int row = 0; row < 2; row++)
		{
			for (int type = 0; type < 2; type++)
			{
				double length;
				if (!type)length = 0;
				for (int index = 0; index < 2; index++)
				{
					if (!type) length += powl(eigenVectors.Data[row][index], 2);
					if (type)eigenVectors.Data[row][index] /= powl(length, 1.0 / 2);

				}
			}
		}

		eigenVectors = eigenVectors.Transpose();

		result.Data.push_back(std::vector<double>(eigenVectors.Data[0]));
		result.Data.push_back(std::vector<double>(eigenVectors.Data[1]));

		result.Data.push_back(std::vector<double>(eigenValues.Data[0]));
		result.Data.push_back(std::vector<double>(eigenValues.Data[1]));

		//----------------------------------------------------------------------
		result.rowCount = 4;
		result.colCount = 2;



		return result;
	}
	else if (rowCount == 3)
	{
		/*
		1-x 2 3
		4 5-x 6
		7 8  9-x

		(1-x)(5-x)(9-x)+2*6*7+3*4*8-((1-x)*6*8+(5-x)*3*7+(9-x)*2*4)
		=(-x)^3+(1+5+9)x^2-(9*5+9*1+5*1)x+1*5*9-(1*6*8-6*8x+5*3*7-3*7x+9*2*4-2*4x)
		=(-x)^3+(1+5+9)x^2-(9*5+9*1+5*1+6*8+3*7+2*4)x+1*5*9++2*6*7+3*4*8-1*6*8-5*3*7-9*2*4
		*/
		result.rowCount = 6;
		result.colCount = 3;
		//-----------------------------------------------------------------------count eigen value
		double a = -1;
		double b = Data[0][0] + Data[1][1] + Data[2][2];
		double c = -(Data[2][2] * Data[1][1] + Data[2][2] * Data[0][0] + Data[0][0] * Data[1][1] - Data[1][2] * Data[2][1] \
			- Data[0][2] * Data[2][0] - Data[0][1] * Data[1][0]);
		double d = Data[0][0] * Data[1][1] * Data[2][2] + Data[0][1] * Data[1][2] * Data[2][0] + Data[0][2] * Data[1][0] * Data[2][1] \
			- Data[0][0] * Data[1][2] * Data[2][1] - Data[1][1] * Data[0][2] * Data[2][0] - Data[2][2] * Data[0][1] * Data[1][0];

		std::vector<double> values;

		values = solveEquation(a, b, c, d);
		//-----------------------------------------------------------------------sovle ax=0

		//create 0 Matrix
		Matrix allZeroMatrix;
		allZeroMatrix.rowCount = rowCount;
		allZeroMatrix.colCount = 1;

		allZeroMatrix.Data.push_back(std::vector<double>{0});
		allZeroMatrix.Data.push_back(std::vector<double>{0});
		allZeroMatrix.Data.push_back(std::vector<double>{0});

		Matrix eigenVectors;
		Matrix eigenValues;
		for (int index = 0, valueCount = 0, valuecount; index < values.size(); index++)
		{
			Matrix temp = *this;
			temp.Data[0][0] -= values[index];
			temp.Data[1][1] -= values[index];
			temp.Data[2][2] -= values[index];

			Matrix tempEigenVector;
			tempEigenVector = SolveLinarSystem(temp, allZeroMatrix);

			// push_back eigenvector
			for (int i = 0; i < tempEigenVector.Data.size(); i++)
			{
				std::vector<double> temp;
				for (int c = 0; c < valueCount; c++)
				{
					temp.push_back(0);
				}
				temp.push_back(values[index]);
				valueCount++;
				for (int c = valueCount; c < tempEigenVector.colCount; c++)
				{
					temp.push_back(0);
				}
				eigenValues.Data.push_back(temp);
				temp.clear();
			}

			//push_back eigenvalue
			for (std::vector<double> v : tempEigenVector.Data)
			{
				eigenVectors.Data.push_back(v);
			}
		}
		eigenVectors.rowCount = eigenVectors.Data.size();
		eigenVectors.colCount = eigenVectors.Data[0].size();

		for (int row = 0; row < 3; row++)
		{
			for (int type = 0; type < 2; type++)
			{
				double length;
				if (!type)length = 0;
				for (int index = 0; index < 3; index++)
				{
					if (!type) length += powl(eigenVectors.Data[row][index], 2);
					if (type)eigenVectors.Data[row][index] /= powl(length, 1.0 / 2);

				}
			}
		}
				
		eigenVectors = eigenVectors.Transpose();
		
		result.Data.push_back(std::vector<double>(eigenVectors.Data[0]));
		result.Data.push_back(std::vector<double>(eigenVectors.Data[1]));
		result.Data.push_back(std::vector<double>(eigenVectors.Data[2]));

		result.Data.push_back(std::vector<double>(eigenValues.Data[0]));
		result.Data.push_back(std::vector<double>(eigenValues.Data[1]));
		result.Data.push_back(std::vector<double>(eigenValues.Data[2]));

		//----------------------------------------------------------------------
		result.rowCount = 6;
		result.colCount = 3;

		

		return result;
	}

	return result;
}

Matrix Matrix::PowerMethod()
{
	Matrix result;

	if (rowCount != colCount)
	{
		result.Error = true;
		return result;
	}

	result.rowCount = rowCount*2;
	result.colCount = colCount;
	for (int row = 0; row < result.rowCount; row++)
	{
		result.Data.push_back(std::vector<double>{});
	}

	Matrix zeroMatrix;
	Matrix initialGuess;
	Matrix processing;
	zeroMatrix.rowCount = rowCount;
	zeroMatrix.colCount = 1;
	processing.rowCount = rowCount;
	processing.colCount = 1;
	initialGuess.rowCount = rowCount;
	initialGuess.colCount = 1;

	for (int row = 0; row < rowCount; row++)
	{
		initialGuess.Data.push_back(std::vector<double>{1});
		zeroMatrix.Data.push_back(std::vector<double>{0});
		processing.Data.push_back(std::vector<double>{1});
	}

	Matrix B = *this;

	for (int i = 0; i < rowCount; i++)
	{
		do
		{
			initialGuess = processing;
			processing = B * initialGuess;

			double length = 0;
			double LeadingPositive = (processing.Data[0][0] < 0 ? -1 : 1);
			for (int i = 0; i < 2; i++)
			{
				if (!i)length = 0;
				for (int row = 0; row < rowCount; row++)
				{
					if (!i)length += powl(processing.Data[row][0], 2);
					else
					{
						processing.Data[row][0] /= powl(length, 1.0 / 2);
						processing.Data[row][0] *= LeadingPositive;
					}
				}
			}

		} while (!((processing - initialGuess) == zeroMatrix));

		double eigenvalue = ((B*processing).Transpose()*processing).Data[0][0] / (processing.Transpose()*processing).Data[0][0];
	
		B = B - (eigenvalue*(processing*processing.Transpose()));
		
		
		for (int row = 0; row < B.rowCount; row++)
		{
			result.Data[row].push_back(processing.Data[row][0]);
		}
		for (int row = rowCount; row < result.rowCount; row++)
		{
			if (row - rowCount == i)
				result.Data[row].push_back(eigenvalue);
			else
				result.Data[row].push_back(0.0);
		}

	}
	
	return result;
}

Matrix LeastSquare(Matrix&  a, Matrix& b)
{
	Matrix x = a.Transpose() * a;
	
	Matrix result=x.Inverse()*a.Transpose()*b;

	result.colCount = 1;
	result.rowCount = a.colCount;

	return result;
}


Matrix::Matrix(std::vector<double> m)
{
	colCount = sqrt(m.size());
	rowCount = m.size()/colCount;

	for (int row = 0; row < rowCount; row++)
	{
		std::vector<double> tempDatas;
		for (int col = 0; col < colCount; col++)
		{
			double value;
			value=m[row*(colCount)+col];
			tempDatas.push_back(value);
		}
		Data.push_back(tempDatas);
		tempDatas.clear();
	}
	
	Error = 0;
}
Matrix operator/(const Matrix& a, const Matrix& b)
{
	Matrix result = a;
	if (b.rowCount == 1 && b.colCount == 1)

		for (int i = 0; i < result.rowCount; i++)
		{
			for (int j = 0; j < result.colCount; j++)
			{
				result.Data[i][j] /= b.Data[0][0];
			}
		}

	return result;
}