#include"unit_test.h"
#include "status.h"
#include<stdlib.h>
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
 MY_STRING hString = NULL;
 
 hString = my_string_init_default();
 
 if(hString == NULL)
  {
  strncpy(buffer, "test_init_default_returns_nonNULL\n"
	"my_string_init_default returns NULL", length);
   my_string_destroy(&hString);
  return FAILURE;
 }
 else
  {
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    return SUCCESS;
  }
}//end test 1

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();

  if(my_string_get_size(hString) != 0)
  {
      status = FAILURE;
      printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	      "Did not receive 0 from get_size after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
  }

  my_string_destroy(&hString);
  return status;
}//end test 2


Status test_jgelsomi_init_c_string_has_correct_size(char* buffer, int length)
{
  MY_STRING hString = NULL;

  hString = my_string_init_c_string("123");

  if(my_string_get_size(hString) != 3 )
    {
      printf("Expected size of 3 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_jgelsomi_init_c_string_has_correct_size\n"
	      "Size from get_size does not match that of string passed\nto init_c_string function.\n", length);
      my_string_destroy(&hString);
      return FAILURE;
    }
  else
  {
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_jgelsomi_init_c_string_has_correct_size\n", length);
    return SUCCESS;
  }
}//end test 3

Status test_jgelsomi_init_c_string_null_terminated_at_size_index(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("123");

  if(*( my_string_at(hString,2) + 1 ) != '\0' )//at function reads size index as
    //out of bounds, so we request the size -1 index and add 1 to it then dereference
    {
      printf("Expected null term. at size index but found %c\n",*( my_string_at(hString,3)) );
      strncpy(buffer, "test_jgelsomi_init_c_string_null_terminated_at_size_index\n"
	      "String was not null terminated at size index\n", length);
       my_string_destroy(&hString);
      return FAILURE;
    }
  else
  {
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_jgelsomi_init_c_string_null_terminated_at_size_index\n",
	    length);
    return SUCCESS;
  }
}//end test 4

Status test_jgelsomi_compare_valid_when_left_is_bigger(char* buffer, int length)
{
  MY_STRING hr = my_string_init_c_string("app");
  MY_STRING hl = my_string_init_c_string("apple");

  if( my_string_compare(hl,hr) > 0 )
    {
       my_string_destroy(&hr);
       my_string_destroy(&hl);
       strncpy(buffer,
	       "\ttest_jgelsomi_compare_valid_when_left_is_bigger\n",
	    length);
    return SUCCESS;
    }
  else
    {
      my_string_destroy(&hr);
      my_string_destroy(&hl);
      printf(
	"Integer greater than 0 expected\n");
      strncpy(buffer, "test_jgelsomi_compare_valid_when_left_is_bigger\n"
	      "Does not return correct value when Left string is lexicographically\nlarger then right string", length);
      return FAILURE;
    }  
}//end test 5

Status test_jgelsomi_compare_valid_when_left_is_smaller(char* buffer, int length)
{
  MY_STRING hr = my_string_init_c_string("aaac");
  MY_STRING hl = my_string_init_c_string("aaabbb");

  if( my_string_compare(hl,hr) < 0 )
    {
       my_string_destroy(&hr);
       my_string_destroy(&hl);
       strncpy(buffer,
	       "\ttest_jgelsomi_compare_valid_when_left_is_smaller\n",
	    length);
    return SUCCESS;
    }
  else
    {
      my_string_destroy(&hr);
      my_string_destroy(&hl);
      printf(
	"Integer less than 0 expected\n");
      strncpy(buffer, "test_jgelsomi_compare_valid_when_left_is_smaller\n"
	      "Does not return correct value when Left string is lexicographically\nsmaller then right string", length);
      return FAILURE;
    }  
}//end test 6

Status test_jgelsomi_compare_valid_when_both_are_same(char* buffer, int length)
{
  MY_STRING hr = my_string_init_c_string("This is a test");
  MY_STRING hl = my_string_init_c_string("This is a test");

  if( my_string_compare(hl,hr) ==  0 )
    {
       my_string_destroy(&hr);
       my_string_destroy(&hl);
       strncpy(buffer,
	       "\ttest_jgelsomi_compare_valid_when_both_are_same\n",
	    length);
    return SUCCESS;
    }
  else
    {
      my_string_destroy(&hr);
      my_string_destroy(&hl);
      printf(
	"Expected zero when strings are equivalent\n");
      strncpy(buffer, "test_jgelsomi_compare_valid_when_both_are_same\n"
	      "Nonzero integer returned by function\n", length);
      return FAILURE;
    }  
}//end test 7

