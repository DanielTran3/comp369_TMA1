#ifndef _USEROPTIONS_H

#include "TriviaInfo.h"
#include <string>
#include <vector>

class UserOptions {
	private:
		int _score;
		int _quizType;
		int _unit;
		int _chapter;
		int _numQuestions;
		std::vector<std::string> _listOfChapters;
	public:
		UserOptions();
		~UserOptions();
		
		void setChaptersBasedOnOptions();
		void fillFilenames(int start, int end);
		
		void setScore(int score);
		void incrementScore();
		int getScore();
		
		void setQuizType(int quizType);
		int getQuizType();
		
		void setUnit(int unit);
		int getUnit();
		
		void setChapter(int chapter);
		int getChapter();
		
		void setNumQuestions(int numQuestions);
		int getNumQuestions();
		
		std::vector<std::string> getListOfChapters();
};
#endif
