#ifndef _TRIVIAINFO_H

#include <string>
#include <vector>

#define NUM_QUESTIONS 4

#define ALL 1
#define UNIT 2
#define CHAPTER 3

#define UNIT_1 1
#define UNIT_2 2
#define UNIT_3 3
#define UNIT_4 4

#define UNIT_1_SIZE 6
#define UNIT_2_SIZE 5
#define UNIT_3_SIZE 5
#define UNIT_4_SIZE 6

#define UNIT_1_LAST 6
#define UNIT_2_LAST 11
#define UNIT_3_LAST 16
#define UNIT_4_LAST 22

#define CHAPTER_1 1
#define CHAPTER_2 2
#define CHAPTER_3 3
#define CHAPTER_4 4
#define CHAPTER_5 5
#define CHAPTER_6 6
#define CHAPTER_7 7
#define CHAPTER_8 8
#define CHAPTER_9 9
#define CHAPTER_10 10
#define CHAPTER_11 11
#define CHAPTER_12 12
#define CHAPTER_13 13
#define CHAPTER_14 14
#define CHAPTER_15 15
#define CHAPTER_16 16
#define CHAPTER_17 17
#define CHAPTER_18 18
#define CHAPTER_19 19
#define CHAPTER_20 20
#define CHAPTER_21 21
#define CHAPTER_22 22

#define NUM_CHAPTERS 22

class TriviaInfo {
	private:
		std::string _question;
		std::vector<std::string> _answers;
	public:
		TriviaInfo();
		~TriviaInfo();
		
		void addAnswer(std::string answer);
		void clearQuestion();
		void clearAnswers();
		
		void setQuestion(std::string question);
		std::string getQuestion();
		
		
		void setAnswer(int index, std::string answer);
		std::string getAnswer(int index);
		
};

#endif
