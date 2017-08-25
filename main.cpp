#include "pocketTrivia.h"
#include <sstream>

int convertKeyPress() {
	if (key[KEY_1]) { return 1; }
	else if (key[KEY_2]) { return 2; }
	else if (key[KEY_3]) { return 3; }
	else if (key[KEY_4]) { return 4; }
	else if (key[KEY_5]) { return 5; }
	else if (key[KEY_6]) { return 6; }
	else if (key[KEY_7]) { return 7; }
	else if (key[KEY_8]) { return 8; }
	else if (key[KEY_9]) { return 9; }
	else if (key[KEY_Q]) { return 10; }
	else if (key[KEY_W]) { return 11; }
	else if (key[KEY_E]) { return 12; }
	else if (key[KEY_R]) { return 13; }
	else if (key[KEY_T]) { return 14; }
	else if (key[KEY_Y]) { return 15; }
	else if (key[KEY_U]) { return 16; }
	else if (key[KEY_I]) { return 17; }
	else if (key[KEY_O]) { return 18; }
	else if (key[KEY_P]) { return 19; }
	else if (key[KEY_A]) { return 20; }
	else if (key[KEY_S]) { return 21; }
	else if (key[KEY_D]) { return 22; }
	else { return -1; }
}

void highlightKey(std::string line, int xOffset, int newLineSpacing, int color) {
	char keyToPress[2];
	strncpy(keyToPress, line.c_str(), 1);
	textout_ex(screen, font, keyToPress, xOffset, newLineSpacing, color, -1);
}

