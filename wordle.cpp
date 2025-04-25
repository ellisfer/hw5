#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
  std::string input,
  std::string options, int start, std::set<std::string>& added,
  std::set<std::string>& words, const std::set<std::string>& dict
);

void swap(std::string& s, int first, int second);

void addWord(std::string in, std::string& options, unsigned int ind, int optionind, std::set<std::string>& words, const std::set<std::string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
   
    // step 1: count n, make set, copy of in, make array of floating and empty 
    int len = in.length();
    int floatlen = floating.length();

    // cout << "in wordle! " << endl;
    // cout << in << " " << floating << "   " << len << " " << floatlen << endl;
    std::set<std::string> words;
    std::set<std::string> added;

    std::string options = floating;
    std::string input = in;
    int empty = 0;

    for(unsigned int i = 0; i < len; i++){
      if(in[i] == '-'){
        if(empty >= floatlen){
          options += '-';
        }
        empty ++;
      }
    }
    //cout << "options: " << options << endl;
    wordleHelper(input, options, 0, added, words, dict);

    return words;
}

void wordleHelper(
  std::string input,
  std::string options, int start, std::set<std::string>& added, std::set<std::string>& words, const std::set<std::string>& dict
){
  //cout << "helper: " << input << " " << options << " " << start << endl;
  if(options.length() == 0){
    addWord(input, options, 0, 0, words, dict);
    return;
  }
  if(start == options.length()-1) {
    if(options.length() == 1){
      addWord(input, options, 0, 0, words, dict);
    }
     return;}

  if(start == 0) {
    //cout << "2 " << endl; 
    addWord(input, options, 0, 0, words, dict); 
    //cout << "done ? " << endl;
  }
  std::string permute = options;
  //cout << "3" << endl;
  for(unsigned int i = options.length()-1; i >= start; i--){
    //cout << " i = " << i << endl;
    wordleHelper(input, permute, start+1, added, words, dict);
    //cout << "Swapping: " << permute << " "<< start << " " << i;
    if(i == start) continue;
    swap(permute, start, i);
   // cout << "permuted: " << permute << endl;
    if(added.find(permute) == added.end() ){
      added.insert(permute);
      addWord(input, permute, 0, 0, words, dict);
    }
    
  }
}

void swap(std::string& s, int first, int second){
  if(!(first < s.length() && second < s.length())){
   // std::cout << "string swap indexing error" << std::endl;
    return;
  }
  char temp = s[first];
  s[first] = s[second];
  s[second] = temp;
} 

void addWord(std::string in, std::string& options, unsigned int ind, int optionind, std::set<std::string>& words, const std::set<std::string>& dict){
    //cout << "adding " << options << endl;
    //cout << "ok ind =  " << ind << " letter = " << in[ind] << " len = " << in.length() << endl;
    // final word
    if(ind == in.length()){

      //std::cout << "going to add " <<  in << std::endl;
      if(dict.find(in) != dict.end()){
        //cout << "real word! " << in << endl;
        words.insert(in);
      }
      return;
    }
    //cout <<" word not done! " << endl;
    if(in[ind] == '-'){
      if(options[optionind] != '-'){
        in[ind] = options[optionind];
        addWord(in, options, ind+1, optionind + 1, words, dict);
      }
      else{
        for(char l = 97; l < 123; l++){
          in[ind] = l;
          addWord(in, options, ind+1, optionind+1, words, dict);
        }
      }
  }
  else{
    addWord(in, options, ind+1, optionind, words, dict);
  }
}

// Define any helper functions here
