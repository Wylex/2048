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

bool move(int& fixed, int& moving)
{
	if(fixed == moving && fixed != -1) {
		fixed++;
		moving = -1;
		return true;
	}
	else if(fixed == -1 && moving != -1) {
		fixed = moving;
		moving = -1;
		return true;
	}
	else
		return false;
}

int main() {
	std::srand(std::time(0));

	array4 state = { {{-1,-1,-1,-1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}} };
	state[std::rand()%4][std::rand()%4] = std::rand()%2;
	

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

		rdm = std::rand()%2;
		state[row][column] = rdm;

		draw(state);
		std::cout << std::endl;

		bool moved = false;
		char shifting;
		do {
			std::cin >> shifting;

			switch(shifting) {
				case 'a':
					//Remove espaces
					for(int i(0); i < 4; i++) {
						for(int a(1); a < 4; a++) {
							if(state[i][a] != -1 and state[i][a-1] == -1) {
								moved = true;
								state[i][a-1] = state[i][a];
								state[i][a] = -1;
								if(a>=2)
									a-=2;
							}	
						}
					}

					//Merge numbers
					for(int i(0); i < 4; i++) {
						for(int a(1); a < 4; a++) {
							if(move(state[i][a-1], state[i][a]))
								moved = true;
						}
					}
					std::cout << "<--" << std::endl;
					break;
				case 's':
					//Remove espaces
					for(int i(2); i >= 0; i--) {
						for(int a(0); a < 4; a++) {
							if(state[i][a] != -1 and state[i+1][a] == -1) {
								moved = true;
								state[i+1][a] = state[i][a];
								state[i][a] = -1;
								if(i<=1)
									i+=2;
								break;
							}	
						}
					}

					//Merge numbers
					for(int i(2); i >= 0; i--) {
						for(int a(0); a < 4; a++) {
							if(move(state[i+1][a], state[i][a]))
								moved = true;
						}
					}
					std::cout << " |" << std::endl;
					std::cout << " v" << std::endl;
					break;
				case 'w':
					//Remove espaces
					for(int i(1); i < 4; i++) {
						for(int a(0); a < 4; a++) {
							if(state[i][a] != -1 and state[i-1][a] == -1) {
								moved = true;
								state[i-1][a] = state[i][a];
								state[i][a] = -1;
								if(i>=2)
									i-=2;
								break;
							}	
						}
					}

					//Merge numbers
					for(int i(1); i < 4; i++) {
						for(int a(0); a < 4; a++) {
							if(move(state[i-1][a], state[i][a]))
								moved = true;
						}
					}
					std::cout << " ^" << std::endl;
					std::cout << " |" << std::endl;
					break;
				case 'd':
					//Remove espaces
					for(int i(0); i < 4; i++) {
						for(int a(2); a >= 0; a--) {
							if(state[i][a] != -1 and state[i][a+1] == -1) {
								moved = true;
								state[i][a+1] = state[i][a];
								state[i][a] = -1;
								if(a<=1)
									a+=2;
							}	
						}
					}

					//Merge numbers
					for(int i(0); i < 4; i++) {
						for(int a(2); a >= 0; a--) {
							if(move(state[i][a+1], state[i][a]))
								moved = true;
						}
					}
					std::cout << "-->" << std::endl;
					break;
			}
		} while(moved == false);

		for(int i(0); i < 50; i++)
			std::cout << std::endl;
	}

	if(lose)
		std::cout << "You lose!" << std::endl;
	else
		std::cout << "YOU WIN" << std::endl;

	return 0;
}
