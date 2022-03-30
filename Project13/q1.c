#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 255
#define ERROR_STR "Allocation Error\n"
#define YEAR_LEN 6


typedef struct {
	unsigned long id;
	char* name;
	unsigned long salary;
	union {
		char hebrewYear[YEAR_LEN];
		unsigned long englishYear;
	}Year;
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

Worker* CreateWorker(const int data);//סריקת עובד
void PrintWorker(const Worker* w, const int data);//הדפסת עובד
char* getStrExactName(const char* msg);//פונקצית עזר לסריקה
char* getDynStr(char* str);//פונקצית עזר יוצרת מקום בזכרון ומעתיקה מחרוזת אליה
char* myGets(char* buffer, int size);//פונקצית עזר סריקה והחלפת באסקלש אן(ירידת שורה) בבאקסלש אפס
WorkerList* addWorker(WorkerList* head, Worker* w);//הוספת עובד לרשימה
WorkerList* createNode(Worker* data, WorkerList* next);//הוספת צומת ברשימה המקושרת
int index(WorkerList* head, long unsigned id);//מיקום תעודת זהות לפי שכר לולאה
int indexRec(WorkerList* head, long unsigned id);//מיקום תעודת זהות לפי שכר רקורסיה
WorkerList* deleteWorstWorker(WorkerList* head);//מחיקת העובד בעל השכר הנמוך
void freeWorker(Worker* w);//שחרור זכרון שם העובד פוקצית עזר
void freeNode(WorkerList* node);// שחרור זכרון צומת פונקצית עזר
void update_worker(WorkerList* head, float percent);//העלאה בשכר
void freeWorkers(WorkerList* head);//שחרור זכרון
void PrintList(const WorkerList* w, const int data);// הדפסת נתונים לאחר מחיקה פוקצית עזר
WorkerList* reverse(WorkerList* head);//כתיבת הרשימה לאחור






int main() {
	printf("please enter data of the worker:\n");
	Worker* w0 = CreateWorker(1);
	printf("\n");
	PrintWorker(w0, 1);
	getchar();
	Worker* w1 = CreateWorker(0);
	printf("\n");
	PrintWorker(w1, 0);
	getchar();
	Worker* w2 = CreateWorker(0);
	printf("\n");
	PrintWorker(w2, 0);
	getchar();
	Worker* w3 = CreateWorker(0);
	printf("\n");
	PrintWorker(w3, 0);
	WorkerList* list = addWorker(NULL, w0);//בניית הרשימה המקושרת
	list = addWorker(list, w1);
	list = addWorker(list, w2);
	list = addWorker(list, w3);
	printf("Location of the ID card by salary\n");
	int i = index(list, 0000);
	printf("id 0000 found in index %d\n", i);
	i = indexRec(list, 2222);
	printf("id 2222 found in index %d\n", i);
	printf("List without the lowest paid employee\n");
	list = deleteWorstWorker(list);
	PrintList(list, 0);
	printf("Raising salary\n");
	update_worker(list, 10);
	PrintList(list, 0);
	printf("Reverse list\n");
	list = reverse(list);
	PrintList(list, 0);
	freeWorkers(list);
	

	

	
	
	return 0;

}



Worker* CreateWorker(const int data) {
	Worker* w = (Worker*)malloc(sizeof(Worker) * 1);
	if (!w) {
		puts(ERROR_STR);
		return NULL;

	}
	printf("please enter id\n");
	scanf("%lu", &w->id);
	getchar();
	char* name = getStrExactName("please enter name");
	if (!name) {
		puts(ERROR_STR);
		free(w);
		return NULL;
	}
	w->name = name;
	printf("please enter a salary \n");
	scanf("%lu", &w->salary);
	if (data == 1) {
		printf("please enter hebrewyear\n");
		getchar();
		fgets(w->Year.hebrewYear, YEAR_LEN, stdin);
	}
	else
	{
		printf("please enter englishyear\n");
		scanf("%lu", &w->Year.englishYear);
	}
	return w;



}

void PrintWorker(const Worker* w, const int data) {
	printf("data of worker\n");
	printf("id:%lu\n", w->id);
	printf("name:%s\n", w->name);
	printf("salary:%lu\n", w->salary);
	if (data == 1) {
		printf("hebrew year: %s\n", w->Year.hebrewYear);
	}
	else
	{
		printf("english year: %lu\n", w->Year.englishYear);
	}
	printf("\n");


}




char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s:\n", msg);
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

WorkerList* addWorker(WorkerList* head, Worker* w) {
	if (head == NULL) {
		return createNode(w, NULL);
	}
	if (w->salary < head->data->salary) {
		return createNode(w, head);
	}
	WorkerList* pre = head;
	WorkerList* cur = pre->next;
	while (cur != NULL) {
		if (w->salary < cur->data->salary) {
			pre->next = createNode(w, cur);
			return head;
		}
		pre = pre->next;
		cur = cur->next;
	}
	pre->next = createNode(w, NULL);
	return head;
}

WorkerList* createNode(Worker* data, WorkerList* next) {  //פונקצית עזר בנית איבר ברשימה המקושרת
	WorkerList* node = (WorkerList*)malloc(sizeof(WorkerList) * 1);
	if (!node) {
		puts(ERROR_STR);
		return NULL;
	}
	node->data = data;
	node->next = next;
	return node;
}

int index(WorkerList* head, long unsigned id){ //לולאה
	if (head == NULL) {
		return -1;
	}
	int counter = 1;
	for (WorkerList* temp = head; temp != NULL; temp = temp->next, counter++) {
		if (temp->data->id == id) {
			return counter;
		}
	}
	return -1;
}

int indexRec(WorkerList* head, long unsigned id) {//רקורסיבית
	if (head == NULL) {
		return -1;
	}
	if (head->data->id == id) {
		return 1;
	}
	int counter = indexRec(head->next, id);
	return (counter == -1) ? -1 : 1 + counter;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	if (head->next != NULL){
		if (head->next->data->salary < head->data->salary) {
			head = reverse(head);
			WorkerList* temp = head->next;
			freeNode(head);
			free(head);
			temp = reverse(temp);
			return temp;

		}
	}
	WorkerList* temp = head->next;
	freeNode(head);
	free(head);
	return temp;

}

void freeWorker(Worker* w) {//פונקצית עזר משחררת זכרון של שם העובד
	free(w->name);
}

void freeNode(WorkerList* node) {//פונקצית עזר משחררת זיכרון של העובד 
	freeWorker(node->data);
	free(node->data);
}

void update_worker(WorkerList* head, float percent) {
	WorkerList* temp = head;
	while (temp != NULL) {
		temp->data->salary += (unsigned long) ((percent / 100) * temp->data->salary);
		temp=temp->next;
	}
}

WorkerList* reverse(WorkerList* head)
{
	WorkerList* pre, * next, * cur;
	pre = next = NULL;
	cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	head = pre;
	return head;
}

void freeWorkers(WorkerList* head) {
	WorkerList* temp = head;
	while(temp!=NULL){
		WorkerList* next = temp->next;
		freeNode(temp);
		free(temp);
		temp = next;
	}
	


}

void PrintList(const WorkerList* w, const int data) {
	WorkerList* temp = w;
	while (temp!= NULL) {
		PrintWorker(temp->data, data);
		temp = temp->next;
	}

}








