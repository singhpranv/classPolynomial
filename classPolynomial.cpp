/*classPolynomial.cpp : Defines a class polynomial, of any degree, 
// with overloaded operators <<,>>,+,-,*,/,==,%
// and a function getDergree() to get the the degree of polynomial
// written by -Pranav Singh (www.github.com/singhpranv) 
*/


#include<iostream>

using namespace std;


// class declaration

class polynomial
{
public:
	polynomial(int);
	int getDegree();

	friend ostream& operator <<(ostream&, polynomial&);
	friend istream& operator >>(istream&, polynomial&);

	bool operator == (polynomial) const;
	
	polynomial operator + (polynomial) const;
	polynomial operator - (polynomial) const;
	polynomial operator * (polynomial) const;
	polynomial operator / (polynomial) const;
	polynomila operator % (polynomial) const;
	
	~polynomial();

private:
	double *coefficents;
	int trueDegree, degree;

};

// definition of function getDegree() to get the degree of polynomial, i.e the highest power of x that exists with a non zero coefficent

int polynomial::getDegree()
{
	for (int i = degree; i >= 0; i--) 	
		if (coefficents[i] != 0)
		{
			trueDegree = i;
			return i;
		}

	return 0;
}

// constructor for polynomial, which takes degree of the polynomial as parameter, creates a array of coefficents, and assigns 0 to each one of them

polynomial::polynomial(int a)
{
	degree = a;
	coefficents = new double[degree+1];
	for (int i = 0; i < degree + 1; i++) coefficents[i] = 0;
}

// destructor

polynomial::~polynomial()
{
	
}

// definition of a overridien == (equal to) operator

bool polynomial::operator==(polynomial secondPoly) const
{
	if (trueDegree != secondPoly.trueDegree) return 0;

	for (int i = trueDegree; i >= 0; i--) if (coefficents[i] != secondPoly.coefficents[i]) return 0;

	return 1;

}

// definition overridden insertion operator to take input

istream & operator>>(istream& streamLoc, polynomial &polyLoc)
{   


	cout << "Enter the coefficents of the terms as asked \n";
	for (int i = polyLoc.degree; i >= 0; i--)
	{
		cout << "x^" << i << "\t";
		streamLoc >> polyLoc.coefficents[i];
	}

	polyLoc.trueDegree = polyLoc.getDegree();

	return streamLoc;
	
}

// definition of overridden extraction operator to print the polynomial

ostream& operator << (ostream& streamLoc, polynomial& polyLoc)
{
	if (polyLoc.trueDegree != 0)
	{
		if(polyLoc.coefficents[polyLoc.degree] != 1)  streamLoc << polyLoc.coefficents[polyLoc.degree];
		streamLoc << "x^" << polyLoc.degree;
	}


	for (int i = polyLoc.trueDegree - 1; i > 0; i--)
	{
		if (polyLoc.coefficents[i] == 1)    	streamLoc << " +x^" << i;
		else if (polyLoc.coefficents[i] > 0)    streamLoc << " +" << polyLoc.coefficents[i] << "x^" << i;
		else if (polyLoc.coefficents[i] < 0)	streamLoc << " " << polyLoc.coefficents[i] << "x^" << i;
	}

	if (polyLoc.coefficents[0] != 0) cout << " +" << polyLoc.coefficents[0];

	streamLoc << endl;

	if (polyLoc.trueDegree == 0 && polyLoc.coefficents[0] == 0) cout << "0\n";

	return streamLoc;
}

//definition of overridden addition (+) operator

