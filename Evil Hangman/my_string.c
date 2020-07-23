//implementation file
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include "my_string.h"

//known type
struct my_string
{
  int size; //number of elements
  int capacity; //number of elements we CAN hold
  char* data; //hold dynamic array of characters representing a string
};
  
typedef struct my_string My_String;


Status my_string_assignment(ITEM* pLeft, ITEM Right)
{
  //cast both items to My_Strings
  //My_String* left_String = (My_String*)*pLeft;
  My_String* right_String = (My_String*) Right;
//  int i;

  //make sure this guy exists
  if (right_String == NULL)
	  return FAILURE;

  if (*pLeft == NULL)
  {
	  *pLeft = my_string_init_c_string( my_string_c_str(Right) );
	  //pLeft = (ITEM*)&left_String;
	  if (*pLeft == NULL)
		  return FAILURE;
  }
  else//not null
  {
	  while (my_string_pop_back(*pLeft) == SUCCESS);
	  my_string_concat(*pLeft, Right);
	////check if we have enough room
	//  if (left_String->capacity < right_String->size)
	//  {
	//	  //since we dont, free old data and allocate enough room for new data
	//	  free(left_String->data);
	//	  //left_String = (MY_STRING*)malloc(sizeof(MY_STRING));
	//	  left_String->capacity = right_String->size + 1;
	//	  left_String->data = (char*)malloc(sizeof(char) * left_String->capacity);
	//	  if(left_String->data == NULL)
	//	  {
	//		  printf("\nFuck");
	//		  exit(1);
	//	  }
	//  }//room made
	//	
	//  //we have enough room
	//  left_String->size = 0;
	//  for (i = 0; i < right_String->size; i++)
	//	  if (my_string_push_back(left_String, right_String->data[i]) == FAILURE)
	//	  {
	//		return FAILURE;
	//	  }
			  
  }//end else
  //left_string has data of right, and pLeft has been left empty
  //pLeft = (ITEM*)&left_String;
  return SUCCESS;

 /*
  if (*pLeft == NULL)
  {
	left_String = my_string_init_default();
	
	if (left_String != NULL)//if string was succesfully initialized
	{
		for (i = 0; i < left_String->size; i++)
		{
			//push onto left_string what is in right_string at i, if it fails
			//free left_string and return failure
			if (my_string_push_back(left_String, right_String->data[i]) == FAILURE)
			{
				my_string_destroy((ITEM*)&left_String);
				return FAILURE;
			}
		}//end for loop
		*pLeft = left_String;
	}
	else//string wasn't init'd properly
	{
		return FAILURE;
	}

  }
  else//if left was not null
  {
      
	  left_String = (My_String*)*pLeft;
	  while(left_String->size > 0)
	  my_string_pop_back(left_String);//erase old data
      
      //concat the string we want to copy over the now empty string
      //if it fails, free any data that may have been allocated
      //for pLeft
      if( my_string_concat(left_String,right_String) == FAILURE)
	  {
		my_string_destroy((ITEM*)&left_String);
		return FAILURE;
	  }//end if
	  *pLeft = left_String;
  }//end else
  *pLeft = left_String;
  return SUCCESS;
  */

}//end my_string_assignment


MY_STRING my_string_init_default(void)
{
  My_String* pString;
  pString = (My_String*)malloc(sizeof(My_String));
  if (pString != NULL)
    {
      pString->size = 0;
      pString->capacity = 7;
      pString->data = (char*)malloc((sizeof(char) * pString->capacity));
      if (pString->data == NULL)
	{
	  free(pString);
	  return NULL;
	}
    }
    pString->data[0] = '\0';
    return(MY_STRING)pString;
}//end my_string_init_default

MY_STRING my_string_init_c_string(const char* c_string)
{
	int length = 0;
	if (c_string == NULL)
		return my_string_init_default();
  //determine length of string passed
  
  while (c_string[length] != '\0')
    {
      length++;
    }
 

  My_String* pString;
  pString = (My_String*)malloc(sizeof(My_String));
  if (pString != NULL)//succesfully allocated
  {
      pString->capacity = length + 1;
      pString->size = (length);
      pString->data = (char*)malloc( (sizeof(char) * pString->capacity));
      if (pString->data == NULL)
	  {
		free(pString);
		return NULL;
	  }
  }

  for(int i = 0; i < length; i++)
    {
      pString->data[i] = c_string[i];
    }
  pString->data[length] = '\0';
  
  return (MY_STRING)(pString);

}//end my_string_init_c_string


//accesor functions
//
int my_string_get_capacity(MY_STRING hMy_string)
{
  My_String* pString = (My_String*)hMy_string;
  return pString->capacity;
}//end get_capacity

int my_string_get_size(MY_STRING hMy_string)
{
   My_String* pString = (My_String*)hMy_string;
   if (pString == NULL)
	   return 0;
   else
	   return pString->size;
}//end get_size


