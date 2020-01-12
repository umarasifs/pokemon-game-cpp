#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <iostream>
#include <cmath>
#include "move.hpp"
#include "monster.hpp"

class Trainer
{
public:

	Trainer(std::string name, Monster* list[6]);
	~Trainer();
	bool is_still_in() const;
	std::string get_name() const;
	Monster *get_list() const;
	Monster *get_mon(int num) const;
	friend std::ostream & operator<< ( std::ostream &out, const Trainer &x);
	std::string to_String() const;
	bool can_switch(int num) const;
private:
	std::string name;
	Monster *list[6];
	bool still_in;
};

Trainer::Trainer(std::string name, Monster* list[6])
{
	this->name = name;
	this->still_in = true;
	for(int i = 0; i < 6; i ++)
	{
		this->list[i] = list[i];
	}

}

Trainer::~Trainer()
{
	delete[] list;
	*list = nullptr;
}

std::string Trainer::get_name() const
{
	return this->name;
}

bool Trainer::is_still_in() const
{
	bool yes = false;
	for(int i= 0; i < 6; i ++)
	{
		if(!list[i]->is_fainted())
		{
			yes = true;
		}
	}
	return yes;
}

Monster * Trainer::get_list() const
{
	return *list;
}
std::string Trainer::to_String() const
{
	std::string out = this->name;
	out += ':';
	out += '\n';
	for(int i = 0; i < 6; i++)
	{
		out += '\n';
		out += list[i]->to_String();
	}

	return out;
}

Monster *Trainer::get_mon( int num) const
{
	return list[num - 1];
}

bool Trainer::can_switch(int num) const
{

	for(int i = 0 ; i < num - 1; i++)
	{
		if(!list[i]->is_fainted())
		{
			return true;
		}
	}
	for(int i = num; i < 6; i ++)
	{
		if(!list[i]->is_fainted())
		{
			return true;
		}
	}
	return false;
}

std::ostream & operator<< ( std::ostream &out, const Trainer &x)
{
	out << x.to_String();
	return out;
}
#endif
