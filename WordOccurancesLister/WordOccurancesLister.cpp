// WordOccurancesLister.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace System;
using namespace std;

void split(std::string input, char delin, std::vector<std::string> &arrayOut) //Split the string by delin, and put all the things in the array.
{
	std::string splitStr;
	std::stringstream ss(input);
	while (!ss.eof())
	{
		getline(ss, splitStr, delin);
		arrayOut.push_back(splitStr);
	}
}

int wordCounter(std::string filename)
{
	ifstream fileIn(filename);
	if (!fileIn.is_open())
	{
		return 0;
	}
	else
	{
		std::map<std::string, int> wordCountMap;
		std::map<std::string, int>::iterator wcIterator;
		std::map<std::string, int>::reverse_iterator wcRevIterator; // For keeping the sorted-by-occurence list in alphabetical order
		std::map<int, std::vector<std::string>> countWordMap;
		std::map<int, std::vector<std::string>>::reverse_iterator cwIterator;
		std::vector<std::string> scratchArray;
		std::string loopStr;

		while (!fileIn.eof())
		{
			getline(fileIn, loopStr);
			split(loopStr, ' ', scratchArray);
		}
		fileIn.close();

		while (!scratchArray.empty())
		{
			wordCountMap[scratchArray.back()]++;
			scratchArray.pop_back();
		}
		scratchArray.clear();

		ofstream fileOneOut("list1.txt");
		for (wcIterator = wordCountMap.begin(); wcIterator != wordCountMap.end(); ++wcIterator)
		{
			fileOneOut << wcIterator->first << " " << wcIterator->second << "\n";
		}
		fileOneOut.close();

		for (wcRevIterator = wordCountMap.rbegin(); wcRevIterator != wordCountMap.rend(); ++wcRevIterator)
		{
			countWordMap[wcRevIterator->second].push_back(wcRevIterator->first);
		}
		wordCountMap.clear();

		ofstream fileTwoOut("list2.txt");
		for (cwIterator = countWordMap.rbegin(); cwIterator != countWordMap.rend(); ++cwIterator)
		{
			fileTwoOut << cwIterator->first;
			while (!countWordMap[cwIterator->first].empty())
			{
				fileTwoOut << " " << cwIterator->second.back();
				cwIterator->second.pop_back();
			}
			fileTwoOut << "\n";
		}
		fileTwoOut.close();
		countWordMap.clear();
	}
	return 1;
}

int main(array<System::String ^> ^args)
{
	std::string filename;
	int listResult;

	cout << "Word Occurrence Lister Program\nWill produce two lists, in list1.txt and list2.txt\nListing the number of occurrances of each word found in a specified text file\nSpecify a text file: ";
	cin >> filename;
	cin.ignore();
	listResult = wordCounter(filename);
	if (listResult == 1)
	{
		cout << "Lists generated successfully";
	}
	else
	{
		cout << "Failed to generate lists";
	}
	cout << "Press Any Key to Coninue";
	cin.get();
    return 0;
}
