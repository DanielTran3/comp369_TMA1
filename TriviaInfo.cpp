#include "TriviaInfo.h"

TriviaInfo::TriviaInfo() {
	
}
TriviaInfo::~TriviaInfo() {
	
}
void TriviaInfo::addAnswer(std::string answer) {
		_answers.push_back(answer);	
}
void TriviaInfo::clearQuestion() {
	_question.clear();
}
void TriviaInfo::clearAnswers() {
//	for (int i = 0; i < _answers.size(); i++) {
//		_answers[i].clear();
//	}
	_answers.clear();
}

void TriviaInfo::setQuestion(std::string question) {
	_question = question;
}
std::string TriviaInfo::getQuestion() {
	return _question;
}

void TriviaInfo::setAnswer(int index, std::string answer) {
	if (index > 0 && index < _answers.size()) {
		_answers[index] = answer;		
	}
}
std::string TriviaInfo::getAnswer(int index) {
	if (index >= 0 && index < _answers.size()) {
		return _answers.at(index);	
	}
	return "";
}