Status test_jgelsomi_extraction_has_correct_size(char* buffer, int length)
{
  MY_STRING hMyString = my_string_init_default();
  FILE* fp = fopen("dictionary.txt", "r");
  my_string_extraction(hMyString, fp);
  fclose(fp);

  if(my_string_get_size(hMyString) == 2)
    {
      my_string_destroy(&hMyString);
      strncpy(buffer,
	       "\ttest_jgelsomi_extraction_has_correct_size\n",
	    length);
    return SUCCESS;
    }
  else
    {
      my_string_destroy(&hMyString);
      printf(
	     "Expected size of 2, got %d instead\n", my_string_get_size(hMyString));
      strncpy(buffer, "test_jgelsomi_extraction_has_correct_size\n"
	      "Error in extraction\n", length);
      return FAILURE;
    }
}//end test 8

Status test_jgelsomi_extraction_fails_on_empty_file(char* buffer, int length)
{
  MY_STRING hMyString = my_string_init_default();
  FILE* fp = fopen("empty.txt", "r");
  
  

  if(my_string_extraction(hMyString, fp) == FAILURE)
    {
      fclose(fp);
      my_string_destroy(&hMyString);
      strncpy(buffer,
	       "\ttest_jgelsomi_extraction_fails_on_empty_file\n",
	    length);
    return SUCCESS;
    }
  else
    {
      fclose(fp);
      my_string_destroy(&hMyString);
      printf("Function failed to fail...\n");
      strncpy(buffer, "test_jgelsomi_extraction_fails_on_empty_file\n"
	      "Extraction did not fail when extracting from empty file\n", length);
      return FAILURE;
    }
}//end test 9

Status test_jgelsomi_extraction_fails_on_file_with_only_whitespace(char* buffer, int length)
{
  MY_STRING hMyString = my_string_init_default();
  FILE* fp = fopen("whitespace.txt", "a");
  fprintf(fp, "\n");
  fclose(fp);
  fp = fopen("whitespace.txt", "r");
  
  

  if(my_string_extraction(hMyString, fp) == FAILURE)
    {
      fclose(fp);
      my_string_destroy(&hMyString);
      strncpy(buffer,
	       "\ttest_jgelsomi_extraction_fails_on_file_with_only_whitespace\n",
	    length);
    return SUCCESS;
    }
  else
    {
      fclose(fp);
      my_string_destroy(&hMyString);
      printf("Function failed to fail...\n");
      strncpy(buffer, "test_jgelsomi_extraction_fails_on_file_with_only_whitespace\n"
	      "Extraction did not fail when extracting from file with only whitespace chars.\n", length);
      return FAILURE;
    }
}//end test 10

Status test_jgelsomi_extraction_succesfully_reads_string_with_whitespace_before_it
(char* buffer, int length)
{
  MY_STRING hMyString = my_string_init_default();
  FILE* fp = fopen("test11.txt", "a");
  fprintf(fp, "\nabc");
  fclose(fp);
  fp = fopen("test11.txt", "r");
  my_string_extraction(hMyString, fp);
  fclose(fp);
  int size = my_string_get_size(hMyString);
  
    if(size  == 3)
    {
      
      my_string_destroy(&hMyString);
      strncpy(buffer,
	       "\ttest_jgelsomi_extraction_succesfully_reads_String_with_whitespace_before_it\n",
	    length);
    return SUCCESS;
    }
  else
    {
      my_string_destroy(&hMyString);
      printf("Expected size of 3, got %d instead\n",size);
      strncpy(buffer, "test_jgelsomi_extraction_succesfully_reads_String_with_whitespace_before_it\n"
	      "Extraction failed to read string proceeding whitespace characters.\n", length);
      return FAILURE;
    }
}//end test 11

Status test_jgelsomi_insertion_fails_with_empty_string(char* buffer, int length)
{
  MY_STRING hString = my_string_init_default();
   if(my_string_insertion(hString,stdout) == FAILURE)
     {
      my_string_destroy(&hString);
      strncpy(buffer,
	       "\ttest_jgelsomi_insertion_fails_with_empty_string\n",
	    length);
      return SUCCESS;
     }
   else
     {
      my_string_destroy(&hString);
      printf("Expected FAILURE on return\n");
      strncpy(buffer, "test_jgelsomi_insertion_fails_with_empty_string\n"
	      "Insertion didn't fail when trying to pass empty string to file pointer.\n", length);
      return FAILURE;
     }
}//end test 12

