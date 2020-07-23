#include <iostream>
#include <sstream>
#include "BigInt.h"
using namespace std;


bool test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred();
bool test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred_with_string_constructor();
bool test_carry_over_40_digits();
bool test_for_negative_zero();

int main()
{
	BigInt a;
	BigInt b;
	a = BigInt("100");
	b = BigInt("3");
	//cout << a / b << endl;
	//a / b;
	string s = "1";
	for (int j = 0; j < 100; j++)
	{
		s.push_back('0');
	}
	a = BigInt(s);
	a / 12345678;

	cout << a << endl << " / " << endl << 12345678 << endl << " = "
		<< a / 12345678;


	if (test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred())
	{
		cout << "You win so far..." << endl;
	}
	else
	{
		cout << "MUAHHAHAHAHAHHAHAH" << endl;
	}
	/*
	if (test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred_with_string_constructor())
	{
		cout << "You win so far..." << endl;
	}
	else
	{
		cout << "MUAHHAHAHAHAHHAHAH" << endl;
	}

	if (test_carry_over_40_digits())
	{
		cout << "Glen rules" << endl;
	}
	else
	{
		cout << "You are feeble" << endl;
	}
	if (test_for_negative_zero())
	{
		cout << "woo" << endl;
	}
	else
	{
		cout << "boo" << endl;
	}*/

	return 0;
}



bool test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred()
{	
	bool test_result = true;
	for (int i = 0; i <= 100; i++)
	{
		for (int j = 1; j <= 100; j++)
		{
			if (j > i)
				continue;

			BigInt bigI(i);
			BigInt bigJ(j);
			
			stringstream int_answer;
			stringstream big_answer;
			stringstream final_output;

			int_answer << i << "%" << j << "=" << i % j;
			big_answer << bigI << "%" << bigJ << "=" << bigI % bigJ;
			//cout << int_answer.str() << endl;
			cout << big_answer.str() << endl;
			if (int_answer.str() != big_answer.str())
			{
				cout << "Everything is deborken when i is " << i << " and j is " << j << endl;
				cout << "Expected:	" << int_answer.str() << endl
							 <<  "Got:		" << big_answer.str() << endl;
				return false;
				test_result = false;
			}
			int_answer.clear();
			big_answer.clear();
		}
	}
	return test_result;
}

bool test_all_pairs_addition_negative_one_hundred_to_positive_one_hundred_with_string_constructor()
{
	for (int i = -100; i <= 100; i++)
	{
		for (int j = -100; j <= 100; j++)
		{
			if (j == 0)
				continue;
			BigInt bigI(to_string(i));
			BigInt bigJ(to_string(j));
			stringstream int_answer;
			stringstream big_answer;

			int_answer << i << "/" << j << "=" << i / j;
			big_answer << bigI << "/" << bigJ << "=" << bigI / bigJ;
			cout << int_answer.str() << endl;
			cout << big_answer.str() << endl;
			if (int_answer.str() != big_answer.str())
			{
				cout << "Everything is deborken when i is " << i << " and j is " << j << endl;
				return false;
			}
			int_answer.clear();
			big_answer.clear();
		}
	}
	return true;
}

bool test_carry_over_40_digits()
{
	BigInt a("9999999999999999999999999999999999999999");
	string answer = "10000000000000000000000000000000000000000";
	BigInt b("1");

	stringstream big_answer;
	big_answer << a + b;
	if (answer == big_answer.str())
	{
		return true;
	}
	return false;
}

bool test_for_negative_zero()
{
	BigInt a("-123456789123456789123456789123456789");
	BigInt b("123456789123456789123456789123456789");
	string answer = "0";
	stringstream big_answer;
	big_answer.clear();
	big_answer << a + b;
	bool result = true;

	if (answer != big_answer.str())
	{
		result = false;
	}
	big_answer.str("");
	big_answer << b + a;
	if (answer != big_answer.str())
	{
		result = false;
	}

	BigInt c("-0");
	BigInt d("-0");

	big_answer.str("");
	big_answer << c + d;
	if (answer != big_answer.str())
	{
		cout << answer << endl;
		cout << "vs." << endl;
		cout << big_answer.str() << endl;
		result = false;
	}
	big_answer.str("");
	big_answer << d + c;
	if (answer != big_answer.str())
	{
		cout << answer << endl;
		cout << "vs." << endl;
		cout << big_answer.str() << endl;
		result = false;
	}
	return result;

}