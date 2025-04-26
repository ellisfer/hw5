#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <unordered_set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
  std::string& input,
  std::string& options, int start, std::unordered_set<std::string>& added,
  std::set<std::string>& words, const std::set<std::string>& dict
);
void wordleHelper3(const string& input, string& current, string& floating,
  int ind, int empty, set<string>& words, const set<string>& dict);
//void swap(std::string& s, int first, int second);
//void wordleHelper2(string& input, int ind, string floating, set<string>& words, const set<string>& dict);

//void addWord(std::string in, const std::string& options, 
//  unsigned int ind, int optionind, std::set<std::string>& words, 
//  const std::set<std::string>& dict, std::unordered_set<std::string>& added);

//bool pruning(const string& prefix, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
   
    // step 1: count n, make set, copy of in, make array of floating and empty 
    // int len = in.length();
    // int floatlen = floating.length();

    //cout << "in wordle! " << endl;
    //cout << in << " " << floating << "   " << len << " " << floatlen << endl;
    std::set<std::string> words;
    std::unordered_set<std::string> added;

    std::string options = floating;
    std::string input = in;
    int empty = count(input.begin(), input.end(), '-');

    // for(unsigned int i = 0; i < len; i++){
    //   if(in[i] == '-'){
    //     // if(empty >= floatlen){
    //      // options += '-';
    //    // }
    //     empty ++;
    //   }
    // }
    string current(in.size(), '-');
    //cout << "options: " << options << endl;

    //wordleHelper(input, options, 0, added, words, dict);
    //wordleHelper2(input, 0, options, words, dict);
    wordleHelper3(input, current, options,
        0, empty, words, dict);
    return words;
}


void wordleHelper3(const string& input, string& current, string& floating,
  int ind, int empty, set<string>& words, const set<string>& dict){
    if((int)floating.size() > empty){
      return;
    }

    if(ind == (int)input.size()){
      if(floating.empty() && dict.count(current)){
        words.insert(current);
      }
      return;
    }

    if(input[ind] != '-'){
      current[ind] = input[ind];
      wordleHelper3(input, current, floating, ind +1, empty, words, dict);
    }
    else {
      //int nextempt = empty - 1;

      int remaining = count(input.begin() + ind, input.end(), '-');
      if((int)floating.size() == remaining){
      set<char> used;
      for(int i = 0; i < (int)floating.size(); i++){
        if(used.count(floating[i])) continue;
        current[ind] = floating[i];
        used.insert(floating[i]);
        string newFloat = floating;
        newFloat.erase(i, 1);
        wordleHelper3(input, current, newFloat, ind +1, empty-1, words, dict);
      }}
      else{
        for(char i = 'a'; i <= 'z'; i++){
          current[ind] = i;
          string newFloat = floating;
          int j = newFloat.find(i);
          if(j != (int)string::npos){
            newFloat.erase(j, 1);
          }
          wordleHelper3(input, current, newFloat, ind+1, empty-1, words, dict);
        }
      }
    }


  }

// void wordleHelper(
//   std::string& input,
//   std::string& options, int start, std::unordered_set<std::string>& added, std::set<std::string>& words, const std::set<std::string>& dict
// ){
//   cout << "helper: " << input << " " << options << " " << start << endl;
//   unsigned int olen = options.length();
//   // if(olen == 0){
//   //   if(added.find(options) == added.end()){
//   //     added.insert(options);
//   //     addWord(input, options, 0, 0, words, dict, added);
//   //   } 
//   //   return;
//   // }
//   if(added.find(options) == added.end()){
//         added.insert(options);
//         addWord(input, options, 0, 0, words, dict, added);
//   } 
//   if(start == (int)olen-1) return;
//   for(size_t i = start; i < options.length(); ++i){
//     if(options[i] == options[start]) continue;
//     swap(options[start], options[i]);
//     wordleHelper(input, options, start+1, added, words, dict);
//     swap(options[start], options[i]);
//   }}
 

