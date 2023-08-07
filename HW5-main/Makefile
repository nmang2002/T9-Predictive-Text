# Navya Mangipudi 
# 5/17/2023, Spring 2023
# CSE 374 HW 5:

# specifies target t9
all: t9

# builds the t9 executable from trie.o and tnine.o
# shows necessary compilation command
t9: trie.o tnine.o
	gcc -Wall -std=c11 -g -o t9 trie.o tnine.o

# rule to generate trie.o from trie.c and trienode.h
# shows necessary compilation command
trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c trienode.h

# rule to generate tnine.o from tnine.c and trienode.h
# shows necessary compilation command
tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -g -c tnine.c trienode.h

# shows command to remove object files and clean proj directory
clean:
	rm -f *.o t9 *~
