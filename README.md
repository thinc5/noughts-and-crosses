# Noughts and Crosses

## Why?

This is a minimal C implementation of the trival game "Noughts and Crosses", "Tic Tac Toe" etc...

The goal is to eventually create a SDK/Library that allows for easy implementation of this game with different targets/interfaces.

The project exists as an experiment in writing these interfaces.

Currently the `main.c` implementation is terminal based.


## Compilation

A C compiler is required.

`gcc -o crosses main.c noughts_and_crosses.c`

## Playing

You may need to set the binary as executable via `chmod +x ./crosses`

Crosses ('X') always go first.

`./crosses`

```
$ ./crosses 
___
___
___
Cross's turn, enter coordinates "x,y" > 
```

The game board is printed at the start of the game and after every successful move.

To make a move enter the target coordinates in the format "x,y" (no spaces) to "place" your piece.

Valid coordinate range is 1-3 on the X and Y axis.

For example;

```
Cross's turn, enter coordinates "x,y" > 2,2
___
_X_
___
Nought's turn, enter coordinates "x,y" > 
```

Now it is the Nought player's turn.

```
Nought's turn, enter coordinates "x,y" > 1,2 
___
OX_
___
Cross's turn, enter coordinates "x,y" > 3,3
___
OX_
__X
Nought's turn, enter coordinates "x,y" > 1,1
O__
OX_
__X
Cross's turn, enter coordinates "x,y" > 1,3
O__
OX_
X_X
Nought's turn, enter coordinates "x,y" > 3,1
O_O
OX_
X_X
Cross's turn, enter coordinates "x,y" > 2,3
O_O
OX_
XXX
Cross player won!
Play again? "y/n" > 
```


At the end of the game the player is prompted to restart the game or terminate the program.
