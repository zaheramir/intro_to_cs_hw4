#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TWO 2


int get_gender(char* noun);
int get_indefinite_article(char* noun);
int get_length_indefinite_article(char* noun);
void add_indefinite_article(char* noun,	char* noun_with_article);
void handle_indefinite_article(int max_length);

bool starts_with_shorakat(char* noun);
bool starts_with_vowel(char* noun);
void equal_strings(char* noun, char* noun_with_article, int j);

int main() {
	int max_length, num_of_nouns;
	scanf("%d %d", &max_length, &num_of_nouns);
	for (int i = 0; i < num_of_nouns; i++) {
		handle_indefinite_article(max_length);
	}
	return 0;
}





//this function checks the last char of a string and by it return weather the 
//gender is male (1) or female (TWO)
int get_gender(char* noun)
{
	char cur = noun[0]; //save the current char untill the last
	for (int i = 1; i!=-1; i++)
	{
		if (noun[i] != '\0')
			cur = noun[i];
		else
			i = -TWO; //stop for
	}
	if (cur == 'o')
		return 1;
	else if (cur == 'a')
		return TWO;
	return 0;
}
//the function returns the right indefinite article according to the requirements
int get_indefinite_article(char* noun)
{
	int gender = get_gender(noun);

	if (gender == 1 && !starts_with_shorakat(noun))
		return 1;
	else if (gender == 1 && starts_with_shorakat(noun))
		return TWO;
	else if (gender == TWO && !starts_with_vowel(noun))
		return (TWO+1);
	else if (gender == TWO && starts_with_vowel(noun))
		return (TWO+TWO);

	return 0;
}
int get_length_indefinite_article(char* noun)
{
	int length = strlen(noun);
	int ind_art = get_indefinite_article(noun);
	if (ind_art == 1 || ind_art == (TWO+TWO))
		length += TWO;
	if (ind_art == TWO || ind_art == (TWO+1))
		length += (TWO+1);
	length += 1; // for the space or the " ' "

	return length;
}
void add_indefinite_article(char* noun, char* noun_with_article)
{
	if (get_indefinite_article(noun) == 1)
	{
		char ind[] = "un ";
		strcat(noun_with_article, ind);
		equal_strings(noun, noun_with_article, (TWO+1));
	}
	else if (get_indefinite_article(noun) == TWO)
	{
		char ind[] = "uno ";
		strcat(noun_with_article, ind);
		equal_strings(noun, noun_with_article, (TWO+TWO));
	}
	else if (get_indefinite_article(noun) == (TWO+1))
	{
		char ind[] = "una ";
		strcat(noun_with_article, ind);
		equal_strings(noun, noun_with_article, (TWO+TWO));
	}
	else if (get_indefinite_article(noun) == (TWO+TWO))
	{
		char ind[] = "un'";
		strcat(noun_with_article,ind);
		equal_strings(noun, noun_with_article, (TWO+1));
	}
}
void handle_indefinite_article(int max_length)
{
	char* noun;
	char* full_noun;
	noun = (char*)malloc((max_length+1) * sizeof(char));
	scanf("%s", noun);
	int length = get_length_indefinite_article(noun) + 1;
	full_noun = (char*)malloc(length * sizeof(char));
	for (int i = 0; i < length; i++)
		full_noun[i] = '\0';
	add_indefinite_article(noun, full_noun);
	printf("%s\n", full_noun);
	free(noun);
	free(full_noun);
}
//the function checks if the noun starts with shorakat letter
bool starts_with_shorakat(char* noun)
{
	if (noun[0] == 'z' || noun[0] == 'x' || noun[0] == 'y' || (noun[0] == 'g' && noun[1] == 'n') || (noun[0] == 'p' && noun[1] == 's'))
		return true;
	else if (noun[0] == 's' && (noun[1] == 'a' || noun[1] == 'e' || noun[1] == 'i' || noun[1] == 'o' || noun[1] == 'u'))
		return true;
	else if (noun[0] == 'i' && (noun[1] != 'a' || noun[1] != 'e' || noun[1] != 'i' || noun[1] != 'o' || noun[1] != 'u'))
		return true;
	return false;
}
//this function checks if the noun starts with vowel
bool starts_with_vowel(char* noun)
{
	if (noun[0] == 'a' || noun[0] == 'e' || noun[0] == 'i' || noun[0] == 'o' || noun[0] == 'u' || noun[0] == 'h')
		return true;

	return false;
}

void equal_strings(char* noun, char* noun_with_article, int j)
{
	for (int i = 0; i!= (TWO) - (TWO+1); i++)
	{
		if (noun[i] != '\0')
		{
			noun_with_article[j] = noun[i];
			j++;
		}
		else
			i=-TWO;
		
	}
}
