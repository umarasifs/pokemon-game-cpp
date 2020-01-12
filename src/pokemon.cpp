#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "trainer.hpp"
#include "dex_read.hpp"
#include "monster.hpp"
#include "move.hpp"
#include <cstdlib>
#include <windows.h>
#include <ctime>


int main();
void set_up_arrays(double x[18][18], std::string y[18]);
Monster* create_pokemon(int);
Trainer* create_trainer();
int rand_lim(int, int);

//choices
int choice(Trainer*, int);
int switch_mon(Trainer*, int);
int choose_move(Trainer*, int);

//battle actions
void switching(Trainer*, int&, int);
void battle(Trainer*, int, int, Trainer*, int, int);
void goes_first(Trainer*&, Monster*&, Move*&, Trainer*&, Monster*&, Move*&);
int calc_damage(Trainer*, Trainer*, Monster*, Monster*, Move*);

bool play_again();

//types
double type[18][18] { };
std::string types[18];


int main() {
	set_up_arrays(type, types);
	bool first_round = true;

	Trainer *player_one = nullptr;

	Trainer *player_two = nullptr;

	int p1_curr;
	;
	int p2_curr;

	bool game = true;
	while (game) {
		if (first_round) {
			delete player_one;
			delete player_two;
			player_one = create_trainer();
			std::cout << *player_one << std::endl;

			std::cout
					<< "=================================================================================="
					<< std::endl;
			std::cout
					<< "=================================================================================="
					<< std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			player_two = create_trainer();
			std::cout << *player_two << std::endl;
			p1_curr = 1;
			p2_curr = 1;
			first_round = false;
		}
		//Player 1 choosing
		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << player_one->get_name() << std::endl;
		std::cout << *(player_one->get_mon(p1_curr)) << std::endl;
		int decision1 = choice(player_one, p1_curr);

		if (decision1 == -1) {
			std::cout << std::endl;
			std::cout << "THANK YOU FOR PLAYING";
			break;
		}
		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		int move1;
		if (decision1 == 2) {
			move1 = switch_mon(player_one, p1_curr);
		}
		if (decision1 == 1) {
			move1 = choose_move(player_one, p1_curr);
		}

		//Player 2 choosing
		std::cout << player_two->get_name() << std::endl;
		std::cout << *(player_two->get_mon(p2_curr)) << std::endl;
		int decision2 = choice(player_two, p2_curr);

		if (decision2 == -1) {
			std::cout << std::endl;
			std::cout << "THANK YOU FOR PLAYING";
			break;
		}
		int move2;
		if (decision2 == 2) {
			move2 = switch_mon(player_two, p2_curr);
		}
		if (decision2 == 1) {
			move2 = choose_move(player_two, p2_curr);
		}

		//Switching P1
		if (decision1 == 2) {
			switching(player_one, p1_curr, move1);
			move1 = -1;
		}

		//Switching P2
		if (decision2 == 2) {
			switching(player_two, p2_curr, move2);
			move2 = -1;
		}

		//Battle

		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout
				<< "=================================================================================="
				<< std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		battle(player_one, p1_curr, move1, player_two, p2_curr, move2);

		if (player_one->get_mon(p1_curr)->is_fainted()) {
			std::cout << player_one->get_mon(p1_curr)->get_name() << " fainted!"
					<< std::endl;
			if (player_one->is_still_in()) {
				p1_curr = switch_mon(player_one, p1_curr);
			} else {
				std::cout << "CONGRATULATIONS " << player_two->get_name()
						<< " HAS WON!!";
				if (!play_again()) {
					game = false;
				} else {
					first_round = true;
				}
			}
		}
		if (game && player_two->get_mon(p2_curr)->is_fainted()) {
			std::cout << player_two->get_mon(p2_curr)->get_name() << " fainted!"
					<< std::endl;
			if (player_two->is_still_in()) {
				p2_curr = switch_mon(player_two, p2_curr);
			} else {
				std::cout << "CONGRATULATIONS " << player_one->get_name()
						<< " HAS WON!!" << std::endl;
				Sleep(1000);
				if (!play_again()) {
					game = false;
				} else {
					first_round = true;
				}
			}
		}
	}

	return 0;
}

