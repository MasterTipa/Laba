#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class casino
{
protected:
	string name;
	int bet;
public:
	casino() {}
	casino(string h, int a)
	{
		name = h;
		bet = a;
	}
	virtual ~casino() {};
	virtual void show() = 0;
	virtual int count() = 0;
};


class random :virtual public casino
{
protected:
	int red_or_black;
public:
	random() {}
	random(string h, int a,int b) :casino(h, a) 
	{
		red_or_black = b;
	}
	~random() {};
	void show() override
	{
		cout << "Name : " << name << endl;
		cout << "Bet: " << bet << endl;
		if (red_or_black == 1)
			cout << "red"<<endl;
		else
			cout << "black" << endl;
	}
	int count()override
	{
		int chance;
		chance = 25 * 2;
		return chance;
	}
};

class kartochnie :virtual public casino
{
protected:
	int koll;
public:
	kartochnie() {}
	kartochnie(string h, int a, int k) : casino(h, a)
	{
		koll = k;
	}
	~kartochnie() {};
	void show() override
	{
		cout << "Name : " << name << endl;
		cout << "Bet: " << bet<< endl;
		cout << "Koll kart : " << koll << endl << endl;

	}
	int count()override
	{
		int koll_igr;
		koll_igr = 1*2;
		return koll_igr;
	}
};


class roulette: public random
{
protected:
	int game;
public:
	roulette() {}
	roulette(string h, int a, int b) : random(h, a, b), casino(h, a)
	{
		game = rand() % 2;
	}
	~roulette()
	{
		cout << "complete.";
	}
	void show() override
	{
		cout << "Name : " << name << endl;
		cout << "Bet: " << bet << endl;
				if (red_or_black == 1)
			cout << "red"<<endl;
		else
			cout << "black" << endl;

	}
	int count() override
	{
		if (game == red_or_black)
			return 1*1;
		else return 0*1000;
	}

};


int main()
{
	time(NULL);
	cout << "Array size: ";
	int size;
	while (1)
	{
		cin >> size;
		if (cin.fail())
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	casino** m = new casino * [size];
	for (int i = 0; i < size; i += 3)
	{
		cout << "Name : " << endl;
		string name;
		cin >> name;
		int bet, red_or_black;
		while (1)
		{
			cin >> bet;
			if (cin.fail())
			{
				cout << "Invalid input" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
				break;
		}
		cout << "red or black(1/2)";
		while (1)
		{
			cin >> red_or_black;
			if (cin.fail()&& red_or_black!=1 && red_or_black!=2)
			{
				cout << "Invalid input" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
				break;
		}
		m[i] = new random(name, bet, red_or_black);
		cout << "Chance " << m[i]->count() << "%"<<endl;
		if (i + 1 < size)
		{
			cout << "Puppet Animation : " << endl;
			string name;
			cin >> name;
			int koll_kart;
			while (1)
			{
				cin >> koll_kart;
				if (cin.fail())
				{
					cout << "Invalid input" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else
					break;
			}
			m[i + 1] = new kartochnie(name, bet, koll_kart);
			cout << "Koll igr" << m[i]->count() << endl;
		}
		if (i + 2 < size)
		{
			cout << " roulette: " << endl;
			string name;
			cin >> name;
			int bet, red_or_black;
			cout << "red or black(1/2)";
			while (1)
			{
				cin >> red_or_black;
				if (cin.fail() && red_or_black != 1 && red_or_black != 2)
				{
					cout << "Invalid input" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else
					break;
			}
			cout << "bet";
			while (1)
			{
				cin >> bet;
				if (cin.fail())
				{
					cout << "Invalid input" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else
					break;
			}
			m[i + 2] = new roulette(name, bet, red_or_black);
			cout << "game";
			int a = m[i]->count();
			if (a == 1)
				cout << "WWWWWWWWWiiiiinnnnnnnnn";
			else cout << "lox";
		}
	}
	cout << endl << endl;
	for (int i = 0; i < size; i++)
		m[i]->show();
	return 0;


}





