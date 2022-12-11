#include "class_decl.h"

Square::Square() {

};
Square::Square(COLOR color, cv::Rect rec, int x, int y) {
	this->color = color;
	this->rec = rec;
	this->position = cv::Point(x, y);
}
Board::Board() {
	this->left = 10000;
	this->top = 10000;
	this->bottom = 0;
	this->right = 0;

}
Board::Board(int left, int right, int top, int bottom) {
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}
Player::Player() {
	this->color = true;
}
Player::Player(bool color) {
	this->color = color;
}