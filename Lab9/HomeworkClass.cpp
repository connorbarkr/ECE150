//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <time.h>
#include <limits.h>
using namespace std;
//////////////////////////////////////////////////////////////
//
// #includes for local testing only
//


#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// Enums and structs for use in assignment

#ifndef MARMOSET_TESTING
enum COURSE
{
	CHE102,
	MATH115,
	MATH117,
	ECE105,
	ECE150,
	ECE190,
	Null
};

struct Assignment
{
	COURSE course;
	int assnNum;         // Assignment number
	int dueMonth;        // 1-12
	int dueDay;          // 1-31
	char*  description;  // Assignment description
};

#endif

struct node
{
	Assignment *data;
	node *next;
};

//////////////////////////////////////////////////////////////
//
// Class declaration; modify but do not remove

class HomeworkQueue {
public:
bool                enqueue(Assignment& assignment);
const Assignment*   dequeue();
int                 daysTillDue(COURSE course);
const Assignment*   dueIn(int numDays);

HomeworkQueue();
~HomeworkQueue();                       //destructor
private:
node *head, *tail;
};


//////////////////////////////////////////////////////////////
//
// Your code here ...
//

bool HomeworkQueue::enqueue(Assignment& assignment)
{
	if (head == NULL && tail == NULL) {
		node *working = new node;
		working->data = &assignment;
		working->next = NULL;
		head = working;
		tail = working;
		return true;
	}
	else if (head->data == NULL) {
		head->data = &assignment;
		return true;
	}
	else if (head != NULL) {
		if (((head->data->dueDay + ((head->data->dueMonth - 1) * 30)) > (assignment.dueDay + ((assignment.dueMonth - 1) * 30)))) {
			node *first = new node;
			first->data = &assignment;
			first->next = head;
			head = first;
			return true;
		}
		node *temp = head;
		while (((head->data->dueDay + ((head->data->dueMonth - 1) * 30)) <= (assignment.dueDay + ((assignment.dueMonth - 1) * 30))) &&
		       head->next != NULL) {
			head = head->next;
		}
		node *insert = new node;
		insert->data = &assignment;
		insert->next = head->next;
		head->next = insert;
		head = temp;
		return true;
	}
	return false;
}

const Assignment* HomeworkQueue::dequeue()
{
	if (head == NULL || head->data == NULL) {
		return NULL;
	}
	Assignment *dequeued = new Assignment;
	dequeued->course = head->data->course;
	dequeued->assnNum = head->data->assnNum;
	dequeued->dueDay = head->data->dueDay;
	dequeued->dueMonth = head->data->dueMonth;
	dequeued->description = head->data->description;
	node *temp = new node;
	temp = head;
	head = head->next;
	delete temp;
	return dequeued;
}

int HomeworkQueue::daysTillDue(COURSE course)
{
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	if (head == NULL || head->data == NULL) {
		return INT_MAX;
	}
	node *temp = head; // store the head info to get back to it later
	while (head->data->course != course && head->next != NULL) {
		head = head->next;
	}
	if (head->data->course == course) {
		int dueIn = ((head->data->dueMonth - 1) * 30) + head->data->dueDay;
		int dayOfYear = ((timeinfo->tm_mon) * 30) + timeinfo->tm_mday;
		head = temp;
		return (dueIn - dayOfYear);
	}
	head = temp;
	return INT_MAX;
}

const Assignment* HomeworkQueue::dueIn(int numDays)
{
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	int dayOfYear = ((timeinfo->tm_mon) * 30) + timeinfo->tm_mday;
	int assnSize = 0;
	node *temp = head;
	while ((((head->data->dueMonth - 1) * 30) + head->data->dueDay) < dayOfYear) {
		if (head->next != NULL) {
			head = head->next;
		}
		else {
			return NULL;
		}
	}
	while ((((head->data->dueMonth - 1) * 30) + head->data->dueDay) < (dayOfYear + numDays)) {
		assnSize++;
		if (head->next != NULL) {
			head = head->next;
		}
		else {
			break;
		}
	}
	Assignment* assnArr = new Assignment[assnSize + 1];
	head = temp;
	int c = 0;
	while ((((head->data->dueMonth - 1) * 30) + head->data->dueDay) < dayOfYear) {
		if (head->next != NULL) {
			head = head->next;
		}
		else {
			return NULL;
		}
	}
	while ((((head->data->dueMonth - 1) * 30) + head->data->dueDay) < (dayOfYear + numDays)) {
		Assignment temp = {
			.course = head->data->course,
			.assnNum = head->data->assnNum,
			.dueMonth = head->data->dueMonth,
			.dueDay = head->data->dueDay,
			.description = head->data->description
		};
		assnArr[c] = temp;
		if (head->next != NULL) {
			head = head->next;
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

HomeworkQueue::HomeworkQueue()
{
	head = NULL;
	tail = NULL;
}

HomeworkQueue::~HomeworkQueue()
{
	//Please clean up
}





#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[])
{
	//formatting
	std::cout << std::endl;

	HomeworkQueue hwq;

	char boring[] = "Something something solubility something something gases something";

	Assignment someAssignment =
	{
		.course = CHE102,
		.assnNum = 1000000,
		.dueMonth = 12,
		.dueDay = 4,
		.description = boring
	};

	Assignment someOtherAssignment =
	{
		.course = ECE105,
		.assnNum = 1000000,
		.dueMonth = 12,
		.dueDay = 12,
		.description = boring
	};

	if(!hwq.enqueue(someAssignment))
	{
		std::cout << "enqueue() unsuccessful" << std::endl;
	}
	else
	{
		std::cout << "enqueue() successful" << std::endl;
	}

	if(!hwq.enqueue(someOtherAssignment))
	{
		std::cout << "enqueue() unsuccessful" << std::endl;
	}
	else
	{
		std::cout << "enqueue() successful" << std::endl;
	}

	const Assignment* assn = hwq.dueIn(40);
	cout << assn[0].description << endl;

	const Assignment* assnInTheQueue = hwq.dequeue();

	if (!assnInTheQueue)
	{
		std::cout << "dequeue() unsuccessful" << std::endl;

	}
	else
	{
		std::cout << "dequeue() successful" << std::endl;
		cout << assnInTheQueue->course << endl;
	}

	const Assignment* assnInTheQueue1 = hwq.dequeue();

	if (!assnInTheQueue1)
	{
		std::cout << "dequeue() unsuccessful" << std::endl;

	}
	else
	{
		std::cout << "dequeue() successful" << std::endl;
		cout << assnInTheQueue1->course << endl;
	}

	//formatting
	std::cout << std::endl;

	return 0;
}
#endif