void drawImage(const char * filename) {
	BITMAP *image;
	image = load_bitmap(filename, NULL);
	if (!image) {
		allegro_message("Error Loading %s", filename);
	}
	
	blit(image, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	destroy_bitmap(image);
}

void drawRandomImage() {
	int randomBackground = rand() % NUM_BACKGROUNDS + 1;
	std::ostringstream numToString;
	numToString << randomBackground;
	std::string tempString = "images/background" + numToString.str() + ".pcx";
	drawImage(tempString.c_str());
}

void drawTitle() {
	// Replace the title with a blit to the screen with a better title
	textout_centre_ex(screen, font, TITLE, WIDTH / 2, HEIGHT / 2, BLACK, 0);
	textout_centre_ex(screen, font, "Press Space to Continue", WIDTH / 2, HEIGHT / 2 + 2 * LINE_SPACING, WHITE, 0);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void drawFinal(UserOptions *user) {
	// Replace rectfill with blit of image
	drawRandomImage();
	textprintf_centre_ex(screen, font, WIDTH / 2, HEIGHT / 4, WHITE, 0, "Your Final Score: %i/%i", user->getScore(), user->getNumQuestions());
	textout_centre_ex(screen, font, "Press Space To Restart of ESC to Quit", WIDTH / 2, HEIGHT / 2, WHITE, 0);
}

void displayInstructions() {
	drawRandomImage();
	textout_centre_ex(screen, font, "Instructions", WIDTH / 2, HEIGHT / 4, WHITE, 0);
	textout_centre_ex(screen, font, "To answer a question,", WIDTH / 2, HEIGHT / 4 + 2 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "press the numbers 1, 2, 3, or 4 corresponding", WIDTH / 2, HEIGHT / 4 + 3 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "to the answer you want to submit!", WIDTH / 2, HEIGHT / 4 + 4 * LINE_SPACING, WHITE, 0);
	
	textout_centre_ex(screen, font, "Press Space to Continue", WIDTH / 2, HEIGHT / 4 + 6 * LINE_SPACING, WHITE, 0);
	rest(100);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void displayUserInformation(UserOptions *user) {
	int xOffset = WIDTH / 2;
	int yOffset = 5;
	textprintf_centre_ex(screen, font, xOffset, yOffset, WHITE, 0, "Pocket Trivia | Quiz Type: %s | Score: %i/%i", user->getQuizName().c_str(),
				  user->getScore(), user->getNumQuestions());
	hline(screen, 0, yOffset + 10, WIDTH, WHITE);
}

void chooseQuizType(UserOptions *user) {
	drawRandomImage();
	int xOffset = WIDTH / 4;
	textout_centre_ex(screen, font, "Choose A Quiz Type", 2 * xOffset, HEIGHT / 4, WHITE, 0);
	textout_ex(screen, font, "1 - Questions From Every Chapter", xOffset, HEIGHT / 4 + 2 * LINE_SPACING, WHITE, 0);
	textout_ex(screen, font, "1", xOffset, HEIGHT / 4 + 2 * LINE_SPACING, LIGHT_GREEN, 0);
	textout_ex(screen, font, "2 - Questions From A Unit", xOffset, HEIGHT / 4 + 4 * LINE_SPACING, WHITE, 0);
	textout_ex(screen, font, "2", xOffset, HEIGHT / 4 + 4 * LINE_SPACING, LIGHT_GREEN, 0);
	textout_ex(screen, font, "3 - Questions From A Chapter", xOffset, HEIGHT / 4 + 6 * LINE_SPACING, WHITE, 0);
	textout_ex(screen, font, "3", xOffset, HEIGHT / 4 + 6 * LINE_SPACING, LIGHT_GREEN, 0);

	rest(100);
	while(1) {
		if (keypressed()) {
			int value = convertKeyPress();
			if (value >= 1 && value <= 3) {
				user->setQuizType(value);
				break;
			}
		}
	}
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void chooseUnit(UserOptions *user) {
	drawRandomImage();
	std::ifstream file(UNITS);
	std::string line;
	int xOffset = 30;
	int newLineSpacing = HEIGHT / 4;
	
	textout_centre_ex(screen, font, "Choose A Unit", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	
	if (file.is_open()) {
		while(!file.eof()) {
			getline(file, line);
			textout_ex(screen, font, line.c_str(), xOffset, newLineSpacing, WHITE, 0);
			highlightKey(line, xOffset, newLineSpacing, LIGHT_GREEN);
			newLineSpacing += 2 * LINE_SPACING;
		}
	}
	
	rest(100);
	while(1) {
		if (keypressed()) {
			int value = convertKeyPress();
			if (value >= 1 && value <= 4) {
				user->setUnit(value);
				break;
			}
		}	
	}
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void chooseChapter(UserOptions *user) {
	drawRandomImage();
	std::ifstream file(CHAPTERS);
	std::string line;
	int xOffset = 30;
	int newLineSpacing = 0;
	textout_centre_ex(screen, font, "Choose A Chapter", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	if (file.is_open()) {
		while(!file.eof()) {
			getline(file, line);
			textout_ex(screen, font, line.c_str(), xOffset, newLineSpacing, WHITE, 0);
			highlightKey(line, xOffset, newLineSpacing, LIGHT_GREEN);
			newLineSpacing += 2 * LINE_SPACING;
		}
	}
	
	rest(100);
	while(1) {
		if (keypressed()) {
			int value = convertKeyPress();
			if (value >= 1 && value <= 22) {
				user->setChapter(value);
				break;
			}
		}
	}
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void chooseNumberOfQuestions(UserOptions *user) {
	drawRandomImage();
	int xOffset = WIDTH / 4;
	int newLineSpacing = HEIGHT / 4;
	textout_centre_ex(screen, font, "Choose The Number of Questions", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "1 - 3 Questions", xOffset, newLineSpacing, WHITE, 0);
	textout_ex(screen, font, "1", xOffset, newLineSpacing, LIGHT_GREEN, 0);
	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "2 - 5 Questions", xOffset, newLineSpacing, WHITE, 0);
	textout_ex(screen, font, "2", xOffset, newLineSpacing, LIGHT_GREEN, 0);
	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "3 - 10 Questions", xOffset, newLineSpacing, WHITE, 0);
	textout_ex(screen, font, "3", xOffset, newLineSpacing, LIGHT_GREEN, 0);
	
	rest(100);
	while(1) {
		if (keypressed()) {
			int value = convertKeyPress();
			if (value >= 1 && value <= 3) {
				if (value == 1) {
					user->setNumQuestions(3);
				}
				if (value == 2) {
					user->setNumQuestions(5);
				}
				if (value == 3) {
					user->setNumQuestions(10);
				}
				break;
			}
		}
	}
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void readFile(const char *filename) {
	std::string line;
	int textPos = 0;
	std::ifstream file(filename);
	if (file.is_open()) {
		getline(file, line);
		textprintf_ex(screen, font, 0, textPos, WHITE, 0, "Question: %s", line.c_str());
		while (!line.empty()) {	
			printf("%s\n", line.c_str());
			textprintf_ex(screen, font, 0, textPos, WHITE, 0, "%s", line.c_str());
			textPos += 10;
			getline(file, line);
		}
		file.close();
	}
}

void randomQuestion(const char *filename, int &answer, int questionNumber, TriviaInfo *triviaInfo) {
	int randomQuestionNumber = rand() % 10;
	printf("%i\n", randomQuestionNumber);
	int randomNumberCounter = 0;
	std::ostringstream numToString;
	numToString << questionNumber;
	
	std::ifstream file;
	std::string line;
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
	drawRandomImage();
	int textPos = 30;
	triviaInfo->clearQuestion();
	triviaInfo->clearAnswers();
	
	file.open(filename);
	if (file.is_open()) {
		while (randomNumberCounter < randomQuestionNumber) {
			getline(file, line);
			if (line.empty()) {
				randomNumberCounter++;
			}
		}
		
		getline(file, line);
		triviaInfo->setQuestion("Question " + numToString.str() + ": " + line);
		textPos = print_long_text(triviaInfo->getQuestion().c_str(), 0, textPos);
		while (!line.empty() && !file.eof()) {
			getline(file, line);
			//printf("%s", line.c_str());
			if (line[0] == '*') {
				line.erase(line.begin());
				answer = (int) line[0] - 48;
			}
			int oldTextPos = textPos;
			textPos = print_long_text(line.c_str(), 0, textPos);
			highlightKey(line.c_str(), 0, oldTextPos, LIGHT_GREEN);
			triviaInfo->addAnswer(line);
		}
		file.close();
	}
	else {
		printf("Error Opening File");
		allegro_message("Error Opening File");
	}
}

void checkAnswer(UserOptions *user, int userAnswer, int answer, Sound *soundEffect, TriviaInfo *triviaInfo) {
	int xOffset = 0;
	int yOffset = 400;
	printf("ANSWER %i\n", answer);
	rectfill(screen, xOffset, yOffset, WIDTH - 1, yOffset + 4* LINE_SPACING, BLACK);
	if (userAnswer == answer) {
		user->incrementScore();		
		soundEffect->setSoundEffect(CORRECT_SOUND);
		soundEffect->playSoundEffect();
		//drawImage();
		rest(100);
		printf("SCORE: %i\n", user->getScore());
		rect(screen, xOffset, yOffset, WIDTH - 1, yOffset + 4* LINE_SPACING, LIGHT_GREEN);
	}
	else {
		soundEffect->setSoundEffect(INCORRECT_SOUND);
		soundEffect->playSoundEffect();
		//drawImage();
		rect(screen, xOffset, yOffset, WIDTH - 1, yOffset + 4* LINE_SPACING, RED);
	}
	xOffset += 1;
	yOffset += 5;
	textout_ex(screen, font, triviaInfo->getQuestion().c_str(), xOffset, yOffset, WHITE, 0);
	textprintf_ex(screen, font, xOffset, yOffset + LINE_SPACING, WHITE, 0, "Your Answer   : %s", triviaInfo->getAnswer(userAnswer - 1).c_str());
	textprintf_ex(screen, font, xOffset, yOffset + 2 * LINE_SPACING, WHITE, 0, "Correct Answer: %s", triviaInfo->getAnswer(answer - 1).c_str());
	rest(1000);
}

void generateMultipleRandomQuestions(UserOptions *user, Sound *soundEffect, TriviaInfo *triviaInfo) {
	int questionNumber = 0;
	while(questionNumber < user->getNumQuestions()) {
		int randomChapterIndex = rand() % user->getListOfChapters().size();
		std::string randomChapter = user->getListOfChapters().at(randomChapterIndex);
		//printf("Chapter: %s | Question: %i\n", randomChapter.c_str(), questionNumber);		
		int answer = -1;

		randomQuestion(randomChapter.c_str(), answer, questionNumber, triviaInfo);
		displayUserInformation(user);
		rest(100);
		while(1) {
			if (keypressed()) {
				int value = convertKeyPress();
				if (value >= 1 && value <= 4) {
					checkAnswer(user, value, answer, soundEffect, triviaInfo);
					break;
				}
			}
		}
		questionNumber++;
	}
}

int print_long_text(const char *text, int x, int y) {
	int numberOfCharactersOnALine = WIDTH / CHARACTER_WIDTH;
	int numberOfCharactersInText = text_length(font, text) / CHARACTER_WIDTH;
	int pointer = 0;
	int newLine = 0;
	
	if (numberOfCharactersInText < numberOfCharactersOnALine) {
		//textout_ex(screen, font, text, x, y, WHITE, 0);
		textprintf_ex(screen, font, x, y, WHITE, 0, "%s", text);
		newLine += 2 * LINE_SPACING;
	}
	else {
		while(pointer < numberOfCharactersInText) {
			char tempString[numberOfCharactersOnALine];
			int numChars = pointer + numberOfCharactersOnALine > numberOfCharactersInText ? numberOfCharactersInText - pointer : numberOfCharactersOnALine;
			std::string temp = text;
			temp.copy(tempString, numChars, pointer);
			tempString[numberOfCharactersOnALine] = '\0';
			//sprintf("%i: %s\n", numChars, tempString);
			textout_ex(screen, font, tempString, x, y + newLine, WHITE, 0);
			pointer += numberOfCharactersOnALine;
			newLine += LINE_SPACING;
			memset(tempString, 0, numberOfCharactersOnALine);
		}	
	}
	return y + newLine;
}

int main (void) {
	while(1) {
		std::string chapter_filenames[NUM_CHAPTERS];
		UserOptions *user = new UserOptions(); 
		printf("User Options Again: %i %i %i %i %i \n", user->getScore(), user->getQuizType(), user->getNumQuestions(), user->getUnit(), user->getChapter());
	
		allegro_init();
		install_keyboard();
		install_mouse();
		install_timer();
		srand(time(NULL));
		
		int ret = set_gfx_mode(MODE_WINDOWED, WIDTH, HEIGHT, 0, 0);
		if (ret != 0) {
			allegro_message(allegro_error);
			return 0;
		}
		
		drawImage(TITLE_IMAGE);
		
		if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
			allegro_message("Error Initializing Sound System");
			return 1;
		}
		
		Sound *pocketTriviaMusic = new Sound();
		TriviaInfo *triviaInfo = new TriviaInfo();
		//fillFilenames(chapter_filenames);	
		drawTitle();
		rest(100);
		displayInstructions();
		chooseQuizType(user);
		if (user->getQuizType() == UNIT) {
			chooseUnit(user);
		}
	
		if (user->getQuizType() == CHAPTER) {
			chooseChapter(user);	
		}
		
		chooseNumberOfQuestions(user);
		
		printf("User Options Again: %i %i %i %i %i \n", user->getScore(), user->getQuizType(), user->getNumQuestions(), user->getUnit(), user->getChapter());
		user->setChaptersBasedOnOptions();
		for (int i = 0; i < user->getListOfChapters().size(); i++) {
			printf("Out: %s\n", user->getListOfChapters().at(i).c_str());
		}
		
		generateMultipleRandomQuestions(user, pocketTriviaMusic, triviaInfo);
		drawFinal(user);
		int doneFlag = 0;
		while(1) {
			if (key[KEY_SPACE]) {
				break;
			}
			if (key[KEY_ESC]) {
				doneFlag = 1;
				break;
			}
		}
		allegro_exit();
		if (doneFlag) {
			break;
		}
	}
}
END_OF_MAIN();
