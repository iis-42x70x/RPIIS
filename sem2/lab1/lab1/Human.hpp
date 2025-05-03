struct Human {
	char* FIO;
	int points;
	int place;
};
Human addHum();
void addHash(Human, Human*, int);
void search(Human*, int);
void deleteH(Human*, int);
static Human* createH(int);
bool correctInput();