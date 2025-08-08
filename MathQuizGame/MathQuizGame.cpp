#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { easy = 1, med = 2, hard = 3, mix = 4 };
enum enOperationType { opAdd = 1, opSub = 2, opMult = 3, opDiv = 4, opMix = 5 };

struct stConfigration {
    short howManyQuestions = 0;
    enQuestionsLevel questionsLevel;
    enOperationType  operationType;
};
struct stFinalResult {
    short numberOfQuestions = 0;
    short numberOfRightAnswers = 0;
    short numberOfWrongAnswers = 0;
    string questionsLevel = "";
    string  operationType = "";
    string finalResult = "";
};
struct stQuestionParts {
    short number1 = 0;
    short number2 = 0;
    short correctAnswer = 0;
    short questionNumber = 0;
    char operation;
};

string tabs(int number) {
    string tap = "";
    for (int i = 1; i <= number; i++) {
        tap += "\t";
    }
    return tap;
}

int randomNumber(int from, int to) {
    int random = rand() % (to - from + 1) + from;
    return random;
}
short readHowManyQuestions() {
    short rounds = 0;
    while (true) {
        cout << "How many Questions do you want to answer? ";
        cin >> rounds;
        if (cin.fail() || rounds<1) {
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
enQuestionsLevel readQuestionsLevel() {
    short questionsLevel = 0;
    while (true) {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> questionsLevel;
        if (cin.fail() || questionsLevel < 1|| questionsLevel>4) {
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

enOperationType readOperationsType() {
    short operationType = 0;
    while (true) {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> operationType;
        if (cin.fail() || operationType < 1 || operationType>5) {
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




string getOperationName(enOperationType operationType) {
    switch (operationType) {
    case enOperationType::opAdd: return "Add";
    case enOperationType::opSub: return "Subtract";
    case enOperationType::opMult: return "Multiplication";
    case enOperationType::opDiv: return "divide";
    case enOperationType::opMix: return "Mix";

    default: return "Un Known!";
    }
}
string getLevelName(enQuestionsLevel questionLevel) {
    switch (questionLevel) {
    case enQuestionsLevel::easy: return "Easy";
    case enQuestionsLevel::med: return "Med";
    case enQuestionsLevel::hard: return "Hard";
    case enQuestionsLevel::mix: return "Mix";
    default: return "Un Known!";
    }
}

int giveNumberForAddAndSub(enQuestionsLevel level) {
    switch (level)
    {

    case enQuestionsLevel::easy:
    {
        int n[3] = { randomNumber(1, 10) ,10 * randomNumber(1, 10) ,100 * randomNumber(1, 10) };
        return n[randomNumber(0, 2)];
    }
    case enQuestionsLevel::med:
    {
        return randomNumber(1, 100);
    }

    case enQuestionsLevel::hard:
    {
        return randomNumber(100, 1000);
    }
    case enQuestionsLevel::mix:
    {
        return giveNumberForAddAndSub((enQuestionsLevel)randomNumber(1, 3));
    }
    }
}

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
        return giveNumberForMulAndSecondNumberForDiv((enQuestionsLevel)randomNumber(1, 3));
    }
}

int giveTheFirstNumberForDivide(int secondNumber) {
    return secondNumber * randomNumber(1, 20);
}

int giveNumber(enQuestionsLevel level, enOperationType operation) {
    if (operation == enOperationType::opAdd || (operation == enOperationType::opSub)) {
        return giveNumberForAddAndSub(level);
    }
    else {
        return giveNumberForMulAndSecondNumberForDiv(level);
    }
}


int getAdd(int firstNumber, int secondNumber) {
    return(firstNumber + secondNumber);
}
int getSub(int firstNumber, int secondNumber) {
    return(firstNumber - secondNumber);
}
int getMul(int firstNumber, int secondNumber) {
    return(firstNumber * secondNumber);
}
int getDiv(int firstNumber, int secondNumber) {
    if (secondNumber == 0) return 0;
    else  return(firstNumber / secondNumber);
}

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
        questionParts = calculation(questionParts, (enOperationType)randomNumber(1, 4));
        break;
    }
    return questionParts;
}

stConfigration readQuestionInfo() {
    stConfigration questionsInfo;
    questionsInfo.howManyQuestions = readHowManyQuestions();
    questionsInfo.questionsLevel = readQuestionsLevel();
    questionsInfo.operationType = readOperationsType();
    return questionsInfo;
}

stQuestionParts readQuestionParts(int questionNumber, stConfigration questionInfo) {
    stQuestionParts questionParts;

    enOperationType currentOperationType =
        questionInfo.operationType ==
        enOperationType::opMix ?
        (enOperationType)randomNumber(1, 4)
        : questionInfo.operationType;

    questionParts.number2 = giveNumber(questionInfo.questionsLevel, currentOperationType);
    if (currentOperationType != enOperationType::opDiv)
        questionParts.number1 = giveNumber(questionInfo.questionsLevel, currentOperationType);
    else
        questionParts.number1 = giveTheFirstNumberForDivide(questionParts.number2);

    questionParts.questionNumber = questionNumber;
    questionParts = calculation(questionParts, currentOperationType);
    return questionParts;
}

int readAnswer() {
    int answer;
    while(true){
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

void printQuestionHeader(int questionNumber, int howManyQuestions) {
    cout << "Question[" << questionNumber << "/" << howManyQuestions << "]\n\n";
}

void printQuestion(stQuestionParts questionParts) {
    cout << questionParts.number1 << "\n";
    cout << questionParts.number2 << "  " << questionParts.operation << "\n";
    cout << "------------------------\n";

}

bool doQuestion(int questionNumber, stConfigration questionInfo) {
    printQuestionHeader(questionNumber, questionInfo.howManyQuestions);
    stQuestionParts questionParts = readQuestionParts(questionNumber, questionInfo);
    printQuestion(questionParts);
    return isRight(readAnswer(), questionParts.correctAnswer);

}


void applyEffect(bool result) {
    if (result)
        system("color 20");
    else {
        system("color 4F");
        cout << "\a";
    }
}

bool calculateIsPass(int rightAnswer, int wrongAnswer) {
    return (rightAnswer >= wrongAnswer);
}

string getFinalResult(int rightAnswer, int wrongAnswer) {
    if (calculateIsPass(rightAnswer, wrongAnswer))
        return "Pass :-)";
    else
        return "Fail :-(";
}

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
    applyEffect(calculateIsPass(result.numberOfRightAnswers, result.numberOfWrongAnswers));
}

void resetUI() {
    system("color 07");
    system("cls");
}

bool playAgain() {
    string again;
    while (true)
    {
        cout << "\n\n" << tabs(2) << "Do you want to play again (Y/N) ? \n\n\n";
        cout << tabs(4);
        getline(cin,again);
        if (again == "Y" || again == "y")
            return true;
        else if (again == "N" || again == "n")
            return false;
    }
}

void startGame() {
    do
    {
        resetUI();
        stConfigration questionInfo = readQuestionInfo();
        stFinalResult finalResult = playQuestions(questionInfo);
        printFinalResult(finalResult);

    } while (playAgain());
}

int main()
{
    srand((unsigned)time(NULL));
    startGame();

    return 0;
}