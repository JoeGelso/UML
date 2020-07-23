//Documentation found in the BigInt.h
//This file contains the implementations for parts 1-4
#include"BigInt.h"

////////////////////helper functions////////////////////////

	//pops back all trailing zeroes in our data past index 1
	void trim_trailing_zeroes(std::string& data); 

	//absolute value of left (<, >, or = ) absolute value of right?
	char comp_abs_val(std::string l, std::string r); 

	// "adds" 2 numeric strings and returns result
	std::string string_addition(std::string l, std::string r); 

	// "subtracts" 2 numeric strings and returns result.
	//char argument indicates which string has greater absolute value
	//will also indicate if they are equivalent in abs value
	std::string string_subtraction(std::string l, std::string r, char comp_abs_val_result);

BigInt::BigInt()
{
	data = "0";
	//no need to reverse data of a single char

	isNegative = false;//if true, display "-" in front of data when prining, leave false for 0 so we dont print "-0"
	return;
}//end default constructor

BigInt::BigInt(int x)
{
	//determine if + or -
	if (x < 0)
	{
		isNegative = true;
		x *= -1;//get rid of minus sign before converting to string
	}
	else
		isNegative = false;


	//convert int to string
	data = std::to_string(x);

	//store the string internally in reverse order for greater ease of operation implementation
	std::reverse(data.begin(), data.end());

	return;
}//end single int constructor

BigInt::BigInt(std::string x)
{
	int i;
	data = "";
	//check for whitespaces, once a +,-, or digit is found we will exit and process with next loop
	for (i = 0; i < x.size(); i++)
	{
		if (isspace(x[i]))
			continue;//if a whitespace, continue searching for first nonspace char
		else
			break;//if a nonspace char is found, finish processing w/ new loop
	}//end first loop: x[i] is the first non whitespace char

	 //ensure x[i] is either a digit, +, or -
	 //ugly if condition, if x[i] is a digit, or if x[i] is a +, -, continue checking the rest of x
	if (!(isdigit(x[i]) || (x[i] == '+' || x[i] == '-')))
	{
		//condition inside previous if() is negated, if conditions weren't made we end the procedure
		std::cout << "exiting after failure to create big int";
		exit(1);
	}

	//update isNegative if x[i] were a + or -
	if (x[i] == '-')
		isNegative = true;
	else if (x[i] == '+')
		isNegative = false;
	else
	{
		data += x[i];//concat to data if a digit
		isNegative = false;
	}


	i++;//update the index

		//continue searching, all proceding chars must be digits and added to data
		//dont stop adding until we hit the end of the string, or a whitespace
		//we fail if we detect a non digit
	for (i; i < x.size(); i++)
	{

		if (isdigit(x[i]))
			data += x[i];//concat the digit char onto our data
		else if (isspace(x[i]))
			break;//exit loop, we are done
		else
		{
			//end procedure if x[i] is not a digit
			std::cout << "exiting after failure to create big int";
			exit(1);
		}//end fail condition

	}//end 2nd for loop: data has all digit chars succesfully concatted to it

	 //could be the case the string: "    -  ", or something similair were passed.
	 //If this were the case, data should be empty, we will interpret this as zero instead of failure
	 //***********Possibility this may have to be changed to failure*******************
	if (data.empty())
	{
		std::cout << "There is no data! exiting" << std::endl;
		exit(1);
		//data = "0";
		//isNegative = false;//no negative zeros allowed!
	}

	//store the string internally in reverse order for greater ease of operation implementation
	std::reverse(data.begin(), data.end());

	//should we trim trailing zeros? (trailing rather then leading because string stored in reverse)
	trim_trailing_zeroes(data);
	if (data == "0")
		isNegative = false;

	return;
}//end string constructor


std::ostream& operator<<(std::ostream& out, const BigInt& right)
{
	int len = right.data.length() - 1;
	if (right.isNegative)
		out << "-";
	//string stored in reverse internally
	//we must print this internal string in reverse to get expected output
	for (int i = 0; (len - i) >= 0; i++)
		out << right.data.at(len - i);
	return out;
}//end insetion overload

 /////////////////////////part 2 functions////////////////////////

