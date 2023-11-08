#include<iostream>
#include<windows.h>
#include<conio.h>
#include<vector>
#include <string>

using namespace std;

class Cell {
	int row;
	int col;
	string value;
public:
	Cell(int row, int col, string val)
	{
		this->row = row;
		this->col = col;
		this->value = val;
	}
	string operator()() const {
		return value;
	}
	friend std::ostream& operator<<(std::ostream& os, const Cell* cell) {
		os << cell->value;
		return os;
	}
};

enum positionCell
{
	righ, lef, up, down
};

template <typename item>
class Node {
public:
	Node<item>* up;
	Node<item>* down;
	Node<item>* left;
	Node<item>* right;
	item data;

	Node(item data)
	{
		up = nullptr;
		down = nullptr;
		left = nullptr;
		right = nullptr;
		this->data = data;
	}
};


template <typename T>
class Excell {
public:
	Node<T>* TopLeft;
	Node<T>* TopRight;
	Node<T>* BottomLeft;
	Node<T>* BottomRight;
	Node<T>* Current;
public:
//Constructor
	Excell(T value)
	{
		TopLeft = nullptr;
		TopRight = nullptr;
		BottomLeft = nullptr;
		BottomRight = nullptr;
		createIntial(5, 6, value);
		Current = TopLeft;
	}
// CreateIntial 5 by 5
	void createIntial(size_t row,size_t col,T value)
	{
		Node<T>* TempUp = nullptr;
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				Node<T>* next = new Node<T>(value);
				if (TopLeft == nullptr || BottomLeft == nullptr)
				{
					next->up = TempUp;
					if(TempUp != nullptr)
						TempUp->down = next;
					next->right = TopLeft;
					if(TopLeft == nullptr)
						TopLeft = next;
					BottomRight = next;
					BottomLeft = next;
					BottomRight = BottomLeft;

				}
				else
				{
					BottomRight->right = next;
					next->left = BottomRight;
					BottomRight = next;
					if (BottomRight->left != nullptr)
						if (BottomRight->left->up != nullptr)
							if (BottomRight->left->up->right != nullptr)
							{
								BottomRight->left->up->right->down = next;
								next->up = BottomRight->left->up->right;
							}

					
				}
			}
			TempUp = BottomLeft;
			BottomLeft = BottomLeft->down;
			BottomRight = BottomLeft;
			
		}

	}
// Add A Row Above
	void addRowAbove(T val)
	{
		Node<T>* temp = Current;
		temp = TillNull(temp,lef);
		if (Current->up == nullptr)
		{
			bool checker = false;
			while (temp != nullptr)
			{
				Node<T>* next = new Node<T>(val);
				if (checker == false)
				{
					next->down = temp;
					TopLeft = next;
					TopRight = next;
					temp->up = next;
					checker = true;
					
				}
				else
				{
				
					next->down = temp;
					temp->up = next;
					TopRight->right = next;
					next->left = TopRight;
					TopRight = next;
				}
				temp = temp->right;
			}
		}
		else
		{
			Node<T>* tempRow = nullptr;
			while (temp != nullptr)
			{
				Node<T>* next = new Node<T>(val);
				if (tempRow == nullptr)
				{
					next->up = temp->up;
					temp->up->down = next;
					temp->up = next;
					next->down = temp;
					tempRow = next;
				}
				else
				{
					next->up = temp->up;
					temp->up->down = next;
					temp->up = next;
					next->down = temp;
					tempRow->right = next;
					next->left = tempRow;
					tempRow = next;


				}
				temp = temp->right;
			}
		}
	}
// Position
	Node<T>* PositionGetter(Node<T>* temp, positionCell x)
	{
		if (x == lef)
			return temp->left;
		if (x == righ)
			return temp->right;
		if (x == up)
			return temp->up;
		if (x == down)
			return temp->down;
	}
// Moe cuurrent till null
	Node<T>* TillNull(Node<T>* temp,positionCell x)
	{
		while (PositionGetter(temp, x) != nullptr)
		{
			temp = PositionGetter(temp, x);
		}
		return temp;
	}
};