//compare function
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  //cast both arguments
  My_String* pLeft = (My_String*)hLeft_string;
  My_String* pRight = (My_String*)hRight_string;
  int i = 0;
  while(pLeft->data[i] == pRight->data[i])
    {
      if ((pLeft->data[i] == '\0') |( pRight->data[i] == '\0'))
	return (pLeft->size - pRight->size);
      i++;
    }
  return pLeft->data[i] - pRight->data[i];
  // return (pLeft->size - pRight->size);
  
}//end compare function


//extraction function
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  //cast to known type
  My_String* pString = (My_String*)hMy_string;

  char c = fgetc(fp);
  int i = 0;
  while(isalpha(c) == 0){
    if( (c = fgetc(fp)) == EOF)
      return FAILURE;//fails if file is empty/ only contains whitespace
  }
  ungetc(c, fp);
  while ( (c = fgetc(fp)) != EOF)
  {
    //if the size of the string is to big, we must resize
     if( i+1 >= pString->capacity)
      {
	char* tmp = (char*)malloc(sizeof(char) * 2 * pString->capacity);//double size
	if(tmp == NULL)//if we failed to allocate space for resize:
	  {
	    return FAILURE;
	  }
	for(int index = 0; index <= pString->size; index++)
	  {
	    tmp[index] = pString->data[index];
	  }
	free(pString->data);//free original array
	pString->data = tmp;//data points to new array
	pString->capacity *= 2;//make the new string twice the size of the original
      }//end resize
    

     if(c == ' ' && i != 0)
      {
	pString->data[i] = '\0';
	ungetc(c, fp);
	pString->size = i;
	return SUCCESS;
      }
     else if(c == '\n' && i != 0)
      {
	pString->data[i] = '\0';
	
	pString->size = i;
	return SUCCESS;
      }
     
       
       pString->data[i] = c;
       //my_string_pushback(pString, c);
    
    i++;
  }
  return FAILURE;
}//end extraction

//Insertion function
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  //cast to known type
  My_String* pString = (My_String*)hMy_string;

  if (pString == NULL)
	  return FAILURE;
  
  if(pString->size <= 0)
    return FAILURE;
  int i = 0;//count variable
  while (pString->data[i] != '\0')//while we havent reached the end of the string
    {
      //write the char to the file pointer
      fputc(pString->data[i],fp);
      i++; 
    }
  return SUCCESS;
}//end insertion

//push back function
Status my_string_push_back(MY_STRING hMy_string, char item)
{
  //cast to known type
  My_String* pString = (My_String*)hMy_string;
  char* tmp;

  //if there's no room for another item, double the size
  if (pString->size+1 >= pString->capacity)
    {
      	tmp = (char*)malloc(sizeof(char) * 2 * pString->capacity);//double size
	if(tmp == NULL)//if we failed to allocate space for resize:
	  {
	    return FAILURE;
	  }
	for(int index = 0; index <= pString->size; index++)
	  {
	    tmp[index] = pString->data[index];
	  }
	free(pString->data);//free original array
	pString->data = tmp;//data points to new array
	pString->capacity *= 2;//make the new string twice the size of the original
    }//end resize
  pString->data[ pString->size ] = item;
  pString->data[pString->size +1] = '\0';
  pString->size++;
  return SUCCESS;
}//end push back

//pop back function
Status my_string_pop_back(MY_STRING hMy_string)
{
  //cast to known type
  My_String*  pString = (My_String*)hMy_string;

  if(pString->size <= 0)
    return FAILURE;
  pString->size--;
  pString->data[pString->size] = '\0';//overwrite old last character
  return SUCCESS;  
}//end pop back

//at function
char* my_string_at(MY_STRING hMy_string, int index)
{
  //cast to known type
  My_String*  pString = (My_String*)hMy_string;

  //check if index is within bounds
  if(index < 0 || index >(pString->size-1))
    return NULL;
  return &(pString->data[index]);

}//end at

//c_str function
char* my_string_c_str(MY_STRING hMy_string)
{
  //cast to known type
  My_String*  pString = (My_String*)hMy_string;
  if(pString == NULL)
    return NULL;
  pString->data[pString->size] = '\0';
 return pString->data;
}//end c_str

//Concat function
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  //cast both arguments
  //My_String* pResult = (My_String*)hResult;
  My_String* pAppend = (My_String*)hAppend;
  int i;
  
  //now concat the 2
  for(i = 0; i < pAppend->size; i++)
    {
      if( my_string_push_back(hResult, pAppend->data[i]) == FAILURE)
	{
	  //if pushing back onto hResult fails, undo changes made to it
	  while(i >0)
	    {
            my_string_pop_back(hResult);
	    i--;
	    }
          
	  return FAILURE;
	}//end if
    }
  
  return SUCCESS;
}//end my_string_concat()

Boolean my_string_empty(MY_STRING hMy_string)
{
  //cast dat boi
  My_String* pString = (My_String*)hMy_string;

  if(pString->size == 0)
    return TRUE;
  return FALSE;
}//end my_string_empty


//destroy function
void my_string_destroy(ITEM* pItem)
{
  My_String* pString;
  pString = (My_String*)*pItem;
  free(pString->data);
  free(pString);
  *pItem = NULL;
}//end my_string_destroy
