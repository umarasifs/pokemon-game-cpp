#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <iostream>
#include <cmath>
#include <string>
#include "move.hpp"


class Monster {
public:
	Monster(std::string name, int type1, int type2, int max_hp, int atk, int def, int spA, int spD,
			int speed, Move *list[4]);
	~Monster();
	std::string get_name() const;
	int get_type1() const;
	int get_type2() const;
	int get_hp() const;
	int get_atk() const;
	int get_def() const;
	int get_spatk() const;
	int get_spdef() const;
	int get_speed() const;
//	int get_status() const;
	bool is_fainted() const;
	Move *get_move(int number) const;
	void change_hp(int number);
//	void change_status(int number);
//	void change_atk(int number);
//	void change_def(int number);
//	//void change_spatk(int number);
//	void change_spdef(int number);
//	void change_speed(int number);
	std::string to_String() const;
	bool operator < (const Monster &x);
	bool operator==(const Monster &x);
	bool operator > (const Monster &x);
	friend std::ostream & operator<< ( std::ostream &out, const Monster &x);
	bool struggle() const;
	std::string health_bar() const;

private:
	std::string name;
	int type1;
	int type2;
	int hp;
	int max_hp;
	int atk;
	int def;
	int spatk;
	int spdef;
	int speed;
//	int status;
	Move *list[4];
};

Monster::Monster(std::string name, int type1, int type2, int max_hp, int atk, int def, int spatk, int spdef,
		int speed, Move *list[4])
{
	this->name = name;
	this->type1 = type1;
	this->type2 = type2;
	this->max_hp = max_hp;
	this-> hp = max_hp;
	this-> atk = atk;
	this->def = def;
	this->spatk = spatk;
	this->spdef = spdef;
	this->speed = speed;
	for(int i = 0; i < 4; i++)
	{
		this->list[i] = list[i];
	}
//	status = 0;
}
Monster::~Monster()
{
	delete[] list;
	*list = nullptr;
}
std::string Monster::get_name() const
{
	return this-> name;
}
int Monster::get_type1() const
{
	return this-> type1;
}
int Monster::get_type2() const
{
	return this-> type2;
}
int Monster::get_hp() const
{
	return this->hp;
}
int Monster::get_atk() const
{
	return this->atk;
}
int Monster::get_def() const
{
	return this->def;
}
int Monster::get_spatk() const
{
	return this->spatk;
}
int Monster::get_spdef() const
{
	return this->spdef;
}
int Monster::get_speed() const
{
	return this->speed;
}
//int Monster::get_status() const
//{
//	return this-> status;
//}
bool Monster::is_fainted() const
{
	return (hp <= 0);
}
Move* Monster::get_move(int number) const
{
	return list[number-1];
}
void Monster::change_hp(int number)
{
	this->hp += number;
	if(this->hp > this->max_hp)
	{
		this->hp = max_hp;
	}
	if(this-> hp < 0)
	{
		hp = 0;
	}
	std::cout << health_bar();
}

bool Monster::struggle() const
{
	for(int i = 0; i < 4; i ++)
	{
		if(list[i]->is_usable())
		{
			return false;
		}
	}
	return true;
}
std::string Monster::to_String() const
{

	std::string out = health_bar();
	for(int i = 1; i < 5; i ++)
	{
		out += get_move(i)->to_String();
	}
	out += '\n';
	return out;
}

bool Monster:: operator< (const Monster &x)
{
	return (this->speed < x.get_speed());
}
bool Monster::operator==(const Monster &x)
{
	return (this->speed == x.get_speed());
}
bool Monster::operator > (const Monster &x)
{
	return (this->speed > x.get_speed());
}

std::ostream &operator<< ( std::ostream &out, const Monster &x)
{
	out << x.to_String();
	return out;
}

std::string Monster::health_bar() const
{
	std::string out = this->name;
	out+= '\t';
	out += '\t';
	if(name.length() < 8)
	{
		out+= '\t';
	}
	out += std::to_string(hp);
	out += '/' ;
	out += std::to_string(max_hp);
	out += '\t';
	out += '\t';
	out += '|' ;
	for(int i = 1; i <= 10; i ++)
	{
		double check = max_hp / 10.0;
		if(hp >= check*i)
		{
			out += static_cast <int>('\u2588');
		}
		else if (hp <= (check*i-1))
		{
			out += ' ';
		}
	}
	out += '|' ;
	out += '\n';
	return out;
}

//void Monster::change_status(int number)
//{
//	this->status = number;
//}
//void Monster::change_atk(int number)
//{
//	this->atk *= 100;
//	this->atk *= number;
//	this->atk /= 100;
//}
//void Monster::change_def(int number)
//{
//	this->def *= 100;
//	this->def *= number;
//	this->def /= 100;
//}
//void Monster::change_spatk(int number)
//{
//	this->spatk *= 100;
//	this->spatk *= number;
//	this->spatk /= 100;
//}
//void Monster::change_spdef(int number)
//{
//	this->spdef *= 100;
//	this->spdef *= number;
//	this->spdef /= 100;
//}
//void Monster::change_speed(int number)
//{
//	this->speed *= 100;
//	this->speed *= number;
//	this->speed /= 100;
//}


#endif
