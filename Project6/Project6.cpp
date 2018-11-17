#include <stdio.h>
#include <stdint.h>
#include "MazeParams.h"
#include "Recursion.h"

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 */
int minIt(int x[], int n) {
	int min = x[0];
	for (int i = 0; i < n; i++) {
	    if (x[i] < min) {
	        min = x[i];
	    }
	}

	return min;
}

/* return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and 
 * use an "n-1" type of decomposition
 */
int minRec1(int x[], int n) {
    if (n <= 1) {
        return x[0];
    }

    // Compare first and last letters
    if (x[0] > x[n-1]) {
        return minRec1(x+1, n-1);
    } else {
        return minRec1(x, n-1);
    }
}

/*
 * return the smallest of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and 
 * use an "n / 2" type of decomposition
 */
int minRec2(int x[], int n) {
    int half, left, right;
    // Base case
    if (n <= 1) {
        return x[0];
    }

    // Find min of left half and of right half
    half = n/2;
    left = minRec2(x, half);

    if (n%2 != 0) {
        right = minRec2(x + half, half + 1);
    } else {
        right = minRec2(x + half, half);
    }

    if (left < right) {
        return left;
    } else {
        return right;
    }
}


/*
 * calculate and return the square root of x.
 * The other two parameters are estimates of the square root.
 * low_guess is smaller than the actual square root, and high_guess 
 * is larger than the actual square root.
 * Searching for the square root can be done much like searching
 * for a name in a phone book.
 *
 * Since you can't calculate a square root exactly, for this problem
 * you're required to calculate the answer to 15 decimal digits of
 * accuracy.
 */
double sqrtIt(double x, double low_guess, double high_guess) {
    double guess = low_guess + ((high_guess - low_guess) / 2); // Binary search for sqrt
    while (high_guess - low_guess > 0.000000000000001) { // Exit condition, our number is within 1^-15
        if (guess * guess > x) {
            high_guess = guess;
        } else {
            low_guess = guess;
        }

        guess = low_guess + ((high_guess - low_guess) / 2);
    }

    return  guess;
}

/*
 * calculate and return the square root of x.
 * The other two parameters are estimates of the square root.
 * low_guess is smaller than the actual square root, and high_guess 
 * is larger than the actual square root.
 * Searching for the square root can be done much like searching
 * for a name in a phone book.
 *
 * Since you can't calculate a square root exactly, for this problem
 * you're required to calculate the answer to 15 decimal digits of
 * accuracy.
 */
double sqrtRec(double x, double low_guess, double high_guess) {
	double guess = low_guess + ((high_guess - low_guess) / 2);

	// Base case, when our guesses are numbers within 1^-15 of each other
	// They are accurate enough
	if (guess == low_guess || guess == high_guess) {
	    return guess;
	}

    // "Searching for the square root can be done much like searching
    // for a name in a phone book" I.E do binary search
	if (guess * guess < x) {
        return sqrtRec(x, guess, high_guess);
	} else {
	    return sqrtRec(x, low_guess, guess);
	}
}


/*
 * using only recursion, write a string comparison function
 * return -1 if str1 is less than str2
 * return 0 if the two strings are equal
 * return +1 if str1 is greater than str2
 * when comparing strings, use the ASCII value to compare each character
 * (i.e., that means 'A' is less than 'a' since it's ASCII value is smaller)
 * The string str1 is less than str2 if either
 * str1[0] < str2[0]
 * or there exists a k such that str1[k] < str2[k] and 
 *   for all j < k str1[j] == str2[j]
 *   and k is less than the length of str1 and str2
 */

int strCompare(char* str1, char* str2) {
    // Ensure lengths are taken into account for string comparison
    if (*str1 == 0 && *str2 != 0) {
        return -1;
    } else if (*str2 == 0 && *str1 != 0) {
        return 1;
    } else if (*str1 == 0 && *str2 == 0) {
        return 0;
    }

	if (*str1 < *str2) {
	    return -1;
	} else if (*str1 > *str2) {
	    return 1;
	} else {
	    return strCompare(str1 + 1, str2 + 1);
	}
}

