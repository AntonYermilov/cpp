#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "expat.h"

#include "phonebook.h"
#include "names.h"

void init_phonebook(phonebook_t* book) {
	book->size = 0;
	book->capacity = 1;
	book->humans = malloc(sizeof(human_t));
}

void init_human(human_t* human, const char* name) {
	size_t len = strlen(name);
	char* name_copy = malloc(sizeof(char) * (len + 1));
	strcpy(name_copy, name);

	strcpy(human->name, strtok(name_copy, " "));
	strcpy(human->middle_name, strtok(NULL, " "));
	strcpy(human->family_name, strtok(NULL, " "));
	human->phones_num = 0;

	free(name_copy);
}

void clear_phonebook(phonebook_t* book) {
	free(book->humans);
}

void start_element(void *data, const char *element, const char **attribute) {
	//printf("start element: %s\n", element);
	if (strcmp(element, "human") == 0) {
		//printf("%s = %s\n", attribute[0], attribute[1]);
		human_t human;
		init_human(&human, attribute[1]);
		push_back_human(data, &human);
	}
}

void end_element(void *data, const char* element) {
	//printf("end element: %s\n", element);
}

void handle_data(void *data, const char *content, int length) {
	if (length > 0 && isdigit(content[0])) {
		char* phone = malloc(sizeof(char) * (length + 1));
		memcpy(phone, content, sizeof(char) * length);		
		phone[length] = '\0';

		//printf("handle data: %s\n", phone);
		add_phone(data, phone);

		free(phone);
	}
}

int compare_humans(const void* ptr1, const void* ptr2) {
	human_t h1 = *(human_t*)(ptr1);
	human_t h2 = *(human_t*)(ptr2);
	return strcmp(h1.family_name, h2.family_name);
}

int load_phonebook_xml(const char* filename, phonebook_t* book) {
	
	FILE* data_in = fopen(filename, "r");
	if (data_in == NULL) {
		printf("Failed to open\n");
		return 1;
	}

	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetElementHandler(parser, start_element, end_element);
	XML_SetCharacterDataHandler(parser, handle_data);
	XML_SetUserData(parser, book);

	size_t buff_size = 1048576;
	char* buff = malloc(buff_size);
	
	int isFinal = 0;

	while (!isFinal) {
		size_t len = fread(buff, sizeof(char), buff_size, data_in);
		isFinal = len < buff_size;
		if (XML_Parse(parser, buff, len, isFinal) == XML_STATUS_ERROR) {
			printf("Failed to parse: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
			XML_ParserFree(parser);
			free(buff);
			fclose(data_in);
			return 2;
		}
	}
	
	XML_ParserFree(parser);
	free(buff);
	fclose(data_in);

	qsort(book->humans, book->size, sizeof(human_t), compare_humans);

	return 0;
}

int save_phonebook_xml(const char* filename, phonebook_t* book) {
	FILE* data_out = fopen(filename, "w");

	fprintf(data_out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(data_out, "<phonebook>\n");
	for (size_t i = 0; i < book->size; i++) {
		human_t* human = &book->humans[i];
		fprintf(data_out, "\t<human name=\"%s %s %s\">\n", human->name, human->middle_name, human->family_name);
		for (size_t j = 0; j < human->phones_num; j++) {
			fprintf(data_out, "\t\t<phone>%s</phone>\n", human->phones[j]);
		}
		fprintf(data_out, "\t</human>\n");
	}
	fprintf(data_out, "</phonebook>\n");

	fclose(data_out);
	return 0;
}

void print_phonebook(phonebook_t* book) {
	printf("%d\n", (int) book->size);
	for (size_t i = 0; i < book->size; i++) {
		human_t* human = &book->humans[i];
		printf("name: %s\n", human->name);
		printf("middle name: %s\n", human->middle_name);
		printf("family name: %s\n", human->family_name);
		for (size_t j = 0; j < human->phones_num; j++)
			printf("phone: %s\n", human->phones[j]);
		printf("\n");
	}
}

human_t gen_human() {
	human_t human;
	
	//strcpy(human.name, kNames[rand() % NAMES_CNT]);
	//strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
	//strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);

	for (int i = 0; i < 255; i++) {
		human.name[i] = (i == 0 ? 'A' : 'a') + rand() % 26;
		human.middle_name[i] = (i == 0 ? 'A' : 'a') + rand() % 26;
		human.family_name[i] = (i == 0 ? 'A' : 'a') + rand() % 26;
	}
	human.name[255] = '\0';
	human.middle_name[255] = '\0';
	human.family_name[255] = '\0';

	//human.phones_num = rand() % 10 + 1;
	human.phones_num = 10;
	for (size_t i = 0; i < human.phones_num; i++) {
		//size_t len = rand() % 20 + 1;
		size_t len = 20;
		for (size_t j = 0; j < len; j++)
			human.phones[i][j] = '0' + rand() % 10;
		human.phones[i][len] = '\0';
	}

	return human;
}

void gen_phonebook(phonebook_t* book, size_t size) {
	while (size--) {
		human_t human = gen_human();
		push_back_human(book, &human);
	}
}

void push_back_human(phonebook_t* book, human_t* human) {
	if (book->size == book->capacity) {
		size_t new_capacity = book->capacity * 2;
		human_t* humans_copy = malloc(sizeof(human_t) * new_capacity);
		memcpy(humans_copy, book->humans, sizeof(human_t) * book->size);
		free(book->humans);
		book->humans = humans_copy;
		book->capacity = new_capacity;
	}
	book->humans[book->size++] = *human;
}

void add_phone(phonebook_t* book, char* phone) {
	human_t* human = &book->humans[book->size - 1];
	strcpy(human->phones[human->phones_num++], phone);
}
