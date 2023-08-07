# T9-Predictive-Text

Programs to implement T9 predictive text. Numbers 2-9 represent three or four letters, 0 represents space, and 1 is for special characters.

2 => ABC
3 => DEF
4 => GHI
5 => JKL
6 => MNO
7 => PQRS
8 => TUV
9 => WXYZ

Multiple letters map to same number so the same sequence of numbers can equal different words. A trie is used to translate from the 
numerical sequences to words and the prefixes of sequences are stored. Here, a compressed trie with only 10 possible branches at each 
node is used. As we travel down the trie, we find the word sequences to correspond to the numerical sequence. 
