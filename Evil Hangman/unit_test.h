#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);

Status test_jgelsomi_init_c_string_has_correct_size(char* buffer, int length);

Status test_jgelsomi_init_c_string_null_terminated_at_size_index(char* buffer, int length);

Status test_jgelsomi_compare_valid_when_left_is_bigger(char* buffer, int length);

Status test_jgelsomi_compare_valid_when_left_is_smaller(char* buffer, int length);

Status test_jgelsomi_compare_valid_when_both_are_same(char* buffer, int length);

Status test_jgelsomi_extraction_has_correct_size(char* buffer, int length);

Status test_jgelsomi_extraction_fails_on_empty_file(char* buffer, int length);

Status test_jgelsomi_extraction_fails_on_file_with_only_whitespace(char* buffer, int length);

Status test_jgelsomi_extraction_succesfully_reads_string_with_whitespace_before_it
(char* buffer, int length);

Status test_jgelsomi_insertion_fails_with_empty_string(char* buffer, int length);

Status test_jgelsomi_init_c_string_creates_empty_string_correctly(char* buffer, int length);

Status test_jgelsomi_push_back_doubles_capacity_on_resize(char* buffer, int length);

Status test_jgelsomi_pop_back_fails_on_empty_string(char* buffer, int length);

Status test_jgelsomi_pop_back_never_resizes(char* buffer, int length);

Status test_jgelsomi_c_str_returns_string_of_equal_length(char* buffer, int length);

Status test_jgelsomi_c_str_NULL_terminated_at_size_index(char* buffer, int length);

Status test_jgelsomi_changes_made_to_object_reflected_in_char_returned_byc_str
(char* buffer, int length);

Status test_jgelsomi_concat_does_not_change_hAppend(char* buffer, int length);

Status test_jgelsomi_concat_hConcat_size_is_correct(char* buffer, int length);

Status test_jgelsomi_is_empty_returns_true_for_empty_string(char* buffer, int length);

Status test_jgelsomi_is_empty_returns_false_for_nonempty_string
(char* buffer, int length);

Status test_jgelsomi_string_destroy_leaves_NULL_handle(char* buffer, int length);


Status test_jgelsomi_string_destroy_leaves_NULL_data(char* buffer, int length);

#endif