/*
 * if c is not a letter return -1
 * if c is a letter, return the position of c in the alphabet 
 * where 'A' (and 'a') are position 1 and 'Z' (and 'z') are position 26
 *
 * This code is rather ugly as I'm exploiting some detailed knowledge of the ASCII table
 */
int whatLetter(char c) {
	if (c < 'A') { return -1; }
	if (c > 'z') { return -1; }
	if (c > 'Z' && c < 'a') { return -1; }
	return c & ~32 - 64;
}

/*
 * same as before, only this time 
 * ignore anything that is not a letter
 * ignore the case (upper case, lower case)
 * So, strCompare2("Hello", "hello") should return 0 (they're the same)
 * strCompare2("The plane!", "theater") should return 1 since "theplane" is larger than "theater"
 * once again, you can only use recursion, no loops
 */
int strCompare2(char* str1, char* str2) {
    int what1 = whatLetter(*str1);
    int what2 = whatLetter(*str2);

    if (*str1 == 0 && *str2 != 0) {
        //Make sure that if one is at the end, the other doesn't still have non-chars
        if (what2 == -1) {
            return strCompare2(str1, str2 + 1);
        } else {
            return -1;
        }
    } else if (*str2 == 0 && *str1 != 0) {
        if (what1 == -1) {
            return strCompare2(str1 + 1, str2);
        } else {
            return 1;
        }
    } else if (*str1 == 0 && *str2 == 0) {
        return 0;
    }

    if (what1 == -1) {
        return strCompare2(str1 + 1, str2);
    }

    if (what2 == -1) {
        return strCompare2(str1, str2 + 1);
    }

    if (what1 < what2) {
        return -1;
    } else if (what1 > what2) {
        return 1;
    } else {
        return strCompare2(str1 + 1, str2 + 1);
    }
}



/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the 
 * value is 1).  Each 0 represents an open space.  
 *
 * Write an recursive solution to find your way out of the maze
 * Your starting point is at row and col. (params to this function)
 * Your exit point is somewhere in the last row (which is: MATRIX_SIZE - 1)
 *
 * There is a relatively easy recursive solution to this problem, the trick is
 * to think of the solution in the following terms:
 *   "In which direction(s) can I go and find a way out of this maze?"
 * In some cases, you may find yourself in a spot in the maze that there's
 * no way out (at least, not without backtracking). In that case, you'd return "false"
 * since the maze has no solution. In most cases, there's one or more ways out
 * from where you are now. Your key question is simply, "what is the first step I need to take"
 *
 * If you considered going "north", and you had a function that could tell you whether
 * it was possible to get out of the maze starting at the square to the north of your 
 * current position, then you could use this function to determine if you can get out by
 * going north first. Similarly, you could consider going south, east or west, and (recursively)
 * determine if the maze can be solved from any of those locations.
 *
 * With that hint, the base case should be pretty obvious.  In fact,
 * I'd suggest you consider the possibility that the base case is "Yup, I'm already at 
 * the exit!"
 *
 * There is one tricky part to this decomposition.  You need to make certain 
 * that the problem is getting smaller.  The "bigness" or "smallness" of this 
 * problem is the number of squares that have not yet been tested.  Each time
 * you test an adjacent square (making a recursive call to decide if there is a 
 * path to the exit through that square), you'll be reducing  the number of squares 
 * that have not yet been tested.  Eventually, you must have tested all the 
 * squares and so you'll have to have found a way to the exit.
 *
 * The easy way to deal with the tricky part is to leave "bread crumbs" behind.
 * Before you recursively check any (or all) of your neighbors to see if you 
 * can find the exit from there -- drop a bread crumb in your current square.
 * Then, don't ever check to see if you can find the exit using a square
 * with a breadcrumb in it (backtracking into that square would be silly).
 *
 * If you're trying to see if you can find an exit from some square, and all 
 * the adjacent squares are either walls, or have bread crumbs in them, then
 * you already know the answer -- "you can't get to the exit from here".
 * Pick up your bread crumb and return false.
 * 
 * You can set the value of the current square to "2" to indicate that a bread
 * crumb has been dropped.  Set the square back to 0 when you want to pick 
 * the bread crumb back up.
 * be sure not to change any of the squares that are 1 (the walls).
 *
 * for partial credit, you can leave all your bread crumbs on the floor.
 * for full credit, you must pick up all the bread crumbs EXCEPT those
 * along a path to the exit.
 */

