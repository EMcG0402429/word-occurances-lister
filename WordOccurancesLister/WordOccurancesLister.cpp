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
		std::map<int, std::vector<std::string>> countWordMap;
		std::map<int, std::vector<std::string>>::iterator cwIterator;
		std::vector<std::string> scratchArray;
		std::string loopStr;

		while (!fileIn.eof())
		{
			getline(fileIn, loopStr, ' ');
			scratchArray.push_back(loopStr);
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

		for (wcIterator = wordCountMap.end(); wcIterator != wordCountMap.begin(); wcIterator--)
		{
			countWordMap[wcIterator->second].push_back(wcIterator->first);
		}
		ofstream fileTwoOut("list2.txt");
		for (cwIterator = countWordMap.begin(); cwIterator != countWordMap.end(); ++cwIterator)
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
