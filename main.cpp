#include "char_counts.h"
#include "PartTwo.cpp"

using namespace std;

//Team 6: Dasari, Deshpande, Kulkarni S., Nidumukkala, Pandit, Phirke

//---
const string READ_FILE_1 = "clear.txt";
const string WRITE_FILE_1 = "freq.txt";
//---

int main() {
	//Part 1:
	//Generate character count from given text file
	ChCounts ch_counter;
	ch_counter.generate_character_counts(READ_FILE_1);
	ch_counter.write_to_file(WRITE_FILE_1);

	// Part 2: Generate huffman codetable
	// Author: Arushi Pandit
	generateCodeTable();

	return 0;
}
