#include <wordgrid.h>
/* ##########################################################################
#
# FILE          Wordfind.cc
#
# Description: Given a grid of words, build a program to search the wanted word
#              in any of the 8 directions. If the word is found, the program
#              have print "Found" and the grid with the letters of the word in
#              uppercase.  Otherwise, the program have to print "Not Found,"
#              while the grid is unchanged.
#
########################################################################## */

void capitalize_found_word(wordgrid & grid, string word,
                           int word_row[], int word_col[]){
  // PRE: Given a grid and a list of locations of each letter of the word
  // POST: For each letter word, use the grid-class set method to capitalize
  // the letter by the locations in the location list.

  // Cite: C++ Passing Arrays to Functions - Tutorialspoint
  // Url: https://www.tutorialspoint.com/cplusplus/cpp_passing
  //      _arrays_to_functions.htm
  // Desc: How to pass an array to another function

  int word_length = word.length();
  char letter;

  // For each letter in the word, capitalize the letter using the grid-class
  // method set using the location of row and column and the letter.
  for(int i = 0; i < word_length; i++){
    letter = (grid.get(word_row[i], word_col[i])) - 32;
    grid.set(word_row[i], word_col[i], letter);
  }
}

bool in_bounds(wordgrid & grid, int row, int column){
  // PRE: Given a grid and a location
  // POST: Return true if the location is in the bound of the grid. Return
  // false if the location is outside of the bound of the grid.

  int g_size = grid.size();

  // If the location are smaller than zero or bigger than g-size, then
  // the location is outside of the grid.
  if(((row < 0) || (row >= g_size)) || ((column < 0) || (column >= g_size))){
    return false;
  }
  return true;
}

bool confirm_pattern(wordgrid & grid, string word, int letter_row,
                     int letter_col, int dr_row, int dr_col){
   // PRE: Given a grid, wanted-word, and the location of the first letter out
   //      of the word, and a direction
   // POST: If the second letter of the wanted-word is found in the given
   //       direction, check if the third word is also match and so on. If
   //       all letters of the wanted word is found in the given direction,
   //       return true. Otherwise, return false.

  int word_length = word.length();
  int item_col[50];
  int item_row[50];

  // Functions that will call later in the code.
  bool in_bounds(wordgrid & grid, int row, int column);
  void capitalize_found_word(wordgrid & grid, string word,
                             int *item_row, int *item_col);
  for(int i = 0; i < word_length; i++){

    // in-bound() check if the next location from the starting location is
    // still in the bound of the word grid.
    if(in_bounds(grid, letter_row, letter_col) == true){

      // If the next location is in bound, but the next letter is not found in
      // the next location, return False
      if(grid.get(letter_row, letter_col) != word[i]){
        return false;
      }
    }

    // If the next location is not in bound, stop checking and return false.
    if(in_bounds(grid, letter_row, letter_col) == false){
      return false;
    }

    // Every time, a letter of the word is found in the direction, save the
    // new location, and move on to the next location in the given direction.
    item_col[i] = letter_col;
    item_row[i] = letter_row;
    letter_row += dr_row;
    letter_col += dr_col;
  }

  // If all letter is found in the given direction, capitalize the letters of
  // the word in that direction; and return true.
  capitalize_found_word(grid, word, item_row, item_col);
  return true;
}

bool find_pattern(wordgrid & grid, string word,
                  int start_row, int start_col){
  // PRE: Given a grid, wanted-word, and the location of the first letter out
  //      of the word
  // POST: From the first-word location, check for a pattern of letters in all
  //       eight directions. If the pattern is found in a single direction,
  //       return true. Otherwise, return false if no pattern is found in any
  //       directions.

  bool result = false;

  // Function that will call later in the code.
  bool confirm_pattern(wordgrid & grid, string word, int start_row,
                       int start_col, int dr_row, int dr_col);

  // Eigth-directions by for-loops
  // For each direction created by the for-loops, check if a pattern of letters
  // is found in that direction.
  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){

      // If the direction is not (0, 0), then send the directions
      if((i || j) != 0){
        result = confirm_pattern(grid, word, start_row, start_col, i, j);
        if(result == true){
          return true;
        }
      }
    }
  }
  return false;
}

bool find(string word, wordgrid & grid){
  // PRE: word consists of lowercase letters
  // POST: If word is found in grid, starting anywhere and in any of the 8
  //       directions, it is converted to uppercase in the grid, and true is
  //       returned. Otherwise, grid is unchanged, and false is returned.

  word = word;
  grid = grid;

  int g_size = grid.size();
  char first_letter = word[0];
  bool pattern = false;

  // Function that will call later in the code.
  bool find_pattern(wordgrid & grid, string word,
                    int start_row, int start_col);

  // Find the all the locations of the given word's first letter in the
  // grid. From each location, start to find a pattern.
  for(int i = 0; i < g_size; i++){
    for (int j = 0; j < g_size; j++){
      if(grid.get(i, j) == first_letter){
        pattern = find_pattern(grid, word, i, j);
        if(pattern == true){
          return true;
          }
      }
    }
  }
  return false;
}
//------------------------------------------------------------------------
int main(){
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search fors
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  std::cin >> dim;  // read the dimension

  // Read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    std::cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  std::cin >> word;              // read the word

  // SEARCH
  found = find(word, grid);

  // REPORT
  if (found){
    std::cout << "FOUND!" << std::endl;
    std::cout << grid;
  }
  else
    std::cout << "NOT FOUND!" << std::endl;
}
