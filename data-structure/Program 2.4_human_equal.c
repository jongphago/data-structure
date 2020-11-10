#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
typedef struct {
	int month;
	int day;
	int year;
}date;

typedef struct {
	char name[10];
	int age;
	float salary;
	date dob;
}human_being;

int human_equal(human_being person1, human_being person2) {
	if (strcmp(person1.name, person2.name))
		return FALSE;
	if (person1.age != person2.age)
		return FALSE;
	if (person1.salary != person2.salary)
		return FALSE;
	if (person1.dob.month != person2.dob.month &&\
		person1.dob.day != person2.dob.day&&\
		person1.dob.year != person2.dob.year)
		return FALSE;
	return TRUE;
}

void main(void) {
	human_being person1, person2;
	person1.age = 22;
	strcpy(person1.name, "jonghyun");
	person1.salary = 220;
	person1.dob.day = 7;
	person1.dob.month = 3;
	person1.dob.year = 1992;

	person2.age = 27;
	strcpy(person2.name, "jihyun");
	person2.salary = 300;
	person2.dob.day = 20;
	person2.dob.month = 2;
	person2.dob.year = 1995;

	if (human_equal(person1, person2))
		printf("The two human beings are the same");
	else 
		printf("The two human beings are not the same");
}