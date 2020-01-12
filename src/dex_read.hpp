#include "move_read.hpp"
#include "move.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


namespace dex {
// File and string parsing
std::ifstream file{};
std::string content{};
std::istringstream input{};
std::string current_entry{};

std::string name{};
int type1{};
int type2{};
int hp{};
int atk{};
int def{};
int spa{};
int spd{};
int spe{};
Move *list[4];


////////////////////
// File functions //
////////////////////

// Open the file for reading
void open_file() {
  // If the file is already open, close it
  //  - this is just in case the file changed since the last opening
  if (file.is_open()) {
    file.close();
  }

  // Open the file and set the character position to zero
  file.open("pokedex.txt");

  // If the file did not open, indicate an error occurred.
  if (!file.is_open()) {
    std::cerr << "[ERROR]: pokedex.txt not found" << std::endl;
  }

  // Assign to the string the 'content' the contents of the file
  content = std::string(std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>());

  input.str(content);
}

void close_file() { file.close(); }


// Moves to the next transaction entry.
bool line(bool a) {
	std::getline(input, current_entry);
	std::stringstream ss(current_entry);
	ss.precision(2);
if(a)
{
  if (!ss.str().empty()) {
	  int temp1{};
	  int temp2{};
	  int temp3{};
	  int temp4{};
    ss >> name >> type1 >> type2>> hp >> atk >> def >> spa >> spd >> spe >> temp1 >> temp2 >> temp3 >> temp4;

    moves::open_file();
    moves::move_num(temp1);
    *(list) = new Move(moves::get_name(), moves::get_type(),moves::get_atk(), moves::get_priority(),
    							moves::get_accuracy(), moves::get_pp(), moves::get_physical());
    moves::close_file();


    moves::open_file();
	moves::move_num(temp2);
	*(list+1) = new Move(moves::get_name(), moves::get_type(),moves::get_atk(), moves::get_priority(),
								moves::get_accuracy(), moves::get_pp(), moves::get_physical());
	moves::close_file();


	moves::open_file();
	moves::move_num(temp3);
	*(list+2) = new Move(moves::get_name(), moves::get_type(),moves::get_atk(), moves::get_priority(),
								moves::get_accuracy(), moves::get_pp(), moves::get_physical());
	moves::close_file();


	moves::open_file();
	moves::move_num(temp4);
	*(list+3) = new Move(moves::get_name(), moves::get_type(),moves::get_atk(), moves::get_priority(),
								moves::get_accuracy(), moves::get_pp(), moves::get_physical());
	moves::close_file();
    return true;
  } else {
    return false;
  }
}
}

void line_num ( int num)
{
	for(int i = 0; i < num; i ++)
	{
		line(i == (num - 1));
	}
}
// Functions to access the parsed fields.
std::string get_name() { return name; }

int get_hp() { return hp; }
int get_type1(){return type1;}

int get_type2() { return type2; }

int get_atk() { return atk; }

int get_def() { return def; }

int get_spa() { return spa; }

int get_spd() { return spd; }

int get_spe() { return spe; }

Move* get_move(int num)
{
	return list[num];
}
Move* get_list()
{
	std::cout << list[0]->to_String();
	std::cout << list[1]->to_String();
	std::cout << list[2]->to_String();
	std::cout << list[3]->to_String();
	return *list;
}

};  // namespace ece150