//it deal with front end
template <typename T>
class FrontEnd {
public:
	int actRow = 3;
	int actCol = 3;
// it print the whole data in tabular form
    void printGrid(Node<T>* top)
	{
		
		Node<T>* tempRow = top;
		Node<T>* tempCol = top;
		int x = 3;
		int y = 3;
		int col = 0;
		char row = 0;
		system("cls");
		while (tempCol != nullptr)
		{
			while (tempRow != nullptr)
			{
				
				CellPrint(tempRow,x,y);
				tempRow = tempRow->right;
				x += 11;
			}
			
			tempCol = tempCol->down;
			tempRow = tempCol;
			y += 5;
			x = 3;
		}
		y = 3;
		
	}
// it print the cell on screen 
	void CellPrint(Node<T>* temp,int x,int y)
	{
		gotoxy(x,y);
		cout << "\033[36m" << "----------";
		gotoxy(x, y+1);
		cout << "|        |";
		gotoxy(x, y+2);
		cout << "|        |";
		gotoxy(x, y+3);
		cout << "|        |";
		gotoxy(x, y+4);
		cout << "----------";
		gotoxy(x+3, y+2);
		cout << temp->data;
	}
// to point at particular position
	void gotoxy(int x, int y)
	{
		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
	}
	Node<T>* assigner(Node<T>* temp,Node<T>* next)
	{
		if (next != nullptr)
		{
			return next;
		}
		return temp;
	}
	// it print the cell on screen 
	void activeCell(Node<T>* temp, int x, int y)
	{
		gotoxy(x, y);
		cout << "\033[32m" << "##########";
		gotoxy(x, y + 1);
		cout << "#        #";
		gotoxy(x, y + 2);
		cout << "#        #";
		gotoxy(x, y + 3);
		cout << "#        #";
		gotoxy(x, y + 4);
		cout << "##########";
		gotoxy(x + 3, y + 2);
		cout <<"\033[34m" << temp->data;
	}
};

template <typename T>
class FunctionModule {
public:
	Node<string>* PositionSt;
	vector<T> NodesLeft;
	vector<T> NodesUp;
	vector<double> sumV;
	vector<double> subV;
	vector<double> divV;
	vector<double> mulV;
	vector<double> avgV;
	int movementDown = 1;
	int movementRight = 1;
	bool collector = false;
	void movementCounter(Node<string>* Cell)
	{
		if (GetAsyncKeyState(VK_SHIFT) )
		{
			if (collector == false)
			{
				PositionSt = Cell;
			}
			collector = !collector;
			cout << "L";
			Sleep(1000);
		}
	}
	void RightCall()
	{
		if (collector)
		{
			movementRight++;
		}
		
	}
	void LeftCall()
	{
		if (collector)
		{
			movementRight--;
		}
	}
	void UpCall()
	{
		if (collector)
		{
			movementDown--;
		}
	}
	void DownCall()
	{
		if (collector)
		{
			movementDown++;
		}
	}

	void Calculator(Node<string>* Cell,FrontEnd<string> x)
	{
		Node<string>* temp = Cell;
		for (int i = 0; i < movementDown; i++)
		{

			double sum = 0;
			double mul = 1;
			double div = 1;
			double sub = 0;
			double max = -1000;
			double min = 9999;
			for (int j = 0; j < movementRight; j++)
			{
				float tem = stoi(Cell->data);
				sum = sum + tem;
				mul = mul * tem;
				if (j == 0)
				{
					sub = tem;
					div = mul;
				}
				else
				{
					sub = sub - tem;
					div = div / tem;
				}
				if (tem > max)
					max = tem;
				if (min > tem)
					min = tem;
				Cell = Cell->right;
			}
			sumV.push_back(sum);
			divV.push_back(div);
			mulV.push_back(mul);
			subV.push_back(sub);
			avgV.push_back(sum / movementRight);
			x.gotoxy(120, 5 + i);
				cout << i + 1 << ". SUM: " << sum << " DIV: " << div << " MUL: " << mul << " SUB: " << sub << " MAX: " << max <<" MIN: "<<min;
			temp = temp->down;
			Cell = temp;
		}
		movementDown = 1;
		movementRight = 1;
	}
	void Paste(Node<string>* Cell, Node<string>* Current,int sit)
	{
		Node<string>* temp = Cell;
		Node<string>* curr = Current;
		Node<string>* down = Current;
		for (int i = 0; i < movementDown; i++)
		{

			double sum = 0;
			double mul = 1;
			double div = 1;
			double sub = 0;
			for (int j = 0; j < movementRight; j++)
			{
				if (curr == nullptr)
					break;
				if(sit == 1 || sit == 2)
				curr->data = Cell->data;
				if (sit == 2)
					Cell->data = "0";
				curr = curr->right;
				Cell = Cell->right;
				
			}
			sumV.push_back(sum);
			divV.push_back(div);
			mulV.push_back(mul);
			subV.push_back(sub);
			avgV.push_back(sum / movementRight);
			temp = temp->down;
			Cell = temp;
			if (down->down == nullptr)
				break;
			else
			{
				down = down->down;
				curr = down;
			}
		}
		movementDown = 1;
		movementRight = 1;
	}
};

