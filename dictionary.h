/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-27-13
 *
 *    Dictionary Header Class
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMap>
#include <QWidget>
#include <QApplication>
#include <iomanip>
#include <QDebug>
#include <iostream>
#include <QString>
#include <qstringlist.h>
#include <QTextStream>
#include <QFile>
#include <QList>
#include <QTime>
#include <QtGui/QTextEdit>
#include <QTextEdit>
#include <QStack>

using namespace std;

class Dictionary
{
private:

    // MapDictionary will store the specified dictionary
    QMap <QString, int> mapDictionary;
    // StoredMap will store the contents of the inputted file
    QMap <QString, int> storedMap;
    // insideDictionary stores the words in the text file that were in the dictionary
    QMap <QString, int> insideDictionary;
    // Containers to hold the number of mispelled
    QMap <QString, int> misspelledWords;
    // Creates a qmap with the values reversed
    QMap<int, QString> storedMapReversed;

    // directs all output streamed into here, to stdout
    static QTextStream sm_cout;

    // Creates two iterators to keep track of various Qmaps
    QMap <QString, int>::iterator mapper;
    QMap <int, QString>::iterator mapperReversedIterator;

    /* The mapReversal function reverses the stored map of the specified file,
    *  it is the reason that we have to reverse the map is so that we can
    *  check search for the key instead of the inputted value, this function
    *  is called multiple times for this functionality. The mapReversal takes
    *  it's helper function which provides a QStringList with the reverse values
    *  and stores it into a map.
    */
    QMap<int, QString> mapReversal(QStringList returnedList);

    /* The mapReversalHelper helps the map reversal function it takes the map
     * that needs to be reversed and reverses it storing it into a QStringList
     */
    QMap<int, QString> mapReversalHelper(QMap<QString, int> toInverse, int wordCount);

    /* The mostPopular function can take in the misspelled map or the
     * word count map ("specified map") that is created by the containsWord function
     * it then dispaly the specified number of words that were used the most and stores
     * them in a QStringList which it returns
     */
    QStringList mostPopular(QMap<int, QString> specifiedMap, int numberOfMostPopular);

    // Formats the word to all lower case and removes punctuation
    QString wordFormat(QString &toBeFormatted);

public:

    /* The basic constructors and destructor functions
    *  construct either the american or british dictionary
    *  depending on the filename parameter. It then
    *  constructs a map called mapDictionary with
    */
    Dictionary(QString filename);
    Dictionary();
     ~Dictionary();

    /* The containsWord functions takes the specified text file and checks each
    *  word to see if it's in the constructed dictionary, if the word is in the
    *  dictionary it will start to count how many times that word appears.
    *  If the word is not in the dictionary it will store that word in a
    *  misspelled map and will count how many times the misspelled word appears,
    *  it will also turn the misspelled word to red text inside of the read in file
    *  There is a function for found words and for misspelled words:
    *   - The containsWordFound function returns a map with words found in the dictionary
    *   - The containsWordMisspelled function returns a map with words misspelled
    */
    QStringList containsWordFound(Dictionary myDictionary, int argumnts);
    QStringList containsWordMisspelled(Dictionary myDictionary, int argumnts);

    /* This fuction reads in text from a file and stores the text in a storedMap
     * The parameter fileName is specified by the user inputcontainsWordMisspelled
     */
    void textBank(QString fileName);

    // Function displays all of the possible inputs
    void formatHelp();

    /* Prompts the user there was a format error, and explains how to display
     * the help menu.
     */
    void formatError();

    /* This function takes the read in of the file and compares it to the requested dictionary
     * it then finds the mispelled words and colors them red inside the original file
     */
    QString spellCheck(Dictionary myDictionary, QString fileName);

    /* The singleWordSpellCheck is similar to the spellCheck function, except instead of
     * checking the spelling of an entire file it checks the spelling of a single word
     */
    QString singleWordSpellCheck(Dictionary myDictionary, QString singleWord);
};

#endif // DICTIONARY_H
