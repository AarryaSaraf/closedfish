#pragma once
#define DEBUG 1 //turn off for final version

#include <iostream>
#include <stdint.h>


class CFBoard {
  public:

    // ----- Constructors, Formatting, Representation -----
    
    CFBoard();

    CFBoard(std::string FEN) : CFBoard() { fromFEN(FEN); }
    CFBoard(uint64_t pawnBoard, uint64_t knightBoard, uint64_t bishopBoard,
            uint64_t rookBoard, uint64_t queenBoard, uint64_t kingBoard,
            int enPassantTarget, int castleCheck, uint64_t blackBoard,
            uint64_t whiteBoard, bool turn)
        : pawnBoard(pawnBoard), knightBoard(knightBoard),
          bishopBoard(bishopBoard), rookBoard(rookBoard),
          queenBoard(queenBoard), kingBoard(kingBoard),
          enPassantTarget(enPassantTarget), castleCheck(castleCheck),
          blackBoard(blackBoard), whiteBoard(whiteBoard), turn(turn) {}
    
    void fromFEN(std::string FEN); // TO DO
    std::string toFEN();


	/**
	* @brief Returns printable board representation.
	*/
    std::string getRepr();
  
	/**
	* @brief This function takes a pieceId and returns the associated
	* character.
	*
	* @param pieceId : <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the
	* piece is black.
	*
	* @return P/N/B/R/Q/K depending on the piece, lowercase if black piece.
	*/
    char pieceIdToChar(int pieceId);

	/**
	* @brief This function takes a pieceId and returns the associated
	* character.
	*
	* @param pieceChar : <char> P/N/B/R/Q/K depending on the piece, lowercase
	* if black piece.
	*
	* @return <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the piece is
	* black.
	*/
    int pieceCharToId(char pieceChar);



    // ----- Get functions -----


	/**
	* @brief This function returns the bitboard for one of the two chess piece
	* colors.
	*
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> copy of stored attribute for all pieces of a color.
	*/
    uint64_t getColorBitBoard(bool color);


	/**
	* @brief This function returns a bitboard for a piece of a specific color.
	*
	* @param pieceId : <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the
	* piece is black.
	*
	* @return <uint64_t> bitboard for the specified piece (color taken into
	* account).
	*/
    uint64_t getPieceColorBitBoard(int pieceId);


	/**
	* @brief This function returns a reference to a board, in order to make
	* iterating over boards easier.
	*
	* @param boardIndex : Index of the required piece bitboard (identical to
	* pieceId>>1).
	*
	* @return <uint64_t &> reference to private attribute bitboard.
	*/
    uint64_t &getPieceBoardFromIndex(int boardIndex);
    

	/**
	* @brief Returns whose turn it is to play.
	*
	* @return Material count for that color.
	*/
    bool getCurrentPlayer();


	/**
	* @brief This function returns the piece id from a specific tile.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	*
	* @return <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the piece is
	* black.
	*/
    int getPieceFromCoords(int tile);


	/**
	* @brief This function returns whether or not there is a piece of pieceId
	* in the specified tile.
	*
	* @param pieceId : <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the
	* piece is black.
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	*
	* @return <bool> 1 if the piece is on that tile, 0 otherwise.
	*/
    bool getBit(int pieceId, int tile);


	/**
	* @brief Computes the material count for a specific color.
	*
	* @param color : 1 for black, 0 for white.
	*
	* @return Material count for that color.
	*/
    int getMaterialCount(bool color);

    // ----- Manipulation -----

	/**
	* @brief Makes a legal chess move. Pawns are promoted to queens by default.
	*
	* @param startTile : start tile for move.
	* @param endTile : end tile for move.
	* @param pawnPromotionType : one of 2/4/6/8 (+1 if black) => N/B/R/Q which indicates the type to which the pawn is promoted in the event of a pawn promotion move.
	*
	* @return void.
	*/
    void movePiece(int starttile, int endtile, int pawnPromotionType = -1);


	/**
	* @brief Forces the undo of a move. Makes assumptions on castling and en passant (they do not get updated).
	*
	* @param startTileLastTurn : start tile for last move.
	* @param endTileLastTurn : end tile for last move.
	* @param capturedPiece : pieceId for any potentially captured piece last turn. -1 (no piece) by default.
	*
	* @return void.
	*/
    void forceUndo(int startTileLastTurn, int endTileLastTurn, int capturedPiece);


