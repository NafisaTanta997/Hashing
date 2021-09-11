// Nafisa Tanta

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  

  //Code for Part I

  //reads the file words.txt
  ifstream read_file;
  read_file.open(words_filename);

  //word holds the string value of each line
  string word;

  while (getline(read_file, word))                  
  {
      //string value of word is added to the hash table
      hash_table.Insert(word);                      
  }

  cout << "Number of items: " << hash_table.getTotalElements() << endl;
  cout << "Size of hash table: " << hash_table.getTableSize() << endl;

  float total_elem = hash_table.getTotalElements();
  float table_size = hash_table.getTableSize();
  float load_factor = (float)total_elem / table_size;

  cout << "Load factor: " << load_factor << endl;

  //total number of collisions 
  size_t total_collisions = hash_table.getTotalCollisions();
  double total_collisions_d = hash_table.getTotalCollisions();

  //avg_coll represents the average number of collisions
  double avg_coll = total_collisions_d / hash_table.getTotalElements();

  cout << "Average number of collisions: " << avg_coll << endl;
  cout << "Total number of collisions: " << total_collisions << endl;

  cout << endl;

  //reads query file
  ifstream read_qfile;
  read_qfile.open(query_filename);           
  string str_w;

  while (getline(read_qfile, str_w))
  {
      if (hash_table.Contains(str_w))
      {
          cout << str_w << " Found " << hash_table.getTotalProbing(str_w) << endl;
      }
      else
      {
          cout << str_w << " Not_Found " << hash_table.getTotalProbing(str_w) << endl;
      }
  }
  read_file.close();
  read_qfile.close();
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    //Default r_value
    int R = 7;                                                         
    if (argument_count == 5) {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear") {
        // cout << "Linear:" << endl;

        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    
    } else if (param_flag == "quadratic") {
        // cout << "Quadratic:" << endl;

        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);

    } else if (param_flag == "double") {
        // cout << "Double:" << endl;
        // cout << "r_value: " << endl;
        // HashTableDouble<string> double_probing_table;
        // double_probing_table.SetR(R);
        // TestFunctionForHashTable(double_probing_table, words_filename,
        //                         query_filename);

        cout << "r_value: " << endl;
        HashTableDouble<string> double_probing_table;
        //sets r value
        double_probing_table.setRvalue(R);                                              
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);

    } else {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED

