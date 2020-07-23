#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"

void clear_keyboard_buffer(void);

//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING* current_word_family, MY_STRING* new_key, MY_STRING word, char guess);

int main(int argc, char* argv[])
{
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	GENERIC_VECTOR dictionary[30];//holds all the words in dictionary
	GENERIC_VECTOR words_in_play; //words that the program is using for the game, will change with each player guess
	GENERIC_VECTOR temp_vec = NULL;
	MY_STRING str = my_string_init_default();//used for populating vectors
	MY_STRING guessedChars = my_string_init_default();//string holding letters that have been guessed
	MY_STRING currentKey = NULL;
	MY_STRING newKey = my_string_init_default();
	NODE game_root = NULL;
	NODE temp = NULL;
	Boolean keepPlaying = TRUE;
	Boolean player_word_length_is_valid = FALSE;//bool to test if length player wants to use is valid
	Boolean chicken_dinner; //has player won?
	Boolean validGuess; //is player's guess valid?
	char play_again;
	char guess = '\0'; //char player is guessing
	int guesses = 0;//how many guesses the player wants
	int player_word_length;
	int turn = 0;//number of turns
	int i = 0;

	for (i = 0; i < 30; i++)//initialize generic vectors
		dictionary[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);

	while (my_string_extraction(str, fp) == SUCCESS)
	{
		//push the current string read by fp into vec at index size of string read
		//words of length i will be stored in dictionary[i]
		generic_vector_push_back(dictionary[my_string_get_size(str)], str);
	}

	my_string_destroy(&str);
	fclose(fp);

	while (keepPlaying == TRUE)
	{
		//initialize
		currentKey = my_string_init_default();
		keepPlaying = TRUE;
		player_word_length_is_valid = FALSE;
		validGuess = FALSE;
		//make sure the lenght of word player wants to use is legit
		while (player_word_length_is_valid == FALSE)
		{
			printf("What length word would you like to play with?\nEnter a number: ");
			scanf("%d", &player_word_length);
			clear_keyboard_buffer();

			if (generic_vector_get_size(dictionary[player_word_length]) == 0)
			{
				printf("Can't play! There are no words of lenght %d\n\n", player_word_length);
			}
			else
			{
				player_word_length_is_valid = TRUE;
				words_in_play = generic_vector_init_default(my_string_assignment, my_string_destroy);

				//populate vector with words of length chosen by player
				for (i = 0; i < generic_vector_get_size(dictionary[player_word_length]); i++)
				{
					generic_vector_push_back(words_in_play,
						generic_vector_at(dictionary[player_word_length], i));
					
				}//words_in_play populated

				for (i = 0; i < player_word_length; i++)
				{
					my_string_push_back(currentKey, '_');
				}
			}
		}//end loop for valid length

		

		do//ask player for number of guesses they want
		{
			printf("How many guesses do you want?\nEnter a number: ");
			scanf("%d", &guesses);
			clear_keyboard_buffer();
			if (guesses <= 0)
				printf("That isnt a valid number of guesses/n");

		} while (guesses <= 0);

		//loop until player is out of guesses
		while (turn < guesses)
		{

			printf("Current word: ");
			my_string_insertion(currentKey, stdout);
			printf("\n");
			if (turn > 0)
			{
				printf("Previous guesses: ");
				for (i = 0; i < my_string_get_size(guessedChars); i++)
					printf("%c ", *my_string_at(guessedChars, i));
			}
			printf("\n");
			//initialize tree
			//current_key will change with each iteration of the loop

			game_root = newNode(currentKey, NULL);

			chicken_dinner = TRUE;
			//check if the player has won. They win if the current key has no "-"
			for (i = 0; i < my_string_get_size(currentKey); i++)
			{
				if (*my_string_at(currentKey, i) == '_')
				{
					chicken_dinner = FALSE;
				}
			}
			if (chicken_dinner == TRUE)
				break;//exit the loop if game is won

					  //ask player to guess a letter, and push it into MY_STRING guesses. if the user enters invalid data, they will be prompted again
					  //data is invalid if the char they guess is not alphabetical, or has already been guessed
			do
			{
				validGuess = TRUE;
				printf("Please enter a guess: ");
				scanf("%c",&guess);
				clear_keyboard_buffer();
				guess = tolower(guess);
				//make sure user input is alphabetical
				if (isalpha(guess) == FALSE)
				{
					printf("\nGuess must be a letter!\n");
					validGuess = FALSE;
					continue;
				}

				//check MY_STRING guesses to see if this char appears in it, if not it is pushed into it
				for (i = 0; i < my_string_get_size(guessedChars); i++)
				{
					if (guess == *my_string_at(guessedChars, i))
					{
						printf("Looks like you already guessed %c.\n", guess);
						validGuess = FALSE;
						break;
					}
				}
				//if the guess was bad dont add it to guessedChars, just continue looping
				if (validGuess == FALSE)
					continue;

				//if the guess was legit, it'll be pushed onto this string, and we should exit the guessing loop
				my_string_push_back(guessedChars, guess);

			} while (validGuess != TRUE);//end guessing loop


										 //when a letter is guessed, iterate through the vector containg valid words, generating a key for each
			for (i = 0; i < generic_vector_get_size(words_in_play); i++)
			{//Status get_word_key_value(MY_STRING* current_word_family, MY_STRING* new_key, MY_STRING word, char guess)
				if (get_word_key_value(&currentKey, &newKey, generic_vector_at(words_in_play, i), guess) == FAILURE)
				{
					printf("Looks like something went wrong, we'll call it a draw!");
					exit(1);
				}

				//words will be inserted into avl tree based on this key, if the key generated in the tree does not exist, a new node shall be created
				//if the key already exists, the string associated with that key will be pushed into the vector corresponding to the same key
					game_root = node_insert(game_root, newKey, (MY_STRING)generic_vector_at(words_in_play, i));
				//printf("%d: This is a for loop, B O I\n", i);
			}



			//words_in_play must be updated, choose vector of largest size inside avl tree
			generic_vector_destroy(&words_in_play);
			//printf("Made it past generic vector destroy\n");
			temp = find_node_with_largest_vector(game_root);
			
			//printf("Made it past find_node_with_largest_vector\n");
			temp_vec = get_node_vec(temp);
			//printf("made it past making a temporary vec\n");

			//update words in play
			words_in_play = generic_vector_init_default(my_string_assignment, my_string_destroy);
			//printf("Size of temp_vec = %d", generic_vector_get_size(temp_vec));

			for (i = 0; i < generic_vector_get_size(temp_vec); i++)
			{
				//printf("Entered for loop\n");
				generic_vector_push_back(words_in_play,
					generic_vector_at( temp_vec, i));
				//printf("Testing this second for loop %d", i);
			}
			//generic_vector_destroy(&temp_vec);
			//printf("current: %s, temp: %s\n", my_string_c_str(currentKey), my_string_c_str(get_node_key(temp)));
			my_string_assignment(&currentKey, get_node_key(temp));
			//printf("current %s\n", my_string_c_str(currentKey));


			//compare old key with new key to see if player's guess is in the new key
			for (i = 0; i < my_string_get_size(currentKey); i++)
			{
				if (guess == *my_string_at(currentKey, i))
				{
					printf("\nGood guess! %c was in my word!\n\n",guess);
					break;
				}
				else if (i == (my_string_get_size(currentKey) - 1) && guess != *my_string_at(currentKey, i))
				{
					printf("\nSorry, but %c wasn't in my word!\n\n",guess);
					break;
				}
			}
			
			//destroy tree before looping again, it will be reinitialized with current_key//
			node_destroy(&game_root);

			//increase turn count and let player know how many guesses they have left
			turn++;
			if(guesses - turn > 0)
				printf("You have %d guesses left.\n", guesses - turn);
			

		}//end loop for number of turns

		//after this loop the player either guessed the word correctly or ran out of turns
		//process which case
		if (chicken_dinner == TRUE)
		{
			printf("Winner winner, chicken dinner!\nYou correctly guessed ");
			my_string_insertion(currentKey, stdout);

			printf("\nI bet you wont win again though!\n\tType 'y' to play again!\n");
			scanf("%c", &play_again);
			clear_keyboard_buffer();
		}
		else
		{
			printf("GG EZ.\nThe correct word was ");
			my_string_insertion(generic_vector_at(words_in_play, 0),stdout);

			printf("\nDon't feel bad though, you can always play again if you'd like!\n\tType 'y' to go again!\n");
			scanf("%c", &play_again);
			clear_keyboard_buffer();

		}
		if (tolower(play_again) == 'y')
			keepPlaying = TRUE;
		else
			keepPlaying = FALSE;

		//clean up before playing again
		generic_vector_destroy(&words_in_play);
		my_string_destroy(&currentKey);
		node_destroy(&game_root);
		while (my_string_pop_back(guessedChars)== SUCCESS);//empty guessed chars
		turn = 0;
		guess = '\0';
		guesses = 0;



	}//end outermost while loop, game is over

	printf("\nThank you for playing!\n");

	//destroy everything:
	//
	//destroy vectors
	for (i = 0; i < 30; i++)
		generic_vector_destroy(&(dictionary[i]));
	//generic_vector_destroy(&words_in_play);
	//generic_vector_destroy(&temp_vec);
	//destroy nodes
	//node_destroy(&temp);
	node_destroy(&game_root);
	//destroy strings
	//my_string_destroy(&str);
	//my_string_destroy(&currentKey);
	my_string_destroy(&newKey);
	my_string_destroy(&guessedChars);


	return 0;
}

