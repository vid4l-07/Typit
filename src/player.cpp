#include <array>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include "player.h"
#include "words_es.h" // all_words array
#include "words_en.h"

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

	if (consecutive_dels > 0){
		consecutive_dels --;
	}
}

void Player::backspace(){
	if (!player_input.empty() && consecutive_dels < 5){
		index --;
		player_input.pop_back();
		rest_str.insert(rest_str.begin(), org_str[index]);
		consecutive_dels ++;
	}
}

void Player::gen_word(bool first){
	const std::array<std::string_view, 1000>* all_words = nullptr;
	if (len == "es") {
		all_words = &all_words_es;
	}else{
		all_words = &all_words_en;
	} 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, (*all_words).size() - 1);

    int indice_aleatorio = dis(gen);
	std::string word;
	if (first){
		word = (*all_words).at(indice_aleatorio);
	} else{
		word = " " + std::string((*all_words).at(indice_aleatorio));
	}
	rest_str.append(word);
	org_str.append(word);
}

void Player::del_char(){
	player_input.erase(player_input.begin());
}
