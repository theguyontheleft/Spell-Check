/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-27-13
 *
 *    Dictionary Class Implementation File
 *
 */

#include "dictionary.h"
#include "dictionarygui.h"
QTextStream Dictionary::sm_cout(stdout);
using namespace std;

Dictionary::Dictionary()
{

}

Dictionary::Dictionary(QString file)
{
    int j=0;
    QFile sm_dictionaryName(file);
    sm_dictionaryName.open(QIODevice::ReadOnly);
    QTextStream readFile(& sm_dictionaryName);

    // read line by line and insert into a QStringList
    while (!readFile.atEnd())
    {
        QString inputCarriage = readFile.readLine();
        // Makes sure the word is inputted in lower case format
        inputCarriage = inputCarriage.toLower();
        // Creates the key as the input
        mapDictionary.insert(inputCarriage, j);
        // Iterates the key
        j++;
    }
    sm_dictionaryName.close();
    // qDebug() << "Dictionary Class Initialized";
}

Dictionary::~Dictionary()
{
    // Empties all of the maps
    mapDictionary.clear();
    storedMap.clear();
    storedMapReversed.clear();
    misspelledWords.clear();

    // Reset all of the iterators
    mapper = 0;
    mapperReversedIterator = 0;
}

void Dictionary::textBank(QString fileName)
{
    QFile testFile(fileName);
    QTextStream text(&testFile);
    int j=1;
    // Open the test file and create a Text Stream from it
    testFile.open(QIODevice::ReadOnly);
    // This while loop will insert the specified textfile into a QMAP called storedMap
    while ( !text.atEnd() )
    {
        QString carriage = text.readLine();
        // Trims both sides of the line in order to prevent seg faults
        carriage = carriage.trimmed();

        QStringList scapeGoatList = carriage.split(" ");
        int k = 0;
        while( k < scapeGoatList.size())
        {
            QString currentWord = scapeGoatList[k];
            /* The next two lines remove characters and put the word in lower case, and
             *  ensures the current word does not have space or a number in it   */
            wordFormat(currentWord);
            if(currentWord.toInt()==0 && !currentWord.isEmpty())
            {
                if (storedMap.contains(currentWord))
                {
                    mapper = storedMap.find(currentWord);
                    // Creates a temp object to pass to the insert function
                    int temporaryKey = mapper.value() + 1;
                    storedMap.insert(currentWord, temporaryKey);
                }
                else storedMap.insert(currentWord, j);
            }
            k++;
        } // End of the first while loop
    } // End of the second while loop
    testFile.close();
}

QString Dictionary::spellCheck(Dictionary myDictionary, QString fileName)
{
    QString returnBuffer;
    QFile testFile(fileName);
    QTextStream buffer(&returnBuffer), text(&testFile);;
    // Open the test file and create a Text Stream from it
    testFile.open(QIODevice::ReadOnly);
    // This while loop will insert the specified textfile into a QMAP called storedMap
    while ( !text.atEnd() )
    {
        QString carriage = text.readLine(), individualWord, tempIndividualWord, tempIndividualWordFormatted;
        // Trims both sides of the line in order to prevent seg faults
        carriage = carriage.trimmed();

        QStringList scapeGoatList = carriage.split(" ");
        // Iterates through the temp list and adds the dictionary to a qmap
        for( QStringList::Iterator listIterator = scapeGoatList.begin();
             listIterator!=scapeGoatList.end(); listIterator++)
        {
            individualWord = *listIterator;
            tempIndividualWord = individualWord;
            tempIndividualWordFormatted = wordFormat(tempIndividualWord);

            if(!myDictionary.mapDictionary.contains(tempIndividualWordFormatted))
            {   // Makes the string red
                QString misspelledWord = "< font color = 'red'>" + individualWord + "</font>";
                buffer << misspelledWord <<" ";
            }
            else buffer << individualWord <<" ";

        } // End of the first for loop
        buffer << "<br>"; // Adds the break line
    } // End of the second while loop
    testFile.close();

    return returnBuffer;
}

QString Dictionary::singleWordSpellCheck(Dictionary myDictionary, QString singleWord)
{

}

