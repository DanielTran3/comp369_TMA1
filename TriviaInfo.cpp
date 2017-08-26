#include "TriviaInfo.h"

// Empty constructor and destructor
TriviaInfo::TriviaInfo() {
	
}
TriviaInfo::~TriviaInfo() {
	
}

// Add an answer to the answer list
void TriviaInfo::addAnswer(std::string answer) {
		_answers.push_back(answer);	
}

// Clear the current question
void TriviaInfo::clearQuestion() {
	_question.clear();
}

// Clear all answers in the answers list
void TriviaInfo::clearAnswers() {
	_answers.clear();
}

// Set a question
void TriviaInfo::setQuestion(std::string question) {
	_question = question;
}

// Get the current question
std::string TriviaInfo::getQuestion() {
	return _question;
}

// Set an answer at an index
void TriviaInfo::setAnswer(int index, std::string answer) {
	if (index > 0 && index < _answers.size()) {
		_answers[index] = answer;		
	}
}

// Get an answer at an index
std::string TriviaInfo::getAnswer(int index) {
	if (index >= 0 && index < _answers.size()) {
		return _answers.at(index);	
	}
	return "";
}