Status test_jgelsomi_init_c_string_creates_empty_string_correctly
(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("");
  
  if (my_string_get_size(hString) == 0 && my_string_get_capacity(hString) == 1)
    {
      my_string_destroy(&hString);
      strncpy(buffer,
	       "\ttest_jgelsomi_init_c_string_creates_empty_string_correctly\n",
	    length);
      return SUCCESS;
    }
  else
    {
      
      printf("Expected size of 0 and capacity of 1\n");
      printf("\tSize was %d and capacity was %d\n",my_string_get_size(hString),
	    my_string_get_capacity(hString) );
      strncpy(buffer, "test_jgelsomi_init_c_string_creates_empty_string_correctly\n"
	      "When passed "" init_c_string incorrectly creates an empty string.\n", length);
      my_string_destroy(&hString);
      return FAILURE;
      }
  
}//end test 13

Status test_jgelsomi_push_back_doubles_capacity_on_resize(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("123");
  int original_capacity = my_string_get_capacity(hString);
  char c = '4';
  my_string_push_back(hString,c);

  if(my_string_get_capacity(hString) == (original_capacity * 2))
    {
      my_string_destroy(&hString);
      strncpy(buffer,
	       "\ttest_jgelsomi_push_back_doubles_capacity_on_resize\n",
	    length);
      return SUCCESS;
    }
  else
    {   
      printf("Expected new capacity of %d\n", original_capacity*2);
      printf("Got %d instead\n/", my_string_get_capacity(hString));
      strncpy(buffer, "test_jgelsomi_push_back_doubles_capacity\n"
	      "New capacity was allocated incorrectly.\n", length);
      my_string_destroy(&hString);
      return FAILURE;
    }
}//end test 14

Status test_jgelsomi_pop_back_fails_on_empty_string(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("");

  if(my_string_pop_back(hString) == FAILURE)
    {
      my_string_destroy(&hString);
      strncpy(buffer,
	       "\ttest_jgelsomi_pop_back_fails_on_empty_string\n",
	    length);
      return SUCCESS;
    }
  else
    {
      my_string_destroy(&hString);
      printf("Expected function to fail");
      strncpy(buffer, "test_jgelsomi_pop_back_fails_on_empty_string\n"
	      "Pop_back didn't fail when attempting to pop off of empty string\n", length);
      return FAILURE;
    }
}//end test 15

Status test_jgelsomi_pop_back_never_resizes(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("");
  int original_capacity;
  int i;
  char c = 'a';
  for(i =0; i < 100; i++)
    {
      my_string_push_back(hString, c);
    }
  original_capacity = my_string_get_capacity(hString);
  
  for( i = 0; i < 100; i++)
  {
    my_string_pop_back(hString);
  }

 if(original_capacity == my_string_get_capacity(hString))
   {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_pop_back_never_resizes\n",
	    length);
      return SUCCESS;
   }
 else
   {
      my_string_destroy(&hString);
      printf("Expected capacity to not change");
      strncpy(buffer, "test_jgelsomi_pop_back_never_resizes\n"
	      "Pop_back caused a change in capacity\n", length);
      return FAILURE;
   }
}//end test 16

Status test_jgelsomi_c_str_returns_string_of_equal_length(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("12345");
  int i;
  char*c = my_string_c_str(hString);

  for(i = 0; c[i] != '\0'; i++)
    ;
  if( i == my_string_get_size(hString))
    {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_c_str_returns_string_of_equal_length\n",
	    length);
      return SUCCESS;
    }
  else
    {
      my_string_destroy(&hString);
      printf("Expected equivalent size between string object and c string returned");
      strncpy(buffer, "test_jgelsomi_c_str_returns_string_of_equal_length\n"
	      "Difference in size\n", length);
      return FAILURE;
    }
}//end test 17

Status test_jgelsomi_c_str_NULL_terminated_at_size_index(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("12345");
  char*c = my_string_c_str(hString);
  if(c[my_string_get_size(hString)] == '\0')
    {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_c_str_NULL_terminated_at_size_index\n",
	    length);
      return SUCCESS;
    }
  else
    {
      my_string_destroy(&hString);
      printf("Expected null terminator at index of original objects size");
      strncpy(buffer, "test_jgelsomi_c_str_NULL_terminated_at_size_index\n"
	      "Not null terminated at size index\n", length);
      return FAILURE;
    }
}//end test 18

Status test_jgelsomi_changes_made_to_object_reflected_in_char_returned_byc_str
(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("12345");
  char* c = my_string_c_str(hString);
  my_string_pop_back(hString);
  
  if(c[4] == '\0')
    {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_changes_made_to_object_reflected_in_char_returned_byc_str\n",
	    length);
     //free(c);
     return SUCCESS;
    }
  else
    {
      my_string_destroy(&hString);
      printf("Expected c[4] to equal null terminator, got %c instead\n", c[4]);
      strncpy(buffer, "test_jgelsomi_changes_made_to_object_reflected_in_char_returned_byc_str\n"
	      "Array c did not change with hString\n", length);
      //free(c);
      return FAILURE;
    }
}//end test 19


