#include <random>
#include <string>
#include <vector>
#include "player.h"

void Player::type(char c, bool correct){
	FormatedChar typedchar;
	typedchar.c = c;
	
	if (correct){
		typedchar.format = true;
	} else{
		typedchar.format = false;
		errors ++;
	}

	index ++;
	player_input.push_back(typedchar);
	rest_str.erase(0,1);
}

void Player::backspace(){
	if (index > 0){
		index --;
		player_input.pop_back();
		rest_str.insert(rest_str.begin(), org_str[index]);
	}
}

void Player::gen_word(bool first){
	std::vector<std::string> all_words = {"hola", "adios", "que", "tal", "ayer", "comi", "carne", "con", "pescado"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, all_words.size() - 1);

    int indice_aleatorio = dis(gen);
	std::string word;
	if (first){
		word = all_words[indice_aleatorio];
	} else{
		word = " " + all_words[indice_aleatorio];
	}
	rest_str.append(word);
	org_str.append(word);
}

void Player::del_char(){
	player_input.erase(player_input.begin());
}
