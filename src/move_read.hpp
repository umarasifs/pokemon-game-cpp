
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


namespace moves {
// File and string parsing
std::ifstream file{};
std::string content{};
std::istringstream input{};
std::string current_entry{};

std::string name{};
int type{};
int atk{};
int acc{};
int pp{};
short priority{};
short physical{};

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
  file.open("moves.txt");

  // If the file did not open, indicate an error occurred.
  if (!file.is_open()) {
    std::cerr << "[ERROR]: moves.txt not found" << std::endl;
  }

  // Assign to the string the 'content' the contents of the file
  content = std::string(std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>());

  input.str(content);
}

void close_file() { file.close(); }

// Moves to the next transaction entry.
bool next_trans_entry() {
  std::getline(input, current_entry);
  std::stringstream ss(current_entry);
  ss.precision(2);

  if (!ss.str().empty()) {
    ss >> name >> atk >> acc >> pp >> type >> priority >> physical;
    return true;
  } else {
    return false;
  }
}

// Functions to access the parsed fields.
std::string get_name() { return name; }

int get_atk() { return atk; }

int get_pp() { return pp; }

int get_type() { return type; }

short get_priority() { return priority; }

double get_physical() { return physical; }

int get_accuracy()
{
	return acc;
}
void move_num (int x)
{
	for(int i = 0; i < x ; i ++)

	{
		next_trans_entry();
	}
}

};  // namespace ece150