BigInt operator+(const BigInt& left, const BigInt& right)
{
	BigInt result; //the result to be returned
	result.data = "";

	//will be '<': if abs(l) < abs(r); '>' if abs(l) > abs(r); and '=' if abs(l) == abs(r)
	char comp_abs_val_result = comp_abs_val(left.data, right.data);

	//4 possible cases: (a + b), (a + -b), (-a + b), (-a  + -b)
	//cases where the sign of the arguments differ, this behaves like subtraction
	//when signs are the same, this is normal addition

	//(a + b) or (-a + -b):
	if (left.isNegative == right.isNegative)
	{
		//sign of result should match that of both args
		result.isNegative = left.isNegative;
		result.data = string_addition(right.data, left.data);
		trim_trailing_zeroes(result.data);//unnecesary?
		return result;
	}
	//case 2: signs differ: -a + b, a + -b
	//this behaves like subtraction
	else if (left.isNegative != right.isNegative)
	{
		//result = left - right
		result.data = string_subtraction(left.data, right.data, comp_abs_val_result);
		trim_trailing_zeroes(result.data);

		//determine sign
		//2 new cases subacases for each case:
		//(-a + b) case 1: |-a| > |b|		new helper function for comparing absolute value?
		if (left.isNegative && !(right.isNegative) && comp_abs_val_result == '>')
			result.isNegative = true;
		//(-a + b) case 2: |-a| < |b|
		else if (left.isNegative && !(right.isNegative) && comp_abs_val_result == '<')
			result.isNegative = false;
		//(a + -b) case 1: |a| > |-b|
		else if (!(left.isNegative) && right.isNegative && comp_abs_val_result == '>')
			result.isNegative = false;
		//(a + -b) case 2: |a| < |-b|
		else if (!(left.isNegative) && right.isNegative && comp_abs_val_result == '<')
			result.isNegative = true;
		else// |-a| == |b| or |a| == |-b|, result is zero from subttraction
			result.isNegative = false;//no negative zeroes on my watch

		return result;
	}//end -a + b or a + -b
}//end addition overload

BigInt operator-(const BigInt& left, const BigInt& right)
{
	BigInt result; //the result to be returned
	result.data = "";

	//will be '<': if abs(l) < abs(r); '>' if abs(l) > abs(r); and '=' if abs(l) == abs(r)
	char comp_abs_val_result = comp_abs_val(left.data, right.data);

	//4 cases like addition (a - b), (-a - -b), (a - -b), and (-a - b)
	//similair to addition: cases where the signs match, it is normal subtraction
	//if signs differ, it is an addition 

	//signs match behaves as subtraction
	if (left.isNegative == right.isNegative)
	{
		//subtract lefts data from rights
		result.data = string_subtraction(left.data, right.data, comp_abs_val_result);
		trim_trailing_zeroes(result.data);

		//determine sign
		if (comp_abs_val_result == '<')//if the right operand is larger
		{
			//sign swaps
			result.isNegative = !(left.isNegative);
		}
		return result;
	}
	//signs do not match, behaves like an addition
	else if (left.isNegative != right.isNegative)
	{
		//"add" the 2 strings
		result.data = string_addition(left.data, right.data);
		trim_trailing_zeroes(result.data);

		//determine sign
		//2 new subacases for each case:
		//(-a - b) case 1: |-a| > |b|
		if (left.isNegative && !(right.isNegative) && comp_abs_val_result == '>')
			result.isNegative = true;
		//(-a - b) case 2: |-a| < |b|
		else if (left.isNegative && !(right.isNegative) && comp_abs_val_result == '<')
			result.isNegative = true;
		//(a - -b) case 1: |a| > |-b|
		else if (!(left.isNegative) && right.isNegative && comp_abs_val_result == '>')
			result.isNegative = false;
		//(a - -b) case 2: |a| < |-b|
		else if (!(left.isNegative) && right.isNegative && comp_abs_val_result == '<')
			result.isNegative = false;
		else// |-a| == |b| or |a| == |-b|, result is zero from subttraction
			result.isNegative = false;//no negative zeroes on my watch >:(
		return result;
	}
}//end subtraction overload

