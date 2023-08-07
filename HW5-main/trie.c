// Navya Mangipudi 
// 5/17/2023, Spring 2023
// CSE 374 HW 5:
/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */
trieNode* put_word(trieNode* treeRoot, char* word);
int* wordInt(char *word);
int get_num(char word);
trieNode* make_node();
/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

// This function inserts a word into the trie data structure. 
// Takes in the root of the trie and a word as parameters. 
// Returns the root of the updated trie. 
trieNode* put_word(trieNode* treeRoot, char* word) {
    trieNode* curr = treeRoot;
    int* number = wordInt(word);

    // trie traversal 
    for (int i = 0; word[i] != '\0'; i++) {
        int j = number[i];
        if (curr->branches[j] == NULL) {
            curr->branches[j] = make_node();
        }
        curr = curr->branches[j];
    }
    
    // Find the first available branch
    while (curr->word != NULL) {
        int avail = 0;
        while (curr->branches[avail] != NULL) {
            avail++;
        }
        curr->branches[avail] = make_node();
        curr = curr->branches[avail];
    }
    
    // memory allocation for word and storage
    curr->word = (char*)malloc(strlen(word) + 1);
    strncpy(curr->word, word, strlen(word) + 1);
    free(number);
    
    return treeRoot; // returns root of updated trie
}

// Function converts a string of chars into an array of 
// numbers. The string of charcters are taken in as input. 
// Array of numbers are returned.
int* wordInt(char *word) {
   int *numWord = malloc(sizeof(int)*(strlen(word)));
  for (int i = 0; i < strlen(word); i++) {
      while (word[i] != '\0') { // each char processed until null terminator
         numWord[i] = get_num(word[i]);
         i++;
      }
  }
    return numWord; // returns aray of numbers
}

// This function returns the number correspondingn to the ascii value 
// for an inputted character (parameter).
int get_num(char word) {
   int iword = (int)word; // char cast to int 
   
   // ascii value ranges used here to return the correct int
   if (iword < 100) {
      return 1;
   }
   else if (iword < 103 && iword >= 100) { 
      return 2;
   } else if (iword < 106 && iword>= 103) {
      return 3;
   } else if (iword < 109 && iword>= 106) {
      return 4;
   } else if (iword < 112 && iword>= 109) {
      return 5;
   } else if (iword < 116 && iword>= 112) {
      return 6;
   } else if (iword < 119 && iword>= 116) {
      return 7;
   } else if (iword < 122 && iword>= 119) {
      return 8;
   } else {
      return 0;
   }
}

// Trie is built here by reading words from provided txt dictionary 
// file. Takes in the file as a parameter. The root of the trie is 
// returned.
trieNode* build_tree(FILE *dict) {
   char word[MAXLEN];
   trieNode* treeRoot = make_node();

   while (fgets(word, MAXLEN, dict)!= NULL) {
      if ((word[strlen(word) - 1]) == '\n') {
         word[strlen(word) - 1] = '\0'; // remove newline char
      }
      treeRoot = put_word(treeRoot, word); // put word into the trie
   }
   return treeRoot; // return root of trie
}

// This function retrieves the word from the pattern from the trie.
// Takes in the root of the trie and the character pattern as parameters.
// Pattern can contain digits from (1-9) and the symbol '#'. Word associated
// with pattern returned.
char * get_word(trieNode *root, char *pattern) {
  trieNode* curr = root; // root of the trie in a 'copy' variable
  for (int i = 0; pattern[i] != '\0'; i++) {
    if (pattern[i] != '#') {
      if (pattern[i] < 49 || pattern[i] > 57) {
        return "Not found in current dictionary."; // invalid character message
      }

      int x = (pattern[i] - '0') - 1;
      if (curr->branches[x] ==  NULL) {
        return "Not found in current dictionary."; // error if branch does not exist
      }
      curr = curr->branches[x];
    } else if (pattern[i] == '#'){
      if (curr->branches[0] == NULL) {
        return "There are no more T9onyms";
      }
      curr = curr->branches[0]; // traverse to next branch
    }
  }
  if (curr->word == NULL) {
    return "Not found in current dictionary."; // if word not found
  } else {
    return curr->word; // return word if found
  }
}

// Memory for the trie is recursively freed, beginning with the 
// root node which is a parameter for this function. Nodes and 
// their branches are freed. Nothing returned. 
void free_tree(trieNode* root) {
   for (int i = 0; i < BRANCHES; i++) {
      if (root -> branches[i] != NULL) {
         free_tree(root->branches[i]); // using recursion to free branches
      }
   }
   if (root->word != NULL) {
      free(root->word);
   }
   free(root); // current node is freed
   root = NULL;
}

// Here, a new trieNode is created/initialized and a pointer
// is returned to the new node. No parameters are taken. 
trieNode* make_node() {
   // memory is allocated for the node
   trieNode* node = (trieNode*)malloc(sizeof(trieNode));
   if (node != NULL) { // allocation check before init
      for (int i = 0; i < BRANCHES; i++) {
         node->branches[i] = NULL; // init branches to NULL
      }
   }
   node->word = NULL;
   return node;
}