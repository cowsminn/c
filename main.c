#include <rlutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define NR_CARACT 40

struct magazin
{
    int nrmag;
    char nume[NR_CARACT];
    int pret;
    char strada[NR_CARACT];
    int sector;
    int nr;
    struct magazin *next;
};

int staremagazin(int deschidere, int inchidere) {
    time_t timpCurent;
    struct tm *localTime;

    time(&timpCurent);
    localTime = localtime(&timpCurent);

    int oraCurenta = localTime->tm_hour;

    if (oraCurenta >= deschidere && oraCurenta < inchidere) {
        printf("Magazinele sunt deschise.\n");
        return 1;
    } else {
        printf("Magazinele sunt inchise.\n");
        return 0;
    }
}

void adaugaremagazin(struct magazin **first) {
  struct magazin *magazinNou;
  magazinNou = (struct magazin*)malloc(sizeof(struct magazin));

  if (magazinNou == NULL) {
    printf("Nu s-a putut aloca memorie.\n");
    return;
  }

  printf("Introduceti numarul de pe lista a magazinului: ");
  scanf("%d", &magazinNou->nrmag);

  printf("Introduceti numele magazinului: ");
  scanf("%39s", magazinNou->nume);

  printf("Introduceti pretul magazinului: ");
  scanf("%d", &magazinNou->pret);

  printf("Introduceti numele strazii magazinului: ");
  scanf("%39s", magazinNou->strada);

  printf("Introduceti numarul sectorului unde se afla magazinul: ");
  scanf("%d", &magazinNou->sector);

  printf("Introduceti numarul magazinului: ");
  scanf("%d", &magazinNou->nr);

  magazinNou->next = NULL;

  if (*first == NULL) {
    *first = magazinNou;
  }
  else {
    struct magazin *magazinCurent;
    magazinCurent = *first;
    while(magazinCurent->next != NULL) {
      magazinCurent = magazinCurent->next;
    }
    magazinCurent->next = magazinNou;
  }

  printf("Magazinul a fost adaugat cu succes.\n");
}

void afisare(struct magazin *first) {
  struct magazin *magazinCurent;
  magazinCurent = first;
  while (magazinCurent != NULL) {
    printf("\nNumar magazin: %d\n", magazinCurent->nrmag);
    printf("Nume: %s\n", magazinCurent->nume);
    printf("Pret per kilogram: %d\n", magazinCurent->pret);
    printf("Strada: %s\n", magazinCurent->strada);
    printf("Sector: %d\n", magazinCurent->sector);
    printf("Numar: %d\n", magazinCurent->nr);
    magazinCurent = magazinCurent->next;
  }
}

void cautare(struct magazin *first) {
  int nr;
  printf("Scrie numarul magazinului de care esti interesat: ");
  scanf("%d", &nr);

  struct magazin *magazinCurent;
  magazinCurent = first;
  while (magazinCurent != NULL) {
    if (magazinCurent->nr == nr)
      break;
    magazinCurent = magazinCurent->next;
  }

  if (magazinCurent == NULL) {
    printf("Din pacate numarul magazinului ales nu apare in lista noastra.\n");
  }
  else {
    printf("Magazinul a fost gasit:\n");
    printf("\nNumar magazin: %d\n", magazinCurent->nrmag);
    printf("Nume: %s\n", magazinCurent->nume);
    printf("Pret per kilogram: %d\n", magazinCurent->pret);
    printf("Strada: %s\n", magazinCurent->strada);
    printf("Sector: %d\n", magazinCurent->sector);
    printf("Numar: %d\n", magazinCurent->nr);
  }
}

void stergere(struct magazin **first) {
  int nr;
  printf("Introduceti numarul magazinului de sters: ");
  scanf("%d", &nr);

  struct magazin *magazinCurent;
  struct magazin *previous;
  magazinCurent = *first;
  previous = NULL;

  while (magazinCurent != NULL) {
    if (magazinCurent->nr == nr)
      break;
    previous = magazinCurent;
    magazinCurent = magazinCurent->next;
  }

  if (magazinCurent == NULL) {
    printf("Din pacate numarul magazinului ales nu apare in lista noastra.\n");
    return;
  }
  if (previous == NULL) {
    *first = magazinCurent->next;
  }
  else {
    previous->next = magazinCurent->next;
  }

  free(magazinCurent);

  printf("Magazinul a fost eliminat din lista noastra cu succes.\n");
}

void salvare(struct magazin *first) {
  FILE *f;
  f = fopen("fis.txt", "w");
  if (f == NULL) {
    fclose(f);
    printf("Fisierul este gol.\n");
    return;
  }

  struct magazin *magazinCurent;
  magazinCurent = first;
  while (magazinCurent != NULL) {
    fprintf(f,"%d %s %d %s %d %d\n", magazinCurent->nrmag, magazinCurent->nume, magazinCurent->pret, magazinCurent->strada, magazinCurent->sector, magazinCurent->nr);
    magazinCurent = magazinCurent->next;
  }

  fclose(f);
  printf("Datele au fost salvate cu succes.\n");
}

void incarcare(struct magazin **first) {
  FILE *f;
  f = fopen("fis.txt","r");
   if (f == NULL) {
    fclose(f);
    printf("Fisierul este gol.\n");
    return;
  }

  struct magazin *magazinCurent;
  magazinCurent = (struct magazin*)malloc(sizeof(struct magazin));
  if (magazinCurent == NULL) {
    printf("Nu s-a putut aloca memorie.\n");
    return;
  }

  while (fscanf(f,"%d %39s %d %39s %d %d\n", &magazinCurent->nrmag, magazinCurent->nume, &magazinCurent->pret, magazinCurent->strada, &magazinCurent->sector, &magazinCurent->nr) == 6) {
    magazinCurent->next = *first;
    *first = magazinCurent;
    magazinCurent = (struct magazin*)malloc(sizeof(struct magazin));
    if (magazinCurent == NULL) {
      printf("Nu s-a putut aloca memorie.\n");
      return;
    }
  }

  free(magazinCurent);
  fclose(f);
  printf("Datele au fost incarcate cu succes.\n");
}
int main()
{
    struct magazin *first=NULL;
    int alegere,deschidere=10,inchidere=19;

  do {
    printf("\n");
    printf("0. Iesire\n");
    printf("1. Adaugare magazin\n");
    printf("2. Afisare magazine\n");
    printf("3. Stare magazine\n");
    printf("4. Cautare magazine\n");
    printf("5. Stergere magazin\n");
    printf("6. Salvare date in fisier\n");
    printf("7. Incarcare date din fisier\n");
    printf("\nAlege numarul din dreptul optiunii dorite: ");
    scanf("%d", &alegere);

    switch(alegere) {
      case 0:
        break;
      case 1:
        adaugaremagazin(&first);
        break;
      case 2:
       afisare(first);
        break;
      case 3:
        staremagazin(deschidere,inchidere);
        break;
      case 4:
        cautare(first);
        break;
      case 5:
        stergere(&first);
        break;
      case 6:
        salvare(first);
        break;
      case 7:
        incarcare(&first);
        break;
      default:
        printf("Alegere incorecta.\n");
    }
  } while (alegere != 0);
cls();
  return 0;
}