bool operator<(const BigInt& left, const BigInt& right)
{
	int left_index = left.data.length() - 1; //left's most significant digit
	int right_index = right.data.length() - 1; //right's most significant digit

											   //easiest cases: 1 arg is negative, 1 is positive
	if (left.isNegative != right.isNegative)
	{
		//we know the signs dont match
		if (left.isNegative)
			return true;//a negative is always less then a positive
		if (right.isNegative)
			return false;//a positive is never less than a negative
	}

	//signs do match
	if (left_index < right_index)//(left has less digits then right) -> (left < right)
		return true && !left.isNegative; //opposite is true if left and right are negative
	else if (left_index > right_index)//left has more digits, therefore left !< right
		return left.isNegative;//opposite is true if both were negative
	else//both opperands have equivalent number of digits
	{
		//we compare the most sig digits, but if they are the same:
		//compare the 2nd most sig digits
		//repeat until the sig digits we are comparing are unequal
		//return appropriate answer
		//if it is discovered that the numbers compared are equivalent, return false
		for (int i = left_index; i >= 0; i--)//chose to use lefts index, makes no difference since left == right
		{
			if (left.data[i] == right.data[i])
				continue;//these sig digits are the same, try the next most sig digits
			else
				if ((left.data[i] - '0') < (right.data[i] - '0'))//convert the chars to ints and compare
					return !left.isNegative;//true if positive, false if negative 
				else if ((left.data[i] - '0') > (right.data[i] - '0'))
				{
					return left.isNegative; //false if args were positive, true if they were negative
				}
		}//exited loop. this means arguments were the same
		return 0;
	}
}//end < overload
 /////////////////////////end part 2 functions/////////////////////

 /////////////////////////part 3 functions////////////////////////
BigInt operator*(const BigInt& left, const BigInt& right)
{
	int product = 0;//the product of 2 digits
	int carry = 0;//the amount of overflow from 2 single digits being multiplied
	std::string temp = "";//extra string to help sum the final result of a multiplication
	int l, r; //left's data index and right's data index
	BigInt result;
	result.data = "0";

	//we have a couple easy cases right off the bat, multiplication by either 1, -1 or 0

	//multiplication by zero
	if (left.data == "0" || right.data == "0")
		return BigInt();//no need to determine sign. default const inits a 0
						//multiplication by 1
	if (left.data == "1")
	{
		result.data = right.data;
	}
	else if (right.data == "1")
	{
		result.data = left.data;
	}
	else//neither left or right are equal to 1, -1 or zero:
	{
		//stay in bounds of the smaller argument and multiply the ones place of the first arg by the second args 1s,10s, 100s...
		//do this for the first args 10's place then 100's... while keeping a running total
		for (l = 0; l <= left.data.length() - 1; l++)//l is index of left
		{
			//before we go into the nested loop, temp will need to have some leading zeroes depending on the value of l
			for (int i = 0; i < l; i++)
				temp += "0";
			//also reset carry
			carry = 0;

			for (r = 0; r <= right.data.length() - 1; r++)//r is index of right
			{
				product = (left.data[l] - '0') * (right.data[r] - '0');//convert the chars to ints and multiply
				product += carry;//add the last carry to the product from the 2 digits
				carry = product / 10; //take the carry out of the product

									  /*if (carry > 9)
									  std::cout << "CARRY IS " << carry;*/

				product %= 10; //the product is a single digit
				temp += std::to_string(product);//put this result onto our data
			}//exited inner loop multiplied left[l] by all digits in right

			 //concat the final carry if it was greater than 0
			if (carry > 0)
				temp += std::to_string(carry);
			trim_trailing_zeroes(temp);//trim any trailing zeroes from temp
			result.data = string_addition(result.data, temp);//add to our running total
			temp = "";//clean up temp before jumping back in
		}//exited outter loop... we are done multiplying
	}//end else

	 //result.data should have the correct value of left * right
	 //determine sign:
	 //signs do not match:
	if (left.isNegative != right.isNegative)
		result.isNegative = true;// negative times a positive is a negative
	else if (left.isNegative == right.isNegative)
		result.isNegative = false; //negative times a negative is a positive, so is pos x pos

	return result;
}//end multiplication overload

bool operator==(const BigInt& left, const BigInt& right)
{
	if (comp_abs_val(left.data, right.data) == '=' && left.isNegative == right.isNegative)
		return true;//if abs val of left and right are equivalent, and the signs match, they are indeed equivalent
	else
		return false;
}//end equivalence overload