int solveMazeRec(int row, int col) {
    int u = 0, d = 0, l = 0, r = 0;
    int temp = maze[row][col];

    if (maze[row][col] == 0 && row == MATRIX_SIZE - 1) {
        maze[row][col] = 2; // Bread Crumb for the last location on the map
        return 1;
    }

    maze[row][col] = 2; // Bread Crumb
    if (row > 0 && row < MATRIX_SIZE) { // Up
	    if (maze[row - 1][col] == 0) {
	        u = solveMazeRec(row - 1, col);
	    }
	    if (u == 1) {
	        return u;
	    }
	}

	if (row >= 0 && row < MATRIX_SIZE - 1) { // Down
        if (maze[row + 1][col] == 0) {
            d = solveMazeRec(row + 1, col);
        }

        if (d == 1) {
            return d;
        }
	}

	if (col > 0 && col < MATRIX_SIZE) { // Left
        if (maze[row][col - 1] == 0) {
            l = solveMazeRec(row, col - 1);
        }

        if (l == 1) {
            return  l;
        }
	}

	if (col >= 0 && col < MATRIX_SIZE - 1) { // Right
        if (maze[row][col + 1] == 0) {
            r = solveMazeRec(row, col + 1);
        }

        if (r == 1) {
            return r;
        }
	}

    maze[row][col] = temp; // Pick bread crumb back up
	return 0;
}


/**********************
 * adjacentCell and isOK are functions provided to help you write
 * solveMazeIt()
 */

/*
 * OK, we're currently at maze[row][col] and we're considering moving
 * in direction dir.  
 * Set trow and tcol (local variables inside the calling function)
 * to the row and column that we would move to IF we moved in
 * that direction
 *
 * For example, there are two good ways to use this function.
 * 1. to actually move one step in a direction use:
 *       adjacentCell(row, col, dir, &row, &col);
 *    That will set row and col to new values.  The new values will
 *    be one square away from the old values.
 *
 * 2. to set trow and tcol to a square that is adjacent to row and col use:
 *       adjacentCell(row, col, dir, &trow, &tcol);
 *    That will not change row and col, but will change trow and tcol.
 *    This is useful if you aren't sure if you can actually move in this 
 *    direction yet (e.g., maze[trow][tcol] may be a wall!).  So, you set
 *    trow and tcol, and then check to see if it's OK to move there
 */
void adjacentCell(int row, int col, int dir, int* trow, int* tcol) {
	*trow = row;
	*tcol = col;
	switch(dir) {
	case 0: // UP
		*trow = *trow - 1;
		break;
	case 1: // RIGHT
		*tcol = *tcol + 1;
		break;
	case 2: // DOWN
		*trow = *trow + 1;
		break;
	case 3: // LEFT
		*tcol = *tcol - 1;
		break;
	}
}


/* 
 * return false if there is a wall in the square for row and col
 * return true if it's not a wall.
 */
int isOK(int row, int col) {
	return (row > 0 && row < MATRIX_SIZE
		&& col > 0 && col < MATRIX_SIZE
		&& maze[row][col] != 1);
}

/*
 * return the value of the direction that is one turn to the right
 */
int turnRight(int dir) {
	return (dir + 1) % 4;
}

/*
 * return the value of the direction that is one turn to the left
 */
int turnLeft(int dir) {
	return (dir + 3) % 4;
}

