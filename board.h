#pragma once
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
using namespace std;


class board
{
public:
	char** field;
	int field_size;
	int row_to_win;
	bool win;
	bool move;
	



	bool IsEmpty(int i, int j)
	{
		if (field[i][j]==NULL)
		{
			return true;
		}
		else return false;
	}

	void set_field()
	{
		move = true;
		win = false;
		field = new char*[field_size];
		for (int i = 0; i < field_size; i++)
		{
			field[i] = new char[field_size];
		}
		for (int j = 0; j < field_size; j++)
		{
			for (int k = 0; k < field_size; k++)
			{
				field[j][k] = NULL;
				
			}
		}
	}

	bool set_field_size(int size, int row)
	{
		if (row >= 3 && row <= 10)
		{
			row_to_win = row;

		}
		else
		{
			cout << "niedozwolona dlugosc znakow" << endl;
			cout << "wybierz z przedzialu od 3 do 10" << endl;
			return false;
		}
		if (size >= 3 && size <= 10)
		{
			field_size = size;
			set_field();
			return true;
		}
		else
		{
			cout << "niedozwolony rozmiar" << endl << "Dozwolone rozmiary:" << endl << "3, 4, 5, 6, 7, 8, 9, 10" << endl;
			return false;
		}
	}

	void show() //funkcja wyœwietlaj¹ca 
	{
		
		int ind = 1;
		for (int i=0; i < field_size; i++)
		{   
			cout << "|";
			for (int j=0; j < field_size; j++)
			{
				if (IsEmpty(i,j))
				{
					if (ind <= 9)
					{
						cout << " " << ind << "  |";
						ind++;
					}
					else
					{
						cout << " " << ind << " |";
						ind++;
					}
				}
				else
				{
					
					cout << " " << field[i][j]<< "  |";
					ind++;
				}
			}
			cout << endl;
			for (int k = 0; k < field_size; k++)
			{
				cout << "-----";
			}
			cout << endl;
		}
	}

	bool player_choice(int choice) //funkcja przekszta³caj¹ca wybór liczbowy na w³aœciwe pola tablicy
	{
		int a; //wiersz
		int b; //kolumna
		
		a = choice / field_size; //dobór kolumny
		b = (choice % field_size); //dobór wiersza
		if (b == 0) //dopasowanie dla ostatnich komórek ¿eby  poprzednie formu³y dzia³a³y poprawnie
		{
			b = field_size;
			--a;
		}
		
		
		
			if (choice > 0 && choice <= (field_size * field_size))
			{
				

				if (field[a][b - 1] == NULL)
				{
					field[a][b - 1] = 'o';
					return true;
				}
				if (field[a][b - 1] != NULL)
				{
					cout << "pole zajete, sprobuj jeszcze raz" << endl;
					return false;
				}
				
			}
			else
			{
				system("CLS");
				show();
				cout << "zly ruch prosze wybrac z zakresu od 1 do " << field_size * field_size << endl;
				return false;
			}
			    
		
		
		
	}

	void player_move()
	{
		int choice;
		
		while (1)
		{
			
			cin >> choice;
			if(player_choice(choice)==true)
				break;

		}
		
	}

	
	

	int result(char a)
	{
		int row_start, col_start, row, col, D, length = 0;
		char mark;
		
		for (int i = 0; i < field_size; i++) //sprawdzenie poziom
		{
			for (int j = 0; j < field_size; j++)
			{
				
				
				mark = field[i][j];
				
				
				if (mark == a)
				{
					length++;

					if (length == row_to_win)
					{
						if (mark == 'x')
						{
							return 10;
						}
						if (mark == 'o')
						{
							return -10;
						}

					}

					if (j == field_size - 1)
					{

						length = 0;
					}



				}
				else if (mark != a && length != 0)
				{

					length = 0;
				}

				



			}
		}

		for (int i = 0; i < field_size; i++) //sprawdzenie kolumn
		{
			for (int j = 0; j < field_size; j++)
			{


				mark = field[j][i];


				if (mark == a)
				{
					length++;

					if (length == row_to_win)
					{
						if (mark == 'x')
						{
							return 10;
						}
						if (mark == 'o')
						{
							return -10;
						}

					}

					if (j == field_size - 1)
					{

						length = 0;
					}



				}
				else if (mark != a && length != 0)
				{

					length = 0;
				}





			}
		}

		for (D = 0, row_start = field_size - 2, col_start = field_size - 1; D < 2 * field_size - 3; row_start ? row_start-- : col_start--, D++) //sprawdzenie przekatnych od lewej
		{
			for (row = row_start, col = col_start; row < field_size && col >= 0; col--, row++)
			{
				mark = field[row][col];
				if (mark == a)
				{
					length++;
					if (length == row_to_win)
					{
						if (mark == 'x')
						{
							return 10;
						}
						if (mark == 'o')
						{
							return -10;
						}

						
						
					}

					if (row == field_size - 1 || col == 0)
					{

						length = 0;
					}
				}
				else if (mark != a && length != 0)
				{

					length = 0;
				}
			}
		}

		for (D = 0, row_start = field_size - 2, col_start = 0; D < 2 * field_size - 3; row_start ? row_start-- : col_start++, D++)//sprawdzenie przekatnych w prawo
		{
			for (row = row_start, col = col_start; row < field_size && col < field_size; col++, row++)
			{
				mark = field[row][col];
				if (mark == a)
				{
					length++;
					if (length == row_to_win)
					{
						if (mark == 'x')
						{
							return 10;
						}
						if (mark == 'o')
						{
							return -10;
						}

						
						
					}

					if (row == field_size - 1 || col == field_size - 1)
					{

						length = 0;
					}
				}

				else if (mark != a && length != 0)
				{

					length = 0;
				}
			}
		}

		return 0;

	}

	
	

	

