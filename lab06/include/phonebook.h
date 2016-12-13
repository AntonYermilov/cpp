#pragma once

#include "stddef.h"

typedef struct human_s {
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
	size_t phones_num;
} human_t;

typedef struct phonebook_s {
    human_t* humans;
    size_t size;
    size_t capacity;
} phonebook_t;

void init_phonebook(phonebook_t* book);
void init_human(human_t* human, const char* name);
void clear_phonebook(phonebook_t* book);

int load_phonebook_xml(const char* filename, phonebook_t* book);
int save_phonebook_xml(const char* filename, phonebook_t* book);
void print_phonebook(phonebook_t* book);
human_t gen_human();
void gen_phonebook(phonebook_t* book, size_t size);

void push_back_human(phonebook_t* book, human_t* human);
void add_phone(phonebook_t* book, char* phone); //adds phone to the last human in book