/*
 * the two dimensional array maze[MATRIX_SIZE][MATRIX_SIZE] contains a maze
 * Each square is (initially) either a 1 or a zero.  Each 1 represents a wall
 * (you cannot walk through walls, so you can't go into any square where the value
 * is 1).  Each 0 represents an open space.  
 *
 * write an iterative solution to find your way out of the maze
 * Your starting point is at row and col. (params to this function)
 * Your exit point is somewhere in the last row (which is: MATRIX_SIZE - 1)
 * The maze can be solved by following the right hand wall.  In fact, there
 * is exactly one path between any two points in the maze (well, between any two
 * points that are not walls).
 *
 * The algorithm is not too bad, although it is certainly not trivial
 * Initially, you'll be headed DOWN (direction 2)
 * Each iteration do one of the following.  Note that only one of two cases
 * can possibly apply (the properties of the maze guarantee that).
 *    case 1: you can move in the current direction
 *       In this case, you should take one step in the current direction
 *       and then turn right.  
 *    case 2: you cannot move in the current direction
 *       If there's a wall directly in front of you, then to follow the right
 *       hand wall, you'd need to turn left (placing your hand on the wall that
 *       used to be directly in front of you).  So, if you discover this case
 *       then turn left.  Don't move, just turn left.
 * If you were walking down a straight corridor (with walls on both sides)
 * then you'd alternate case 1 and case 2.  On the first iteration, you'd
 * take a step, and then turn right (case 1).  This causes you to walk
 * one position down the hallway but then turn to face the wall.
 * On the next iteration, you'll be facing the wall, so you can't walk
 * forward and therefore (case 2) you'll turn left.  On the third iteration
 * you'll be able to walk down the hallway again.
 *
 * If you follow those two cases, then you'll eventually find your way out
 * of the maze.  To confirm that you're making it out, leave a "bread crumb" 
 * behind each square along the path to the exit.
 * For partial credit, place a bread crumb in every square you visit.
 * For full credit, pick up all the breadcrumbs when you backtrack.  
 * Backtracking is when you go back to a square you've already been before.  
 * If the square you're about to step into has a breadcrumb, then pick up 
 * the bread crumb in the square you're at now.
 * You indicate "bread crumbs" by setting the square equal to "2"
 */
void solveMazeIt(int row, int col) {
    int dir = 2; // 0 is up, 1 is right, 2 is down, 3 is left.
    maze[row][col] = 2; // drop a bread crumb in the starting square
    while (row < MATRIX_SIZE - 1) { // the exit is the only open square
        // in the last row

        /* the rest of this loop is yours */

    }
}


Martian minMartian(Martian m1, Martian m2, Martian m3) {
    // Number of coins in each martian
    int sum1 = m1.pennies + m1.nicks + m1.dodeks;
    int sum2 = m2.pennies + m2.nicks + m2.dodeks;
    int sum3 = m3.pennies + m3.nicks + m3.dodeks;

    // We should not include martians who do not have any coins
    // Find the minimum
    if (sum1 != 0 && sum2 != 0 && sum3 != 0){
        if (sum1 <= sum2 && sum1 <= sum3) {
            return m1;
        } else if (sum2 <= sum1 && sum2 <= sum3) {
            return m2;
        } else if (sum3 <= sum1 && sum3 <= sum2){
            return m3;
        }
    } else {
        if (sum1 == 0 && sum2 == 0) {
                return m3;
        } else if (sum1 == 0 && sum3 == 0) {
            return m2;
        } else if (sum2 == 0 && sum3 == 0) {
            return m1;
        } else {
            if (sum1 == 0) {
                if (sum2 <= sum3) {
                    return m2;
                } else {
                    return m3;
                }
            } else if (sum2 == 0) {
                if (sum1 <= sum3) {
                    return m1;
                } else {
                    return m3;
                }
            } else if (sum3 == 0) {
                if (sum1 <= sum2) {
                    return m1;
                } else {
                    return m2;
                }
            }
        }
    }
}


/*
 * using recursion, with no loops or globals, write a function that calculates the optimal
 * (fewest total coins) change for a given amount of money. Return a Martian struct that indicates
 * this optimal collection of coins.
 */