int choice(Trainer *curr, int x) {
	char decision1 = 0;

	while (decision1 != 'f' && decision1 != 'F' && decision1 != 'q'
			&& decision1 != 'Q' && decision1 != 's' && decision1 != 'S') {
		std::cout << " press 'f' to fight, 's' to switch, 'q' to quit "
				<< std::endl;
		std::cin >> decision1;
		if (decision1 == 'q' || decision1 == 'Q') {
			std::cout << "WOULD YOU LIKE TO QUIT (Y/N)" << std::endl;
			char yes = 0;
			while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N') {
				std::cin >> yes;
			}
			if (yes == 'n' && yes == 'N') {
				decision1 = 0;
			}
		}
		if (decision1 == 's' && decision1 == 'S') {
			if (!curr->can_switch(x)) {
				decision1 = 0;
				std::cout << "CANNOT SWITCH" << std::endl;
			}
		}
	}

	if (decision1 == 'f' || decision1 == 'F') {
		return 1;
	}
	if (decision1 == 's' || decision1 == 'S') {
		return 2;
	}
	if (decision1 == 'q' || decision1 == 'Q') {
		return -1;
	}
	return 0;
}

int switch_mon(Trainer *curr, int x) {
	std::cout << "CHOOSE A POKEMON TO SWITCH TO" << std::endl;
	int num = 0;
	char q;
	bool done = false;
	std::cout << *curr;
	while (!done) {
		while (num < 1 || num > 6) {
			std::cin >> q;
			num = q - 48;
		}
		done = true;
		if (num == x) {
			std::cout << "This Pokemon is already out" << std::endl;
			num = 0;
			done = false;
		} else if (curr->get_mon(num)->is_fainted()) {
			std::cout << "CANNOT switch to this Pokemon" << std::endl;
			num = 0;
			done = false;
		}
	}
	return num;
}
int choose_move(Trainer *curr, int x) {
	if (curr->get_mon(x)->struggle()) {
		return 0;
	}
	std::cout << "choose a move" << std::endl;
	int move = 0;
	while (!(move > 0 && move < 5)) {
		char input;
		std::cin >> input;
		move = input - 48;
		if (move > 0 && move < 5) {
			if (!curr->get_mon(x)->get_move(move)->is_usable()) {
				move = 0;
				std::cout << "CANNOT choose this move" << std::endl;
			}
		} else {
			move = 0;
		}
	}
	return move;
}

void switching(Trainer *curr, int &out, int to_goto) {
	std::cout << curr->get_name() << " switches their "
			<< curr->get_mon(out)->get_name() << " with their "
			<< curr->get_mon(to_goto)->get_name() << "!" << std::endl;
	Sleep(1000);
	out = to_goto;
}

void battle(Trainer *one, int p1_mon, int p1_move, Trainer *two, int p2_mon,
		int p2_move) {
	bool p1_chose { p1_move != -1 };
	bool p2_chose { p2_move != -1 };
	Trainer *first = one;
	Trainer *second = two;
	Monster *first_mon = one->get_mon(p1_mon);
	Monster *second_mon = two->get_mon(p2_mon);
	if (p1_chose && !p2_chose) {
		Move *first_move = first_mon->get_move(p1_move);
		second_mon->change_hp(
				-calc_damage(first, second, first_mon, second_mon, first_move));
		Sleep(1000);
	}
	if ((!p1_chose && p2_chose)) {
		Move *second_move = second_mon->get_move(p2_move);
		first_mon->change_hp(
				-calc_damage(second, first, second_mon, first_mon,
						second_move));
		Sleep(1000);
	}
	if (p1_chose && p2_chose) {
		Move *first_move = first_mon->get_move(p1_move);
		Move *second_move = second_mon->get_move(p2_move);

		//first pokemon attacks

		goes_first(first, first_mon, first_move, second, second_mon,
				second_move);

		second_mon->change_hp(
				-1
						* calc_damage(first, second, first_mon, second_mon,
								first_move));
		Sleep(1000);

		//check if second is alive
		if (!second_mon->is_fainted()) {
			std::cout
					<< "=================================================================================="
					<< std::endl;
			std::cout
					<< "=================================================================================="
					<< std::endl;
			std::cout << std::endl;
			std::cout << std::endl;

			first_mon->change_hp(
					-1
							* calc_damage(second, first, second_mon, first_mon,
									second_move));
			Sleep(1000);
		}
	}

}

void goes_first(Trainer *&one, Monster *&onem, Move *&onev, Trainer *&two,
		Monster *&twom, Move *&twov) {
	if (*onev < *twov) {
		std::swap(one, two);
		std::swap(onem, twom);
		std::swap(onev, twov);
		return;
	}
	if (*onev == *twov) {
		if (*onem < *twom) {
			std::swap(one, two);
			std::swap(onem, twom);
			std::swap(onev, twov);
			return;
		}
		if (*onem == *twom) {
			int a = rand_lim(0, 10);
			int b = rand_lim(0, 10);
			if (a > b) {
				std::swap(one, two);
				std::swap(onem, twom);
				std::swap(onev, twov);
				return;
			}
		}
	}
}