	bool left_moves()
	{
		for (int i = 0; i < field_size; i++)
		
			for (int j = 0; j < field_size; j++)
			
				if (IsEmpty(i,j))
					return true;
		return false;
			
		

	}

	

	int evaluate()
	{
		
		if (result('x') == 10)
			return 10;
		if (result('o') == -10)
			return -10;
		if (left_moves() == false)
			return 0;
				
			
			
		
		
		
	}

	void check_win()
	{
		if (evaluate() == 10)
		{
			cout << "wygrana x" << endl;
			win = true;
		}
			
		if (evaluate() == -10)
		{
			cout << "wygrana o" << endl;
			win = true;
		}
		else if (!left_moves())
		{
			cout << "remis" << endl;
			win = true;
		}
	}

	

	int alphabetaminimax(int depth, bool isMax,int alpha,int beta)
	{
		int score = evaluate();
		int max_depth;
		if (row_to_win == 3)
		{
			max_depth = 2 * field_size;
		}
		else
		{
			max_depth = 2 * field_size - row_to_win;
		}
		
		
		if (score == 10)
			return 10;
		if (score == -10)
			return -10;
		
		if (left_moves() == false)
			return 0;
		
		if (depth >= max_depth)
			return 1;
		
		if (isMax)
		{
			int best = INT_MIN;
			for (int i = 0; i < field_size; i++)
			{
				for (int j = 0; j < field_size; j++)
				{
					if (IsEmpty(i,j))
					{
						field[i][j] = 'x';
						int val = alphabetaminimax(depth + 1, false,alpha,beta);
						
						field[i][j] = NULL;
						best = max(best, val);
						alpha = max(alpha, best);
						
						if (beta <= alpha)
							break;
					}
				}
			}
			
			return best;

		}
		else
		{
			int minval = INT_MAX;

			for (int i = 0; i < field_size; i++)
			{
				for (int j = 0; j < field_size; j++)
				{
					if (IsEmpty(i,j))
					{
						field[i][j] = 'o';
						int val = alphabetaminimax(depth + 1, true, alpha, beta);
						
						field[i][j] = NULL;
						minval = min(minval, val);
						alpha = min(beta, minval);
						
						if (beta <= alpha)
							break;
					}
				}
			}
			return minval;
		}

	}

	void MoveAI()
	{
		int row=-1;
		int col=-1;
		int bestval = INT_MIN;
		int moveVal;
		
		for (int i = 0; i < field_size; i++)
		{
			for (int j = 0; j < field_size; j++)
			{
				if (IsEmpty(i,j))
				{
					
					field[i][j] = 'x';
					moveVal = alphabetaminimax( 0, false,INT_MIN,INT_MAX);
					
					field[i][j] = NULL;
					if (moveVal > bestval)
					{
						bestval = moveVal;
						row = i;
						col = j;
						
					}
				}

			}
		}

		if(IsEmpty(row,col))
		field[row][col] = 'x';

	}

	void play()
	{
		int size;
		int row;
		cout << "Kolko i krzyzyk" << endl;
		cout << "Podaj rozmiar :" << endl;
		cin >> size;
		cout << "Podaj dlugosc lini znakow do wygranej(musi byc mniejsza lub rowna rozmiarowi" << endl;
		cin >> row;
		if (!set_field_size(size, row))
			cout << "nie udalo sie zaladowac gry sprobuj jeszcze raz" << endl;

		while (!win)
		{

			if (!win)
			{
				system("CLS");
				cout << "Kolej ruchu X" << endl;
				show();
				MoveAI();
				system("CLS");
				cout << "Kolej ruchu X" << endl;
				show();
				check_win();
			}
			if (!win)
			{
				system("CLS");
				cout << "Kolej ruchu O" << endl;
				show();
				player_move();
				system("CLS");
				cout << "Kolej ruchu O" << endl;
				show();
				check_win();
			}

			

		}
	}
	

};