Martian change(int cents) {
    // Find every combination of coins that add up to cents
    Martian m1 =  {0, 0, 0}; // If we subtracted a 12 first
    Martian m2 =  {0, 0, 0}; // If we subtracted a 5 first
    Martian m3 =  {0, 0, 0}; // If we subtracted a penny first

    // This line ensures that minMartian shouldn't count martians that have 0 coins
    // when trying to find the minimum number of coins used to get the sum
    // Base Case
    if (cents < 1) {
        return m1;
    }

    // Subtract 12 from cents if possible
    // If not possible, m1 will be 0- which is why we check for 0 in minMartian
    if (cents >= 12) {
        m1 = change(cents - 12);
        m1.dodeks += 1;
    }

    // Subtract nick from cents if possible
    // If not possible, m2 will be 0- which is why we check for 0 in minMartian
    if (cents >= 5) {
        m2 = change(cents - 5);
        m2.nicks += 1;
    }


    // Subtract 1 from cents if possible
    // If not possible, m3 will be 0- which is why we check for 0 in minMartian
    if (cents >= 1) {
        if (cents < 5 /*&& cents < 12*/ ) { // Small optimization so it doesn't just call this function a bunch
            m3.pennies = cents;
            return m3;
        } else {
            m3 = change(cents - 1);
            m3.pennies += 1;
        }
    }

    return minMartian(m1, m2, m3); // Return the martian with the smallest number of coins used to make the total
}

/*
 * Same as before, except the more general version where the coins have values
 * a cents and b cents, with a and b being algebraic. For the original problem, 
 * a is the constant 5 (nick_value = 5 cents) and b is the constant 12 
 * (dodek_value = 12 cents). 
 * If you've really mastered thinking recursively, then this version of the 
 * martian change problem is just as easy as the concrete version 
 */
Martian change(int cents, int nick_val, int dodek_val) {
    // Find every combination of coins that add up to cents
	Martian m1 =  {0, 0, 0}; // If we subtracted a dodek first
    Martian m2 =  {0, 0, 0}; // If we subtracted a nick first
    Martian m3 =  {0, 0, 0}; // If we subtracted a penny first

    // This line ensures that minMartian shouldn't count martians that have 0 coins
    // when trying to find the minimum number of coins used to get the sum
    // Base Case
    if (cents < 1) {
        return m1;
    }

    // Subtract dodek from cents if possible
    // If not possible, m1 will be 0- which is why we check for 0 in minMartian
    if (cents >= dodek_val) {
        m1 = change(cents - dodek_val, nick_val, dodek_val);
        m1.dodeks += 1;
    }

    // Subtract nick from cents if possible
    // If not possible, m2 will be 0- which is why we check for 0 in minMartian
    if (cents >= nick_val) {
        m2 = change(cents - nick_val, nick_val, dodek_val);
        m2.nicks += 1;
    }


    // Subtract 1 from cents if possible
    // If not possible, m3 will be 0- which is why we check for 0 in minMartian
    if (cents >= 1) {
        if (cents < nick_val && cents < dodek_val) { // Small optimization so it doesn't just call this function a bunch
            m3.pennies = cents;
            return m3;
        } else {
            m3 = change(cents - 1, nick_val, dodek_val);
            m3.pennies += 1;
        }
    }

    return minMartian(m1, m2, m3); // Return the martian with the smallest number of coins used to make the total
}

/* 
 * without using recursion, solve the Martian change problem described above.
 * it's not too bad for the specific case of nick_value = 5 and dodek_value = 12
 */
Martian changeIt(int cents) {
	return Martian{}; // delete this line, it's broken. Then write the function properly!
}

/*
 * However, I don't have a solution for the general case. In fact, I consider 
 * the general problem to "challenging" (i.e, an exercise in futility). 
 * But, if you like banging your head against the wall for zero credit
 * this is the problem for you!
 */
Martian changeIt(int cents, int nick_value, int dodek_value) {
	return Martian{}; // delete this line, it's broken. Then write the function properly!
}
