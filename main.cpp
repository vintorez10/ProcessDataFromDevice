#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <future>
#include <thread>
#include <shared_mutex>


using namespace std;


string punctuation_marks_filter(const string& pu_marks);
void read_from_file(const string& name_file);
void write_to_file(const string& name_file);
void sort_words();

map<string, int> g_words_from_file;
vector<pair<string, int>> g_sort_words;


int main()
{
    read_from_file("London_Jack-South_Sea_Tales_In.txt");

    sort_words();

    write_to_file("London_Jack-South_Sea_Tales_Out.txt");


   return 0;
}

void read_from_file(const string& name_file)
{
    string temp_str;

    ifstream fin;
    fin.open(name_file, ios_base::in);

    if(fin.is_open()){

        while(fin >> temp_str){

            auto filtered_words(punctuation_marks_filter(temp_str));

            ++g_words_from_file[filtered_words];
        }
        fin.close();
    }
    else{
        cerr << "Can not open file for output" << endl;
        exit(EXIT_FAILURE);
    }

}

void sort_words()
{
    /**< reserver memory for a vector "g_sort_words" */
    g_sort_words.reserve(g_words_from_file.size());

    /**< fill the" g_sort_words " array with the key-value data in the order
     they were in the associative array "g_words_from_file" */
    move(begin(g_words_from_file), end(g_words_from_file), back_inserter(g_sort_words));

    /**< let's sort the array "g_sort_words" in descending order */
    sort(begin(g_sort_words), end(g_sort_words), [](const auto& key, const auto& val){

         return key.second > val.second;
    });
}

void write_to_file(const string& name_file)
{
    ofstream fout(name_file, ios::out);

    if(!fout.is_open()){
        cerr << "Can not open file for output" << endl;
        exit(EXIT_FAILURE);
    }

    for(const auto & a: g_sort_words){
        fout << a.first << "- " << a.second << endl;
    }

    fout.close();

}

/**< this function helps to trim punctuation marks in text */
string punctuation_marks_filter(const string& pu_marks)
{
    /**< string with punctuation marks, that need to be trimmed */
    const char* unnecessary {".,:;-/0123456789 "};

    /**< run the filter and find the first occurrence of a character,
     not defined in the unnecessary string */
    const auto start_filter(pu_marks.find_first_not_of(unnecessary));

    const auto end_filter(pu_marks.find_last_not_of(unnecessary));

    if(start_filter == string::npos){
        return {};
    }

    /**< return a string with clipped punctuation marks */
    return pu_marks.substr(start_filter, end_filter - start_filter + 1);
}




