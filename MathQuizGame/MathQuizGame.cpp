#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum to represent question difficulty levels
enum enQuestionsLevel { easy = 1, med = 2, hard = 3, mix = 4 };

// Enum to represent operation types for math questions
enum enOperationType { opAdd = 1, opSub = 2, opMult = 3, opDiv = 4, opMix = 5 };

// Struct to hold quiz configuration info selected by the user
struct stConfigration {
    short howManyQuestions = 0;     // Number of questions user wants to answer
    enQuestionsLevel questionsLevel; // Difficulty level
    enOperationType  operationType;  // Operation type
};

// Struct to hold final result summary after the quiz
struct stFinalResult {
    short numberOfQuestions = 0;
    short numberOfRightAnswers = 0;
    short numberOfWrongAnswers = 0;
    string questionsLevel = "";
    string  operationType = "";
    string finalResult = "";  // Pass or Fail status
};

// Struct to hold parts of a single question
struct stQuestionParts {
    short number1 = 0;        // First number in the question
    short number2 = 0;        // Second number
    short correctAnswer = 0;  // Correct answer calculated
    short questionNumber = 0; // Question index
    char operation;           // Operation symbol (+, -, *, /)
};

// Function to generate string of tabs for formatted output
string tabs(int number) {
    string tap = "";
    for (int i = 1; i <= number; i++) {
        tap += "\t";
    }
    return tap;
}

// Generate a random integer between 'from' and 'to' inclusive
int randomNumber(int from, int to) {
    int random = rand() % (to - from + 1) + from;
    return random;
}

