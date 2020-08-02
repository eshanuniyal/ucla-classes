#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cctype>
#include <cstring> // defines strlen, strcpy, strcat, strcmp
#include <cassert>
using namespace std;

const int MAX_MESSAGE_LENGTH = 81; // max message length is 81 characters (including potential newline character at the end)
const int MAX_N_MESSAGES = 60; // 60 maximum newlines
const int N_ALPHABET = 26; // number of letters in the alphabet
const int a_ENCODING = 'a'; // encoding of 'a' in whichever encoding scheme is used


// declaring helper functions
void move_to_back(char a[], int n, int pos);
int detect_match(const char a[], int n, char target);
void extracting_messages(const char ciphertext[], char messages[][MAX_MESSAGE_LENGTH + 1], int& n_messages);
void simplify_text(char simple_crib[]);
bool crib_search(const char crib[], const char message[], char substitutions[]);

bool decrypt(const char ciphertext[], const char crib[]);

int main() {

	const char crib_1[33] = "hush-hush until January 20, 2021";

	const char cipher_1[27] = "Vlgmgak zfefyfektkyy.\nIfk!";
	const char cipher_2[73] = "DiebjiggK, zyxZYXzyx--Abca abCa    bdefg## $$hidbijk6437 wvuWVUwvu\n\n8 9\n";
	const char crib_2[48] = "   hush???hUSh---     --- until    JanuARY !!  ";

	assert(decrypt(cipher_1, crib_1) == false);
	assert(decrypt(cipher_2, crib_2) == true);

	const char cipher_3[184] = "Zysqjs zbguncyqzo jdsbyo eybmnu bg Wqzsvbbf.\nUnysqx eybmgxrsuu ymtbyu kcq Jicjjsy.\nNbuj sajysts rcvsyqr qgx sajysts zbgusykqjcks nbucjcbgu bg xcuzmuucbg wbymtu.\nZU 31 cu zdqrrsGECGE!";
	const char crib_3[19] = "conspiracy THEORY";
	assert(decrypt(cipher_3, crib_3) == true);
	
	const char cipher_4[45] = "abcd efg hijk ilm nppq rst dccb cba uwwx wyz";
	const char crib_4[9] = "good one";
	assert(decrypt(cipher_4, crib_4) == true);
	
	const char cipher_5[40] = "Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n";
	const char crib_5[10] = "my secret";
	assert(decrypt(cipher_5, crib_5) == true);
	
	const char crib_6[7] = "shadow";
	assert(decrypt(cipher_5, crib_6) == false);

	const char cipher_6[6] = "28\n39";
	assert(decrypt(cipher_6, crib_6) == false);

	const char cipher_7[1] = "";
	assert(decrypt(cipher_7, crib_6) == false);

	const char cipher_8[30] = "Kpio't dmpbl-boe-ebhhfs opwfm";
	const char crib_7[12] = "s cloak and";

	assert(decrypt(cipher_8, crib_7) == true);

	const char crib_8[1] = "";
	assert(decrypt(cipher_8, crib_8) == false);

	const char crib_9[8] = "273\n823";
	assert(decrypt(cipher_8, crib_9) == false);

	const char cipher_9[5] = "y es";
	assert(decrypt(cipher_9, crib_7) == false);
}

