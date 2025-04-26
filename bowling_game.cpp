#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

class BowlingGame {
public:
    void roll(int pins) {
        if (pins < 0 || pins > 10) {
            throw std::invalid_argument("Invalid pin count. Pins must be between 0 and 10.");
        }
        rolls.push_back(pins);
    }

    int score() {
        int totalScore = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (rollIndex >= rolls.size()) {
                throw std::out_of_range("Not enough rolls to complete the game.");
            }

            if (isStrike(rollIndex)) {
                int bonus = getRoll(rollIndex + 1) + getRoll(rollIndex + 2);
                totalScore += 10 + bonus;
                printFrame(frame + 1, 10 + bonus, totalScore);
                rollIndex += 1;
            } else if (isSpare(rollIndex)) {
                validateFrame(rollIndex);
                int bonus = getRoll(rollIndex + 2);
                totalScore += 10 + bonus;
                printFrame(frame + 1, 10 + bonus, totalScore);
                rollIndex += 2;
            } else {
                validateFrame(rollIndex);
                int frameScore = getRoll(rollIndex) + getRoll(rollIndex + 1);
                totalScore += frameScore;
                printFrame(frame + 1, frameScore, totalScore);
                rollIndex += 2;
            }
        }

        return totalScore;
    }

private:
    std::vector<int> rolls;

    int getRoll(int index) const {
        if (index >= rolls.size()) return 0;
        return rolls[index];
    }

    bool isStrike(int index) const {
        return getRoll(index) == 10;
    }

    bool isSpare(int index) const {
        return getRoll(index) + getRoll(index + 1) == 10;
    }

    void validateFrame(int index) {
        if (getRoll(index) != 10) { // not a strike
            int sum = getRoll(index) + getRoll(index + 1);
            if (sum > 10) {
                throw std::logic_error("Frame score exceeds 10 pins.");
            }
        }
    }

    void printFrame(int frameNumber, int frameScore, int totalScore) {
        std::cout << "Frame " << std::setw(2) << frameNumber << ": "
                  << "Frame Score = " << std::setw(3) << frameScore
                  << ", Total Score = " << std::setw(3) << totalScore << std::endl;
    }
};

// === MAIN ===

int main() {
    BowlingGame game;
    std::vector<int> inputRolls;
    int pin;

    std::cout << "Enter the rolls (0-10), separated by space, end with -1:\n";

    try {
        while (std::cin >> pin && pin != -1) {
            game.roll(pin);  // Validation inside roll()
        }

        std::cout << "\n=== SCORE SUMMARY ===\n";
        int total = game.score();
        std::cout << "\nFinal Total Score: " << total << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "[Invalid Input] " << e.what() << std::endl;
    } catch (const std::logic_error& e) {
        std::cerr << "[Logical Error] " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "[Out of Range] " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "[Unknown Error] Something went wrong." << std::endl;
    }

    return 0;
}
