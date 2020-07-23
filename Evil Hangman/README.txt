Joe Gelsomini
4/30/18

The hangman program is in main.c. I've been struggling to resolve program crashes. Whenever the user is prompted to guess a letter, the program crashes everytime. What the intended behavior for this segment is the following:
-ask the user for a guess
-make sure the guess is an alphabetical character
-push the guessed char into a MY_STRING object holding all the letter that have been guessed tgus far, not keeping track of duplicates
-after getting a guess from the player, iterate through the vector holding all the words that are in play (stored in words_in_play) generating a key for each
-as each key is generated, it is added to the avl tree the key value and the word itself are passed to the root of the tree
-if the key isnt in the tree, a new node is created and a generic vector is initialized within it, and the word that was passed is pushed into it
-if the key generated does already exist in the tree, the word gets pushed into that nodes vector, and the duplicate key is destroyed
-after all the words in the current words_in_play vector get keys aand are placed into the tree, the tree is searched and the node containing the largest vector gets returned
-that nodes key becomes the new current key, and the nodes vector becomes the new words_in_play
- Old tree should be destroyed, and we built back up after getting another guess, and the above steps will be repeated
-this goes on until either they current key contains no "_", or until the player runs out of guesses
-at this point the player will be told that they won or lost and will be asked if they wish to play again

In my debugging process, functions that have given me trouble were typically the ones associated with the associative_array.c file. I get problems when trying to insert a new node into the tree, specifically on line 172
from my main.c file. I've also ran into trouble with my find_node_with_largest_vector function. After going through main, and my implementation files, I'm unsure of the origin ofthe crashes. 
I would assume it would be a flaw with the implementation of my associative array as an avl tree.

UPDATE 5/3/18

Thanks to help from TAs All of the above problems had been resolved. Major sources of errors were rather silly things, such as
-destroying a memory address that had already been destroyed (i left them commented out)
-in my insertion function I accidently passed a nodes vector to the my_string_compare function, instead of the nodes key
-a semicolon at the end of an if statement in a function where i search for the largest vector in a tree
-general logic errors

Program now works as intended :^) 

UPDATE 7/23/20

No changes made, just preparing the directory to be uploaded online. From the hangman directory, run make to compile, then ./string_driver to play