#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";
const string CYAN   = "\033[36m";
const string BOLD   = "\033[1m";

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string trim(string s) {
    while (!s.empty() && isspace(s[0]))
        s.erase(0, 1);
    while (!s.empty() && isspace(s[s.length() - 1]))
        s.erase(s.length() - 1, 1);
    return s;
}

void divider() {
    cout << CYAN << "=====================================================\n" << RESET;
}


class Puzzle {

protected:
    string question;
    string answer;
    int points;

public:
    Puzzle(string q, string a, int p = 10) {
        question = q;
        answer = a;
        points = p;
    }

    virtual ~Puzzle() {}

    virtual void display() = 0;
    virtual bool solve() = 0;

    int getPoints() {
        return points;
    }
};


class MCQPuzzle : public Puzzle {

private:
    vector<string> choices;

public:
    MCQPuzzle(string q, vector<string> c, string a, int p = 10)
        : Puzzle(q, toLower(trim(a)), p) {
        choices = c;
    }

    void display() {
        divider();
        cout << BOLD << YELLOW << "MCQ PUZZLE\n" << RESET;
        divider();
        cout << question << "\n\n";

        char option = 'A';
        for (int i = 0; i < choices.size(); i++) {
            cout << BLUE << option++ << ". " << RESET << choices[i] << "\n";
        }
        cout << "\n";
    }

    bool solve() {
        string input;

        while (true) {
            cout << CYAN << "Enter answer (A/B/C/D): " << RESET;
            getline(cin, input);
            input = toLower(trim(input));

            if (input == "a" || input == "b" || input == "c" || input == "d") {
                if (input == answer) {
                    cout << GREEN << "\nCorrect!\n" << RESET;
                    return true;
                } else {
                    cout << RED << "\nWrong answer!\n" << RESET;
                    return false;
                }
            }

            cout << RED << "Invalid input.\n" << RESET;
        }
    }
};


class LogicPuzzle : public Puzzle {

private:
    int minVal;
    int maxVal;

public:
    LogicPuzzle(string q, string a, int minV, int maxV, int p = 15)
        : Puzzle(q, trim(a), p) {
        minVal = minV;
        maxVal = maxV;
    }

    void display() {
        divider();
        cout << BOLD << YELLOW << "LOGIC PUZZLE\n" << RESET;
        divider();
        cout << question << "\n\n";
        cout << BLUE << "Enter a number between " << minVal << " and " << maxVal << RESET << "\n\n";
    }

    bool solve() {
        string input;

        while (true) {
            cout << CYAN << "Your answer: " << RESET;
            getline(cin, input);
            input = trim(input);

            bool valid = true;

            if (input.empty())
                valid = false;

            for (int i = 0; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << RED << "Enter a valid number.\n" << RESET;
                continue;
            }

            int value = atoi(input.c_str());

            if (value < minVal || value > maxVal) {
                cout << RED << "Out of range.\n" << RESET;
                continue;
            }

            if (input == answer) {
                cout << GREEN << "\nCorrect!\n" << RESET;
                return true;
            } else {
                cout << RED << "\nWrong answer!\n" << RESET;
                return false;
            }
        }
    }
};


class Riddle : public Puzzle {

private:
    string hint;

public:
    Riddle(string q, string a, string h, int p = 20)
        : Puzzle(q, toLower(trim(a)), p) {
        hint = h;
    }

    void display() {
        divider();
        cout << BOLD << YELLOW << "RIDDLE\n" << RESET;
        divider();
        cout << question << "\n\n";
    }

    bool solve() {
        string input;
        int attempts = 0;

        while (attempts < 2) {
            cout << CYAN << "Your answer: " << RESET;
            getline(cin, input);
            input = toLower(trim(input));

            if (input == answer) {
                cout << GREEN << "\nCorrect!\n" << RESET;
                return true;
            }

            attempts++;

            if (attempts < 2) {
                cout << RED << "Wrong!\n" << RESET;
                cout << BLUE << "Hint: " << hint << RESET << "\n\n";
            }
        }

        cout << RED << "\nOut of attempts!\n" << RESET;
        cout << "Correct answer: " << answer << "\n";
        return false;
    }
};


class Player {

private:
    string name;
    int health;
    int score;
    vector<string> inventory;

public:
    Player(string n) {
        name = n;
        health = 100;
        score = 0;
    }

    string getName() { return name; }
    int getHealth()  { return health; }
    int getScore()   { return score; }

    void addScore(int p) {
        score += p;
    }

    void takeDamage(int d = 15) {
        health -= d;
        if (health < 0)
            health = 0;
    }

    bool isAlive() {
        return health > 0;
    }

    void addItem(string item) {
        inventory.push_back(item);
    }

    void showInventory() {
        divider();
        cout << BOLD << CYAN << "INVENTORY COLLECTED\n" << RESET;
        divider();

        if (inventory.empty()) {
            cout << RED << "No items collected.\n" << RESET;
        } else {
            for (int i = 0; i < inventory.size(); i++) {
                cout << YELLOW << " " << (i + 1) << ". " << RESET << inventory[i] << "\n";
            }
        }

        divider();
        cout << "\n";
    }

