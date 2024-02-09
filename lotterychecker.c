#include <stdio.h>

#include <stdlib.h>

#include <string.h>


#define ERROR_CODE 1
#define SUCCESS_CODE 0

#define MIN_NUMBER 1
#define MAX_NUMBER 39

/* Limit and sizes */
#define NUMBERS_SIZE 5
#define MAX_FILE_NAME_SIZE 255
#define MAX_NUMBERS_TO_CHECK 100

//this function will compare two number, 1 for same , 0 otherwise
int iStheSame(int num1, int num2) {

  return num1 == num2;
}

/*
this function will go over and check index of two array if they have matches number will increment count
*/
 int countNumMatches(int arr1[], int arr2[], int size) {
  int i, j, count = 0;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (iStheSame(arr1[i], arr2[j])) { // Compare each element of arr1 with each element of arr2
        count++; // Increment count if a match is found
        break; // Exit the inner loop as we've found a match for the current element of arr1
      }
    }
  }
  return count; // Return the total count of matches
}

/* this function will looping and print out each index of array*/
void displayArray(int arr[], int arrsize) {
  int i;

  printf("(");

  for (i = 0; i < arrsize; i++) {

    printf("%d", arr[i]);

    if (i < arrsize - 1) {

      printf(", ");

    }
  }
  printf(")");
} //end func

/* this function will looping and print out the matches number, index of array*/
void printWinners(int numMatches, int input[], int line[]) {

  printf("%d Matches Number: ", numMatches);

  displayArray(input, NUMBERS_SIZE);

  printf(" Matches Number: ");

  displayArray(line, NUMBERS_SIZE);

  printf("\n");

} //end of func

//This function must tell the user the format of the arguments and how to use command
void userHelpInfo() {
  printf("=====================================================================\n");
  printf("***                 usage instruction                             ***\n");
  printf("---------------------------------------------------------------------\n");
  printf(" Enter -n <num1>,<num2>,<num3>,<num4>,<num5> -f filename\n");
  printf(" <num1> to <num5>: 5 numbers must be in the range 1 to 39\n");
  printf(" <filename>: the name of the file must containing groups of 5 numbers\n");
  printf("=====================================================================\n");
}

int main(int argc, char * argv[]) {
    //if the number of argument is less than 5 argument 
    if (argc != NUMBERS_SIZE) {
      userHelpInfo();
      return ERROR_CODE;
    }

      // Parse the input numbers from the command line argument
      int input[NUMBERS_SIZE];

      //given delimiters and returns the next token. 
      //It needs to be called in a loop to get all tokens. It returns NULL when there are no more tokens.
      char * token = strtok(argv[2], ",");
      int i = 0;
      while (token != NULL && i < NUMBERS_SIZE) {
        // convert a string argument to an integer
        input[i] = atoi(token);
        //get the next prt point to next token
        token = strtok(NULL, ",");

        i++;
      }//end while

      // Check if the number is out of range
      for (i = 0; i < NUMBERS_SIZE; i++) {

        if (input[i] < 1 || input[i] > MAX_NUMBER) {

          printf("Invalid input number: %d\n", input[i]);

          return ERROR_CODE;
        }
      } //end for

      /*reads lines from the file named filename and places each group of 5 numbers in a row of the numbers_to_check[][] array.
       * On failures, this function returns zero.
       * On success, this function returns the number of 5 number lines read from the
       * file. Must handle error like lines with more or less than 5 numbers, numbers
       * that are not in the appropriate range, filename having more lines that your
       * max numbers to check.
       */

      FILE * myfile = fopen(argv[4], "r"); //read mode

      if (myfile == NULL) {

        printf("Unable to open file: %s\n", argv[4]);
        // Print an error message if the file cannot be opened
        return ERROR_CODE;
      }//if

      // Read the file line by line and check for matches
      char line[MAX_FILE_NAME_SIZE];

      int line_num[NUMBERS_SIZE];

      while (fgets(line, sizeof(line), myfile)) {
        //The strtok() function parses the string up to the first instance of the delimiter character,
        token = strtok(line, " ");
        i = 0;
        while (token != NULL && i < NUMBERS_SIZE) {

          line_num[i] = atoi(token);
          // convert a string argument to an integer
          token = strtok(NULL, " ");
          i++;
        }

        for (i = 0; i < NUMBERS_SIZE; i++) {
          if (line_num[i] < 1 || line_num[i] > MAX_NUMBER) {
            printf("Invalid line number: %d\n", line_num[i]);

            return ERROR_CODE;
          }
        }

        // Count how many numbers match with the input numbers
        int matchesNum = countNumMatches(input, line_num, NUMBERS_SIZE);

        if (matchesNum >= 2) {
          printWinners(matchesNum, input, line_num);
        }
      }//end while loop

      fclose(myfile);

      return SUCCESS_CODE;
}
    