int calc_damage(Trainer *one, Trainer *two, Monster *onem, Monster *twom,
		Move *onev) {
	std::cout << onem->get_name() << " used " << onev->get_name() << "!"
			<< std::endl;
	onev->change_pp(-1);
	int a = rand_lim(1, 100);

	if (onev->get_accuracy() < a) {
		std::cout << onem->get_name() << " missed! " << std::endl;
		return 0;
	} else {
		double dam { 22 };
		double atk;
		double def;
		//choose atk type
		if (onev->get_physical() == 0) {
			atk = onem->get_atk();
			def = twom->get_def();
		} else {
			atk = onem->get_spatk();
			def = twom->get_spdef();
		}

		//calc base atk
		dam *= (atk / def);
		dam *= onev->get_atk();
		dam /= 50;

		//calc modifier

		double mod = 1;

		//calc stab
		double stab = 1;
		if (onev->get_type() == onem->get_type1()
				|| onev->get_type() == onem->get_type2()) {
			stab = 1.5;
		}

		//calc random
		double rand = rand_lim(85, 100);

		//calc super_effective
		double super_effective = type[onev->get_type() - 1][twom->get_type1()
				- 1];
		if (twom->get_type2() != 0) {
			super_effective *=
					type[onev->get_type() - 1][twom->get_type2() - 1];
		}
		std::cout << std::endl;
		if (super_effective <= 0) {
			std::cout << twom->get_name() << " is not effected by "
					<< onev->get_name() << "!" << std::endl;
		} else if (super_effective > 1) {
			std::cout << "It's super-effective!" << std::endl;
		} else if (super_effective != 1) {
			std::cout << "It's not very effective!" << std::endl;
		}
		//calc crit
		double crit = 1;
		if (rand_lim(1, 10000) <= 625) {
			crit = 1.5;
			std::cout << "It's a Critical hit!" << std::endl;
		}

		mod = super_effective * rand * stab * crit / 100.0;
		dam *= mod;
		return (int) dam;
	}

}

Monster* create_pokemon(int num) {
	dex::open_file();

	dex::line_num(num);
	Move *list[4];
	for (int i = 0; i < 4; i++) {
		list[i] = dex::get_move(i);
	}
	Monster *curr { new Monster(dex::get_name(), dex::get_type1(),
			dex::get_type2(), dex::get_hp(), dex::get_atk(), dex::get_def(),
			dex::get_spa(), dex::get_spd(), dex::get_spe(), list) };
	dex::close_file();
	return curr;

}

void set_up_arrays(double x[18][18], std::string y[18]) {
	std::ifstream file { };
	std::string content { };
	std::istringstream input { };
	std::string current_entry { };

	if (file.is_open()) {
		file.close();
	}

	// Open the file and set the character position to zero
	file.open("types.txt");

	// If the file did not open, indicate an error occurred.
	if (!file.is_open()) {
		std::cerr << "[ERROR]: types.txt not found" << std::endl;
	}

	content = std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());

	input.str(content);
	for (int i = 0; i < 18; i++) {
		std::getline(input, current_entry);
		std::stringstream ss(current_entry);
		ss.precision(2);
		if (!ss.str().empty()) {
			ss >> y[i];
			for (int j = 0; j < 18; j++) {
				ss >> x[i][j];
			}
		}
	}

	file.close();
}

int rand_lim(int begin, int end) {
	std::srand(std::time(0));
	int mod = 1 + end - begin;
	return (std::rand() % mod) + begin;
}

Trainer* create_trainer() {
	std::string name;
	int one, two, three, four, five, six;
	std::cout << "Enter your name:";
	std::cin >> name;
	std::cout << "choose 6 pokemon";
	std::cin >> one >> two >> three >> four >> five >> six;
	Monster *list[6] { create_pokemon(one), create_pokemon(two), create_pokemon(
			three), create_pokemon(four), create_pokemon(five), create_pokemon(
			six) };
	Trainer *curr { new Trainer(name, list) };
	return curr;
}

bool play_again() {
	char answer = 0;
	std::cout << '\n' << "Would you like to play again (y/n)" << std::endl;
	while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
		std::cin >> answer;
	}
	if (answer == 'n' || answer == 'N') {
		return 0;
	}
	std::cout << "Select new teams \n\n\n";
	std::cout << std::endl;
	return 1;
}
