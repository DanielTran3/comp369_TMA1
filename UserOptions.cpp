#include "UserOptions.h"

// Intialize the user's options upon creation
UserOptions::UserOptions() {
	_score = 0;
	_quizType = 0;
	_unit = 0;
	_chapter = 0;
	_numQuestions = 0;
}

UserOptions::~UserOptions() {

}

// Increment the score
void UserOptions::incrementScore() {
	_score++;
}

// Method to get a list of chapters that questions will be pulled from based on what the user has inputted
void UserOptions::setChaptersBasedOnOptions() {
	int start = 0;
	int end = 0;
	
	// If the user selected "Questions From Every Chapter", then get a list of all chapters
	if (_quizType == ALL) {
		start = CHAPTER_1;
		end = CHAPTER_22 + 1;
		_quizName = "Questions From Every Chapter";
	}
	
	// If the user selected "Questions From A Unit", then get a list of chapters based on the
	// unit the user selected
	if (_quizType == UNIT) {
		_quizName = "Questions From A Unit";
		if (_unit == UNIT_1) {
			start = CHAPTER_1;
			end = UNIT_1_LAST + 1;
		}
		if (_unit == UNIT_2) {
			start = UNIT_1_LAST + 1;
			end = UNIT_2_LAST + 1;
		}
		if (_unit == UNIT_3) {
			start = UNIT_2_LAST + 1;
			end = UNIT_3_LAST + 1;
		}
		if (_unit == UNIT_4) {
			start = UNIT_3_LAST + 1;
			end = UNIT_4_LAST + 1;
		}
	}

	// If the user selected "Questions From A Chapter", then get the chapter that the user selected
	if (_quizType == CHAPTER) {
		_quizName = "Questions From A Chapter";
		start = _chapter;
		end = _chapter + 1;
	}
	
	fillFilenames(start, end);
}

// Method to get store the list of chapters into the UserOptions list
void UserOptions::fillFilenames(int start, int end) {
	_listOfChapters.clear();
	char tempString[30];
	int diff = end - start;
	int chapterNum = start;
	for (int i = 0; i < diff; i++) {
		snprintf(tempString, sizeof(tempString), "%s%d%s", "questions/chapter", chapterNum, ".txt");
		_listOfChapters.push_back(tempString);
		chapterNum++;
	}
}

// Getters and setters for UserOptions properties
void UserOptions::setScore(int score) {
	_score = score;
}

int UserOptions::getScore() {
	return _score;
}

void UserOptions::setNumQuestions(int numQuestions) {
	_numQuestions = numQuestions;
}

int UserOptions::getNumQuestions() {
	return _numQuestions;
}

void UserOptions::setQuizType(int quizType) {
	_quizType = quizType;
}

int UserOptions::getQuizType() {
	return _quizType;
}

void UserOptions::setUnit(int unit) {
	_unit = unit;
}

int UserOptions::getUnit() {
	return _unit;
}

void UserOptions::setChapter(int chapter) {
	_chapter = chapter;
}

int UserOptions::getChapter() {
	return _chapter;
}

void UserOptions::setQuizName(std::string quizName) {
	_quizName = quizName;
}

std::string UserOptions::getQuizName() {
	return _quizName;	
}

std::vector<std::string> UserOptions::getListOfChapters() {
	return _listOfChapters;
}
