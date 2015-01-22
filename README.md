Connect-4
=========

A simple c++ console application. A connect-4 game with reasonable ai.

## Alpha-beta pruning

The Alpha-beta prunning is an adversarial searching algorithm used for playing of two-player games. It is an advanced algorithm which is evaluated by the minimax algorithm in its search tree.

Reference from [Minimax with Alpha Beta Pruning](http://cs.ucla.edu/~rosen/161/notes/alphabeta.html)
and [Brian's Project - Connect Four](http://www.brian-borowski.com/software/connectfour/)

## Description

This project is to learn the alpha-beta pruning by implementing the algorithm to a simple [connect-4](http://en.wikipedia.org/wiki/Connect_Four) game. Because there are too many possible situations for the search tree, the computer cannot solve the search tree by simply implement the minimax algorithm just like the [tictactoe](https://github.com/prgerLeo/tictactoe) project. Therefore, alpha-beta pruning is implemented to limit the possible predictation and make the reasonable decision.

## How to play

Run the main.o file `./connect4` in terminal and start playing the connect-4. 

