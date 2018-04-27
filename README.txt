DS mini project:Book Indexing
Team:
	 Tarun Kaushik
	 Sushmeendra Rudravaram
	 Shreyas Pujari

The problem statement:
To index books based on words that are non-trivial, (meaning that they are less commonly used than others) and show the corrseponding page numbers in which they occur.The input book must be converted to a text format, before the indexing can be carried out.The default length for a trivial word has been taken as 7; this can be increased or decreased as desired.

how to run the files:
	1.run gcc main.c to generate  index.txt which contains the words indexed by page number(with repeating words)
	2.to remove repetitions, run gcc rm_dp.c and then run ./a.out to generate index_f.txt which contains all the words indexed by page number and reeating words removed
	3.run gcc main.c again and choose one of three options to view words as desired.

Note:
	1.DDE5.txt was a pdf file that has been converted to text format.
	2.words.txt contains a list of trivial words(see code comments) to filter out the non-trivial ones  
	  into index.txt
Caveat : The array of structures in rm_dp.c 'struct word w' must be updated to be the size of index.txt, which would obviously vary with the text file that you use.The subsequent for-loop index must also be changed.

