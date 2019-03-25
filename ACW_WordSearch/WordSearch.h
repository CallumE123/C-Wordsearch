#pragma once

#include <string>
#include <vector>

using namespace std;

class WordSearch 
{
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	
	const char* outputName;
	int gridSize;
	int *word;
	bool simple = true;
	vector<vector<char>> wordsearchGrid;
	vector<string> dictionary;
	vector<string> foundWords;
	vector<string> foundWordsCoords;
	vector<string> unmatched;
	vector<string> cells;

	public:
		explicit WordSearch(const char * const filename);
		~WordSearch();

		void ReadSimplePuzzle();
		void ReadSimpleDictionary();
		void ReadAdvancedPuzzle();
		void ReadAdvancedDictionary();
		void SolvePuzzleSimple();
		void SolvePuzzleAdvanced();
		void WriteResults(const	double loadTime, const double solveTime) const;

		bool sRightCheck(int x, int y, char letter);
		bool sLeftCheck(int x, int y, char letter);
		bool sRightDownCheck(int x, int y, char letter);
		bool sRightUpCheck(int x, int y, char letter);
		bool sLeftDownCheck(int x, int y, char letter);
		bool sLeftUpCheck(int x, int y, char letter);
		bool sDownCheck(int x, int y, char letter);
		bool sUpCheck(int x, int y, char letter);
};