bool operator>(const BigInt& left, const BigInt& right)
{
	char c = comp_abs_val(left.data, right.data); //c will be <, > , or = depending on result
												  //easiest cases: signs do not match
												  // -left and +right
	if (left.isNegative && !right.isNegative)
		return false;
	// +left and -right
	else if (!left.isNegative && right.isNegative)
		return true;
	//both positive
	else if (!left.isNegative && !right.isNegative)
	{
		if (c == '>')
			return true;
		else
			return false;
	}
	//both negatives
	else if (left.isNegative && right.isNegative)
	{
		if (c == '<')
			return true;
		else
			return false;
	}
}//end greater then overload

 /////////////////////////end part 3 functions///////////////////


 //////////////////////part 4 functions///////////////////////////////////
BigInt operator/(const BigInt& left, const BigInt& right)
{
	bool carry = true; //boolean to indicate if temp was a 0 after the subtractions, will be used later
	BigInt quotient;//the quotient to be returned
	quotient.data = "";
	std::string temp; //temp string to be used to determine quotient
	std::string rest_of_left;//substring that represent the portion of that temp will be concatted onto after the subtractions
	char comp_abs_val_result;//char indicating if the abs value of left param is ( < , > , = ) the right param
	int i; //integer used to index left string to generate substring of equal or greater size of the right string
	int j = 1;//value to be added to right.length() for generating new substr in the case that the temp is < the right
	int partial_quotient;//partial quotient generated from each long division iteration, will be concatted onto quotient.data

						 //dividing by zero is bad
	if (right.data == "0")
	{
		std::cout << "'No'";
		exit(1);
	}
	else if (left.data == "0")
		return BigInt();
	else if (right.data == "1")
		quotient.data = left.data;//sign determined after else
	else
	{
		//begin by comparing the absolute values of the left and right argument
		comp_abs_val_result = comp_abs_val(left.data, right.data);

		//if this char is '<'; we have (smaller #) / (larger #) which will always be 0 under integer division
		if (comp_abs_val_result == '<')
			return BigInt();
		else if (comp_abs_val_result == '=')
			quotient.data = "1"; //sign to be determined later
		else if (comp_abs_val_result == '>')
		{
			//left is bigger than right
			//left will be broken into the smallest substring that is greater than right to see how 
			//many times right will fit into that.
			//number of times right will fit into the left substring will be concated to the quotient
			//the remainder of these subtractions will have the rest of lefts digits concatted to it
			//we will continue the process with the new substring until the substring cant be made such
			//that it will be larger then right arg

			//set the index to the end point of left, subtracted by the length of right 
			//this index will keep being subtracted by right.length util it results in 
			//an invalid index (negative number)

			temp = "";
			rest_of_left = left.data;
			for (i = right.data.length(); i > 1; i--)
				quotient.data += "0";

			//before jumping into the loop, temp is guaranteed to be the same length as right,
			//but not necesarily larger than right
			while (rest_of_left != "")
			{
				//reassemble the string before seperating into the two parts
				temp = rest_of_left + temp;

				//degenerate the temp into an appropriate substr:
				//determine at what index temp should begin
				//i will also represent the length of the rest of the string
				i = (temp.length()) - (right.data.length());
				if (i < 0)//if we cant make a substring, right cant fit into the temp anymore 
				{
					//right will fit into the substr 0 times, apend this to our quotient
					quotient.data += "0";
					break;//exit the loop
				}
				rest_of_left = temp.substr(0, i);
				temp = temp.substr(i, right.data.length());
				//trim_trailing_zeroes(temp);

				//is the substring generated (<,>,=) the right string?
				j = 1;//how many digits longer must temp be than right?
				while (comp_abs_val(temp, right.data) == '<')//while the temp is smaller then the right arg...
				{
					temp = rest_of_left + temp;//unsplit the string

					i--;//decrement the index

					if (i < 0)//make sure it doesn't go negative, if it does we have to add zeroes
					{
						for (j = left.data.length() - quotient.data.length(); j > 0; j--)
							quotient.data += "0";
						break;//we cant execute the next line, so we are done with the loop, our quotient is generated
					}

					//split the string apart again, temp will be 1 digit longer than last iteration
					rest_of_left = temp.substr(0, i);
					temp = temp.substr(i, right.data.length() + j);

					j++;//increment j 

						//if there was a direct carry of rest_of_left (temp was 0 from the subtractions)
					if (/*temp[temp.length()-1] == '0'  &&*/ carry /*&& rest_of_left != ""*/)
					{
						quotient.data += "0";
						continue;
					}

				}//end while (temp < right)	
				if (i < 0)
					break;//break outta here too

						  //need subloop to count how many times right can go into this left substring, if it can
						  //if it cant go into it still, a 0 is concatted
				partial_quotient = 0;
				comp_abs_val_result = comp_abs_val(temp, right.data);

				while (comp_abs_val_result == '>' || comp_abs_val_result == '=')
				{
					temp = string_subtraction(temp, right.data, comp_abs_val_result);
					comp_abs_val_result = comp_abs_val(temp, right.data);
					partial_quotient++;
				}//end inner while

				 //concat the partial quotient to quotient.data
				quotient.data += std::to_string(partial_quotient);

				//temp has the remainder from the subtractions
				//update temp
				if (temp == "0")
				{
					temp = "";
					carry = true;
				}
				else
					carry = false;
				//comp_abs_val_result = comp_abs_val(temp, right.data);
				//change the index
				//i = i - right.data.length();
			}//end outer while
			std::reverse(quotient.data.begin(), quotient.data.end());
		}//end else

	}
	//quotient.data should have the correct value...

	//all that is left is to determine sign, an easy thing to find
	if (left.isNegative != right.isNegative)
		quotient.isNegative = true;
	else
		quotient.isNegative = false;

	trim_trailing_zeroes(quotient.data);
	return quotient;

}//end division overload