polynomial polynomial::operator+(polynomial secondPoly) const
{
	int tempDegree;

	if (degree > secondPoly.degree) tempDegree = degree;
	else tempDegree = secondPoly.degree;

	polynomial tempPoly(tempDegree);

	for (int i = tempPoly.degree; i >= 0; i--)
	{
		if ( ( i <= degree) && (i <= secondPoly.degree))
			{
				tempPoly.coefficents[i] = coefficents[i] + secondPoly.coefficents[i];
			}
		else if (i<=degree && i>secondPoly.degree)
		{
			tempPoly.coefficents[i] = coefficents[i];
	    }
		else 
		{
			tempPoly.coefficents[i] = secondPoly.coefficents[i];
		}
	}

	tempPoly.trueDegree = tempPoly.getDegree();
	return tempPoly;
}

//definition of overridden subtraction (-) operator

polynomial polynomial::operator-(polynomial secondPoly) const
{
	int tempDegree;
	if (degree > secondPoly.degree) tempDegree = degree;
	else tempDegree = secondPoly.degree;

	polynomial tempPoly(tempDegree);

	for (int i = tempPoly.degree; i >= 0; i--)
	{
		if ((i <= degree) && (i <= secondPoly.degree))
		{
			tempPoly.coefficents[i] = coefficents[i] - secondPoly.coefficents[i];
		}
		else if (i <= degree && i>secondPoly.degree)
		{
			tempPoly.coefficents[i] = coefficents[i];
		}
		else
		{
			tempPoly.coefficents[i] = 0-secondPoly.coefficents[i];
		}
	}

	tempPoly.trueDegree = tempPoly.getDegree();
	return tempPoly;
}

//definition of overridden multiplication (*) operator

polynomial polynomial::operator*(polynomial secondPoly) const
{
	int tempDegree;
	tempDegree = degree + secondPoly.degree;

	polynomial tempPoly(tempDegree);

	for (int i = 0; i <= degree; i++)
	{
		for (int j = 0; j <= secondPoly.degree; j++)
		{
			tempPoly.coefficents[i + j] = tempPoly.coefficents[i+j] + (coefficents[i] * secondPoly.coefficents[j]);
		}
	}

	tempPoly.trueDegree = tempPoly.getDegree();
	return tempPoly;
}


//definition of overridden division (-) operator

polynomial polynomial::operator/(polynomial secondPoly) const
{
	polynomial empty(0);
	empty.trueDegree = empty.getDegree();
	
	if (trueDegree < secondPoly.trueDegree) return empty;

	polynomial quotient(trueDegree - secondPoly.trueDegree), remainder(trueDegree), tempPoly(trueDegree);
	
	for (int i = trueDegree; i >= 0; i--) remainder.coefficents[i] = coefficents[i];

	if (remainder == secondPoly)
	{
		quotient.coefficents[0] = 1;
		goto divide;
	}
	
	quotient.coefficents[trueDegree - secondPoly.trueDegree] = coefficents[trueDegree]/secondPoly.coefficents[secondPoly.trueDegree];

divide:	
	tempPoly = quotient * secondPoly;
	remainder = remainder - tempPoly;
	quotient = quotient + (remainder / secondPoly);

	quotient.trueDegree = quotient.getDegree();
	return quotient;
}

//definition of overridden remainder (%) operator

polynomial polynomial::operator%(polynomial secondPoly) const
{
	polynomial remainder(trueDegree),tempPoly(trueDegree);

	for (int i = trueDegree; i >= 0; i--)   remainder.coefficents[i] = coefficents[i];
		
    
	if (trueDegree < secondPoly.trueDegree)  goto theEnd;

	{
		polynomial  quotient(trueDegree - secondPoly.trueDegree);

		if (remainder == secondPoly)
		{
			quotient.coefficents[0] = 1;
			goto divide;
		}

		quotient.coefficents[trueDegree - secondPoly.trueDegree] = coefficents[trueDegree] / secondPoly.coefficents[secondPoly.trueDegree];

	divide:
		tempPoly = quotient * secondPoly;
		remainder = remainder - tempPoly;

		remainder = (remainder%secondPoly);

	}

theEnd:
	remainder.trueDegree = remainder.getDegree();
	return remainder;
}



