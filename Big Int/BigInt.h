/******************************************************************************************************
FileName: BigInt.h
Coded By: Joe Gelsomini
date completed: 11/10/18
Time spent:parts 1-3 could be tough, but I fell i overcame the challenges, part 4 on the other hand was quite brutal. Even after
testing division and modulo im still unsure of how confident I am in saying that it works 100% of the time. As the assignments progressed
I found myself spending more time then I did on the previous assignment, although I suppose these assignments were designed that way...
Purpose of this assignment: Practice with operator overloading. I am a master now...
Challenges: I dont want to talk about them... but believe me there were many.
*******************************************************************************************************/
#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include<stdexcept>

class BigInt
{
public:
	BigInt(); // Initializes the BigInt to zero.
	BigInt(int x); //Initializes the BigInt to have the same value as x
	explicit BigInt(std::string x);//Initalizes the BigInt to have the value of the given string BUT
									//must check that the string is valid or exit(1) otherwise.
	friend std::ostream& operator<<(std::ostream& out, const BigInt& right);

	/////////////////////////part 2 functions////////////////////////
	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend bool operator<(const BigInt& left, const BigInt& right);
	/////////////////////////end part 2 functions/////////////////////

	/////////////////////////part 3 functions///////////////////////////////
	friend BigInt operator*(const BigInt& left, const BigInt& right);
	friend bool operator>(const BigInt& left, const BigInt& right);
	friend bool operator==(const BigInt& left, const BigInt& right);
	//////////////////////end part 3 functions///////////////////////////////

	//////////////////////part 4 functions///////////////////////////////////
	friend BigInt operator/(const BigInt& left, const BigInt& right);
	friend BigInt operator%(const BigInt& left, const BigInt& right);
	//////////////////////end part 4 functions///////////////////////////////

private:
	std::string data; //string representing the BigInt, will be stored internally in reverse order for greater
						//ease of implementing operations such as + , - , * , /
	bool isNegative; //true if (BigInt < 0)

};

#endif