// void addWord(std::string in, const std::string& options, unsigned int ind, int optionind, std::set<std::string>& words, const std::set<std::string>& dict, std::unordered_set<std::string>& added){
//     //cout << "adding " << options << endl;
//     //cout << "ok ind =  " << ind << " letter = " << in[ind] << " len = " << in.length() << endl;
//     if(!pruning(in.substr(0, ind), dict)) return;
//     // final word
//     if(ind == in.length()){

//       //std::cout << "going to add " <<  in << std::endl;
//       if(dict.find(in) != dict.end()){
//         //cout << "real word! " << in << endl;
//         words.insert(in);
//       }
//       return;
//     }

//     //cout <<" word not done! " << endl;
//     if(in[ind] == '-'){
//       if(options[optionind] != '-'){
//         in[ind] = options[optionind];
//         if(ind+1 == in.length() && dict.find(in) != dict.end()){
//           words.insert(in);
//           return;
//         }
//         addWord(in, options, ind+1, optionind + 1, words, dict, added);
//       }
//       else{
//         for(char l = 97; l < 123; l++){
//           in[ind] = l;
//           addWord(in, options, ind+1, optionind+1, words, dict, added);
//         }
//       }
//   }
//   else{
//     if(ind+1 == in.length() && dict.find(in) != dict.end()){
//           words.insert(in);
//           return;
//      }
//     addWord(in, options, ind+1, optionind, words, dict, added);
//   }
// }

// bool pruning(const string& prefix, const set<string>& dict){
//   auto it = dict.lower_bound(prefix);
//   return(it != dict.end() && it->compare(0, prefix.length(), prefix)==0);

// }

// Define any helper functions here

// void wordleHelper2(string& input, int ind, string floating, set<string>& words, const set<string>& dict){
//   if(ind == input.size()){
//     if(floating.empty() && (dict.find(input) != dict.end())){
//       words.insert(input);
//     }
//     return;
//   }

//   if(input[ind] != '-'){
//     wordleHelper2(input, ind +1, floating, words, dict);
//     return;
//   }

//   else{
//     unordered_set<char> usedFloaters;
//     for(int i = 0; i < floating.size(); ++i){
//       if(usedFloaters.count(floating[i])) continue;
//       usedFloaters.insert(floating[i]);

//       char c = floating[i];
//       input[ind] = c;
//       string next = floating;
//       next.erase(i, 1);
//       wordleHelper2(input, ind+1, next, words, dict);
//       input[ind] = '_'; 
//     }

//     if(floating.size() < count(input.begin(), input.end(), '-')){
//       for(char c = 'a'; c <= 'z'; ++c){
//         input[ind] = c;
//         wordleHelper2(input, ind+1, floating, words, dict);
//         input[ind] = '-';
//       }
//     }
//   }
// }


  // if(start == 0) {
  //   cout << "2 " << endl; 
  //   if(added.find(options) == added.end()){
  //     added.insert(options);
  //     addWord(input, options, 0, 0, words, dict, added);
  //   } 
  //   cout << "done ? " << endl;
  // }

  // string permute = options;
  // cout << "3" << endl;
  // for(int i = olen; i >= start; i--){
  //   cout << " i = " << i << endl;
  //   wordleHelper(input, permute, start+1, added, words, dict);
  //   cout << "Swapping: " << permute << " "<< start << " " << i;
  //   if(i == start) continue;
  //   if(options[i] == options[start])continue;
  //   swap(permute, start, i);
  //   cout << "permuted: " << permute << endl;
  //   if(added.find(permute) == added.end() ){
  //     added.insert(permute);
  //     addWord(input, permute, 0, 0, words, dict, added);
  //   }
    
  // }


// void swap(std::string& s, int first, int second){
//   if(!(first < s.length() && second < s.length())){
//    std::cout << "string swap indexing error" << std::endl;
//     return;
//   }
//   char temp = s[first];
//   s[first] = s[second];
//   s[second] = temp;
// }