BigInt operator%(const BigInt& left, const BigInt& right)
{
	bool carry = true; //boolean to indicate if temp was a 0 after the subtractions, will be used later
	BigInt quotient;//the quotient to be returned
	quotient.data = "";
	std::string temp; //temp string to be used to determine quotient
	std::string rest_of_left;//substring that represent the portion of that temp will be concatted onto after the subtractions
	char comp_abs_val_result;//char indicating if the abs value of left param is ( < , > , = ) the right param
	int i; //integer used to index left string to generate substring of equal or greater size of the right string
	int j = 1;//value to be added to right.length() for generating new substr in the case that the temp is < the right
	int partial_quotient;//partial quotient generated from each long division iteration, will be concatted onto quotient.data

						 //dividing by zero is bad
	if (right.data == "0")
	{
		std::cout << "'No'";
		exit(1);
	}
	else if (left.data == "0")
		return BigInt();
	else if (right.data == "1")
		quotient.data = left.data;//sign determined after else
	else
	{
		//begin by comparing the absolute values of the left and right argument
		comp_abs_val_result = comp_abs_val(left.data, right.data);

		//if this char is '<'; we have (smaller #) / (larger #) which will always be 0 under integer division
		if (comp_abs_val_result == '<')
			return BigInt();
		else if (comp_abs_val_result == '=')
			quotient.data = "1"; //sign to be determined later
		else if (comp_abs_val_result == '>')
		{
			//left is bigger than right
			//left will be broken into the smallest substring that is greater than right to see how 
			//many times right will fit into that.
			//number of times right will fit into the left substring will be concated to the quotient
			//the remainder of these subtractions will have the rest of lefts digits concatted to it
			//we will continue the process with the new substring until the substring cant be made such
			//that it will be larger then right arg

			//set the index to the end point of left, subtracted by the length of right 
			//this index will keep being subtracted by right.length util it results in 
			//an invalid index (negative number)

			temp = "";
			rest_of_left = left.data;
			for (i = right.data.length(); i > 1; i--)
				quotient.data += "0";

			//before jumping into the loop, temp is guaranteed to be the same length as right,
			//but not necesarily larger than right
			while (rest_of_left != "")
			{
				//reassemble the string before seperating into the two parts
				temp = rest_of_left + temp;

				//degenerate the temp into an appropriate substr:
				//determine at what index temp should begin
				//i will also represent the length of the rest of the string
				i = (temp.length()) - (right.data.length());
				if (i < 0)//if we cant make a substring, right cant fit into the temp anymore 
				{
					//right will fit into the substr 0 times, apend this to our quotient
					quotient.data += "0";
					break;//exit the loop
				}
				rest_of_left = temp.substr(0, i);
				temp = temp.substr(i, right.data.length());
				//trim_trailing_zeroes(temp);

				//is the substring generated (<,>,=) the right string?
				j = 1;//how many digits longer must temp be than right?
				while (comp_abs_val(temp, right.data) == '<')//while the temp is smaller then the right arg...
				{
					temp = rest_of_left + temp;//unsplit the string

					i--;//decrement the index

					if (i < 0)//make sure it doesn't go negative, if it does we have to add zeroes
					{
						for (j = left.data.length() - quotient.data.length(); j > 0; j--)
							quotient.data += "0";
						break;//we cant execute the next line, so we are done with the loop, our quotient is generated
					}

					//split the string apart again, temp will be 1 digit longer than last iteration
					rest_of_left = temp.substr(0, i);
					temp = temp.substr(i, right.data.length() + j);

					j++;//increment j 

						//if there was a direct carry of rest_of_left (temp was 0 from the subtractions)
					if (/*temp[temp.length()-1] == '0'  &&*/ carry /*&& rest_of_left != ""*/)
					{
						quotient.data += "0";
						continue;
					}

				}//end while (temp < right)	
				if (i < 0)
					break;//break outta here too

						  //need subloop to count how many times right can go into this left substring, if it can
						  //if it cant go into it still, a 0 is concatted
				partial_quotient = 0;
				comp_abs_val_result = comp_abs_val(temp, right.data);

				while (comp_abs_val_result == '>' || comp_abs_val_result == '=')
				{
					temp = string_subtraction(temp, right.data, comp_abs_val_result);
					comp_abs_val_result = comp_abs_val(temp, right.data);
					partial_quotient++;
				}//end inner while

				 //concat the partial quotient to quotient.data
				quotient.data += std::to_string(partial_quotient);

				//temp has the remainder from the subtractions
				//update temp
				if (temp == "0")
				{
					temp = "";
					carry = true;
				}
				else
					carry = false;
				//comp_abs_val_result = comp_abs_val(temp, right.data);
				//change the index
				//i = i - right.data.length();
			}//end outer while
			std::reverse(quotient.data.begin(), quotient.data.end());
		}//end else

	}
	if (temp == "")
		temp = "0";
	//quotient.data should have the correct value...
	quotient.data = temp;

	//all that is left is to determine sign, an easy thing to find
	if (left.isNegative != right.isNegative)
		quotient.isNegative = true;
	else
		quotient.isNegative = false;

	trim_trailing_zeroes(quotient.data);
	return quotient;

}//end modulo overload
 //////////////////////end part 4 functions///////////////////////////////


 ////////////////////////helper functions///////////////////////////