Status test_jgelsomi_concat_does_not_change_hAppend(char* buffer, int length)
{
  //return SUCCESS;
  
  MY_STRING hcat;
  hcat = my_string_init_c_string("1");
  MY_STRING happ;
  happ = my_string_init_c_string("2");
  
  my_string_concat(hcat,happ);

  if(my_string_c_str(happ)[1] == '\0')
    {
     my_string_destroy(&hcat);
     my_string_destroy(&happ);
     strncpy(buffer,
	       "\ttest_jgelsomi_concat_does_not_change_hAppend\n",
	    length);
      return SUCCESS;
    }
  else
    {
      my_string_destroy(&hcat);
      my_string_destroy(&happ);
      printf("Difference detected in value of hAppend before and after concat function");
      strncpy(buffer, "test_jgelsomi_concat_does_not_change_hAppend\n"
	      "Changes made to hAppend.\n", length);
      return FAILURE;
    }

  
}//end test 20

Status test_jgelsomi_concat_hConcat_size_is_correct(char* buffer, int length)
{
  int size;
  MY_STRING hcat = my_string_init_c_string("123");
  MY_STRING happ = my_string_init_c_string("678");

  size = (my_string_get_size(hcat) + my_string_get_size(happ));

  my_string_concat(hcat,happ);

  if(my_string_get_size(hcat) == size)
    {
     my_string_destroy(&hcat);
     my_string_destroy(&happ);
     strncpy(buffer,
	       "\ttest_jgelsomi_concat_hConcat_size_is_correct\n",
	    length);
      return SUCCESS;
    }
  else
    {
      printf("Expected size %d, got %d instead.\n",size, my_string_get_size(hcat) );
      my_string_destroy(&hcat);
      my_string_destroy(&happ);
      strncpy(buffer, "test_jgelsomi_concat_hConcat_size_is_correct\n"
	      "Wrong size discovered after concat operation.\n", length);
      return FAILURE;
    }
}//end test 21

Status test_jgelsomi_is_empty_returns_true_for_empty_string(char* buffer, int length)
{
  MY_STRING hString = my_string_init_default();

  if(my_string_empty(hString) == TRUE)
    {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_is_empty_returns_true_for_empty_string\n",
	    length);
      return SUCCESS;
    }
  else
    {
      printf("Expected TRUE, got FALS.\n");
      my_string_destroy(&hString);
      strncpy(buffer, "test_jgelsomi_is_empty_returns_true_for_empty_string\n"
	      "Got wrong result.\n", length);
      return FAILURE;
    }
}//end test 22

Status test_jgelsomi_is_empty_returns_false_for_nonempty_string
(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("Not Empty");

  if(my_string_empty(hString) == FALSE)
    {
     my_string_destroy(&hString);
     strncpy(buffer,
	       "\ttest_jgelsomi_is_empty_returns_false_for_nonempty_string\n",
	    length);
      return SUCCESS;
    }
  else
    {
      printf("Expected FALSE, got TRUE.\n");
      my_string_destroy(&hString);
      strncpy(buffer, "test_jgelsomi_is_empty_returns_false_for_nonempty_string\n"
	      "Got wrong result.\n", length);
      return FAILURE;
    }
}//end test 23

Status test_jgelsomi_string_destroy_leaves_NULL_handle(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("NO DON'T DELETE ME I WANT TO LIVE");
  my_string_destroy(&hString);

  if(hString == NULL)
    {
      strncpy(buffer,
	       "\ttest_jgelsomi_string_destroy_leaves_NULL_handle\n",
	    length);
      return SUCCESS;
    }
  else
    {
      printf("Failed to succsefully delete object.\n");
      strncpy(buffer, "test_jgelsomi_string_destroy_leaves_NULL_handle\n"
	      "Handle not left NULL after destroy.\n", length);
      return FAILURE;
    }
  
}//end test 24

Status test_jgelsomi_string_destroy_leaves_NULL_data(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("THANK YOU FOR GIVING ME LIFE AGAIN");
  my_string_destroy(&hString);

  if(my_string_c_str(hString) == NULL)
    {
      strncpy(buffer,
	       "\ttest_jgelsomi_string_destroy_leaves_NULL_data\n",
	    length);
      
      return SUCCESS;
    }
  else
    {
      printf("Failed to succsefully delete object's data.\n");
      strncpy(buffer, "test_jgelsomi_string_destroy_leaves_NULL_data\n"
	      "Data not left NULL after destroy.\n", length);
      return FAILURE;
    }
}//end test 25
