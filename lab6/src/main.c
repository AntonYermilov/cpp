#include "stdlib.h"
#include "stddef.h"
#include "assert.h"

#include "phonebook.h"

void phonebook_in(char* infile) {
	phonebook_t book;
	init_phonebook(&book);
	assert(load_phonebook_xml(infile, &book) == 0);
	print_phonebook(&book);
	clear_phonebook(&book);
}

void phonebook_out(char* outfile, size_t MAX_SIZE) {
	phonebook_t book;
	init_phonebook(&book);
	size_t size = rand() % MAX_SIZE + 1;
	gen_phonebook(&book, size);
	assert(save_phonebook_xml(outfile, &book) == 0);
	clear_phonebook(&book);
}

int main(int argc, char* argv[]) {
	
	assert(argc >= 3);
	phonebook_in(argv[1]);
	phonebook_out(argv[2], 100);

	//phonebook_in("pbook.xml");
	//phonebook_out("pbook_out.xml", 25);
	//phonebook_in("pbook_out.xml");

	return 0;
}
