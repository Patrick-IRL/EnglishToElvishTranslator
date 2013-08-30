/*
 * Translator.h
 *
 *  Created on: 10 Apr 2013
 *      Author: Pat
 */


#include <iostream>
#include <string>
#include <map>

using namespace std;

#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

class Dictionary {
public:
		Dictionary(const char dictFileName[]);
		void translateToElvish(string& out, string& in);
		void translateToEnglish(string& out, string& in);
private:
		map<string, string> english_to_elvish_dict;
		map<string, string> elvish_to_english_dict;
};

class Translator {
public:
		Translator(const char filename[]);
		void toElvish(char translatedLine[], const char lineToTranslate[]);
		void toEnglish(char translatedLine[], const char lineToTranslate[]);
private:
Dictionary dict;
};


#endif /* TRANSLATOR_H_ */
