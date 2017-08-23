#include "pocketTrivia.h"

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

void highlightKey(std::string line, int xOffset, int newLineSpacing) {
	char keyToPress[2];
	strncpy(keyToPress, line.c_str(), 1);
	textout_ex(screen, font, keyToPress, xOffset, newLineSpacing, LIGHT_GREEN, 0);
}

void drawTitle() {
	// Replace the title with a blit to the screen with a better title
	textout_centre_ex(screen, font, TITLE, WIDTH / 2, HEIGHT / 2, WHITE, 0);
	textout_centre_ex(screen, font, "Press Space to Continue", WIDTH / 2, HEIGHT / 2 + 2 * LINE_SPACING, WHITE, 0);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void displayInstructions() {
	textout_centre_ex(screen, font, "Instructions", WIDTH / 2, HEIGHT / 4, WHITE, 0);
	textout_centre_ex(screen, font, "To answer a question,", WIDTH / 2, HEIGHT / 4 + 2 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "press the numbers 1, 2, 3, or 4 corresponding", WIDTH / 2, HEIGHT / 4 + 3 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "to the answer you want to submit!", WIDTH / 2, HEIGHT / 4 + 4 * LINE_SPACING, WHITE, 0);
	
	textout_centre_ex(screen, font, "Press Space to Continue", WIDTH / 2, HEIGHT / 4 + 6 * LINE_SPACING, WHITE, 0);
	rest(100);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

void chooseQuizType(UserOptions *user) {
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
			highlightKey(line, xOffset, newLineSpacing);
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
			highlightKey(line, xOffset, newLineSpacing);
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
		textprintf_ex(screen, font, 0, textPos, WHITE, -1, "Question: %s", line.c_str());
		while (!line.empty()) {	
			printf("%s\n", line.c_str());
			textprintf_ex(screen, font, 0, textPos, WHITE, -1, "%s", line.c_str());
			textPos += 10;
			getline(file, line);
		}
		file.close();
	}
}

void randomQuestion(const char *filename) {
	int randomQuestionNumber = rand() % 10;
	printf("%i\n", randomQuestionNumber);
	int randomNumberCounter = 0;
	
	std::string line;
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
	int textPos = 0;
	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		while (randomNumberCounter < randomQuestionNumber) {
			getline(file, line);
			if (line.empty()) {
				randomNumberCounter++;
			}
		}
		
		getline(file, line);
		std::string questionString = "Question: " + line;
		textPos = print_long_text(questionString.c_str(), 0, textPos);
		while (!line.empty() && !file.eof()) {
			getline(file, line);
			textPos = print_long_text(line.c_str(), 0, textPos);
		}
		file.close();
		printf("RanomQuestion file closed\n");
	}
	else {
		printf("Error Opening File");
		allegro_message("Error Opening File");
	}
}

void generateMultipleRandomQuestions(UserOptions *user) {
	int questionNumber = 0;
	while(questionNumber < user->getNumQuestions()) {
		printf("Question: %i\n", questionNumber);
		
		randomQuestion(user->getListOfChapters().at(0).c_str());
		rest(100);
		while(1) {
			if (keypressed()) {
				int value = convertKeyPress();
				if (value >= 1 && value <= 4) {
					if (value == 1) {
						
					}
					if (value == 2) {
						
					}
					if (value == 3) {
						
					}
					if (value == 4) {
						
					}
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
		//textout_ex(screen, font, text, x, y, WHITE, -1);
		textprintf_ex(screen, font, x, y, WHITE, -1, "%s", text);
		newLine += LINE_SPACING;
	}
	else {
		while(pointer < numberOfCharactersInText) {
			char tempString[numberOfCharactersOnALine];
			int numChars = pointer + numberOfCharactersOnALine > numberOfCharactersInText ? numberOfCharactersInText - pointer : numberOfCharactersOnALine;
			std::string temp = text;
			temp.copy(tempString, numChars, pointer);
			tempString[numberOfCharactersOnALine] = '\0';
			printf("%i: %s\n", numChars, tempString);
			textout_ex(screen, font, tempString, x, y + newLine, WHITE, -1);
			pointer += numberOfCharactersOnALine;
			newLine += LINE_SPACING;
			memset(tempString, 0, numberOfCharactersOnALine);
		}	
	}
	return y + newLine;
}

int main (void) {
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
	//fillFilenames(chapter_filenames);	
	drawTitle();
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
	
	generateMultipleRandomQuestions(user);
	while(!key[KEY_ESC]) {
		
	}
	printf("Exiting Program\n");
	allegro_exit();
	printf("Exited\n");
}
END_OF_MAIN();
