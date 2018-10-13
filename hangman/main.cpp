#include <iostream>//for "cin" and "cout"
#include <fstream>//to open the word list file
#include <cstdlib>//for random
#include <vector>//to make the very long word list
#include <ctime>//to seed random

using namespace std;//so I don't have to type "std::"

void fill_word_list(vector<string>& word_list);
string word_with_blanks(const string &word, const string &guessed_letters);//takes a string and replaces the unknown letters with '_'
void print_lives_remaining(const int &lives);
bool letter_in_string(const char &letter, const string &s);//checks to see if a specific character is in a string
bool all_letters_guessed(const string &word, const string &guessed_letters);//sees if all letters in a word were guessed
void print_end_message(const bool &win, const string &word);//tells player if they won or lost
void again(bool& play);//asks player if they want to play again

int main() {
	
	vector<string> word_list;//list of words with indefinite size
	
	srand(time(0));//seeding random
	
	fill_word_list(word_list);
	
	bool play = true;//allows player to start
	
	while (play) {
		
		string word;
		
		word = word_list[rand() % word_list.size()];//picks random word from list
		
		int lives(16);//sets number of lives
		string guessed_letters;//list of guessed letters with indefinate size
		bool win(false);//player has not won yet
		
		for(int life(lives); life; --life){//start with n lives and n decrements
			
			cout <<word_with_blanks(word, guessed_letters) <<endl;//prints the word with the unguessed letters as '_'
			print_lives_remaining(life);
			
			string guess;
			cin >>guess;//takes in guess
			
			if (guess.length() > 1){//if player guesses a word
				if (guess == word){
					win = true;//player wins
					break;//out of for loop
				}
			}
			
			else{//if player guesses a letter
				
				if(letter_in_string(guess[0], guessed_letters))//if letter was already guessed
					cout <<"You already guessed that letter.\n";
				
				else if (letter_in_string(guess[0], word))//elif letter is in the word
					guessed_letters += guess;//add new letter to list of guessed letters
				
				if (all_letters_guessed(word, guessed_letters)){
					win = true;//player wins
					break;//out of for loop
				}
			}
		}
		
		print_end_message(win, word);//tells player if they win or lose
		
		again(play);//do you want to play again?
	}
	
	return 0;
}

void fill_word_list(vector<string>& word_list){
	
	ifstream in_file;
	in_file.open("/Users/Kn3rd/Desktop/hangman/hangman/american-words_95.txt");//makes conection between the file and variable "word_list"
	
	string word;
	
	while (in_file >> word)
		if (!letter_in_string('\'', word))//makes sure word does not have apostrophe
			word_list.push_back(word);//Until the words run out, adds each word from the list to the end of the list
	
	in_file.close();//closes file
}

string word_with_blanks(const string &word, const string &guessed_letters){//this was made a string so I could use this to see if all the letters were guessed. This allowed me to call upon this function instead of coding a lot of the same things into "all_letters_guessed"
	
	string ans;//string that will be printed out
	
	for (auto e : word){
		bool letter_guessed(false);//letter is not guessed yet
		for (auto &f : guessed_letters){
			if (e == f){
				letter_guessed = true;//sees if letter has been guessed
				break;
			}
		}
		(letter_guessed) ? (ans += e) : (ans += '_');
	}
	return ans;//makes output a string
}

void print_lives_remaining(const int &lives){
	string num_lives;
	(lives > 1) ? (num_lives = (to_string(lives) + " lives")) : (num_lives = "1 life");

	cout << "You have " << num_lives << " remaining" << endl;
}

bool letter_in_string(const char &letter, const string &s){
	for (auto &e : s) if (e == letter) return true;
	return false;
}

bool all_letters_guessed(const string &word, const string &guessed_letters){return (word ==  word_with_blanks(word, guessed_letters));}//sees if the word with only the guessed letters is the same as the word

void print_end_message(const bool &win, const string &word){
	string end;
	(win) ? (end = "win") : (end = "lose");
	
	cout <<"You " << end << endl << "The word was " << word << endl;
}

void again(bool& play){//the variable "play" is tied to this function
	
	cout << "Play again? (y/n)" << endl;
	
	char yn;
	cin >> yn;
	
	if (yn != 'y') play = false;
}
