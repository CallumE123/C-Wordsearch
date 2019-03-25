#include "WordSearch.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>

using namespace std;

WordSearch::WordSearch(const char * const filename)
{
	outputName = filename;
}

WordSearch::~WordSearch()
{

}

void WordSearch::ReadSimplePuzzle()
{
	vector<char> line;
	char c;
	string gridSizeLine;
	ifstream grid(puzzleName);
	if (grid.is_open()) {
		getline(grid, gridSizeLine);
		gridSize = stoi(gridSizeLine);

		//Populates the grid with the Wordsearch data.
		for (int x = 0; x < gridSize; x++)
		{
			for (int y = 0; y < gridSize; y++)
			{
				grid >> c;
				line.push_back(c);
			}
			wordsearchGrid.push_back(line);
			line.clear();
		}
	}
	else cout << "Unable to open the file";
}

void WordSearch::ReadSimpleDictionary()
{
	string line;
	ifstream dictionaryFile(dictionaryName);

	//Reads the dictionary eachline at a time.
	while (getline(dictionaryFile, line))
		dictionary.push_back(line);
}

void WordSearch::ReadAdvancedPuzzle()
{
	//asks if the document is the simple puzzle, as it isn't it returns false.
	simple = false;
	std::cout << "Have not implemented an advanced puzzle" << endl;
}

void WordSearch::ReadAdvancedDictionary()
{
	simple = false;
}

void WordSearch::SolvePuzzleSimple()
//Solves the wordsearch using the directions provided.
{
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			sRightCheck(x, y, wordsearchGrid[x][y]);
			sLeftCheck(x, y, wordsearchGrid[x][y]);
			sRightDownCheck(x, y, wordsearchGrid[x][y]);
			sRightUpCheck(x, y, wordsearchGrid[x][y]);
			sLeftDownCheck(x, y, wordsearchGrid[x][y]);
			sLeftUpCheck(x, y, wordsearchGrid[x][y]);
			sUpCheck(x, y, wordsearchGrid[x][y]);
			sDownCheck(x, y, wordsearchGrid[x][y]);
		}
	}
}

void WordSearch::SolvePuzzleAdvanced()
{
	std::cout << "Have not implemented the advanced puzzle solution" << endl;
}

void WordSearch::WriteResults(const double loadTime, const double solveTime) const
{
	ofstream file;
	if (simple)
		file.open("output_simple.txt");
	else
		file.open("output_advanced.txt");

	//Outputs the number of words that have been matched by the wordsearch
	file << "NUMBER_OF_WORDS_MATCHED: " << foundWords.size() << endl;
	
	//Outputs the words and co-ordinates of the discovered words
	file << "WORDS_MATCHED_IN_GRID: " << endl;
	for (int i = 0; i < foundWordsCoords.size(); i++)
	{
		file << foundWordsCoords[i] << endl;
	}

	//Compares each word in the dictionary and the wordsearch resulting in the unmatched words being the output
	file << "WORDS_UNMATCHED_IN_GRID: "  << endl;
	for (int i = 0; i < dictionary.size(); i++) {
		for (int j = 0; j < foundWords.size(); j++) {
			if (dictionary[i] == foundWords[j]) {
				break;
			}
			else if (j == foundWords.size() - 1) {
				file << dictionary[i] << endl;
			}
		}
	}

	//Shows the number of the cells in the wordsearch that have been visited to all completion of the wordsearch
	file << "NUMBER_OF_GRID_CELLS_VISITED: " << cells.size() << endl;

	//Outputs the number of entries read in the dictionary file
	file << "NUMBER_OF_DICTIONARY_ENTRIES: " << dictionary.size() << endl;

	//Outputs the amount of time that it took for the grid to be populated from the text file
	file << "TIME_TO_POPULATE_GRID_STRUCTURE: " << loadTime << endl;

	//Outputs the time that it took for the programme to solve the puzzle
	file << "TIME_TO_SOLVE_PUZZLE: " << solveTime << endl;
	file.close();
}

bool WordSearch::sRightCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0])
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++)
			{
				int const newy = y + j;
				if (newy >= gridSize)
					return false;
				found += wordsearchGrid[x][newy];

				if (found == dictionary[i])
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}

	}
}

bool WordSearch::sLeftCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0])
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++)
			{
				int const newy = y - j;
				if (newy < 0)
					return false;
				found += wordsearchGrid[x][newy];

				if (found == dictionary[i])
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sRightDownCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0]) 
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++) 
			{
				int const newx = x + j;
				int const newy = y + j;
				if (newx >= gridSize)
					return false;
				if (newy >= gridSize)
					return false;
				found += wordsearchGrid[newx][newy];

				if (found == dictionary[i]) 
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sRightUpCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0]) 
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++) 
			{
				int const newx = x - j;
				int const newy = y + j;
				if (newx < 0 )
					return false;
				if (newy >= gridSize)
					return false;
				found += wordsearchGrid[newx][newy];

				if (found == dictionary[i]) 
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sLeftDownCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0]) 
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++) 
			{
				int const newx = x + j;
				int const newy = y - j;
				if (newx >= gridSize)
					return false;
				if (newy < 0)
					return false;
				found += wordsearchGrid[newx][newy];

				if (found == dictionary[i])
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sLeftUpCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0])
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++)
			{
				int const newx = x - j;
				int const newy = y - j;
				if (newx < 0)
					return false;
				if (newy < 0)
					return false;
				found += wordsearchGrid[newx][newy];

				if (found == dictionary[i]) 
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sDownCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0]) 
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++) {
				int const newx = x + j;
				if (newx >= gridSize)
					return false;
				found += wordsearchGrid[newx][y];

				if (found == dictionary[i])
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}

bool WordSearch::sUpCheck(int const x, int const y, char const letter)
{
	string visit;
	string found;

	visit = letter;
	cells.push_back(visit);

	for (int i = 0; i < dictionary.size(); i++)
	{
		if (letter == dictionary[i][0])
		{
			found = letter;
			for (int j = 1; j < dictionary[i].size(); j++)
			{
				int const newx = x - j;
				if (newx < 0)
					return false;
				found += wordsearchGrid[newx][y];

				if (found == dictionary[i])
				{
					foundWords.push_back(found);
					foundWordsCoords.push_back(to_string(y) + " " + to_string(x) + " " + found);
				}
			}
		}
	}
}