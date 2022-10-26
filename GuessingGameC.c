/*	
 *	GuessingGameC.C
 *
 *	Trevor Lambas
 *	10/17/15
 *  CSC 389 Introduction to Operating Systems
 *  University of Illinois Springfield 
 *
 *	This short guessing game has two players alternate back and forth guessing a number between 1 and 100. When a player guesses, the program will tell 
 *	the player if their guess was too high or too low. If the player guesses the correct number, then the program tells that player that they have won. 
 *	A player must enter their player number at the beginning of each round, and if they are not the current player then the program will tell them to 
 *	wait their turn. A player may choose to PASS instead of guessing a number. Each player gets only three chances to PASS until they are forced to guess,
 * 	and they cannot PASS more than two turns in a row. Play proceeds until one of the two players has won.
 *
 *  NOTE: There are various printf statements throughout the code that are commented out. These statements were for debugging and have been left in case
 *  	  any changes are made to the code and more debugging must be done at a later time.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define NUMHI 100
#define PLAYERHI 2

		/*
		 *	swapCurrPlayer() is used to change the current player. It takes a pointer to an int as its sole parameter, and then changes the value of the 
		 *  int being pointed to. If currentPlayer is 1, then it is changed to 2, otherwise it is changed to 1. This function returns nothing.
		 */
        void swapCurrPlayer(int *currentPlayer)
        {
			// Logic to check and change the current player.
            if (*currentPlayer == 1)
                *currentPlayer = 2;
            else
                *currentPlayer = 1; 
        }

		/* 
		 *  checkPasses() checks to see how many passes a player has remaining. It takes a pointer to an int as its sole parameter. The parameter would 
		 * 	point to the player's number of remaining passes. If the player has no more passes remaining, then the player is told that they must guess.
		 *  If the player has passes remaining and did not pass on their last turn, then their number of passes remaining is decremented and they are 
		 *	told how many passes they have left. This function returns a boolean value depending on if the player has any passes remaining and did not
		 *	pass on their last turn. If they are out of passes or passed last turn then false is returned, otherwise true is returned. 
		 */
	    bool checkPasses(int *passes, bool *hasPassed)
        {
			// Variable for return result.
            bool result = false;
			
			// Logic to check the player's remaining passes.
            if (*passes == 0)
            {
				// Tell the player that they have no passes left.
                printf("You have no passes left. You must guess.\n");
            }
			else if (*hasPassed)
			{
				// Tell the player that they passed last turn
				printf("You passed last turn. You must guess.\n");
			}
            else
            {
				// Decrement the player's passes.
                *passes = *passes - 1;
				// Set the player's hasPassed flag to true
				*hasPassed = true;
				// Tell player how many passes they have left.
                printf("You have passed %d times, you have %d passes left\n", 3 - *passes, *passes);
                result = true;
            }
			
            return result;
        }
		
		/*
		 *	checkForNumInRange() checks to make sure that the input received from the player is a number in the correct range. It takes two parameters: a 
		 *  pointer to a character array (string) and an int. The function first checks to see if the input is a number using strcmp. If the input is a 
		 *  number then it is checked to make sure that it is in range. This is done using the int parameter num. This function returns a boolean value 
		 *	based on whether the input is in range or not.
		 */
		bool checkForNumInRange(char *str, int num)
		{
			// Variable for return result.
			bool result = false;
			
			// Logic for checking to make sure the input is a number and is in range. strcmp is used on str to make sure it is a number, then num is checked
			// to make sure it's in range.
			if ((strcmp(str, "1") >= 0) && (strcmp(str, ":") < 0))
				if (num >= 1 && num <= NUMHI)
					result = true;
				
			return result;
		}
		
		/*
		 *  stringToInt() converts a string to an integer. It takes a character array (string) as its sole parameter. This function runs through the string and
		 *  gets the value of each character. The number is multiplied by ten each iteration to move the digits to the left as the number is being calculated. 
		 *  Once the null character is reached, the for loop stops. 
		 */
		int stringToInt(char *str)
		{
			// Variables for iteration and return result.
			int i, n = 0;	
			
			// for loop to iterate through the string and get the values for conversion
			for (i = 0; str[i] != '\0'; i++)
				n = n * 10 + str[i] - '0';
			
			return n;
		}
		
        main()
        {
			// Variables to calculate and hold the psuedorandom values for the beginning current player and the number to be guessed. 
			int r1, r2;
			srand (time(NULL));
			r1 = rand() % NUMHI + 1;
			r2 = rand() % PLAYERHI + 1;
			
			// Variables to hold the number to be guessed, the current player, the number of passes for each player, and the number guessed.
			int guessNum = r1, currPlayer = r2, inNum = -1, p1Passes = 3, p2Passes = 3;
			// Variables to check if the player passed last turn.
			bool p1HasPassed = false, p2HasPassed = false;
			// Character arrays (strings) to hold the current guess, the player number input, and the current player.
			char guessIn[100], pnIn[100], currPlayerStr[15];

			//printf("guessNum = %d\n", guessNum);
            //printf("currPlayer = %d\n", currPlayer);
			
			// Tell the players what they are playing.
            printf("Guess the number!! (1-%d)\n", NUMHI);
			
			// while loop to continue the progress of the game.
            while (inNum != guessNum) 
            {
				// Assign the currentPlayer int to a string for comparison.
				sprintf(currPlayerStr, "%d", currPlayer);
				
				// while loop to to continue looping until the correct current player number is entered.
                while (strcmp(pnIn, currPlayerStr) != 0)
                {
                    //printf("currPlayer = %d\n", currPlayer);
                    printf("Please enter which player (1 or 2): ");
						
						// Get user input for the current player
                        gets(pnIn);
						// Check input to make sure it's a 1 or a 2. If it is not, tell user to enter 1 or 2. If it is, then check to make sure
						// that it is the current player. If it is not current player, tell the player to wait their turn. If it is, tell the 
						// player to guess or PASS.
                        if ((strcmp(pnIn,"1") != 0) && (strcmp(pnIn, "2") != 0))
                            printf("Please enter 1 for player 1, or 2 for player 2.\n");
                        else if (strcmp(pnIn, currPlayerStr) != 0)
                            printf("Please wait your turn.\n");
                        else
                            printf("Guess the number or PASS: ");
                    //printf("pnIn = %d\n", pnIn);
                }
				
				// Get user input for the guess
                gets(guessIn);
				// Check to see if the player is passing. If they are passing, check which player it is so we can call checkPasses() on the correct
				// player. 
                if (strcmp(guessIn, "PASS") == 0)
                {
                    if (currPlayer == 1)
                    {
                        if (checkPasses(&p1Passes, &p1HasPassed))
                            swapCurrPlayer(&currPlayer);
                        else
                            printf("Please enter a number 1-%d: ", NUMHI);
                    }
                    else 
                    {
                        if (checkPasses(&p2Passes, &p2HasPassed))
                            swapCurrPlayer(&currPlayer);
                        else
                            printf("Please enter a number 1-%d: ", NUMHI);
                    }
                }
				// If the player is not passing, first set the player's hasPassed flag to false, then convert the input to an integer for range checking 
				// using stringToInt(), and call checkForNumInRange() to make sure the number is in the correct range. If the input is correct, then we 
				// will determine if the player's guess is too low, too high, or correct. If it is correct, the game will end. If it is not, then play 
				// will continue.
                else
                {
					if (currPlayer == 1)
						p1HasPassed = false;
					else 
						p2HasPassed = false;
					
					inNum = stringToInt(guessIn);
					
					if (checkForNumInRange(guessIn, inNum)) 
					{
						if (inNum < guessNum)
							printf("Guess too low.\n");
						if (inNum > guessNum)
							printf("Guess too high.\n");
						if (inNum == guessNum)
							printf("Player %d wins!!\n", currPlayer);
						swapCurrPlayer(&currPlayer);
					}
					else
						printf("Please enter a number 1-%d or PASS: ", NUMHI);
					//printf("%d\n", inNum);
                }
            }
			
			// Pause the window after the game is over.
            gets(guessIn);
        }