bool decrypt(const char ciphertext[], const char crib[]) {
	// ------------------------------------------------------
	// simplifying crib and testing the length of the crib
	char simple_crib[MAX_MESSAGE_LENGTH + 1]; // array to store simplified version of crib
	strcpy(simple_crib, crib); // copying crib into simple_crib

	simplify_text(simple_crib); // simplifying simple_crib
	cerr << "Simple crib: " << simple_crib << endl;

	// crib is too long to possibly match any of the messages
	if (strlen(simple_crib) > MAX_MESSAGE_LENGTH)
		return false;

	// ------------------------------------------------------
	// extracting messages from ciphertext, finding n_messages
	char messages[MAX_N_MESSAGES][MAX_MESSAGE_LENGTH + 1];
	// initialising array to store all message C-Strings; number of characters per message can be MAX_MESSAGE_LENGTH + 1 
	// (to account for zero byte character)
	int n_messages = 0; // initialising integer to keep track of number of messages

	// populating messages
	extracting_messages(ciphertext, messages, n_messages);

	char substitutions[N_ALPHABET  + 1]; // array to store substitutions
	for (int i = 0; i < N_ALPHABET; i++)
		substitutions[i] = ' ';
	substitutions[N_ALPHABET] = '\0';

	// ------------------------------------------------------
	// searching for crib matches in each message 
	bool match_found = false; // boolean to store whether a match was found

	for (int i = 0; i < n_messages; i++)
		if (crib_search(simple_crib, messages[i], substitutions)) {
			match_found = true; // updating match_found
			break; // breaking out of loop when first match is found
		}
	// ------------------------------------------------------
	// examining match_found

	// match not found
	if (!match_found)
		return false;

	// match was found
	else {

		int cipher_length = static_cast<int>(strlen(ciphertext));

		for (int i = 0; i < cipher_length; i++) {

			char cipher_char = ciphertext[i]; // character we're currently looking at

			// m_char is not a letter
			if (!isalpha(cipher_char))
				cout << cipher_char;

			// m_char is a letter
			else {

				// integer stores -1 if there's no conversion, and the encoding of cipher_char relative to a_ENCODING if there is one
				int sub_exists = detect_match(substitutions, N_ALPHABET + 1, tolower(cipher_char));

				// no conversion found
				if (sub_exists == -1)
					cout << static_cast<char>(tolower(cipher_char));
				// conversion exists
				else
					// printing converted character
					cout << static_cast<char>(toupper(a_ENCODING + sub_exists));
			}
		}
		cerr << endl << "-------------" << endl;
		// returning true
		return true;
	}
}

void extracting_messages(const char ciphertext[], char messages[][MAX_MESSAGE_LENGTH + 1], int& n_messages) {
	
	// initialising integer to store the current index we're looking at in the ciphertext array
	int cipher_index = 0;

	while (ciphertext[cipher_index] != '\0') {

		char message[MAX_MESSAGE_LENGTH + 1]; // variable to store the current message

		int m_index = 0; // variable to store the index of characters in the current message

		int total_index; // index to keep track of message characters in ciphertext

		// loop runs until we reach '\n' or '\0' in ciphertext
		for (total_index = cipher_index + m_index; ciphertext[total_index] != '\n' && ciphertext[total_index] != '\0'; total_index++) {
			message[m_index] = ciphertext[total_index]; // adding character to message
			m_index++; // updating m_index
		}

		// appending newline character if message ends with one
		if (ciphertext[total_index] == '\n') {
			message[m_index] = '\n';
			m_index++; // incrementing m_index
			total_index++; // incrementing total index
		}

		message[m_index] = '\0'; // appending zero byte character to end C String
		strcpy(messages[n_messages], message); // copying message into messages array
		n_messages++; // incrementing n_messages
		cipher_index = total_index; // updating cipher_index
	}
}

