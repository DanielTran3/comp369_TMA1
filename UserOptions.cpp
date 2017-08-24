#include "UserOptions.h"

UserOptions::UserOptions() {
	_score = 0;
	_quizType = 0;
	_unit = 0;
	_chapter = 0;
	_numQuestions = 0;
}

UserOptions::~UserOptions() {
	//delete[] _listOfChapters;
}

void UserOptions::incrementScore() {
	_score++;
}


void UserOptions::setChaptersBasedOnOptions() {
	int start = 0;
	int end = 0;
	if (_quizType == ALL) {
		//_listOfChapters = new string[NUM_CHAPTERS];
		start = CHAPTER_1;
		end = CHAPTER_22 + 1;
		_quizName = "Questions From Every Chapter";
	}
	if (_quizType == UNIT) {
		_quizName = "Questions From A Unit";
		if (_unit == UNIT_1) {
			//_listOfChapters = new string[UNIT_1_SIZE];
			start = CHAPTER_1;
			end = UNIT_1_LAST + 1;
		}
		if (_unit == UNIT_2) {
			//_listOfChapters = new string[UNIT_2_SIZE];			
			start = UNIT_1_LAST + 1;
			end = UNIT_2_LAST + 1;
		}
		if (_unit == UNIT_3) {
			//_listOfChapters = new string[UNIT_3_SIZE];
			start = UNIT_2_LAST + 1;
			end = UNIT_3_LAST + 1;
		}
		if (_unit == UNIT_4) {
			//_listOfChapters = new string[UNIT_4_SIZE];
			start = UNIT_3_LAST + 1;
			end = UNIT_4_LAST + 1;
		}
	}
	if (_quizType == CHAPTER) {
		_quizName = "Questions From A Chapter";
		//_listOfChapters = new string[1];
		start = _chapter;
		end = _chapter + 1;
	}
	
	fillFilenames(start, end);
}

void UserOptions::fillFilenames(int start, int end) {
	_listOfChapters.clear();
	char tempString[30];
	int diff = end - start;
	int chapterNum = start;
	for (int i = 0; i < diff; i++) {
		snprintf(tempString, sizeof(tempString), "%s%d%s", "questions/chapter", chapterNum, ".txt");
		//filenameList[i - 1] = tempString;
		_listOfChapters.push_back(tempString);
		printf("In: %s\n", _listOfChapters.at(i).c_str());
		chapterNum++;
	}
}

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
