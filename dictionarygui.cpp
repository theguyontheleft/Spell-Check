/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-27-13
 *
 *    Dictionary GUI Implementation File
 */

#include "dictionary.h"
#include "dictionarygui.h"
#include "ui_dictionarygui.h"
#include <QtGui>

dictionaryGUI::dictionaryGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dictionaryGUI)
{
    ui->setupUi(this);

    /* In order to globally change the value in the private object dictionaryOpened you have
     * to first store the data you want to change it to in a temp obejct, and then set the
     * private object = to the newly created temp object. You will see this type of object
     * declaration throughout this class
     */
    bool temp = false;
    dictionaryOpened = temp;

    // Clears the display file
    ui->fileDisplayed->clear();
    ui->fileDisplayed->setAcceptRichText(true);
}

dictionaryGUI::~dictionaryGUI()
{
    delete ui;
}

void dictionaryGUI::openFile()
{
    // Uses QDileDialog to browse the files
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        loadFile(fileName);

        bool temp = true;
        fileOpened = temp;
    }
}

void dictionaryGUI::saveFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    // Ensures the file isn't empty
    if (!fileName.isEmpty())
    {
        loadFile(fileName);

        bool temp = true;
        fileOpened = temp;
    }
}

void dictionaryGUI::loadFile(const QString &fileName)
{
    // Sets the global flag as true, allowing spellcheck to be run
    bool tempFileOpened = true;
    fileOpened = tempFileOpened;

    QFile file(fileName);
    // Ensures that the file was successfully opened
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Simple Mian Window Example"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return;
    }

    QString tempFileName = fileName;
    fileNameStored = tempFileName;

    // If a dictionary has already been chosen then run spellcheck
    if(dictionaryOpened)
    {
        // Clears the display  windows because a new file was chosen:
        ui->fileDisplayed->clear();
        ui->foundWordOccurances->clear();
        ui->misspelledWordOccurances->clear();

        // Calls functions to repopulate the windows with the new file
        QString buffer = myDictionary.spellCheck(myDictionary, fileNameStored);
        ui->fileDisplayed->append(buffer);
        displayCommonWords();
    }
    else // Display the file as is
    {
        QTextStream text(&file);
        // Open the test file and create a Text Stream from it
        file.open(QIODevice::ReadOnly);

        // This while loop will insert the entire textfile as is into the window
        while ( !text.atEnd() )
        {
            ui->fileDisplayed->append(text.readAll());
        }
        file.close();
    }
    statusBar()->showMessage(tr("File Opened"), 2000);
}

void dictionaryGUI::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Simple Mian Window Example"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return;
    }
    // For debugging purposes
    // qDebug() << "save fileName " << fileName;

    // Sets the file as an output and takes the input from the window to save as text
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->fileDisplayed->toPlainText();
    QApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("File saved"), 2000);
    setCurrentFile(fileName);
}

void dictionaryGUI::setCurrentFile(const QString &fileName)
{   // Gives you global control of the filename
    m_FileName = fileName;
}

void dictionaryGUI::on_dictionarySelection_currentIndexChanged(const QString &arg1)
{
    qDebug() << arg1;
    // Goes through case statements for all 3 possible choices in the dropdown box
    if(arg1 == "Choose Dictionary")
    {
        // The next 4 lines update global variables ensuring that spellcheck and word count donn't run
        QString tempDictionaryPath = "None";
        dictionaryPath = tempDictionaryPath;
        bool tempFalse = false;
        dictionaryOpened = tempFalse;

        // Because the dictionary was unselected clear the common word windows
        ui->foundWordOccurances->clear();
        ui->misspelledWordOccurances->clear();

        // Use the status bar to alert the user to select a dictionary, displays for 4 seconds
        statusBar()->showMessage(tr("Please Select a Dictionary"), 4000);
        return;
    }
    else if(arg1 == "British")
    {
        bool tempTrue = true;
        dictionaryOpened = tempTrue;
        QString tempDictionaryPath = "/usr/share/dict/british-english";
        /* Calls the helper function to store the selected dictionary and update the
         * three windows on the GUI
         */
        setDictionaryHelper(tempDictionaryPath);
    }
    else if(arg1 == "American")
    {
        bool tempTrue = true;
        dictionaryOpened = tempTrue;
        QString tempDictionaryPath = "/usr/share/dict/american-english";
        setDictionaryHelper(tempDictionaryPath);
    }
    else // Something in the GUI is buggy
    {
        dictionaryOpened = false;
        qDebug() << "Drop Down Error!?";
        return;
    }
}