	// -------   Non-Legal Manipulation -------

#if DEBUG == 1
	/**
	* @brief Functionally the same as addPiece but is only exposed when debug is enabled
	*/
	void forceAddPiece(int pieceId, int tile) {
		addPiece(pieceId, tile);
	}

	/**
	* @brief Functionally the same as removePiece but is only exposed when debug is enabled
	*/
	void forceRemovePiece(int tile) {
		removePiece(tile);
	}
#endif

    // ----- Ruleset -----

	/**
	* @brief This function returns the naive move pattern for a rook.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> bitboard for where a rook at tile can move/capture.
	*/
    uint64_t getCardinals(int tile, bool color);


	/**
	* @brief This function returns the naive move pattern for a bishop.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> bitboard for where a bishop at tile can move/capture.
	*/
    uint64_t getDiagonals(int tile, bool color);


	/**
	* @brief This function returns the naive move pattern for a knight.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> bitboard for where a knight at tile can move/capture.
	*/
    uint64_t getKnightPattern(int tile, bool color);

	/**
	* @brief This function returns the naive move pattern for a king.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> bitboard for where a king at tile can move/capture.
	*/
    uint64_t getKingPattern(int tile, bool color);


	/**
	* @brief This function returns the naive move pattern for a pawn.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	* @param color : 1 for black, 0 for white.
	*
	* @return <uint64_t> bitboard for where a pawn at tile can move/capture.
	*/
    uint64_t getPawnPattern(int tile, bool color);


	/**
	* @brief This function returns the naive move pattern for a pieceId piece.
	*
	* @param pieceId : <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the
	* piece is black.
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	*
	* @return <uint64_t> bitboard for where a piece of pieceId at tile can
	* move/capture.
	*/
    uint64_t getLegalMoves(int pieceId, int tile);


	/**
	 * @brief Checks if the current king is being checked by the opponent or not
	 *
	 * @param color current color
	 * @param coordA (optional) pretend that there is nothing here
	 * @param coordB (optional) pretend that there is something here with the
	 * current color
	 * @return true if it is checked
	 * @return false if it is not checked
	 */
    bool naiveCheckCheck(bool color, int coordA = -1, int coordB = -1);

    // Misc

    friend bool operator==(const CFBoard &board1, const CFBoard &board2) {
        return board1.pawnBoard == board2.pawnBoard &&
               board1.knightBoard == board2.knightBoard &&
               board1.bishopBoard == board2.bishopBoard &&
               board1.rookBoard == board2.rookBoard &&
               board1.queenBoard == board2.queenBoard &&
               board1.kingBoard == board2.kingBoard &&
               board1.enPassantTarget == board2.enPassantTarget &&
               board1.castleCheck == board2.castleCheck &&
               board1.blackBoard == board2.blackBoard &&
               board1.whiteBoard == board2.whiteBoard &&
               board1.turn == board2.turn;
    }

  private:
    uint64_t pawnBoard;
    uint64_t knightBoard;
    uint64_t bishopBoard;
    uint64_t rookBoard;
    uint64_t queenBoard;
    uint64_t kingBoard;

    int enPassantTarget; // a single coordinate from 0-63
    int castleCheck; // 4 bits of information (long black - short black- long
                     // white - short white)

    uint64_t blackBoard;
    uint64_t whiteBoard;

    bool turn; // 0 for white, 1 for black


	/**
	* @brief This function places a piece on a given tile. It will replace any
	* piece on the target tile.
	*
	* @param pieceId : <int> equal to 0/2/4/6/8/10 for P/N/B/R/Q/K, +1 if the
	* piece is black.
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	*
	* @return void
	*/
	void addPiece(int pieceId, int tile);


	/**
	* @brief This function removes a piece on a given tile.
	*
	* @param tile : <int> from 0 to 63, in the order (a8, b8, ..., h8, a7, ...,
	* h7, ......, a1, ..., h1).
	*
	* @return void
	*/
	void removePiece(int tile);

    /*
        a8 = 2^0
        b8 = 2^1
        ...
        h1 = 2^63
    */
};
