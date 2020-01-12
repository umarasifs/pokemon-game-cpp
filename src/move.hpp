#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>
#include <cmath>
#include <string>

class Move
{
public:
	Move(std::string name, int type, int atk, short priority, int accuracy, int pp , short physical);
	std::string get_name() const;
	int get_type() const;
	int get_atk() const;
	short get_priority() const;
	int get_accuracy() const;
	int get_max_pp() const;
	int get_pp() const;
	short get_physical() const;
	std::string to_String() const;
	bool is_usable() const;
	void change_pp(int);

	bool operator < (const Move &x) const;
	bool operator > (const Move &x) const;
	bool operator ==(const Move &x) const;
private:
	int type;
	std::string name;
	int atk;
	short priority;
	int accuracy;
	int max_pp;
	int pp;
	short physical;
};

Move::Move(std::string name, int type, int atk, short priority, int accuracy, int pp, short physical)
{
	this->name = name;
	this->type = type;
	this->atk = atk;
	this->priority = priority;
	this->accuracy = accuracy;
	this->pp = pp;
	this->max_pp = pp;
	this->physical= physical;
}
std::string Move::to_String() const
{
	std::string yes = this->name;
	if(name.length() < 8)
	{
		yes+= '\t';
	}
	yes+= '\t';
	yes+= std::to_string(this->pp);
	yes+= '/';
	yes+= std::to_string(this->max_pp);
	yes+= '\n';
	return yes;
}
std::string Move::get_name() const
{
	return this->name;
}

int Move::get_accuracy() const
{
	return accuracy;
}

int Move::get_atk() const
{
	return atk;
}

int Move::get_max_pp() const
{
	return max_pp;
}

short Move::get_physical() const
{
	return physical;
}

short Move::get_priority() const
{
	return priority;
}

int Move::get_pp() const
{
	return pp;
}

int Move::get_type() const
{
	return type;
}

bool Move::is_usable() const
{
	return(pp != 0);
}
void Move::change_pp(int x)
{
	this->pp+= x;
}
bool Move::operator < (const Move &x) const
{
	return (this->priority < x.get_priority());
}
bool Move::operator > (const Move &x) const
{
	return (this->priority > x.get_priority());
}
bool Move::operator ==(const Move &x) const
{
	return (this->priority == x.get_priority());
}
#endif