    void showStatus() {
        divider();
        cout << BLUE   << "PLAYER : " << RESET << name     << "\n";
        cout << GREEN  << "HEALTH : " << RESET << health   << "%\n";
        cout << YELLOW << "SCORE  : " << RESET << score    << "\n";

        if (!inventory.empty()) {
            cout << CYAN << "ITEMS  : " << RESET;
            for (int i = 0; i < inventory.size(); i++) {
                cout << inventory[i];
                if (i != inventory.size() - 1)
                    cout << ", ";
            }
            cout << "\n";
        }

        divider();
        cout << "\n";
    }
};


class Room {

private:
    string name;
    string description;
    Puzzle* puzzle;
    string reward;

public:
    Room(string n, string d, Puzzle* p, string r = "") {
        name = n;
        description = d;
        puzzle = p;
        reward = r;
    }

    ~Room() {
        delete puzzle;
    }

    bool enter(Player& player) {
        player.showStatus();

        cout << BOLD << CYAN << "ROOM: " << name << RESET << "\n\n";
        cout << description << "\n\n";

        puzzle->display();

        bool solved = puzzle->solve();

        if (solved) {
            player.addScore(puzzle->getPoints());

            if (reward != "") {
                player.addItem(reward);
                cout << GREEN << "\nYou found: " << reward << RESET << "\n";
            }

            cout << GREEN << "\nDoor unlocked!\n" << RESET;
        } else {
            player.takeDamage();
            cout << RED << "\nWrong answer! Health reduced.\n" << RESET;
        }

        cout << "\nPress Enter to continue...";
        string temp;
        getline(cin, temp);

        return solved;
    }
};


class GameManager {

private:
    vector<Room*> rooms;
    Player* player;

public:
    GameManager() {
        player = NULL;
    }

    ~GameManager() {
        for (int i = 0; i < rooms.size(); i++)
            delete rooms[i];
        delete player;
    }

    void setup() {
        divider();
        cout << BOLD << YELLOW << "DIGITAL ESCAPE ROOM\n" << RESET;
        divider();

        cout << CYAN << "Enter your name: " << RESET;
        string name;
        getline(cin, name);

        if (trim(name) == "")
            name = "Explorer";

        player = new Player(name);

        vector<string> mcq1;
        mcq1.push_back("Encapsulation");
        mcq1.push_back("Polymorphism");
        mcq1.push_back("Abstraction");
        mcq1.push_back("Compilation");

        rooms.push_back(new Room(
            "Dusty Library",
            "Bookshelves surround you.\nA glowing monitor asks a question.",
            new MCQPuzzle(
                "Which OOP concept allows derived classes to override base class functions?",
                mcq1, "b", 10
            ),
            "Rusty Key"
        ));

        rooms.push_back(new Room(
            "Clockwork Chamber",
            "Gears spin above your head.\nA numeric keypad blocks the exit.",
            new LogicPuzzle(
                "A vector starts empty.\nYou call push_back() 7 times.\nWhat is the vector size?",
                "7", 0, 100, 15
            ),
            "Gear Token"
        ));

        rooms.push_back(new Room(
            "Whispering Vault",
            "Ancient voices echo through the walls.",
            new Riddle(
                "What has keys but cannot open locks?",
                "keyboard",
                "You use it while programming.",
                20
            ),
            "Crystal Shard"
        ));

        vector<string> mcq2;
        mcq2.push_back("Array");
        mcq2.push_back("Pointer");
        mcq2.push_back("Vector");
        mcq2.push_back("Stack frame");

        rooms.push_back(new Room(
            "Lab of Echoes",
            "A computer terminal flickers in the dark.",
            new MCQPuzzle(
                "Which data structure automatically resizes itself in C++?",
                mcq2, "c", 10
            ),
            "Lab Badge"
        ));

        rooms.push_back(new Room(
            "Final Vault",
            "One final lock stands between you and freedom.",
            new LogicPuzzle(
                "If a loop runs from i=1 to i<=10\nand prints i*i,\nwhat is the LAST number printed?",
                "100", 1, 1000, 20
            )
        ));
    }

    void run() {
        bool escaped = true;

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->enter(*player);

            if (!player->isAlive()) {
                escaped = false;
                break;
            }
        }

        divider();

        if (escaped) {
            cout << GREEN << BOLD << "CONGRATULATIONS! YOU ESCAPED!\n" << RESET;
        } else {
            cout << RED << BOLD << "GAME OVER!\n" << RESET;
        }

        cout << "\n";
        cout << YELLOW << "Final Score : " << RESET << player->getScore()   << "\n";
        cout << BLUE   << "Health Left : " << RESET << player->getHealth()  << "%\n";
        cout << "\n";

        player->showInventory();
    }

    void start() {
        setup();
        run();
    }
};


int main() {
    GameManager game;
    game.start();
    return 0;
}
