/*
 *	Translator.cpp
 *
 *  Created on: 10 Apr 2013
 *  Author: Patrick Moorehouse
 *
 *  This program takes an input file written in English,
 *  and translates it to Elfish, writing translation to file.
 *  The translated file is then read and translated back
 *  to English, which is also written to file.
 */

#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include "Translator.h"

using namespace std;

Dictionary::Dictionary(const char dictFileName[])
{
  fstream str;
  str.open(dictFileName, ios::in);
  string englishWord, elvishWord;

  //Building two maps, one for english to elvish,
  //and the other for elvish to english.
  while (!str.eof())
    {
      str >> englishWord;
      str >> elvishWord;
      english_to_elvish_dict[englishWord]=elvishWord;
      elvish_to_english_dict[elvishWord]=englishWord;
    }

  str.close();
}

//Processes English word, and returns Elvish translation.
void Dictionary::translateToElvish(string& out, string& in)
{
	//normalises by converting first letter to lower case.
	if (isupper(in[0]))
	{
		in[0] = tolower (in[0]);
		out = english_to_elvish_dict[in];
		//If no translation is found, returns *input-word*
		if (out.empty())
			{
				out = '*' + in + '*';
				out[1] = toupper (out[1]);
			}
		else
		{
		out[0] = toupper (out[0]);
		}
	}
	else
	{
		out = english_to_elvish_dict[in];
		if (out.empty())
		{ out = '*' + in + '*'; }
	}

}

//Processes Elvish word, and returns English translation.
void Dictionary::translateToEnglish(string& out, string& in)
{
	if (isupper(in[0]))
	{
		in[0] = tolower (in[0]);
		out = elvish_to_english_dict[in];
		if (out.empty())
			{
				out = '*' + in + '*';
				out[1] = toupper (out[1]);
			}
		else
		{
		out[0] = toupper (out[0]);
		}
	}
	else
	{
		out = elvish_to_english_dict[in];
		if (out.empty())
		{ out = '*' + in + '*'; }
	}
}

Translator::Translator(const char filename[]) : dict(filename)
{

}

//Takes in a line of English, parses, sending words to translator function.
void Translator::toElvish(char translatedLine[], const char lineToTranslate[])
{
	string newString, tmp;
	for (int i = 0; lineToTranslate[i] != '\0' && lineToTranslate[i] != '\n'; i++)
	{
		char c = lineToTranslate[i];

		//If char is letter or - then append to the output string.
		if (isalpha(c) || c == '-')
		{
			while (isalpha(c) || c == '-')
			{
				tmp += lineToTranslate[i];
					c = lineToTranslate[++i];
			}
			string out_s;
			dict.translateToElvish(out_s, tmp);
			newString.append(out_s) += lineToTranslate[i];
			tmp.clear();
		}

		//If not a letter or - then append to string for printing.
		//If it is a * then skip it, so that *word* prints as word.
		else
		{
			if (c != '*')
			{
				newString += lineToTranslate[i];
			}
			else
			{
				c = lineToTranslate[++i];
				while(c != '*')
				{
					newString += lineToTranslate[i];
					c = lineToTranslate[++i];
				}
			}
		}
	}
	strcpy(translatedLine,newString.c_str());
}

//Takes in a line of Elvish, parses, sending words to translator function.
void Translator::toEnglish(char translatedLine[], const char lineToTranslate[])
{
	string newString, tmp;
		for (int i = 0; lineToTranslate[i] != '\0' && lineToTranslate[i] != '\n'; i++)
		{
			char c = lineToTranslate[i];

			if (isalpha(c) || c == '-')
			{
				while (isalpha(c) || c == '-')
				{
					tmp += lineToTranslate[i];
						c = lineToTranslate[++i];
				}
				string out_s;
				dict.translateToEnglish(out_s, tmp);
				newString.append(out_s) += lineToTranslate[i];
				tmp.clear();
			}
			else
			{
				if (c != '*')
				{
					newString += lineToTranslate[i];
				}
				else
				{
					c = lineToTranslate[++i];
					while(c != '*')
					{
						newString += lineToTranslate[i];
						c = lineToTranslate[++i];
					}
				}
			}
		}
		strcpy(translatedLine,newString.c_str());
}
