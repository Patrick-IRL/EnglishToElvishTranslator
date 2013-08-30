EnglishToElvishTranslator
=========================

English To Elvish Translator written in C++
Author: Patrick Moorehouse
Software: Eclipse with CDT
          GCC/MinGW

This program was written for an assignment in an M.Sc in Computer Science course.
The program translates English text files into Elvish, then translates the translated file
back to english again.

main.cpp was supplied by the lecturer, and changes to this file were forbidden. Students
were instructed to write all of their code in additional .cpp and .h files.

The program was also required to be run from command line, with the input file specified by a command line argument.
In order to run the program to translate a file called story.txt, one must enter this command in command line:
    EnglishToElvishTranslator.exe story.txt
This of course assumes that the command is executed from the executable file's location.

main.cpp is written such that it reads the input file one line at a time, and the line is sent to the translation
function, toElvish. The toElvish function then parses the line, sending each word to the translateToElvish function.
translateToElvish returns words that have been translated, or if there is no translation, it returns the English word
encapsulated in a pair of * symbols, such as *word*. The returned word is appended to an output string.
Characters that are not to be included in the translation, such as spaces and tabs, are simply appended to the
output string without any processing, as these are required to be preserved.

When the input line has been processed and a translated output line generated, the output line is written to file.
Once the file has been fully translated, the same is repeated, but translating the Elvish file back to English.

Words that had no Elvish translation, and thus appear in the Elvish text file as *word*, are simply written without
the encapsulating symbols, so they return to their original state.

The folder stories contains sets of example files. There are three levels.
  simplestory1
  simplestory2
  story1
  
In each folder there is a story file, an Elvish translation file, and a back to English file. These were given as
examples, but can also be used to test by running the input file and testing the outputs against those supplied by
the lecturer.
There is a 4th input file called huge.txt. This is the same difficulty level as story1, but it is much longer,
and is used to evaluate the speed of the program.

For testing the speed using huge.txt, if compiling from source, the flag -03 should be used, as this improves the
speed greatly. Example:
  gcc -o EnglishToElvishTranslator.exe -O3 main.cpp Translator.cpp