void trim_trailing_zeroes(std::string& data)
{
	int most_sig_dig = data.length() - 1; //integer indexing the most significant digit of our data string

	for (most_sig_dig; most_sig_dig > 0; most_sig_dig--)
	{
		if (data[most_sig_dig] == '0')//if the most significant digit in our number is a 0
		{
			data.pop_back();//remove it
		}
		else
			break;//if it isn't our job is done, no need to continue looping
	}
	return;
}//end trim_trailing_zeroes

char comp_abs_val(std::string l, std::string r)
{
	trim_trailing_zeroes(l);
	trim_trailing_zeroes(r);
	int left_index = l.length() - 1; //index of left's most significant digit
	int right_index = r.length() - 1; //index of right's most significant digit

	if (left_index < right_index)//(left has less digits then right) -> (left < right)
		return '<'; //looks like 2 eyes and a nose
	else if (left_index > right_index)//left has more digits, therefore left > right
		return '>';
	else//both opperands have equivalent number of digits
	{
		//we compare the most sig digits, but if they are the same:
		//compare the 2nd most sig digits
		//repeat until the sig digits we are comparing are unequal
		//return appropriate answer
		//if it is discovered that the numbers compared are equivalent, return '='
		for (int i = left_index; i >= 0; i--)//chose to use lefts index, makes no difference since left and right have same number of digits
		{
			if (l[i] == r[i])
				continue;//these sig digits are the same, try the next most sig digits
			else if ((l[i] - '0') < (r[i] - '0'))//convert chars to ints and compare
				return '<';
			else if ((l[i] - '0') > (r[i] - '0'))
				return '>';
		}//exited loop. this means we discovered that the arguments were the same
		return '=';
	}
}//end comp_abs_val() helper function

