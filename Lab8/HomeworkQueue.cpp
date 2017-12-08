//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <time.h>
#include <limits.h>

using namespace std;
//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions
//
#ifndef MARMOSET_TESTING

enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment
{
	COURSE course; // CHE102, MATH117, etc.
	int assnNum; // Assignment Number
	int dueMonth; // Month due (1-12)
	int dueDay; // Day due (1-31)
	char* description; // Assignment description
};

struct HomeworkQueue
{
	Assignment* assn;
	HomeworkQueue* nextInQueue;
};

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool enqueue(HomeworkQueue*& queue, Assignment& assignment);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//

bool enqueue(HomeworkQueue*& queue, Assignment& assignment) // Adds an assignment reference to the queue, ordered by due date
{
	if (queue == NULL || assignment.dueMonth <= 0 || assignment.dueDay <= 0 ||
	    assignment.dueMonth > 12 || assignment.dueDay > 31 || assignment.course == Null ||
	    assignment.description[0] == '\0') {
		return false;
	}
	if (queue->assn == NULL) { // if the list is empty
		queue->assn = &assignment;
		return true; // or true if successful
	}
	else {
		if ((((assignment.dueMonth - 1) * 30) + assignment.dueDay) < (((queue->assn->dueMonth - 1) * 30) + queue->assn->dueDay)) {
			HomeworkQueue* node = new HomeworkQueue;
			node->assn = queue->assn;
			node->nextInQueue = queue->nextInQueue;
			queue->assn = &assignment;
			queue->nextInQueue = node;
			return true;
		}
		else {
			HomeworkQueue *temp = queue;
			while (((((assignment.dueMonth - 1) * 30) + assignment.dueDay) >= (((queue->assn->dueMonth - 1) * 30) + queue->assn->dueDay)) &&
			       queue->nextInQueue != NULL) {
				queue = queue->nextInQueue;
			}
			HomeworkQueue* insert = new HomeworkQueue;
			insert->nextInQueue = queue->nextInQueue;
			insert->assn = &assignment;
			queue->nextInQueue = insert;
			queue = temp;
			return true;
		}
	}
	return false;
}

const Assignment* dequeue(HomeworkQueue*& queue) {
	if (queue == NULL || queue->assn == NULL) {
		return NULL;
	}
	HomeworkQueue *current = new HomeworkQueue;
	current = queue;
	Assignment* working = new Assignment;
	working->assnNum = current->assn->assnNum;
	working->course = current->assn->course;
	working->dueMonth = current->assn->dueMonth;
	working->dueDay = current->assn->dueDay;
	working->description = current->assn->description;
	queue = queue->nextInQueue;
	delete current;
	return working;
}

int daysTillDue(const HomeworkQueue* q, const COURSE course) {
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	if (q == NULL) {
		return INT_MAX;
	}
	const HomeworkQueue *current = new HomeworkQueue;
	current = q;
	while (current->assn->course != course && current->nextInQueue != NULL) {
		current = current->nextInQueue;
	}
	if (current->assn->course == course) {
		int dueIn = ((current->assn->dueMonth - 1) * 30) + current->assn->dueDay;
		int dayOfYear = ((timeinfo->tm_mon) * 30) + timeinfo->tm_mday;
		return (dueIn - dayOfYear);
	}
	current = NULL;
	delete current;
	return INT_MAX;
}

const Assignment* dueIn(const HomeworkQueue* q, const int numDays) {
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	int dayOfYear = ((timeinfo->tm_mon) * 30) + timeinfo->tm_mday;
	int assnSize = 0;
	const HomeworkQueue *current = new HomeworkQueue;
	current = q;
	while ((((current->assn->dueMonth - 1) * 30) + current->assn->dueDay) < dayOfYear) {
		if (current->nextInQueue != NULL) {
			current = current->nextInQueue;
		}
		else {
			return NULL;
		}
	}
	while ((((current->assn->dueMonth - 1) * 30) + current->assn->dueDay) < (dayOfYear + numDays)) {
		assnSize++;
		if (current->nextInQueue != NULL) {
			current = current->nextInQueue;
		}
		else {
			break;
		}
	}
	Assignment* assnArr = new Assignment[assnSize + 1];
	current = q;
	int c = 0;
	while ((((current->assn->dueMonth - 1) * 30) + current->assn->dueDay) < dayOfYear) {
		current = current->nextInQueue;
	}
	while ((((current->assn->dueMonth - 1) * 30) + current->assn->dueDay) < (dayOfYear + numDays)) {
		Assignment temp = {
			.course = current->assn->course,
			.assnNum = current->assn->assnNum,
			.dueMonth = current->assn->dueMonth,
			.dueDay = current->assn->dueDay,
			.description = current->assn->description
		};
		assnArr[c] = temp;
		if (current->nextInQueue != NULL) {
			current = current->nextInQueue;
			c++;
		}
		else {
			break;
		}
	}
	Assignment end = {
		.course = Null
	};
	assnArr[c + 1] = end;
	return assnArr;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {

	HomeworkQueue* p_queue = new HomeworkQueue;
	HomeworkQueue* n_queue = new HomeworkQueue;

	char one[] = "assn1";
	char two[] = "assn2";
	char three[] = "assn3";
	Assignment assn1 =
	{
		.course = ECE150,
		.assnNum = 0,
		.dueMonth = 12,
		.dueDay = 15,
		.description = one
	};
	Assignment assn2 =
	{
		.course = ECE105,
		.assnNum = 1,
		.dueMonth = 12,
		.dueDay = 16,
		.description = two
	};
	Assignment assn3 =
	{
		.course = ECE190,
		.assnNum = 2,
		.dueMonth = 11,
		.dueDay = 30,
		.description = three
	};
	n_queue->nextInQueue = NULL;
	n_queue->assn = &assn2;
	p_queue->assn = &assn1;
	p_queue->nextInQueue = n_queue;
	bool enqueueSuccess = enqueue(p_queue, assn3);
	if(enqueueSuccess)
	{
		std::cout << "assn3 enqueued successfully" << std::endl << std::endl;
	}
	else
	{
		std::cout << "enqueue() failed" << std::endl << std::endl;
	}

	int due = daysTillDue(p_queue, ECE150);
	const Assignment* assn = dueIn(p_queue, 40);
	const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);

	if (p_firstAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}

	delete p_queue;

	return 0;
}

#endif
