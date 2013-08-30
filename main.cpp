#include <iostream>
#include <fstream>
#include "Translator.h"

using namespace std;

// maximum number of characters in a line of the text
const int MAXLINE=1000;
int main(int argc, char *argv[])
{
  if (argc<2)
    {
      cout << "No story file specified." << endl;
      return -1;
    }

  fstream infile;
  infile.open(argv[1], ios::in);

  if (infile.fail())
    {
      cout << "Could not open the story file." << endl;
      return -1;
    }

  Translator translator("englishtoelvish.txt");
  fstream outfile;
  outfile.open("story_in_elvish.txt", ios::out);
  if (outfile.fail())
    {
      cout << "Could not open the output file." << endl;
      return -1;
    }

  char english_line[MAXLINE], elvish_line[MAXLINE];

  // Translate the story into Elvish
  while (!infile.fail())
    {
      infile.getline(english_line, MAXLINE, '\n');
      if (!infile.fail())
	{
	  translator.toElvish(elvish_line, english_line);
	  outfile << elvish_line << endl;
	}
    }
  outfile.close();
  infile.close();

  // Read the translated story and re-translate into English
  infile.open("story_in_elvish.txt", ios::in);
  outfile.open("story_backto_english.txt", ios::out);
  while (!infile.eof())
    {
      infile.getline(elvish_line, MAXLINE, '\n');
      if (!infile.fail())
	{
	  translator.toEnglish(english_line, elvish_line);
	  outfile << english_line << endl;
	}
    }

  infile.close();
  outfile.close();
}