bool crib_search(const char crib[], const char message[], char substitutions[]) {

	// --------------------------------------------------------
	// Simplifying message, checking for letter characters in message, comparing lengths of message and crib

	int m_length = static_cast<int>(strlen(message)); // length of unsimplified message
	bool letters = false; // represents whether there are any letters in message

	// looping through message to check for letters
	for (int i = 0; i < m_length; i++)
		if (isalpha(message[i])) {
			letters = true;
			break;
		}

	// no letters found, returning false
	if (letters == false) {
		cerr << "No letters found" << endl;
		return false;
	}

	char simple_message[MAX_MESSAGE_LENGTH + 1]; // array to store simplified message
	strcpy(simple_message, message); // copying message into simple_message
	simplify_text(simple_message); // simplifying text in simple_message
	cerr << "Simple message: " << simple_message << endl;

	m_length = static_cast<int>(strlen(simple_message)); // updating m_length to represent length of simple_message
	int crib_length = static_cast<int>(strlen(crib)); // number of characters in crib

	// crib longer than message --> returning false
	if (crib_length > m_length) {
		cerr << "Crib longer than message" << endl;
		return false;
	}

	// --------------------------------------------------------
	// Searching for crib in message

	int start_index = 0; // index at which we start comparing message and crib

	// main loop
	while (true) {

		// resetting subs
		for (int i = 0; i < N_ALPHABET; i++)
			substitutions[i] = ' ';

		int m_index = start_index; // current index we're looking at in message
		int crib_index = 0; // current index we're looking at in crib

		bool match_found = true; // bool to store whether a match was found with current start_index

		while (true) {

			char m_char = simple_message[m_index]; // current message character
			char crib_char = crib[crib_index]; // current crib character

			// if both are letters
			if (isalpha(crib_char) && isalpha(m_char)) {

				int char_index = crib_char - a_ENCODING; // corresponding index of crib_char in substitutions

				// known substitution does not exist
				if (substitutions[char_index] == ' ') {

					// checking if substitution has already been assigned to another character
					bool sub_used = false; // boolean returns true if substitution has already been assigned

					// running through subs
					for (int i = 0; i != N_ALPHABET; i++)
						if (substitutions[i] == m_char) {
							sub_used = true; // updating sub_used
							break;
						}
					// substitution has already been assigned, updating match_found and breaking
					if (sub_used) {
						match_found = false;
						break;
					}
					// assigning substitution to m_char
					else
						substitutions[char_index] = m_char;
				}
				// already encountered this character; there exists a known substitution
				else {
					// if known substitution does not match m_char, match_found = false
					if (substitutions[char_index] != m_char) {
						match_found = false;
						break;
					}
				}
			}
			// if not both are spaces
			else if (!(crib_char == ' ' && m_char == ' ')) {
				match_found = false;
				break;
			}

			// incrementing respective indices
			crib_index++;
			m_index++;

			// crib ran out
			if (crib[crib_index] == '\0') {
			
				// current word in simple_message hasn't run out
				if (isalpha(simple_message[m_index]))
					match_found = false;
				break;
			}
			// crib hasn't run out, but simple_message has
			else if (simple_message[m_index] == '\0') {
				match_found = false;
				break;
			}
		}

		// if match found, updating substitutions and returning true
		if (match_found == true) {
			cerr << "Match found!" << endl;

			cerr << "Letters:       ";
			for (int i = 0; i != N_ALPHABET; i++)
				cerr << static_cast<char>(a_ENCODING + i) << " ";
			cerr << endl;

			cerr << "Substitutions: ";
			for (int i = 0; i != N_ALPHABET; i++)
				cerr << substitutions[i] << " ";
			cerr << endl;

			return true;

		}
		// match not found
		else {
			bool next_word = false; // boolean to store whether there exists a next word
			// running through simple_message
			for (int i = start_index + 1; i < m_length; i++)
				// next word exists
				if (simple_message[i] == ' ') {
					start_index = i + 1; // updating start_index
					next_word = true; // updating next_word
					break;
				}

			// no next word found and no match found yet; returning false
			if (!next_word)
				return false;
		}
	}
}

void simplify_text(char text[]) {

	int text_length = static_cast<int>(strlen(text));

	// going through text
	for (int i = 0; i < text_length; i++)
		// if not a letter, replace with space
		if (!isalpha(text[i]))
			text[i] = ' ';
		// if a letter, replace with lowercase version
		else
			text[i] = tolower(text[i]);

	// removing extra spaces
	char space = ' '; // space character

	// running through list
	for (int i = 0; i < strlen(text); i++)
		// if character equals space
		if (text[i] == space)
			// while next character is space character
			while (text[i + 1] == space) {
				// move next character to back
				move_to_back(text, text_length + 1, i + 1);
				text_length--;
			}

	// removing first space, if any
	if (text[0] == space) {
		move_to_back(text, text_length + 1, 0);
		text_length--;
	}

	// removing last space, if any
	if (text[text_length - 1] == space) {
		move_to_back(text, text_length + 1, text_length - 1);
		text_length--;
	}
}

int detect_match(const char a[], int n, char target) {
	if (n < 0) // negative n
		return -1;

	// running through array
	for (int i = 0; i != n; i++)
		if (a[i] == target)
			return i; // returning smallest position where target is found

	return -1; // no target found
}

void move_to_back(char a[], int n, int pos) {

	// storing the string to be eliminated
	char eliminated = a[pos];

	// moving all items after pos to the left
	for (int i = pos + 1; i < n; i++)
		a[i - 1] = a[i];

	// adding eliminated string to the end
	a[n - 1] = eliminated;
}