void clear_keyboard_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}

//lab 8 function
Status get_word_key_value(MY_STRING* current_word_family, MY_STRING* new_key, MY_STRING word, char guess)
{
	int i = 0;

	//empty whatever is in new_key, we will build a new one from the ground up
	while (my_string_pop_back(*new_key) == SUCCESS)//will fail on empty string
		;//do nothing


		 //process word with guess
	for (i = 0; i < my_string_get_size(word); i++)
	{
		if (guess == *my_string_at(word, i))//if the char they guessed is in the word at this index
		{
			if (my_string_push_back(*new_key, tolower(guess)) == FAILURE)//push it onto the new key we are building
				return FAILURE;
		}
		else
		{
			if (my_string_push_back(*new_key, *my_string_at(*current_word_family, i)) == FAILURE)//otherwise push whatever was in the old key onto the new key instead
				return FAILURE;
		}
	}
	return SUCCESS;
}//end get_word_key_value


 /*		LAB 7 and 8
 BELONGS IN MAIN
 FILE* fp;
 fp = fopen("dictionary.txt", "r");
 GENERIC_VECTOR vec[30];
 MY_STRING str = my_string_init_default();
 int i;

 for(i = 0; i < 30; i++)//initialize generic vectors
 vec[i] = generic_vector_init_default(my_string_assignment,my_string_destroy);


 while(my_string_extraction(str, fp) == SUCCESS)
 {
 //push the current string read by fp into vec at index size of string read
 generic_vector_push_back(vec[my_string_get_size(str)], str);
 }

 for (i = 0; i <30; i++)
 {
 printf("Number of words of length %d: %d\n",i,generic_vector_get_size(vec[i]) );
 }

 //destroy vec and str
 for (i = 0; i < 30; i++)
 {
 generic_vector_destroy(&vec[i]);
 }
 my_string_destroy(&str);
 fclose(fp);


 MY_STRING str1 = my_string_init_c_string("The");
 MY_STRING oldKey1 = my_string_init_c_string("---");
 MY_STRING newKey1 = my_string_init_default();

 MY_STRING str2 = my_string_init_c_string("Truck");
 MY_STRING oldKey2 = my_string_init_c_string("-----");
 MY_STRING newKey2 = my_string_init_default();

 MY_STRING str3 = my_string_init_c_string("happy");
 MY_STRING oldKey3 = my_string_init_c_string("--ppy");
 MY_STRING newKey3 = my_string_init_default();

 MY_STRING str4 = my_string_init_c_string("awesome");
 MY_STRING oldKey4 = my_string_init_c_string("--e---e");
 MY_STRING newKey4 = my_string_init_default();

 get_word_key_value(oldKey1, newKey1, str1, 'T');
 get_word_key_value(oldKey2, newKey2, str2, 'r');
 get_word_key_value(oldKey3, newKey3, str3, 'h');
 get_word_key_value(oldKey4, newKey4, str4, 'z');


 printf("%s\n", my_string_c_str(newKey1));
 printf("%s\n", my_string_c_str(newKey2));
 printf("%s\n", my_string_c_str(newKey3));
 printf("%s\n", my_string_c_str(newKey4));

 my_string_destroy(&str1);
 my_string_destroy(&str2);
 my_string_destroy(&str3);
 my_string_destroy(&str4);
 my_string_destroy(&oldKey1);
 my_string_destroy(&oldKey2);
 my_string_destroy(&oldKey3);
 my_string_destroy(&oldKey4);
 my_string_destroy(&newKey1);
 my_string_destroy(&newKey2);
 my_string_destroy(&newKey3);
 my_string_destroy(&newKey4);
 */
