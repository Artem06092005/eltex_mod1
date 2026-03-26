#include <stdio.h>
#include <string.h>

#include "../src/contactList.h"
#include "../unity/unity.h"

void setUp() {}
void tearDown() {}

void test_initContactList(void) {
	ContactList list = {0};
	int size = 10;
	int res = initContactList(&list, size);
	TEST_ASSERT_EQUAL(res, 0);
	TEST_ASSERT_EQUAL(0, list.quantityNotes);
	TEST_ASSERT_EQUAL(size, list.size);
	TEST_ASSERT_NOT_NULL(list.notes);
	res = initContactList(&list, size);
	TEST_ASSERT_EQUAL(res, -2);
	freeContactList(&list);
	resetContactCounter();
}

void test_addContact(void) {
	ContactList list = {0};
	initContactList(&list, 2);
	const char* links1[] = {"fafa", "gdgnd", "usgns"};
	int res = addContact(&list, "name", "fam", "email", 3, links1);

	TEST_ASSERT_EQUAL(res, 0);
	TEST_ASSERT_EQUAL(1, list.quantityNotes);
	TEST_ASSERT_EQUAL(3, list.notes[0].quantityLink);
	TEST_ASSERT_EQUAL_STRING("name", list.notes[0].firstName);
	TEST_ASSERT_EQUAL_STRING("fam", list.notes[0].secondName);
	TEST_ASSERT_EQUAL_STRING("email", list.notes[0].email);
	for (int i = 0; i < list.notes[0].quantityLink; i++) {
		TEST_ASSERT_EQUAL_STRING(links1[i], list.notes[0].socialMediaLink[i]);
	}

	const char* links2[] = {"fafa", "gdgnd", "usgns"};
	res = addContact(&list, "name2", "fam2", NULL, 1, links2);
	TEST_ASSERT_EQUAL(res, 0);
	TEST_ASSERT_EQUAL(2, list.quantityNotes);
	TEST_ASSERT_EQUAL(1, list.notes[1].quantityLink);
	TEST_ASSERT_EQUAL_STRING("name2", list.notes[1].firstName);
	TEST_ASSERT_EQUAL_STRING("fam2", list.notes[1].secondName);
	TEST_ASSERT_EQUAL_STRING("", list.notes[1].email);
	for (int i = 0; i < list.notes[1].quantityLink; i++) {
		TEST_ASSERT_EQUAL_STRING(links2[i], list.notes[1].socialMediaLink[i]);
	}

	freeContactList(&list);
	resetContactCounter();
}

void test_findIndexById(void) {
	ContactList list = {0};
	initContactList(&list, 10);

	addContact(&list, "Ivan", "Ivanov", NULL, 0, NULL);
	addContact(&list, "Petr", "Petrov", NULL, 0, NULL);

	int index = findIndexById(&list, 1);
	TEST_ASSERT_EQUAL_INT(0, index);

	index = findIndexById(&list, 2);
	TEST_ASSERT_EQUAL_INT(1, index);

	index = findIndexById(&list, 999);
	TEST_ASSERT_EQUAL_INT(-1, index);

	freeContactList(&list);
	resetContactCounter();
}

void test_rmNote(void) {
	ContactList list = {0};
	initContactList(&list, 10);

	addContact(&list, "hhw", "agagag", NULL, 0, NULL);
	addContact(&list, "tty", "gaganghmghj", NULL, 0, NULL);
	addContact(&list, "foo", "dhdhnve", NULL, 0, NULL);

	TEST_ASSERT_EQUAL_INT(3, list.quantityNotes);

	int result = rmNote(&list, 2);
	TEST_ASSERT_EQUAL_INT(0, result);
	TEST_ASSERT_EQUAL_INT(2, list.quantityNotes);
	TEST_ASSERT_EQUAL_STRING("hhw", list.notes[0].firstName);
	TEST_ASSERT_EQUAL_STRING("foo", list.notes[1].firstName);

	freeContactList(&list);
	resetContactCounter();
}

void test_editNote(void) {
	ContactList list = {0};
	initContactList(&list, 5);

	const char* links[] = {"user1_link1", "user1_link2"};
	addContact(&list, "User1", "FAm1", "user1@mail.com", 2, links);

	int res = editNote(&list, 1, "Petr", "Petrov", NULL, NULL, NULL);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("Petr", list.notes[0].firstName);
	TEST_ASSERT_EQUAL_STRING("Petrov", list.notes[0].secondName);
	TEST_ASSERT_EQUAL_STRING("user1@mail.com", list.notes[0].email);
	TEST_ASSERT_EQUAL_INT(2, list.notes[0].quantityLink);

	for (int i = 0; i < list.notes[0].quantityLink; i++) {
		TEST_ASSERT_EQUAL_STRING(links[i], list.notes[0].socialMediaLink[i]);
	}

	res = editNote(&list, 1, NULL, NULL, "petr@mail.com", NULL, NULL);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_STRING("Petr", list.notes[0].firstName);
	TEST_ASSERT_EQUAL_STRING("Petrov", list.notes[0].secondName);
	TEST_ASSERT_EQUAL_STRING("petr@mail.com", list.notes[0].email);

	const char* newLinks[] = {"https://t.me/petr"};
	size_t newQuantity = 1;
	res = editNote(&list, 1, NULL, NULL, NULL, &newQuantity, newLinks);
	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(1, list.notes[0].quantityLink);
	TEST_ASSERT_EQUAL_STRING("https://t.me/petr",
							 list.notes[0].socialMediaLink[0]);

	res = editNote(&list, 999, "Test", "Test", NULL, NULL, NULL);
	TEST_ASSERT_EQUAL_INT(-1, res);

	freeContactList(&list);
	resetContactCounter();
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_initContactList);
	RUN_TEST(test_addContact);
	RUN_TEST(test_findIndexById);
	RUN_TEST(test_rmNote);
	RUN_TEST(test_editNote);
	return UNITY_END();
}