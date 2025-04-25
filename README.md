# Bowling_Game
Bowling Game
Bowling Game
Please implement a program calculating the score of a single player in Bowling.

Game Rules
. A bowling game consists of 10 frames.
. Each frame, the player has two tries to knock down 10 pins with a bowling ball.
. The score for the frame is the total of knocked down pins, plus bonuses for strikes and
spared.
. A Spare is when a player knocks down all 10 pins in two tries.
o The bonus for this frame is the number of pins knocked down by the next roll.
. A Strike is when the player knocks down all 10 pins on his first try.
o The bonus for this frame is the number of pins knocked down by the next two rolls.
. In the 10h frame, a player is allowed to throw an extra ball if she/he scores a Spare or a
Strike.
o No more than three throws are allowed for the 10m frame.
o No bonus scores are granted for Strikes and Spares in 10™h frame.
o If a player hits a Strike / Spare, 10 pins will be avallable again for the next throw within
the 10h frame.

Example

1 4
5

4 5
14


. 2nd Frame:
o Frame score is 9 (4+5)
o Total score is 14 (9 frame score + 5 total score of frame 1)
· 3rd Frame:
o Frame score is 10 (Spare)
o Total score is 29 (10 frame score + 14 total score of frame 2 + 5 bonus for next roll)
. 5th Frame:
o Frame score is 10 (Strike)
o Total score is 60 (10 frame score + 49 total score of frame 4 + 1 bonus for the next
two rolls)
