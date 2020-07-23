#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

/*int main(int argc, char* argv[])
{

   MY_STRING hMy_string = NULL;
   FILE* fp;
   hMy_string = my_string_init_default();
   fp = fopen("simple.txt", "r");
   while(my_string_extraction(hMy_string, fp)) 
   {
      my_string_insertion(hMy_string, stdout);
      printf("\n");
      if(fgetc(fp)== ' ')
      {
         printf("Found a space after the string\n");
      }
   }
   my_string_destroy(&hMy_string);
   fclose(fp);
   
  /* LAB 2 MAIN DRIVER
  MY_STRING hMy_string1 = NULL;
  MY_STRING hMy_string2 = NULL;

  hMy_string1 = my_string_init_c_string("Apple");

  hMy_string2 = my_string_init_c_string("App");
  
  printf("Size of string 1: %d ", my_string_get_size(hMy_string1));
  printf("\nCapacity of string 1: %d", my_string_get_capacity(hMy_string1));

  printf("\nSize of string 2: %d", my_string_get_size(hMy_string2));
  printf("\nCapacity of string 2: %d", my_string_get_capacity(hMy_string2));

  printf("\nResult of my_string_compare(): %d\n", my_string_compare(hMy_string2, hMy_string1));

  
  my_string_destroy(&hMy_string1);
  my_string_destroy(&hMy_string2);


  return 0;
}
*/
