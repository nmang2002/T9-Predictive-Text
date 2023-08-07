// Navya Mangipudi 
// 5/17/2023, Spring 2023
// CSE 374 HW 5:
/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  wordTrie = build_tree(dictionary);
  // run interactive session
  run_session(wordTrie);
  // clean up
  free_tree(wordTrie);
  fclose(dictionary);

  return(EXIT_SUCCESS);
}

// This function runs the session for t9 and takes in user input.
// The function takes a wordTrie parameter, the root if trie data 
// for the prediction. 
void run_session(trieNode *wordTrie) {
  char userInput[MAXLEN];
  char prev[MAXLEN];

  printf("Enter \"exit\" to quit.\n"); // exits run session when user types 'exit'
  while(1) {
    printf("Enter Key Sequence (or \"#\" for next word):\n>");
    scanf("%s", userInput); // user input 

    // exit if user types exit
    if (strncmp(userInput, "exit", 4) == 0) {
      break;
    // if user types '#', next word prediction indicated
    } else if (strncmp(userInput, "#", 1) == 0) {
      int i = strlen(prev);
      prev[i+1] = '\0';
      prev[i] = '#';  // append '#'
    // copy user input into prev array for prediction
    } else {
      int j = strlen(userInput);
      strncpy(prev, userInput, j + 1);
    }
    // retrieve prediction based on sequence entered 
    printf("%s\n", get_word(wordTrie, prev));
  }

}





