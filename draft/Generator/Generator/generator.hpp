//
//  generator.hpp
//  generator
//
//  Created by Ariel Flahaut on 27/11/2022.
//

#include <fstream>      //For files
#include <stdlib.h>     // include rand
#include <iostream>
#include <vector>
using namespace std;
std::vector<std::vector<int>> listpawns();
std::vector<std::vector<int>> listpawnsclosed();
std::vector<std::vector<int>> listpawns_6_white_6_black();
std::vector<std::vector<int>> listpawnsaced();
std::vector<std::vector<int>> listpawns_0_4();
void file_generator_general(int); //Input number of pawns and return a file with every possible closed position with only pawns
void file_generator_100_closed(int);
void file_generator_6_white_6_black(int);
void file_generator_general_spaced(int position_amount);
void file_generator_0_to_4(int position_amount);
void database_edit(); // cannot be implemented


class ArrayElement { // Array element class
public:
    ArrayElement(int piece, int piece_color, int square_color);
    ArrayElement();


    bool is_empty(); // Checks if the position is empty

    int get_piece();

    int get_piece_color();
    
    int get_square_color();
    
    int piece;
    int piece_color;
    int square_color; 
};

/*Notation: Chess board representation

 An array of 64 elements, with each element of the array from a class, with attributes "piece" indicating the piece on said square , "piece_color" indicating the color of the piece, and "square_color" indicating the color of the square.
 
 The pieces shall be named: king = 1, queen = 2, bishop = 3, knight = 4, rook (castle) = 5, pawn = 6
 
 For the color of the pieces: white = 0, black = 1
 
 For the color of the square: white = 0, black = 1
 
 For example: The first row of an untouched chess game would be:
 {elem1, elem2, elem3, elem4, elem5, elem6, elem7, elem8, ... }
 
 where the first piece, (a black rook in the upper left corner);
 elem1.get_piece() = 5 (a rook)
 elem1.get_piece_color() = 1 (a black piece)
 elem1.get_square_color() = 0 (a white square)

*/

class Chessboard{
    /* Chess board is an array of 64 where the elements are ArrayElements from the class above.
     
     To access an element in the board just do board[i] where i is a number from 1 to 64
     
     The goal of the function replace element is to intake a position and an ArrayElement and to replace the current element with the one that is inputed at the position which is inputed.*/
public:
    Chessboard();
    Chessboard(ArrayElement);
    void replace_element(int, int, int);
    ArrayElement board[64];

    double closeness(Chessboard); //Etienne, input a position consiting only of pawns, return a percentage
    /*Strategy:
     Since we are only considering pawns, we iterate over the board, counting the number of closed pawns (pawns that have another pawn in front of them and that don't have a pawn to their diagonal). Then, since we know the total number of pawns on the board, we return a ratio of the number of closed pawns to the total number of pawns.
     */
    
    double openness(Chessboard); //Etienne, input a position consiting only of pawns, return a percentage
    /*Strategy:
    We iterate over the board, counting the number of open pawns (pawns that don't have another pawn in front of them or that have at least one pawn to their diagonal). We return a ratio of the number of closed pawns to the total number of pawns.
     */
    void completion();// Shirelle, input a board with only pawns and fill the board with other pieces randomly
    
    int get_total_pawns(Chessboard);// inputs a chessboard and returns how many pawns are in the chess board
    
    int get_white_pawns(Chessboard); //inputs a chessboard and returns how many white pawns there are
    
    int get_black_pawns(Chessboard); //inputs a chessboard and returns how many black pawns there are
    
    void visualize(); // inputs a chessboard and returns a visual representation
    
    void single_generator(int pawns); //Input number of pawns and return a random closed position with only pawns
    void single_generator_spaced(int pawns);

    bool check(); // check if the king is in check or not

    //Attributes
    int find_pawn_in_column(Chessboard, int, int);
    
    ArrayElement element;
    //double closeness; // to be used? - needs to be decided 
    //double openness;
};

