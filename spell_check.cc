// NAFISA TANTA

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename HashTableType>
void SpellChecker(HashTableType& dictionary, const string& dictionary_filename, const string& document_filename)
{
    //reads dictionary file
    ifstream read_dict;
    read_dict.open(dictionary_filename);                                        
    string dict;

    while (read_dict >> dict)
    {
        dictionary.Insert(dict);
    }

    //reads document file
    ifstream read_doc;
    read_doc.open(document_filename);                                           
    string doc_word;

    while (read_doc >> doc_word)
    {
        size_t len = doc_word.length();

        //Converts the words to an acceptable format before checking its spelling
        for (size_t i = 0; i < len; i++)
        {
            //Removes non-alpha character
            //Similar to Case B
            if (!(isalpha(doc_word[i])))
            {
                doc_word.erase(doc_word.begin() + i);
                //Readjusts the iterator if the non-alphabetic character is anywhere
                //before the last character in the string
                if (i != len - 1)
                {
                    i--;
                    len--;
                }
            }

            //Checks if the character is within A-Z
            //Changes character from uppercase to lowercase
            doc_word[i] = tolower(doc_word[i]);

        }
        
        //When word is not found in dictionary
        //Begin checking doc_word

        //Saves the alternate possible words and later prints them out
        vector<string> alt_words;

        if (!(dictionary.Contains(doc_word)))
        {
            cout << doc_word << " is INCORRECT" << endl;

            //Case A : Adding one character in any possible position
            for (size_t i = 0; i < len; i++)
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    string temp = doc_word;

                    //Adds the character in the ith index in the string
                    temp.insert(i, 1, ch);                          
                    if (dictionary.Contains(temp))
                    {
                        temp += " *** case A";
                        alt_words.push_back(temp);
                    }
                }
            }

            //Case B : Removing one character from the word
            for (size_t i = 0; i < len; ++i)
            {
                string temp = doc_word;

                //Erases 1 character at the ith index in the string
                temp.erase(i, 1);
                
                if (dictionary.Contains(temp))
                {
                    temp += " *** case B";
                    alt_words.push_back(temp);
                }
            }

            //Case C : Swapping adjacent characters in the word
            for (size_t i = 0; i < len - 1; i++)
            {
                string temp = doc_word;

                //Swaps the characters in the ith and (i+1)th indices in the string
                swap(temp[i], temp[i + 1]);

                if (dictionary.Contains(temp))
                {
                    temp += " *** case C";
                    alt_words.push_back(temp);
                }
            }

            //Prints out the alternate words which are in the dictionary
            for (size_t i = 0; i < alt_words.size(); i++)
            {
                cout << "*** " << doc_word << " -> " << alt_words[i] << endl;
            }

            //Clears alt_words to save the alternate words for the next incorrect word
            alt_words.clear();
        }
        //When word is found in dictionary
        else
        {
            cout << doc_word << " is CORRECT" << endl;
        }

    }
    read_dict.close();
    read_doc.close();
}

int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.

    HashTableDouble<string> dictionary;

    //Default R value is "7" consistent with create_and_test_hash.cc
    dictionary.setRvalue(7);
    SpellChecker(dictionary, dictionary_filename, document_filename);

    
    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
