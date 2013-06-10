Dictionary, Spell Check, Word Count
==========
James Dagres
DESCRIPTION:
=============

This software uses a GUI interface to perform spellcheck and list word frequency. It can open and read in any text document and compare its contents to multiple dictionaries (American English and British English). It then lists the frequency of each word in the selected document that was spelled correctly and incorrectly. Furthermore, it highlights every misspelled word and contains a text editor window where the misspelled words can be changed. For that reason it also has the ability to save the changes made.

FEATURES:
=============
* Can spellcheck any document
* Can query any word (as a QString) to see if it’s located in either of the two English dictionaries
* Can count the number of correctly spelled words using a dictionary object 
* Can count the number of incorrectly spelled words using a misspelled object 
* Can query the document to return N most used word 
* Marks the misspelled words red
* Can edit, correct and save changes to any document

NOTES:
=============
I originally wrote this program to run through the command line, but later changed it to run through a GUI. If you’re interested in the command line version then shoot me a message.

ADDITIONAL ITEMS TO RUN THE PROJECT:
=======================================
QT
* The program can be made and executed from the terminal as well 
as from QT.
For references on how to install Qt on various OS, please go to
http://qt-project.org/doc/qt-4.8/installation.html
* To install QT on a Linux OS the following terminal instruction 
will download everything needed.
Be warned it is a massive download (174 MB):

        $ sudo apt-get install qt-sdk

- Dictionaries
* Two dictionary files are attached in this project in case Ubuntu or whatever OS you’re running the program on doesn’t have them installed.
* If you’re using Ubuntu and you have the dictionary files installed you can initialize them with the following commands:

        $ Dictionary myAmericanEnglishDictionary(QString(“/usr/share/dict/American-english”));
        $ Dictionary myBritishEnglishDictionary(QString(“/usr/share/dict/British-english”));

INSTRUCTIONS:
=======================================
* From the terminal once in the project directory run the following commands to make and build the project:

		$ qmake -project
		$ qmake
		$ make

* There are some test files to try the project in the TestFiles 
directory.
* You can open any of those file with the open button pinned to 
the quick access toolbar 
* Once the file has been loaded the GUI's interface should be 
pretty straight forward.