void dictionaryGUI::setDictionaryHelper(QString tempDictionaryPath)
{
    // For debugging purposes
    qDebug() << "Dictionary Initialized In function" << tempDictionaryPath;

    if(!dictionaryOpened)
    {   // Failsafe incase a dictionary has not been chosen
        return;
    }

    // If the dictionary has been changed then:
    if(dictionaryPath != tempDictionaryPath)
    {
        dictionaryPath = tempDictionaryPath;
        Dictionary temp(dictionaryPath); // The class object
        // Stores the temp map in the private global object
        myDictionary = temp;
        statusBar()->showMessage(tr("Dictionary Selected"), 2000);

        if(fileOpened)
        {   // Clears the windows display file
            ui->fileDisplayed->clear();

            qDebug() << "The dictionary is set, start the horses!";
            // Calls the spellcheck function to check mispelled words
            QString buffer = myDictionary.spellCheck(myDictionary, fileNameStored);
            // Prints the results to the text window
            ui->fileDisplayed->append(buffer);

            // Calls a function to display the common words
            displayCommonWords();
        }
    }
}

void dictionaryGUI::on_fileopen_triggered()
{   // If the open file button was hit then call the openfile function
    openFile();
}

void dictionaryGUI::on_openButton_released()
{     // If the open file button was hit then call the openfile function
    openFile();
}

void dictionaryGUI::on_numberOfPopularSpinBox_valueChanged(const int &arg1)
{
    int temp = arg1;
    numOfPopularWords = temp;
    // For debugging purposes
    // qDebug() << "Number of Popular Words" << numOfPopularWords;

    // Ensures that a file was opened and a dictionary was selected
    if (fileOpened & dictionaryOpened)
    {
        // Calls a function to display the common words
        displayCommonWords();
    }
}

void dictionaryGUI::displayCommonWords()
{
    // Failsafe in case a file wasn't opened or a dictionary wasn't chosen
    if (!fileOpened | !dictionaryOpened)
    {   // If not then don't do anything:
        return;
    }

    // Calls the necessary functions from the dictionary class to return two string lists of common words
    Dictionary tempDictionary(dictionaryPath); // The class object
    myDictionary = tempDictionary;
    myDictionary.textBank(fileNameStored); // Creates a map of the stored text
    QStringList popularInsideDictionaryList = myDictionary.containsWordFound(myDictionary, numOfPopularWords);
    QStringList popularMisspelledDictionaryList = myDictionary.containsWordMisspelled(myDictionary, numOfPopularWords);

    // Clears the word occurances windows, and displays the standard index
    ui->foundWordOccurances->clear();
    ui->misspelledWordOccurances->clear();

    for(int j=0; (j < popularInsideDictionaryList.length() ) & (j<= numOfPopularWords); j++)
    {   // Traverses through the popular inside dictionary list and displays each word
        ui->foundWordOccurances->append(popularInsideDictionaryList[j]);
    }
    for(int j=0; (j < popularMisspelledDictionaryList.length() ) & (j<= numOfPopularWords); j++)
    {   // Traverses through the popular misspelled dictionary list and displays each word
        ui->misspelledWordOccurances->append(popularMisspelledDictionaryList[j]);
    }

    //Updates the status bar for two seconds
    statusBar()->showMessage(tr("Popular List Updated"), 2000);
}

void dictionaryGUI::on_saveAsButton_released()
{
    // The next line is critical for being able to save as a specified "fileName"
    QString fileName = QFileDialog::getSaveFileName(this);
    saveFile(fileName);
}

void dictionaryGUI::on_actionSave_As_triggered()
{
    // The next line is critical for being able to save as a specified "fileName"
    QString fileName = QFileDialog::getSaveFileName(this);
    saveFile(fileName);
}

void dictionaryGUI::on_fileDisplayed_textChanged()
{ /*
   * This function is for the extra credit realtime read in,
   * due to lack of time it is currently incomplete
   *
    if (fileOpened & dictionaryOpened)
    {
        Dictionary temp(dictionaryPath); // The class object
        // Stores the temp map in the private global object
        myDictionary = temp;

        QString changedWord;
        // Reads the changed value added
        // ui->fileDisplayed->changeEvent();

        qDebug() << "File has been changed";

        // Calls a single word spellcheck function to check the added words
        QString buffer = myDictionary.singleWordSpellCheck(myDictionary, changedWord);
        ui->fileDisplayed->append(buffer);

      //     ui->fileDisplayed->selectionChanged();
        // Calls a function to display the common words
        // displayCommonWords();
        statusBar()->showMessage(tr("Dictionary Selected"), 2000);
    } */
}