void main()
{
	Excell<string>* link = new Excell<string>("22");
	FrontEnd<string> x;
	FunctionModule<Node<string>> Functions;
	x.printGrid(link->TopLeft); 
	int sit = 0;
	link->Current->data = "3";
	while (true)
	{
		
		
		if (GetAsyncKeyState(VK_UP))
		{
			x.CellPrint(link->Current,x.actCol,x.actRow);
			if (link->PositionGetter(link->Current, up) != nullptr)
			{
				x.activeCell(link->Current, x.actCol, x.actRow -= 5);
				Functions.UpCall();
			}
			else
				x.activeCell(link->Current, x.actCol, x.actRow);
			link->Current = x.assigner(link->Current, link->PositionGetter(link->Current, up));

		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			x.CellPrint(link->Current, x.actCol, x.actRow);
			if (link->PositionGetter(link->Current, righ) != nullptr)
			{
				x.activeCell(link->Current, x.actCol += 11, x.actRow);
				Functions.RightCall();
			}
			else
				x.activeCell(link->Current, x.actCol, x.actRow);
			link->Current = x.assigner(link->Current,link->PositionGetter(link->Current, righ));
		
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			x.CellPrint(link->Current, x.actCol, x.actRow);
			if (link->PositionGetter(link->Current, lef) != nullptr)
			{
				Functions.LeftCall();
				x.activeCell(link->Current, x.actCol -= 11, x.actRow);
			}
			else
				x.activeCell(link->Current, x.actCol, x.actRow);
			link->Current = x.assigner(link->Current,link->PositionGetter(link->Current, lef));
		
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			x.CellPrint(link->Current, x.actCol, x.actRow);
			if (link->PositionGetter(link->Current, down) != nullptr)
			{
				Functions.DownCall();
				x.activeCell(link->Current, x.actCol, x.actRow += 5);
			}
			else
				x.activeCell(link->Current, x.actCol, x.actRow);

			link->Current = x.assigner(link->Current,link->PositionGetter(link->Current, down));
			
		}

		else if (GetAsyncKeyState(VK_CONTROL))
		{
			if (GetAsyncKeyState(0x57))
			{
				
				link->addRowAbove("123");
				x.printGrid(link->TopLeft);
				link->Current = link->TopLeft;
				x.actCol = 3;
				x.actRow = 3;
			}
			if (GetAsyncKeyState(0x42))
			{
				sit = 1;
			}
			if (GetAsyncKeyState(0x58))
			{
				sit = 2;
			}
			if (GetAsyncKeyState(0x56))
			{
				Functions.Paste(Functions.PositionSt, link->Current,sit);
				x.printGrid(link->TopLeft);
				
			}
			
		}
		else if (GetAsyncKeyState(VK_TAB) && Functions.PositionSt != nullptr)
		{
			x.printGrid(link->TopLeft);
			Functions.Calculator(Functions.PositionSt,x);

		}
		Functions.movementCounter(link->Current);
		Sleep(100);
	}
}