QStringList Dictionary::containsWordMisspelled(Dictionary myDictionary, int argumnts)
{
    QStringList popularMisspelledList;
    // Iterates through the stored textfile map and dictionary map
    for (mapper = storedMap.begin(); mapper != storedMap.end(); mapper++)
    {
        // If the iterating word isn't found then add it to the misspelled map
        QString textWord = mapper.key();
        if (!myDictionary.mapDictionary.contains(textWord))
        {
            misspelledWords.insert(mapper.key(), mapper.value());
            storedMap.erase(mapper);
        }
    }

    if(argumnts > 0)
    {   // Creates a QMap to temporarly store the reversed map
        QMap<int, QString> misspelledReversed;
        // Calls a function to reverse the map
        misspelledReversed = myDictionary.mapReversalHelper(misspelledWords, argumnts);
        // Calls a function to get a StringList of popular words
        popularMisspelledList = myDictionary.mostPopular(misspelledReversed, argumnts);
    }
    return popularMisspelledList;
}

QStringList Dictionary::containsWordFound(Dictionary myDictionary, int argumnts)
{
    QStringList popularInsideDictionaryList;
    // Iterates through the stored textfile map and dictionary map
    for (mapper = storedMap.begin(); mapper != storedMap.end(); mapper++)
    {
        QString textWord = mapper.key();
        // If the iterating word is found then add it to the inside dictionary map
        if (myDictionary.mapDictionary.contains(textWord))
        {
            insideDictionary.insert(mapper.key(), mapper.value());
        }
    }

    if(argumnts > 0)
    {
        // Calls a function to reverse the map
        QMap<int, QString> insideDictionaryReversed;
        // Calls a function to reverse the map
        insideDictionaryReversed = myDictionary.mapReversalHelper(insideDictionary, argumnts);
        // Calls a function to get a StringList of popular words
        popularInsideDictionaryList = myDictionary.mostPopular(insideDictionaryReversed, argumnts);
    }
    // For debugging purposes
    // qDebug() << popularInsideDictionaryList;
    return popularInsideDictionaryList;
}

QMap<int, QString> Dictionary::mapReversalHelper(QMap<QString, int> toInverse, int wordCount)
{
    // This function returns the list of keys from your map
    QList<QString> lanyard = toInverse.keys();
    // New QMap with reversed value
    QMap<int, QString> storedMapReversed;
    for(int j=0; j < lanyard.size(); j++)  // Insert the inverse = x, regular = y in (x,y)
        storedMapReversed.insertMulti(toInverse.value(lanyard[j]),(lanyard[j]));

    // Sets the reversed map to the end value in the mapmapperReversedIterator
    mapperReversedIterator = storedMapReversed.end()-1;
    for(int i=0; mapperReversedIterator != storedMapReversed.end()-1; i++)
    {
        // Makes sure that it only inserts when there's words left to reverse
        if( i < wordCount)
        {
            storedMapReversed.insert( (mapperReversedIterator.value()).toInt(),
                                      QString::number(mapperReversedIterator.key()) );
        }
        else break; // If it's greater, we don't want to keep iterating
        mapperReversedIterator = mapperReversedIterator - 1;
    }
    return storedMapReversed;
}

QStringList Dictionary::mostPopular( QMap<int, QString>  specifiedMapReversed, int numberOfMostPopular)
{
    int  i=0, temp = numberOfMostPopular;
    QStringList specifiedFunctionList;

    mapperReversedIterator = specifiedMapReversed.end()-1;
    //Counts the most popular word, using words found in the dictionary
    while(mapperReversedIterator != specifiedMapReversed.begin()-1)
    {
        if(i <  temp)
        {
            specifiedFunctionList.append(QString::number(mapperReversedIterator.key()) +
                                         ": " + (mapperReversedIterator.value() ) );
        }
        else break;
        i++;
        mapperReversedIterator--;
    }
    return specifiedFunctionList;
}

// Erases the characters in a string and then turns that string to all lower case, then returns that string
QString Dictionary::wordFormat(QString &toBeFormatted)
{
    toBeFormatted = toBeFormatted.toLower();
    toBeFormatted.remove(QRegExp(QString::fromUtf8("[-~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
    return toBeFormatted;
}

void Dictionary::formatHelp()
{
    sm_cout << "Help Initialized" << endl << endl // For debugging purposes
            << "The dictionaries available are 'american' and 'british'" << endl
            << "<language> can either be 'american' or 'british'" << endl
            << "Make sure you're in either the spellCheck or wordCount project folder" << endl
            << "The following outputs are accepted for wordCount: " << endl
            << "<filename> <language> <int>" << endl
            << "The following outputs are accepted for spellChecl: " << endl
            << "<filename> <language> <int>" << endl
            << "-h (currently running help application) " << endl << endl;
}

// Prompts the user they had a format error and alerts them of the help class
void Dictionary::formatError()
{
    sm_cout << "Incorrect format, for the help menu type '-h' " << endl;
    return;
}
