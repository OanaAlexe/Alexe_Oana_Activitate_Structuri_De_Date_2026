#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct StructuraStudent {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};

typedef struct StructuraStudent Student;
typedef struct Nod Nod;

struct Nod {
	Student info;
	Nod* next;
	Nod* prev;
};


struct Lista {
	Nod* prim;
	Nod* ultim;
	int nrNoduri;
};
typedef struct Lista Lista;

Student citireStudentDinFIisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Student s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.varsta = atoi(aux);
	aux = strtok(NULL, sep);
	s.medie = atof(aux);
	aux = strtok(NULL, sep);
	s.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.facultate = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);
	s.grupa = *strtok(NULL, sep);
	return s;
}

void afisareStudent(Student s) {
	printf("Id: %d\nVarsta: %d\nMedie: %2.f\nNume: %s\nFacultate: %s\nGrupa: %s\n", s.id, s.varsta, s.medie, s.nume, s.facultate, &s.grupa);
}

void afisareListaStudentiInceput(Lista lista) {
	Nod* p = lista.prim; //aici folosim . pentru vrem doar sa accesam campurile din lista
	while (p) {
		afisareStudent(p->info);
		p = p->next;
	}
}

void adaugaStudentInLista(Lista* lista, Student studentNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = studentNou;
	nou->next = NULL;
	nou->prev = lista->ultim;
	if (lista->ultim) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void adaugaLaInceputInLista(Lista* lista, Student studentNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = studentNou;
	nou->prev = NULL;
	nou->next = lista->prim;
	if (lista->prim) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}
	lista->prim = nou;
}

Lista citireLDStudentiDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		adaugaStudentInLista(&lista, citireStudentDinFIisier(f));
	}
	fclose(f);
	return lista;
}

void afisareListaStudentiDeLaFinal(Lista lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareStudent(p->info);
		p = p->prev;
	}
}

int main() {
	Lista lista = citireLDStudentiDinFisier("studenti.txt");
	afisareListaStudentiInceput(lista);
	afisareListaStudentiDeLaFinal(lista);
}