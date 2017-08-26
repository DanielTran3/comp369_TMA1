#include "pocketTrivia.h"
#include <sstream>

/*
	Used to convert a key press into an int value for return and comparison on which keys are pressed.
*/
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

/*
	Function used to highlight the first character of a line of text.
	Purpose is to highlight the key to be pressed by the user.
*/
void highlightKey(std::string line, int xOffset, int newLineSpacing, int color) {
	char keyToPress[2];
	strncpy(keyToPress, line.c_str(), 1);
	textout_ex(screen, font, keyToPress, xOffset, newLineSpacing, color, -1);
}

/*
	Draws a fullscreen image given the filename input. Generally used to display a background image
*/
void drawImage(const char * filename) {
	BITMAP *image;
	image = load_bitmap(filename, NULL);
	if (!image) {
		allegro_message("Error Loading %s", filename);
	}
	
	blit(image, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	destroy_bitmap(image);
}

/*
	Chooses a background image from the images folder with the format background + NUMBER + .pcx
	and displays it to the screen
*/
void drawRandomImage() {
	// Creates a random number based on the number of backgrounds available
	int randomBackground = rand() % NUM_BACKGROUNDS + 1;
	
	// Convert the number to a string and concatenate the string to create the filename of 
	// the image to be displayed
	std::ostringstream numToString;
	numToString << randomBackground;
	std::string tempString = "images/background" + numToString.str() + ".pcx";
	drawImage(tempString.c_str());
}

/*

*/
void drawTitle() {
	// Replace the title with a blit to the screen with a better title
	drawImage(TITLE_IMAGE);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

/*
	Draws the final output screen, after the quiz has been completed
*/
void drawFinal(UserOptions *user) {
	// Replace rectfill with blit of image
	drawRandomImage();
	draw_pretty_box("Press Space To Restart of ESC to Quit", WIDTH / 2, HEIGHT / 2, 200, 30, 2);
	textprintf_centre_ex(screen, font, WIDTH / 2, HEIGHT / 2 - 10, WHITE, 0, "Your Final Score: %i/%i", user->getScore(), user->getNumQuestions());
	textout_centre_ex(screen, font, "Press Space To Restart of ESC to Quit", WIDTH / 2, HEIGHT / 2 + 20, WHITE, 0);
}

/*
	Draws the instructions screen
*/
void displayInstructions() {
	int xOffset = WIDTH / 2;
	int yOffset = HEIGHT / 4;
	
	drawRandomImage();
	draw_pretty_box("press the numbers 1, 2, 3, or 4 corresponding", xOffset, yOffset, 200, 30, 21);	
	textout_centre_ex(screen, font, "Instructions", xOffset, yOffset, WHITE, 0);
	textout_centre_ex(screen, font, "Navigate through the quiz by pressing,", xOffset, yOffset + 2 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "the colored keys on the screen.", xOffset, yOffset + 4 * LINE_SPACING, WHITE, 0);
	
	textout_centre_ex(screen, font, "To answer a question,", xOffset, yOffset + 7 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "press the numbers 1, 2, 3, or 4 corresponding", xOffset, yOffset + 9 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "to the answer you want to submit!", xOffset, yOffset + 11 * LINE_SPACING, WHITE, 0);
	
	textout_centre_ex(screen, font, "The game can be closed only", xOffset, yOffset + 14 * LINE_SPACING, WHITE, 0);
	textout_centre_ex(screen, font, "once a quiz has been completed!!!", xOffset, yOffset + 16 * LINE_SPACING, WHITE, 0);
	
	textout_centre_ex(screen, font, "Press Space to Continue", xOffset, yOffset + 20 * LINE_SPACING, WHITE, 0);
	
	rest(100);
	while (!key[KEY_SPACE]);
	rectfill(screen, 0, 0, WIDTH, HEIGHT, BLACK);
}

/*
	Function to display the title of the game, the type of quiz the user selected, and the user's score.
*/
void displayUserInformation(UserOptions *user) {
	int xOffset = WIDTH / 2;
	int yOffset = 5;
	rectfill(screen, 0, 0, WIDTH, yOffset + 10, BLACK);
	textprintf_centre_ex(screen, font, xOffset, yOffset, WHITE, 0, "Pocket Trivia | Quiz Type: %s | Score: %i/%i", user->getQuizName().c_str(),
				  user->getScore(), user->getNumQuestions());
	hline(screen, 0, yOffset + 10, WIDTH, WHITE);
}

/*
	Displays the quiz type that the user can select from by pressing keys 1 - 3
	User can select questions from every chapter, from a specific unit, or from a specific chapter
*/
void chooseQuizType(UserOptions *user) {
	int xOffset = WIDTH / 4;
	int yOffset = HEIGHT / 4;
	
	drawRandomImage();
	draw_pretty_box("1 - Questions From Every Chapter", WIDTH / 2, yOffset, 200, 30, 6);
	textout_centre_ex(screen, font, "Choose A Quiz Type", 2 * xOffset, yOffset, WHITE, 0);
	textout_ex(screen, font, "1 - Questions From Every Chapter", xOffset, yOffset + 2 * LINE_SPACING, WHITE, 0);
	highlightKey("1 - Questions From Every Chapter", xOffset, yOffset + 2 * LINE_SPACING, LIGHT_GREEN);
	textout_ex(screen, font, "2 - Questions From A Unit", xOffset, yOffset + 4 * LINE_SPACING, WHITE, 0);
	highlightKey("2 - Questions From A Unit", xOffset, yOffset + 4 * LINE_SPACING, LIGHT_GREEN);
	textout_ex(screen, font, "3 - Questions From A Chapter", xOffset, yOffset + 6 * LINE_SPACING, WHITE, 0);
	highlightKey("3 - Questions From A Chapter", xOffset, yOffset + 6 * LINE_SPACING, LIGHT_GREEN);

	// Check what option the user pressed and save the value if it is valid
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

/*
	If the user chose to select questions from a unit, this function displays a screen for
	the user to select which unit they want the questions from
*/
void chooseUnit(UserOptions *user) {
	drawRandomImage();
	
	// Read from the UNITS text file 
	std::ifstream file(UNITS);
	std::string line;
	int xOffset = 30;
	int newLineSpacing = HEIGHT / 4;
	
	draw_pretty_box("1. PART 1: Cross-Platform Game Programming With The Allegro Library", WIDTH / 2, newLineSpacing, 500, 30, 8);
	textout_centre_ex(screen, font, "Choose A Unit", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	
	// Read and display the units lines from the text file
	if (file.is_open()) {
		while(!file.eof()) {
			getline(file, line);
			textout_ex(screen, font, line.c_str(), xOffset, newLineSpacing, WHITE, 0);
			highlightKey(line, xOffset, newLineSpacing, LIGHT_GREEN);
			newLineSpacing += 2 * LINE_SPACING;
		}
	}
	
	// Check what option the user pressed and save the value if it is valid
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

/*
	If the user chose to select questions from a chapter, the user can select which chapter they want the 
	questions from here	
*/
void chooseChapter(UserOptions *user) {
	drawRandomImage();
	
	// Read text from the CHAPTERS text file
	std::ifstream file(CHAPTERS);
	std::string line;
	int xOffset = 30;
	int newLineSpacing = 0;
	
	draw_pretty_box("R - Chapter 13: Creating a Game World: Editing Tiles and Levels", WIDTH / 2, newLineSpacing, 300, 30, 45);
	textout_centre_ex(screen, font, "Choose A Chapter", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	
	// Read all of the lines from the text file
	if (file.is_open()) {
		while(!file.eof()) {
			getline(file, line);
			textout_ex(screen, font, line.c_str(), xOffset, newLineSpacing, WHITE, 0);
			highlightKey(line, xOffset, newLineSpacing, LIGHT_GREEN);
			newLineSpacing += 2 * LINE_SPACING;
		}
	}
	
	// Check what option the user pressed and save the value if it is valid
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

/*
	Allow the user to choose how many questions to answer, ranging between 3, 5, or 10 questions
*/
void chooseNumberOfQuestions(UserOptions *user) {
	drawRandomImage();
	int xOffset = WIDTH / 4;
	int newLineSpacing = HEIGHT / 4;
	draw_pretty_box("Choose The Number of Questions", WIDTH / 2, newLineSpacing, 200, 30, 6);
	textout_centre_ex(screen, font, "Choose The Number of Questions", WIDTH / 2, newLineSpacing, WHITE, 0);
	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "1 - 3 Questions", xOffset, newLineSpacing, WHITE, 0);
	highlightKey("1 - 3 Questions", xOffset, newLineSpacing, LIGHT_GREEN);

	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "2 - 5 Questions", xOffset, newLineSpacing, WHITE, 0);
	highlightKey("2 - 5 Questions", xOffset, newLineSpacing, LIGHT_GREEN);

	newLineSpacing += 2 * LINE_SPACING;
	textout_ex(screen, font, "3 - 10 Questions", xOffset, newLineSpacing, WHITE, 0);
	highlightKey("3 - 10 Questions", xOffset, newLineSpacing, LIGHT_GREEN);

	// Check what option the user pressed and save the value if it is valid	
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

/*
	Prints a random question from a file
*/
void randomQuestion(const char *filename, int &answer, int questionNumber, TriviaInfo *triviaInfo) {
	// Get a random questions from 0 to 9
	int randomQuestionNumber = rand() % 10;
	int randomNumberCounter = 0;

	std::ostringstream numToString;
	numToString << questionNumber;	
	std::ifstream file;
	std::string line;
	
	drawRandomImage();
	rectfill(screen, 0, 0, WIDTH, HEIGHT / 4 + 20, BLACK);
	hline(screen, 0, HEIGHT / 4 + 20, WIDTH, WHITE);
	
	int textPos = 30;
	triviaInfo->clearQuestion();
	triviaInfo->clearAnswers();
	
	file.open(filename);
	if (file.is_open()) {

		// Read blank spaces equal to the random number generated, to put the line
		// at the start of the question
		while (randomNumberCounter < randomQuestionNumber) {
			getline(file, line);
			if (line.empty()) {
				randomNumberCounter++;
			}
		}
		
		// Store and read the question
		getline(file, line);
		triviaInfo->setQuestion("Question " + numToString.str() + ": " + line);
		textPos = print_long_text(triviaInfo->getQuestion().c_str(), 0, textPos);
		
		// Read the multiple choice answers. If the line starts with a *, that denotes that that choice
		// is the answer. Store the answer into the triviaInfo class and return the multiple choice number
		// through pass-by-reference
		while (!line.empty() && !file.eof()) {
			getline(file, line);
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

/*
	Check if the answer the user input is correct or not.
*/
void checkAnswer(UserOptions *user, int userAnswer, int answer, Sound *soundEffect, TriviaInfo *triviaInfo) {
	int xOffset = 0;
	int yOffset = 409;

	rectfill(screen, xOffset, yOffset, WIDTH - 1, yOffset + 7* LINE_SPACING, BLACK);
	
	// User's answer is correct
	if (userAnswer == answer) {
		// Increment the user's score
		user->incrementScore();		
		// Play a sound effect for a correct answer
		soundEffect->setSoundEffect(CORRECT_SOUND);
		soundEffect->playSoundEffect();
		
		// Draw a check mark for
		drawImage(CORRECT_IMAGE);
		
		// Draw a green border around the results box
		rect(screen, xOffset, yOffset, WIDTH - 1, yOffset + 7* LINE_SPACING, LIGHT_GREEN);
	}
	else {
		// Play a sound effecto for an incorrect answer
		soundEffect->setSoundEffect(INCORRECT_SOUND);
		soundEffect->playSoundEffect();
		
		drawImage(INCORRECT_IMAGE);
		
		// Draw a red border around the results box
		rect(screen, xOffset, yOffset, WIDTH - 1, yOffset + 7* LINE_SPACING, RED);
	}
	xOffset += 1;
	yOffset += 5;

	// Display some statistics (User's answer, Correct answer, and the user's score)
	yOffset = print_long_text(triviaInfo->getQuestion().c_str(), xOffset, yOffset, 1, BLACK);
	std::string tempString = "Your Answer   : " + triviaInfo->getAnswer(userAnswer - 1);
	yOffset = print_long_text(tempString.c_str(), xOffset, yOffset, 1, BLACK);

	tempString = "Correct Answer: " + triviaInfo->getAnswer(answer - 1);
	yOffset = print_long_text(tempString.c_str(), xOffset, yOffset, 1, BLACK);

	textprintf_centre_ex(screen, font, xOffset + 50, yOffset + 5, BLACK, -1, "Score: %i/%i", user->getScore(), user->getNumQuestions());
	rest(1500);
}

/*
	Generate a random number of questions based on the number of questions that the user selected.
*/
void generateMultipleRandomQuestions(UserOptions *user, Sound *soundEffect, TriviaInfo *triviaInfo) {
	int questionNumber = 1;
	
	// 
	while(questionNumber < user->getNumQuestions() + 1) {
		// Get a random chapter from the available chapters (change based on the users quiz type selection
		int randomChapterIndex = rand() % user->getListOfChapters().size();
		std::string randomChapter = user->getListOfChapters().at(randomChapterIndex);
	
		int answer = -1;

		// Display the random question
		randomQuestion(randomChapter.c_str(), answer, questionNumber, triviaInfo);
		displayUserInformation(user);
		
		// Check what option the user pressed and check the input
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

/*
	Print text that will wrap the screen if the text is too long.
	Output: The new y textline after the texts have been displayed
*/
int print_long_text(const char *text, int x, int y) {
	// Get the maximum number of characters on a line
	int numberOfCharactersOnALine = WIDTH / CHARACTER_WIDTH;
	// Get the number of texts in the line to be printed
	int numberOfCharactersInText = text_length(font, text) / CHARACTER_WIDTH;
	// Pointer keeps track of the characters that have been displayed on the screen
	int pointer = 0;
	// Keeps track of the line spacing
	int newLine = 0;
	
	// If the number of characters to be displayed is less than the number of characters that can fit on a line, then display it
	if (numberOfCharactersInText < numberOfCharactersOnALine) {
		textprintf_ex(screen, font, x, y, WHITE, 0, "%s", text);
		newLine += 2 * LINE_SPACING;
	}
	
	// If there are more characters than the amount that can fit on a line, split the line and display the characters on separate lines
	else {
		while(pointer < numberOfCharactersInText) {
			char tempString[numberOfCharactersOnALine];
			int numChars = pointer + numberOfCharactersOnALine > numberOfCharactersInText ? numberOfCharactersInText - pointer : numberOfCharactersOnALine;
			std::string temp = text;
			temp.copy(tempString, numChars, pointer);
			tempString[numberOfCharactersOnALine] = '\0';
			textout_ex(screen, font, tempString, x, y + newLine, WHITE, 0);
			pointer += numberOfCharactersOnALine;
			newLine += LINE_SPACING;
			memset(tempString, 0, numberOfCharactersOnALine);
		}	
	}
	return y + newLine;
}

/*
	Print text that will wrap the screen if the text is too long. Has options for the line spacing and text color
	Output: The new y textline after the texts have been displayed
*/
int print_long_text(const char *text, int x, int y, int lineMultiple, int textColor) {
	// Get the maximum number of characters on a line
	int numberOfCharactersOnALine = WIDTH / CHARACTER_WIDTH;
	// Get the number of texts in the line to be printed
	int numberOfCharactersInText = text_length(font, text) / CHARACTER_WIDTH;
	// Pointer keeps track of the characters that have been displayed on the screen
	int pointer = 0;
	// Keeps track of the line spacing
	int newLine = 0;

	// If the number of characters to be displayed is less than the number of characters that can fit on a line, then display it	
	if (numberOfCharactersInText < numberOfCharactersOnALine) {
		textprintf_ex(screen, font, x, y, textColor, -1, "%s", text);
		newLine += lineMultiple * LINE_SPACING;
	}
	
	// If there are more characters than the amount that can fit on a line, split the line and display the characters on separate lines
	else {
		while(pointer < numberOfCharactersInText) {
			char tempString[numberOfCharactersOnALine];
			int numChars = pointer + numberOfCharactersOnALine > numberOfCharactersInText ? numberOfCharactersInText - pointer : numberOfCharactersOnALine;
			std::string temp = text;
			temp.copy(tempString, numChars, pointer);
			tempString[numberOfCharactersOnALine] = '\0';
			textout_ex(screen, font, tempString, x, y + newLine, textColor, -1);
			pointer += numberOfCharactersOnALine;
			newLine += LINE_SPACING;
			memset(tempString, 0, numberOfCharactersOnALine);
		}	
	}
	return y + newLine;
}

/*
	Get the number of characters in the inputted text
*/
int getHorizontalSpacing(const char *text) {
	return text_length(font, text) / CHARACTER_WIDTH;
}

/*
	Draw a box based on the text length and number of lines
*/
void draw_pretty_box(const char * textToMeasure, int x, int y, int offset_x, int offset_y, int numLines) {
	int textLength = getHorizontalSpacing(textToMeasure);
	rectfill(screen, x - offset_x, y - offset_y, x + offset_x, y + (numLines * LINE_SPACING) + offset_y, BLACK);
	rect(screen, x - offset_x, y - offset_y, x + offset_x, y + (numLines * LINE_SPACING) + offset_y, WHITE);
}

int main (void) {
	// Initialize allegro functions
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
	
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error Initializing Sound System");
		return 1;
	}
	
	// Game loop
	while(1) {
		std::string chapter_filenames[NUM_CHAPTERS];
		UserOptions *user = new UserOptions(); 	
		Sound *pocketTriviaMusic = new Sound();
		TriviaInfo *triviaInfo = new TriviaInfo();
		
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
		
		user->setChaptersBasedOnOptions();
		
		generateMultipleRandomQuestions(user, pocketTriviaMusic, triviaInfo);
		drawFinal(user);
		
		int doneFlag = 0;
		
		// If the escape key is pressed, the game is quit, otherwise if space is pressed, restart the games
		while(1) {
			if (key[KEY_SPACE]) {
				break;
			}
			if (key[KEY_ESC]) {
				doneFlag = 1;
				break;
			}
		}

		if (doneFlag) {
			delete pocketTriviaMusic;
			allegro_exit();
			break;
		}
	}
}
END_OF_MAIN();
