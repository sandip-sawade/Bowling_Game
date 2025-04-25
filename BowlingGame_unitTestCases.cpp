// used google test for unit test cases 
/* Test Case	Description	Expected Result
TC1: All Gutter Balls	20 rolls of 0	Score = 0
TC2: All Ones	20 rolls of 1	Score = 20
TC3: One Spare	5 + 5 + 3 + 0...	Score = 16 + rest
TC4: One Strike	10 + 3 + 4 + 0...	Score = 24 + rest
TC5: Perfect Game	12 rolls of 10 (300 score)	Score = 300
TC6: Random Normal Game	No strikes or spares	Sum of rolls
TC7: Invalid Roll Input	Roll more than 10 pins	Should throw invalid_argument
TC8: Frame Sum > 10 Without Strike	Rolls like 7 + 6	Should throw logic_error
TC9: Incomplete Game	Less than required rolls	Should throw out_of_range
TC10: Extra Rolls (Perfect Game Bonus)	Allow correct extra rolls in 10th frame	Should handle correctly

*/
#include "gtest/gtest.h"
#include "BowlingGame.h"  // Assuming your class is in this file

// Helper to roll multiple times
void rollMany(BowlingGame& game, int n, int pins) {
    for (int i = 0; i < n; ++i) {
        game.roll(pins);
    }
}

TEST(BowlingGameTest, AllGutterBalls) {
    BowlingGame game;
    rollMany(game, 20, 0);
    EXPECT_EQ(game.score(), 0);
}

TEST(BowlingGameTest, AllOnes) {
    BowlingGame game;
    rollMany(game, 20, 1);
    EXPECT_EQ(game.score(), 20);
}

TEST(BowlingGameTest, OneSpare) {
    BowlingGame game;
    game.roll(5);
    game.roll(5); // spare
    game.roll(3);
    rollMany(game, 17, 0);
    EXPECT_EQ(game.score(), 16);
}

TEST(BowlingGameTest, OneStrike) {
    BowlingGame game;
    game.roll(10); // strike
    game.roll(3);
    game.roll(4);
    rollMany(game, 16, 0);
    EXPECT_EQ(game.score(), 24);
}

TEST(BowlingGameTest, PerfectGame) {
    BowlingGame game;
    rollMany(game, 12, 10);
    EXPECT_EQ(game.score(), 300);
}

TEST(BowlingGameTest, RandomNormalGame) {
    BowlingGame game;
    std::vector<int> rolls = {1, 2, 3, 4, 5, 2, 7, 1, 2, 5, 6, 2, 4, 3, 3, 5, 2, 3, 4, 4};
    for (int pins : rolls) {
        game.roll(pins);
    }
    EXPECT_EQ(game.score(), 74);  // Sum of all
}

TEST(BowlingGameTest, InvalidRollThrows) {
    BowlingGame game;
    EXPECT_THROW(game.roll(11), std::invalid_argument);
}

TEST(BowlingGameTest, FrameSumExceedsThrows) {
    BowlingGame game;
    game.roll(7);
    EXPECT_NO_THROW(game.roll(2)); // okay
    game.roll(7);
    EXPECT_THROW(game.roll(6), std::logic_error); // should throw
}

TEST(BowlingGameTest, IncompleteGameThrows) {
    BowlingGame game;
    rollMany(game, 5, 4); // 5 rolls, not enough
    EXPECT_THROW(game.score(), std::out_of_range);
}

TEST(BowlingGameTest, ExtraRollsInTenthFrame) {
    BowlingGame game;
    rollMany(game, 18, 0); // 9 frames
    game.roll(10); // 10th frame strike
    game.roll(10); // bonus
    game.roll(10); // bonus
    EXPECT_EQ(game.score(), 30);
}
