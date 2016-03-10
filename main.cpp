#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>

typedef std::array<std::array<int, 4>, 4 > array4;

void draw(const array4& state) {
	for(int i(0); i < 4; i++) {
		for(int a(0); a < 4; a++) {
			if(state[i][a] == -1)
				std::cout << "|" << " ";
			else
				std::cout << "|" << state[i][a];
		}

		std::cout << "|" << std::endl;
	}
}

bool haveWin(const array4& state) {
	for(int i(0); i < 4; i++) {
		for(int a(0); a < 4; a++) {
			if(state[i][a] == 10)
				return true;
		}	
	}

	return false;
}

int main() {
	std::srand(std::time(0));

	array4 state = { {{-1,-1,-1,-1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}} };
	draw(state);

	bool lose = false;

	while(!haveWin(state))
	{
		//Random move
		int rdm = std::rand()%10 + 1;
		int coincidences = 0, row = -1, column = -1;
		do {
			for(int i(0); i < 4; i++) {
				for(int a(0); a < 4; a++) {
					if(state[i][a] == -1) {
						coincidences++;
						row = i;
						column = a;
						if(coincidences >= rdm)
							break;
					}
				}
				if(coincidences >= rdm)
					break;
			}

			if(row == -1) 
				break;
		} while(coincidences < rdm);

		if(row == -1) {
			lose = true;
			break;
		}

		rdm = std::rand()%1;
		state[row][column] = rdm;

		int m;
		std::cin >> m;

		draw(state);
	}

	if(lose)
		std::cout << "You lose!" << std::endl;
	else
		std::cout << "YOU WIN" << std::endl;

	return 0;
}
