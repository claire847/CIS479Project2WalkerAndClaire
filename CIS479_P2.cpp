//Claire Hofmann & Walker Bass CIS-479 P2

#include <iostream>
#include <iomanip>
using namespace std;

const int ROWS = 8;
const int COLS = 9;
//P(sense obstacle | obstacle) = 0.8
float probSenseObstacle = 0.8;
//P(senses no obstacle | obstacle) = 1 - 0.8 = 0.2
float probFalseNoObstacle = 0.2;
//P(sense obstacle | no obstacle) = 0.15
float probFalseObstacle = 0.15;
//P(senses no obstacle | no obstacle) = 1 - 0.15 = 0.85
float probSenseNoObstacle = 0.85;

//Puzzle including a border around the edge
int maze[ROWS][COLS] = 
{   {1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1}, 
	{1,0,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1},
};

//Matrix of probabilities
float probs[ROWS][COLS];

//Temporary matrix
float motionPuzzle[ROWS][COLS];

float sensingCalculation(int evidence[4], int row, int col)
{
	float result = 1.0;

	//If obstacle sensed to the west
	if (evidence[0] == 1)
	{
		//If obstacle to the west in maze
		if (maze[row][col - 1] == 1)
			result *= probSenseObstacle;

		//If no obstacle to the west in maze
		else
			result *= probFalseObstacle;
	}
	//If no obstacle sensed to the west
	else
	{
		//If obstacle to the west in maze
		if (maze[row][col - 1] == 1)
		{
			result *= probFalseNoObstacle;
		}

		//If no obstacle to the west in maze
		else
		{
			result *= probSenseNoObstacle;
		}
	}

	//If obstacle sensed to the north
	if (evidence[1] == 1)
	{
		//If obstacle to the north in maze
		if (maze[row - 1][col] == 1)
			result *= probSenseObstacle;

		//If no obstacle to the north in maze
		else
			result *= probFalseObstacle;
	}
	//If no obstacle sensed to the north
	else
	{
		//If obstacle to the north in maze
		if (maze[row - 1][col] == 1)
		{
			result *= probFalseNoObstacle;
		}

		//If no obstacle to the north in maze
		else
		{
			result *= probSenseNoObstacle;
		}
	}

	//If obstacle sensed to the east
	if (evidence[2] == 1)
	{
		//If obstacle to the east in maze
		if (maze[row][col + 1] == 1)
			result *= probSenseObstacle;

		//If no obstacle to the east in maze
		else
			result *= probFalseObstacle;
	}
	//If no obstacle sensed to the east
	else
	{
		//If obstacle to the east in maze
		if (maze[row][col + 1] == 1)
		{
			result *= probFalseNoObstacle;
		}

		//If no obstacle to the east in maze
		else
		{
			result *= probSenseNoObstacle;
		}
	}

	//If obstacle sensed to the south
	if (evidence[3] == 1)
	{
		//If obstacle to the south in maze
		if (maze[row + 1][col] == 1)
			result *= probSenseObstacle;

		//If no obstacle to the south in maze
		else
			result *= probFalseObstacle;
	}
	//If no obstacle sensed to the south
	else
	{
		//If obstacle to the south in maze
		if (maze[row + 1][col] == 1)
		{
			result *= probFalseNoObstacle;
		}

		//If no obstacle to the south in maze
		else
		{
			result *= probSenseNoObstacle;
		}
	}

	return result;
}

//Use evidence conditional probability P(Zt|St)
void sensing(int evidence[4])
{
	float denominator = 0;

	//Calculates denominator
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (maze[r][c] != 1)
			{
				denominator += sensingCalculation(evidence, r, c) * probs[r][c];
			}
		}
	}

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			//If the current space isn't an obstacle
			if (maze[row][col] != 1)
			{
				float currentProbabilty = probs[row][col];
				float numerator = sensingCalculation(evidence, row, col)*currentProbabilty;
				float result = numerator / denominator;

				probs[row][col] = result;
			}

		}
	}
}


//Use transition probability P(St|St-1)
void motion(int direction)
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (maze[row][col] != 1)
			{
				float total = 0.0;
				//north
				if (direction == 1)
				{
					//checking west
					if (maze[row][col - 1] != 1)
					{
						total += probs[row][col - 1]  * 0.1;
					}
					else
					{
						total += probs[row][col] * 0.1;
					}

					//checking north
					if (maze[row - 1][col] != 1)
					{
						total += probs[row - 1][col] * 0;
					}
					else
					{
						total += probs[row][col] * 0.8;
					}

					//checking east
					if (maze[row][col + 1] != 1)
					{
						total += probs[row][col + 1] * 0.1;
					}
					else
					{
						total += probs[row][col] * 0.1;
					}

					//checking south
					if (maze[row + 1][col] != 1)
					{
						total += probs[row + 1][col] * 0.8;
					}
					else
					{
						total += probs[row][col] * 0;
					}
				}

				//west
				else if (direction == 0)
				{
					//checking west
					if (maze[row][col - 1] != 1)
					{
						total += probs[row][col - 1] * 0;
					}
					else
					{
						total += probs[row][col] * 0.8;
					}

					//checking north
					if (maze[row - 1][col] != 1)
					{
						total += probs[row - 1][col] * 0.1;
					}
					else
					{
						total += probs[row][col] * 0.1;
					}

					//checking east
					if (maze[row][col + 1] != 1)
					{
						total += probs[row][col + 1] * 0.8;
					}
					else
					{
						total += probs[row][col] * 0;
					}

					//checking south
					if (maze[row + 1][col] != 1)
					{
						total += probs[row + 1][col] * 0.1;
					}
					else
					{
						total += probs[row][col] * 0.1;
					}
				}
				motionPuzzle[row][col] = total;
			}
			else
			{
				motionPuzzle[row][col] = -1;
			}
		}
	}

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			probs[r][c] = motionPuzzle[r][c];
		}
	}
}

void printPuzzle(float puzzle[ROWS][COLS])
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (puzzle[row][col] == -1)
				cout << "##### ";
			else
				cout << setprecision(2) << fixed << puzzle[row][col]*100.0 << "  ";
		}

		cout << endl;
	}
}

int main()
{
	//Initial probability matrix
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (maze[row][col] == 0)
			{
				probs[row][col] = (1.0 / 38);
			}
			else
			{
				probs[row][col] = -1;
			}
		}
	}
	printPuzzle(probs);
	cout << endl;

	int s1[4] = { 0, 0, 0, 0 };
	sensing(s1);
	printPuzzle(probs);
	cout << endl;

	//1 = north
	motion(1);
	printPuzzle(probs);
	cout << endl;

	int s2[4] = { 1,0,0,0 };
	sensing(s2);
	printPuzzle(probs);
	cout << endl;

	//1 = north
	motion(1);
	printPuzzle(probs);
	cout << endl;

	int s3[4] = { 0,0,0,0 };
	sensing(s3);
	printPuzzle(probs);
	cout << endl;

	//0 = west
	motion(0);
	printPuzzle(probs);
	cout << endl;

	int s4[4] = { 0,1,0,1 };
	sensing(s4);
	printPuzzle(probs);
	cout << endl;

	//0 = west
	motion(0);
	printPuzzle(probs);
	cout << endl;

	int s5[4] = { 1,0,0,0 };
	sensing(s5);
	printPuzzle(probs);
	cout << endl;

	return 0;
}