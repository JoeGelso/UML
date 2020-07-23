#include <stdio.h>
#include "unit_test.h"

/*

int main(int argc, char* argv[])
{
  Status (*tests[])(char*, int) =
    {
      test_init_default_returns_nonNULL,
      test_get_size_on_init_default_returns_0,
      
      test_jgelsomi_init_c_string_has_correct_size,
      test_jgelsomi_init_c_string_null_terminated_at_size_index,
      test_jgelsomi_compare_valid_when_left_is_bigger,
      test_jgelsomi_compare_valid_when_left_is_smaller,
      test_jgelsomi_compare_valid_when_both_are_same,
      test_jgelsomi_extraction_has_correct_size,
      test_jgelsomi_extraction_fails_on_empty_file,
      test_jgelsomi_extraction_fails_on_file_with_only_whitespace,
      test_jgelsomi_extraction_succesfully_reads_string_with_whitespace_before_it,
      test_jgelsomi_insertion_fails_with_empty_string,
      test_jgelsomi_init_c_string_creates_empty_string_correctly,
      test_jgelsomi_push_back_doubles_capacity_on_resize,
      test_jgelsomi_pop_back_fails_on_empty_string,
      test_jgelsomi_pop_back_never_resizes,
      test_jgelsomi_c_str_returns_string_of_equal_length,
      test_jgelsomi_c_str_NULL_terminated_at_size_index,
      test_jgelsomi_changes_made_to_object_reflected_in_char_returned_byc_str,
      test_jgelsomi_concat_does_not_change_hAppend,
      test_jgelsomi_concat_hConcat_size_is_correct,
      test_jgelsomi_is_empty_returns_true_for_empty_string,
      test_jgelsomi_is_empty_returns_false_for_nonempty_string,
      test_jgelsomi_string_destroy_leaves_NULL_handle,
      test_jgelsomi_string_destroy_leaves_NULL_data
    };
  int number_of_functions = sizeof(tests) / sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;

  for(i=0; i<number_of_functions; i++)
    {
      if(tests[i](buffer, 500) == FAILURE)
	{
	  printf("FAILED: Test %d failed miserably\n", i);
	  printf("\t%s\n", buffer);
	  failure_count++;
	}
      else
	{
	  //printf("PASS: Test %d passed\n", i);
	  // printf("\t%s\n", buffer);
	  success_count++;
	}
    }

  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count,
	 number_of_functions, failure_count, number_of_functions);
return 0;
}

*/
