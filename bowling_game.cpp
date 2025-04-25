#include <iostream>
#include <vector>
#include <iomanip>

class BowlingGame {
public:
    void roll(int pins) {
        rolls.push_back(pins);
    }

    int score() {
        int totalScore = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (isStrike(rollIndex)) {
                int frameScore = 10 + strikeBonus(rollIndex);
                totalScore += frameScore;
                printFrame(frame + 1, frameScore, totalScore);
                rollIndex += 1;
            } else if (isSpare(rollIndex)) {
                int frameScore = 10 + spareBonus(rollIndex);
                totalScore += frameScore;
                printFrame(frame + 1, frameScore, totalScore);
                rollIndex += 2;
            } else {
                int frameScore = sumOfBallsInFrame(rollIndex);
                totalScore += frameScore;
                printFrame(frame + 1, frameScore, totalScore);
                rollIndex += 2;
            }
        }

        return totalScore;
    }

private:
    std::vector<int> rolls;

    bool isStrike(int index) {
        return index < rolls.size() && rolls[index] == 10;
    }

    bool isSpare(int index) {
        return index + 1 < rolls.size() &&
               rolls[index] + rolls[index + 1] == 10;
    }

    int strikeBonus(int index) {
        if (index + 2 < rolls.size()) {
            return rolls[index + 1] + rolls[index + 2];
        }
        return 0;
    }

    int spareBonus(int index) {
        if (index + 2 < rolls.size()) {
            return rolls[index + 2];
        }
        return 0;
    }

    int sumOfBallsInFrame(int index) {
        if (index + 1 < rolls.size()) {
            return rolls[index] + rolls[index + 1];
        }
        return rolls[index]; // In case of incomplete data
    }

    void printFrame(int frameNumber, int frameScore, int totalScore) {
        std::cout << "Frame " << std::setw(2) << frameNumber << ": "
                  << "Frame Score = " << std::setw(3) << frameScore
                  << ", Total Score = " << std::setw(3) << totalScore << std::endl;
    }
};

int main() {
    BowlingGame game;

    // Generic: you can replace this input with any sequence of rolls
    std::vector<int> rolls;

    std::cout << "Enter the rolls (enter -1 to end):" << std::endl;
    int pin;
    while (std::cin >> pin && pin != -1) {
        if (pin < 0 || pin > 10) {
            std::cout << "Invalid input. Enter a number between 0 and 10.\n";
            continue;
        }
        rolls.push_back(pin);
    }

    for (int pins : rolls) {
        game.roll(pins);
    }

    std::cout << "\n=== SCORE SUMMARY ===" << std::endl;
    int total = game.score();
    std::cout << "\nFinal Total Score: " << total << std::endl;

    return 0;
}
