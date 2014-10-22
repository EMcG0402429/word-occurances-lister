// WordOccurancesLister.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace System;
using namespace std;

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
		std::vector<std::string> scratchArray;
		std::string loopStr;
		int maxOccur;

		while (!fileIn.eof())
		{
			getline(fileIn, loopStr, ' ');
			scratchArray.push_back(loopStr);
		}
		fileIn.close();

		while (!scratchArray.empty())
		{
			wordCountMap[scratchArray.back()]++;
			if (wordCountMap[scratchArray.back()] > maxOccur)
			{
				maxOccur = wordCountMap[scratchArray.back()];
			}
			scratchArray.pop_back();
		}
		scratchArray.clear();

		ofstream fileOneOut("list1.txt");
		for (wcIterator = wordCountMap.begin(); wcIterator != wordCountMap.end(); ++wcIterator)
		{
			fileOneOut << wcIterator->first << " " << wcIterator->second << "\n";
		}
		fileOneOut.close();

		ofstream fileTwoOut("list2.txt");

		fileTwoOut.close();
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
    return 0;
}
