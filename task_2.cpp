#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>


class Human
{
private:
	int _age;
	bool _live = false;
	int _id;

public:

	Human(int id, int age) {
		_id = id;
		_live = true;
		_age = age;
	}

	bool is_alive() {
		return _live;
	}

	int get_age() {
		return _age;
	}

	void set_live(bool alive) {
		_live = alive;
	}

	int get_id() {
		return _id;
	}

	void die()
	{
		_live = false;
	}


};

class BankCell
{
private:
	std::vector<std::shared_ptr<Human>> _owners;
	float _debet = 0;
	bool _is_open = false;

public:
	BankCell(std::shared_ptr<Human> opener)
	{
		if ((*opener).is_alive()) {
			_owners.push_back(opener);
		}
		_is_open = true;
	}

	bool check_cell() {
		for (int i = 0; i < _owners.size(); i++) {
			if ((*_owners[i]).is_alive()) {
				return true;
			}
		}
		_is_open = false;
		std::cout << "Cell is close" << std::endl;
	}

	void add_owner(std::shared_ptr<Human> owner)
	{
		if (not _is_open) {
			std::cout << "Cell has closed" << std::endl;
		}
		if ((*owner).is_alive()) {
			_owners.push_back(owner);
		};
	}

	void add_money(float money) {
		_debet += money;
		std::cout << _debet << std::endl;
	}

	void get_money(float money) {

		if (not _is_open) {
			std::cout << "Cell has closed" << std::endl;
		}

		if (_debet < money) {
			std::cout << "not enougth money in your debet" << std::endl;
		}
		else {
			//transfer
			_debet -= money;
			std::cout << _debet << std::endl;
		}

	}
};


int main()
{
	auto human1 = std::make_shared<Human> (1, 20);
	auto human2 = std::make_shared<Human> (2, 30);
	BankCell cell(human1);
	if (cell.check_cell()) {
		cell.add_owner(human2);
	}

	(* human1).die();

	if (cell.check_cell()) {
		cell.add_money(1000);
	}

	(*human2).die();

	if (cell.check_cell()) {
		cell.add_money(1000);
	}

	return 0;
}


