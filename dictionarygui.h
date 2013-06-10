/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-27-13
 *
 *    Dictionary GUI Header File
 */

#ifndef DICTIONARYGUI_H
#define DICTIONARYGUI_H

#include <QMainWindow>
#include "dictionary.h"

// forward declarations
class QLabel;
class QTextEdit;
class QSplitter;

namespace Ui {
class dictionaryGUI;
}

class dictionaryGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit dictionaryGUI(QWidget *parent = 0);
    ~dictionaryGUI();

private slots:
    /* The virtual declaration means that it can override its inherents
     * The next two functions are almost identical calling an open/close
     * helper function which initializes the process of file manipulation
     */
    virtual void openFile();
    virtual void saveFile();

    /* The dictionarySelection function ensures that the global value of dictionary path is
     * updated depending on which dictionary was chosen (arg1) and sets a boolean flag to open
     * this flag allows the spellcheck and common misspelled words function to operate
     */
    void on_dictionarySelection_currentIndexChanged(const QString &arg1);

    /* The next two functions creates the menu bar function calls the set open file function
     * and the save as file function
     */
    void on_fileopen_triggered();
    void on_actionSave_As_triggered();

    /* This function runs when the open file button was released, it then calls the modular
     * open file function which calls the load file function to load the file which then calls
     * the setCurrentFunction to finalize the changes
     */
    void on_openButton_released();

    /* This function reads in the spin box to get the number of popular words to display
     * it recieves the number as a string and then converts it to an int
     */
    void on_numberOfPopularSpinBox_valueChanged(const int &arg1);

    /* This button will start the modular function calls to save the edited version as any specified
     * text file
     */
    void on_saveAsButton_released();

    /* This function allows for dynamic spell checking, as soon as a word or the text is altered
     * spellcheck is automatically ran again
     */
    void on_fileDisplayed_textChanged();

private:
    Ui::dictionaryGUI *ui;
    // This is the string that contains the path of the selected dictionary
    QString dictionaryPath;

    // The next five objects are used to display different windows and prompts in the GUI
    QSplitter *m_horizontalSplitter;
    QTextEdit *m_TextEdit1;
    QTextEdit *m_TextEdit2;
    QAction *m_OpenAction;
    QAction *m_ExitAction;

    /* The next three strings globaly store the value of the file name
     * This enables the file to be called throughout the class
     */
    QString fileName, fileNameStored, m_FileName;

    // This bool ensures a dictionary has been selected
    bool fileOpened, dictionaryOpened;
    QMenu *m_FileMenu;
    QMenu *m_ExitMenu;
    QLabel *m_StatusLabel;

    /* This is the private global class object which allows calls through the
     * member functions
     */
    Dictionary myDictionary;

    // The integer that will save the number of popular words to display
    int numOfPopularWords;

    /* The displayCommonWords function is called whenever the file, dictionary
     * or the numberOfPopularWordstoDisplay changes. It displays the most popular
     * words found in the dictionary and misspelled
     */
    void displayCommonWords();

    /* The setDictionaryHelper takes the dictionaryselection function and modulates the common statements
     * it's job is to create the dictionary specified and if the dictionary has been
     * changed and a file is open it calls the displayCommonWords to display the new dictionary values
     */
    void setDictionaryHelper(QString tempDictionaryPath);

protected:
    /* These functions load/saves the current file based on the filenamepath parameter
     * it also initializes flags letting the program know to begin spell check iff a
     * dictionary has been selected
     */
    virtual void loadFile(const QString &fileName);
    virtual void saveFile(const QString &fileName);

    // This function sets the current file based on the filenamepath parameter
    virtual void setCurrentFile(const QString &fileName);
};

#endif // DICTIONARYGUI_H