// Read from user how many questions they want to answer
short readHowManyQuestions() {
    short rounds = 0;
    while (true) {
        cout << "How many Questions do you want to answer? ";
        cin >> rounds;
        // Validate input: must be positive number
        if (cin.fail() || rounds < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a positive number.\n\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return rounds;
}

// Read from user the desired difficulty level of questions
enQuestionsLevel readQuestionsLevel() {
    short questionsLevel = 0;
    while (true) {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> questionsLevel;
        // Validate input is between 1 and 4
        if (cin.fail() || questionsLevel < 1 || questionsLevel > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return (enQuestionsLevel)questionsLevel;
}

// Read from user the operation type for the questions
enOperationType readOperationsType() {
    short operationType = 0;
    while (true) {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> operationType;
        // Validate input is between 1 and 5
        if (cin.fail() || operationType < 1 || operationType > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return (enOperationType)operationType;
}

// Get string name of operation type for display
string getOperationName(enOperationType operationType) {
    switch (operationType) {
    case enOperationType::opAdd: return "Add";
    case enOperationType::opSub: return "Subtract";
    case enOperationType::opMult: return "Multiplication";
    case enOperationType::opDiv: return "Divide";
    case enOperationType::opMix: return "Mix";

    default: return "Unknown!";
    }
}

// Get string name of difficulty level for display
string getLevelName(enQuestionsLevel questionLevel) {
    switch (questionLevel) {
    case enQuestionsLevel::easy: return "Easy";
    case enQuestionsLevel::med: return "Med";
    case enQuestionsLevel::hard: return "Hard";
    case enQuestionsLevel::mix: return "Mix";
    default: return "Unknown!";
    }
}

// Generate a number for addition or subtraction based on difficulty level
int giveNumberForAddAndSub(enQuestionsLevel level) {
    switch (level)
    {
    case enQuestionsLevel::easy:
    {
        // Random choice between small, medium, and large numbers
        int n[3] = { randomNumber(1, 10) ,10 * randomNumber(1, 10) ,100 * randomNumber(1, 10) };
        return n[randomNumber(0, 2)];

    }

    case enQuestionsLevel::med:
        return randomNumber(1, 100);
    case enQuestionsLevel::hard:
        return randomNumber(100, 1000);
    case enQuestionsLevel::mix:
        // Mix picks random level between easy, med, hard
        return giveNumberForAddAndSub((enQuestionsLevel)randomNumber(1, 3));
    }
}

// Generate number for multiplication or second number for division based on difficulty
int giveNumberForMulAndSecondNumberForDiv(enQuestionsLevel level) {
    switch (level)
    {
    case enQuestionsLevel::easy:
        return randomNumber(1, 10);
    case enQuestionsLevel::med:
        return randomNumber(10, 50);
    case enQuestionsLevel::hard:
        return randomNumber(50, 100);
    case enQuestionsLevel::mix:
        // Randomly pick one of the difficulty levels except mix itself
        return giveNumberForMulAndSecondNumberForDiv((enQuestionsLevel)randomNumber(1, 3));
    }
}

// For division, calculate first number as a multiple of second number to ensure integer division
int giveTheFirstNumberForDivide(int secondNumber) {
    return secondNumber * randomNumber(1, 20);
}

// Wrapper to get a number based on level and operation type
int giveNumber(enQuestionsLevel level, enOperationType operation) {
    if (operation == enOperationType::opAdd || (operation == enOperationType::opSub)) {
        return giveNumberForAddAndSub(level);
    }
    else {
        return giveNumberForMulAndSecondNumberForDiv(level);
    }
}

// Basic math operations functions
int getAdd(int firstNumber, int secondNumber) {
    return (firstNumber + secondNumber);
}
int getSub(int firstNumber, int secondNumber) {
    return (firstNumber - secondNumber);
}
int getMul(int firstNumber, int secondNumber) {
    return (firstNumber * secondNumber);
}
int getDiv(int firstNumber, int secondNumber) {
    if (secondNumber == 0) return 0; // avoid division by zero
    else  return (firstNumber / secondNumber);
}

// Calculate correct answer and set operation char in question struct
stQuestionParts calculation(stQuestionParts questionParts, enOperationType type) {
    switch (type) {
    case enOperationType::opAdd:
        questionParts.operation = '+';
        questionParts.correctAnswer = getAdd(questionParts.number1, questionParts.number2);
        break;
    case enOperationType::opSub:
        questionParts.operation = '-';
        questionParts.correctAnswer = getSub(questionParts.number1, questionParts.number2);
        break;
    case enOperationType::opMult:
        questionParts.operation = '*';
        questionParts.correctAnswer = getMul(questionParts.number1, questionParts.number2);
        break;
    case enOperationType::opDiv:
        questionParts.operation = '/';
        questionParts.correctAnswer = getDiv(questionParts.number1, questionParts.number2);
        break;
    case enOperationType::opMix:
        // For mix, randomly select an operation and calculate
        questionParts = calculation(questionParts, (enOperationType)randomNumber(1, 4));
        break;
    }
    return questionParts;
}

// Read all quiz configuration info from the user
stConfigration readQuestionInfo() {
    stConfigration questionsInfo;
    questionsInfo.howManyQuestions = readHowManyQuestions();
    questionsInfo.questionsLevel = readQuestionsLevel();
    questionsInfo.operationType = readOperationsType();
    return questionsInfo;
}

// Generate question numbers and calculate the correct answer based on config and question number
stQuestionParts readQuestionParts(int questionNumber, stConfigration questionInfo) {
    stQuestionParts questionParts;

    // Decide operation type per question, randomly if 'Mix' is selected
    enOperationType currentOperationType =
        questionInfo.operationType == enOperationType::opMix ?
        (enOperationType)randomNumber(1, 4)
        : questionInfo.operationType;

    // Generate the second number based on difficulty and operation
    questionParts.number2 = giveNumber(questionInfo.questionsLevel, currentOperationType);

    // Generate the first number, special case for division
    if (currentOperationType != enOperationType::opDiv)
        questionParts.number1 = giveNumber(questionInfo.questionsLevel, currentOperationType);
    else
        questionParts.number1 = giveTheFirstNumberForDivide(questionParts.number2);

    questionParts.questionNumber = questionNumber;

    // Calculate the correct answer and set operation symbol
    questionParts = calculation(questionParts, currentOperationType);
    return questionParts;
}

// Read user's answer with validation
int readAnswer() {
    int answer;
    while (true) {
        cin >> answer;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return answer;
}

// Check if user's answer is correct and print appropriate feedback
bool isRight(int answer, int result) {
    if (answer == result) {
        cout << "\n\n\n";
        cout << "-----------------------------\n";
        cout << "Right Answer :-)\n";
        cout << "-----------------------------\n\n";
        return true;
    }
    else {
        cout << "\n\n\n";
        cout << "-----------------------------\n";
        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer is : " << result << endl;
        cout << "-----------------------------\n\n";
        return false;
    }

}

// Print the header showing current question number out of total
void printQuestionHeader(int questionNumber, int howManyQuestions) {
    cout << "Question[" << questionNumber << "/" << howManyQuestions << "]\n\n";
}

// Print the question numbers and operation symbol
void printQuestion(stQuestionParts questionParts) {
    cout << questionParts.number1 << "\n";
    cout << questionParts.number2 << "  " << questionParts.operation << "\n";
    cout << "------------------------\n";

}

// Execute the question flow: print header, generate question, print it, read answer and check
bool doQuestion(int questionNumber, stConfigration questionInfo) {
    printQuestionHeader(questionNumber, questionInfo.howManyQuestions);
    stQuestionParts questionParts = readQuestionParts(questionNumber, questionInfo);
    printQuestion(questionParts);
    return isRight(readAnswer(), questionParts.correctAnswer);

}

// Change console color and beep sound based on correctness of answer
void applyEffect(bool result) {
    if (result)
        system("color 20"); // green background for correct answer
    else {
        system("color 4F"); // red background for wrong answer
        cout << "\a";      // beep sound
    }
}

// Determine if user passed (right answers >= wrong answers)
bool calculateIsPass(int rightAnswer, int wrongAnswer) {
    return (rightAnswer >= wrongAnswer);
}

// Get final result text based on pass or fail
string getFinalResult(int rightAnswer, int wrongAnswer) {
    if (calculateIsPass(rightAnswer, wrongAnswer))
        return "Pass :-)";
    else
        return "Fail :-(";
}

// Run all questions and collect results
stFinalResult playQuestions(stConfigration questionInfo) {
    stFinalResult finalResult;
    finalResult.numberOfQuestions = questionInfo.howManyQuestions;
    finalResult.operationType = getOperationName(questionInfo.operationType);
    finalResult.questionsLevel = getLevelName(questionInfo.questionsLevel);
    for (int i = 1; i <= questionInfo.howManyQuestions; i++) {
        bool resultQuestion = doQuestion(i, questionInfo);
        if (resultQuestion)
            finalResult.numberOfRightAnswers++;
        else
            finalResult.numberOfWrongAnswers++;
        applyEffect(resultQuestion);
    }
    finalResult.finalResult = getFinalResult(finalResult.numberOfRightAnswers, finalResult.numberOfWrongAnswers);
    return finalResult;
}

// Print a summary of the final results nicely formatted
void printFinalResult(stFinalResult result) {
    cout << "\n";
    cout << tabs(4) << "============================================\n";
    cout << tabs(5) << "Final Results is " << result.finalResult << "\n";
    cout << tabs(4) << "============================================\n\n";
    cout << tabs(4) << "Number of Questions     : " << result.numberOfQuestions << ".\n";
    cout << tabs(4) << "Questions Level         : " << result.questionsLevel << ".\n";
    cout << tabs(4) << "Operation Type          : " << result.operationType << ".\n";
    cout << tabs(4) << "Number of Right Answers : " << result.numberOfRightAnswers << ".\n";
    cout << tabs(4) << "Number of Wrong Answers : " << result.numberOfWrongAnswers << ".\n";
    cout << tabs(4) << "============================================" << endl;

    // Apply color effect for pass/fail after summary
    applyEffect(calculateIsPass(result.numberOfRightAnswers, result.numberOfWrongAnswers));
}

// Reset console UI to default color and clear screen
void resetUI() {
    system("color 07"); // default console colors
    system("cls");      // clear screen (Windows)
}

// Ask user if they want to play again, return true or false
bool playAgain() {
    string again;
    while (true)
    {
        cout << "\n\n" << tabs(2) << "Do you want to play again (Y/N) ? \n\n\n";
        cout << tabs(4);
        getline(cin, again);
        if (again == "Y" || again == "y")
            return true;
        else if (again == "N" || again == "n")
            return false;
    }
}

// Main game loop: repeat until user chooses to stop
void startGame() {
    do
    {
        resetUI();                     // Clear screen and reset colors
        stConfigration questionInfo = readQuestionInfo();  // Get user settings
        stFinalResult finalResult = playQuestions(questionInfo);  // Run the quiz
        printFinalResult(finalResult);    // Show results

    } while (playAgain());  // Repeat if user wants
}

int main()
{
    srand((unsigned)time(NULL));  // Seed random number generator with current time
    startGame();                  // Start the quiz game loop

    return 0;
}