/*7.	Napisati program koji kreira rang listu studenata za dobivanje stipendije. Rang lista se formira na
temelju prosjeka ocjena studenata i broja bodova koje je student dobio na intervjuu.
Uvjeti za bilo koju ocjenu:
-koristiti funkcije
- provjeriti uspješnost dinamièkih alokacija memorije (i obaviti miran prekid programa u sluèaju neuspješne alokacije)
- provjeriti usoješnost otvaranja datoteka (i obaviti miran prekid programa u sluèaju neuspješnog otvaranja)
- zatvoriti datoteke nakon rada s njima
- na kraju programa oèistiti svu dinamièki alociranu memoriju
- zabranjeno koristiti globalne varijable i funkciju exit()

zadatak:
-iz datoteke grade_list.txt proèitati podatke o prosjeku ocjena studenata (ID studenta, prosjek ocjena).
Èim se proèita jedan redak iz datoteke (ID studenta i prosjek ocjena), potrebno je nasumièno izgenerirati
broj bodova dobivenih na intervjuu (0-10) i izraèunati ukupan broj bodova. Te podatke (ID studenta, prosjek ocjena,
broj bodova s intervjua i ukupni broj bodova) unijeti u jednostruko vezanu listu.
Zatim iz datoteke student_list.txt proèitati podatke studentima (ID studenta, ime, prezime)
i s tim podatcima nadopuniti postojeæu listu.
U konzoli ispisati podatke o studentima (ID, ime, prezime, prosjek ocjena, bodovi s intervjua, ukupni broj bodova)
Napomena:
-ukupni broj bodova se raèuna na sljedeæi naèin:
Ukupni_broj_bodova = 3*prosjek_ocjena + 2* bodovi_s_intervjua
-	Možete korisiti strukturu:
struct _studentGrade;
typedef struct _studentGrade studentGrade;
typedef struct _studentGrade* studentGradePosition;

struct _studentGrade{
int ID;
char firstName [20], lastName [20];
float avgGrade, interviewPoints, totalPoints;
studentGradePosition next;
};
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _studenti;
typedef struct _studenti studenti;
typedef studenti* position;

struct _studenti {

	int id;
	char ime[20];
	char prezime[20];
	float prosocj, bodint, ukupnobod;

	position next;
};

int CitajDatOcjene(position head);
int GenerirajBodove();
int UnesuUListuOcjene(position head, int id, float prosocj, float bodint, float ukupnobod);
int CitajDatStudenti(position head);
int UnesiUListuStudente(position head, int id, char ime[20], char prezime[20]);
int IspisListe(position head);



int main()
{
	srand((unsigned int)(time));

	studenti head;
	head.next = NULL;
	int result;
	result = CitajDatOcjene(&head);
	if (result == -1)
	{
		printf("nisu se ucitale ocjene");
		return -1;
	}

	result = CitajDatStudenti(&head);
	if (result == -1)
	{
		printf("nisu se ucitali studenti");
		return -1;
	}

	result = IspisListe(&head);
	if (result == -1)
	{
		printf("ne ispisuje se");
		return -1;
	}

	return 0;
}

int CitajDatOcjene(position head)
{
	char buffer[1024] = "\0";
	int id = 0;
	float prosocjena, bodoviint, ukupnobod;

	FILE* file;
	file = fopen("ocjene.txt", "r");

	if (file == NULL)
	{
		printf("nije se otvorila");
		return -1;
	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		id = 0;
		prosocjena = 0;

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
		{
			sscanf(buffer, "%d %f.2", &id, &prosocjena);

			bodoviint = GenerirajBodove();

			ukupnobod = 3 * prosocjena + 2 * bodoviint;

		}
		int result = UnesuUListuOcjene(head, id, prosocjena, bodoviint, ukupnobod);
		if (result == -1)
		{
			printf("nije se spremija");
			return -1;
		}
	}

	fclose(file);
	return 0;
}

int GenerirajBodove()
{
	float x;

	x = rand() % 11;

	return x;
}

int UnesuUListuOcjene(position head, int id, float prosocj, float bodint, float ukupnobod)
{
	position temp;
	temp = (position)malloc(sizeof(studenti));
	if (temp == NULL)
	{
		printf("nije se alociralo");
		return -1;
	}

	temp->id = id;
	temp->prosocj = prosocj;
	temp->bodint = bodint;
	temp->ukupnobod = ukupnobod;

	while (head->next != NULL)
	{
		head = head->next;
	}

	temp->next = NULL;
	head->next = temp;

	return 0;
}

int CitajDatStudenti(position head)
{
	char buffer[1024] = "\0";
	char ime[20] = "\0";
	char prezime[20] = "\0";
	int id;

	FILE* file;
	file = fopen("studenti.txt", "r");

	if (file == NULL)
	{
		printf("nije se otvorila studenti datoteka");
		return -1;
	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		strcpy(ime, "\0");
		strcpy(prezime, "\0");
		id = 0;

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
		{
			sscanf(buffer, "%d %s %s", &id, ime, prezime);
			int result = UnesiUListuStudente(head, id, ime, prezime);

			if (result == -1)
			{
				printf("nije se spremilo u listu");
				return -1;
			}
		}
	}

	fclose(file);
	return 0;
}

int UnesiUListuStudente(position head, int id, char ime[20], char prezime[20])
{
	head = head->next;
	while (head != NULL)
	{
		if (head->id == id)
		{
			strcpy(head->ime, ime);
			strcpy(head->prezime, prezime);
		}
		head = head->next;
	}


	return 0;
}


int IspisListe(position head)
{
	head = head->next;
	printf("\nstudenti i njihove ocjene:\n");

	while (head != NULL)
	{
		printf("\n%d %s %s prosocj: %.2f bodint: %.2f\t ukupno: %.2f\n", head->id, head->ime, head->prezime, head->prosocj, head->bodint, head->ukupnobod);
		head = head->next;
	}



	return 0;
}




























