std::string string_addition(std::string l, std::string r)
{
	int sum;//the sum of an "10^X" place addition
	int carry = 0; //the amount to be added to the next 10^X place
	int i;
	std::string largest; //largest arg
	std::string result = ""; //the result to be returned

							 //determine largest str for future use
	if (l.length() > r.length())
		largest = l;
	else if (r.length() > l.length())
		largest = r;

	//first for loop:begin processing sum of 2 strings of digits
	//comppletion of result.data will continue in next loop when we pass the boundry of the smallest arg
	for (i = 0; i <= (l.length() - 1) && i <= (r.length() - 1); i++)//stay in bounds of the smaller arg
	{
		//the "-'0'" i learned can convert a char 0-9 to its corresponding int value by subtracting '0' = 48 from the ascii value of the char
		sum = (l[i] - '0') + (r[i] - '0') + carry;//add the digits in the 10^i position
		carry = sum / 10;
		sum %= 10; //sum is a single digit
		result += std::to_string(sum); //concat the digit representing the 10^i place to the result
	}
	//exited the loop after passing the bounds of smallest arg.

	if (r.length() == l.length())//if 2 args have equivalent number of digits
	{
		if (carry > 0)
			result += std::to_string(carry);//concat the final carry if it is greater than 0
		return result;
	}
	else
	{
		//continue adding like before, except now we only add the largest strings digits 
		//to the last carry until we've added every digit in the upper half of the number
		//if the carry is greater then 0 after the last addition, concat the carry to the end of the number
		for (i; i <= (largest.length() - 1); i++)
		{
			sum = (largest[i] - '0') + carry;
			carry = sum / 10;
			sum %= 10;
			result += std::to_string(sum);
		}
		if (carry > 0)
			result += std::to_string(carry);//concat the final carry if it is greater than 0	
		return result;
	}
}//end string addition friendly helper

std::string string_subtraction(std::string l, std::string r, char comp_abs_val_result)
{
	int difference = 0;//the differnce of 2 digits in the 10^x's place
	int i = 0;

	//int borrow = 0; //the amount to be taken away from the next 10^x place if our difference was negative
	//if this next 10^x's place digit is a zero, we will try borrowing from the next place 

	std::string result = "";//the resulting string to be returned

	std::string* pLargest = NULL;//pointer to largest string
	std::string* pSmallest = NULL;//pointer to smallest string

	if (comp_abs_val_result == '>')
	{
		//we will call the largest left and the smallest right
		pLargest = &l;
		pSmallest = &r;
	}
	else if (comp_abs_val_result == '<')
	{
		pLargest = &r;
		pSmallest = &l;
	}
	else if (comp_abs_val_result == '=')
	{
		//easiest case, the result of the operation is (a - a)
		//save ourselves some computation and return 0
		return "0";
	}
	//first for loop, make sure to stay in bounds of smallest argument
	//start subtracting largest string's 1's place digit from smallest string's 1's place
	//then do the same for the 10's place ect
	for (i = 0; (i <= pSmallest->length() - 1); i++)
	{
		difference = (pLargest->at(i) - '0') - (pSmallest->at(i) - '0');
		if (difference < 0)//if the difference was negative
		{
			//we need to borrow from the next place in left's data
			//also make sure we do not pass the bounds
			for (int j = 1; j <= (pLargest->length() - 1 - i); j++)
			{
				if ((*pLargest)[i + j] == '0')//if this next spot is a 0
				{
					//remember we borrowed
					(*pLargest)[i + j] = '9';
					continue;//we will try the next spot
				}
				else
				{
					(*pLargest)[i + j] -= 1; //subtracting 1 from the asccii value of this char to get 1 less than the original char
					break;
				}

			}
			//redo the subtraction after "borrowing" a 10 from the next digit's place
			difference = ((*pLargest)[i] - '0' + 10) - ((*pSmallest)[i] - '0');
		}
		//difference is a positive integer
		//borrow was made if it was needed
		//now concat the difference into our data
		result += std::to_string(difference);
	}
	//exited for loop, passed the bound of the smaller argument
	//put the remaining digits from the larger string into our result
	for (i; i <= pLargest->length() - 1; i++)
	{
		result += (*pLargest)[i];
	}
	trim_trailing_zeroes(result);
	return result;
}//end string subtraction helper function

 ////////////////////////end helper functions//////////////////////