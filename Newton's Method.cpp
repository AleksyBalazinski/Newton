// Copyright © 2019 by Aleksy Bałaziński 
// Permission is granted to freely distribute this file in any form for personl and educational use,
// provided this copyright notice is not removed. Commercial use is prohibited.

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	string equation;
	cout << "              **** Welcome to a root finding program! ****\n";
	cout << "Input equation you struggle to solve in a following way \n";
	cout << "Make sure that every x is preluded by a coefficient, even if it is equal to 1 \n";
	cout << "Also, every x should have an exponent, even if it is equal to 0 \n";
	getline(cin, equation, '=');
	int cnt = 0;
	int eq_length = equation.length();
	for (int i = 0; i <= eq_length; i++)
	{
		if (equation[i] == 'x') cnt++;
	}
	cout << "number of x's = " << cnt << "\n";
	string equation1 = equation + "+";
	double* coef = new double[cnt];
	double* exp = new double[cnt];
	for (int i = 0; i <= cnt - 1; i++)
	{
		int x_pos = equation1.find('x');
		coef[i] = stod(equation1.substr(0, x_pos));
		equation1.erase(0, x_pos + 2);
		int plus_pos = equation1.find('+');
		int minus_pos = equation1.find('-');
		if (plus_pos < minus_pos)
		{
			if (plus_pos != string::npos)
			{
				exp[i] = stod(equation1.substr(0, plus_pos));
				equation1.erase(0, plus_pos);
			}
			else
			{
				exp[i] = stod(equation1.substr(0, minus_pos));
				equation1.erase(0, minus_pos);
			}
		}
		else
		{
			if (minus_pos != string::npos)
			{
				exp[i] = stod(equation1.substr(0, minus_pos));
				equation1.erase(0, minus_pos);
			}
			else
			{
				exp[i] = stod(equation1.substr(0, plus_pos));
				equation1.erase(0, plus_pos);
			}
		}
	}
	//test
	for (int i = 0; i <= cnt - 1; i++)
	{
		cout << "coefficient no. " << i << ": " << coef[i] << "\n";
		cout << "exponent no. " << i << ": " << exp[i] << "\n";
	}
	cin.get();
	cout << "specifying the interval \n";
	cout << "enter the beginning (integer)\n";
	double a;
	cin >> a;
	cout << "enter the end (integer)\n";
	double b;
	cin >> b;
	int N = 10 * (b - a); //that's how many iterations we want, thus step = 0.1
	//we'll be generating x1's in the following loop, starting at x1=a, then x1=a+0.1, etc.
	double x1, pol_vl, der_vl;
	double* zeros = new double[N];
	pol_vl = 0;
	der_vl = 0;
	x1 = 0;
	for (int t = 0; t < N; t++)
	{
		x1 = a + 0.1 * t;
		for (int k = 0; k <= 999; k++) //Take sth bigger than "999" for better accuracy
		{
			pol_vl = 0;
			der_vl = 0;
			for (int i = 0; i <= cnt - 1; i++)
			{
				pol_vl = coef[i] * pow(x1, exp[i]) + pol_vl;
			}
			for (int i = 0; i <= cnt - 1; i++)
			{
				der_vl = coef[i] * exp[i] * pow(x1, exp[i] - 1) + der_vl;
			}
			if (der_vl != 0)
			{
				x1 = x1 - pol_vl / der_vl;
			}
			else
			{
				break;
			}
		}
		zeros[t] = x1;
	}
	//we're too precise
	for (int k = 0; k < N; k++) 
	{
		zeros[k] = zeros[k] * 1000; //multiply by sth bigger for better accuracy
		zeros[k] = round(zeros[k]);
		zeros[k] = zeros[k] / 1000;
	}
	//there are some weird results (namely NaN characters due to mathematical faux pas such as dividing by zero)
	//Nan Killer
	for (int k = 0; k < N; k++)
	{
		if (zeros[k] != zeros[k]) zeros[k] = zeros[k - 1];
	}
	//In most cases numbers in zeros[] array are already sorted, however, not always.
	//Thus we use a sorting algorithm (we're using that one from <algorithm> library)
	//because this code would take forever otherwise (Not a cheat! Not at all!)
	sort(zeros, zeros + N);
	//now we shall remove all duplicates from our zeros[] array
	//Dupicate Killer 
	double pivot = zeros[0];
	double nope = 12345; //some random number, really
	for (int k = 1; k <= N - 1; k++)
	{
		if (zeros[k] == pivot)
		{
			zeros[k] = nope;
		}
		else
		{
			pivot = zeros[k];
		}
	}
	int cnt1 = 0;
	for (int k = 0; k < N; k++)
	{
		if (zeros[k] != nope) cnt1++;
	}
	double* uni = new double[cnt1];
	int cnt2 = 0;
	for (int k = 0; k < N; k++)
	{
		if (zeros[k] != nope)
		{
			uni[k - cnt2] = zeros[k];
		}
		else
		{
			cnt2++;
		}
	}
	if (cnt1 > exp[0]) //I don't know what's wrong, but works fine
	{
		cout << "No real roots found!";
	}
	else
	{
		cout << "\nRoots found: \n";
		for (int k = 0; k < cnt1; k++)
		{
			cout << uni[k] << "\n";
		}
	}

	delete[] zeros;
	delete[] uni;
	delete[] coef;
	delete[] exp;
}
