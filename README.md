# Library System in C

## Descrizione
Questo progetto implementa un **sistema di gestione di una biblioteca** scritto in linguaggio C. Permette di gestire utenti e libri, inclusi prestiti, restituzioni e archiviazione dei dati su file CSV. Il progetto è modulare, con una chiara separazione tra logica degli utenti, dei libri e delle utilità generali.

---

## Struttura del progetto

```
library-system/
│
├─ include/           # Header files (.h)
│  ├─ models.h        # Definizione delle struct User e Book
│  ├─ books.h         # Dichiarazioni funzioni libri
│  ├─ users.h         # Dichiarazioni funzioni utenti
│  └─ utils.h         # Funzioni di utilità generiche
│
├─ src/               # Implementazioni dei moduli (.c)
│  ├─ books.c
│  ├─ users.c
│  └─ utils.c
│
├─ data/              # File CSV per persistenza dati
│  ├─ books.csv
│  └─ users.csv
│
├─ CMakeLists.txt     # Configurazione build
└─ main.c             # Programma principale
```

---

## Funzionalità principali

### Gestione libri (`books.c`)
- Aggiunta di un nuovo libro
- Rimozione di un libro
- Modifica di titolo, autore e copie disponibili
- Ricerca libro per codice
- Salvataggio e caricamento dei libri su file CSV

### Gestione utenti (`users.c`)
- Aggiunta e rimozione utenti
- Modifica nome utente
- Prestito libri (borrow)
- Restituzione libri (return)
- Salvataggio e caricamento utenti e prestiti su file CSV

### Funzioni di utilità (`utils.c`)
- Input sicuro di stringhe e numeri
- Generazione codici unici per utenti e libri
- Controllo validità dei puntatori
- Controllo validità dei codici utenti/libri

---

## Strutture dati principali

```c
#define MAX_BORROWED 10
#define USER_PREFIX "USR"
#define BOOK_PREFIX "BK"

typedef struct {
    char code[20];
    char title[100];
    char author[50];
    int available;
} Book;

typedef struct {
    char code[20];
    char name[50];
    char borrowedBooks[MAX_BORROWED][20];
    int borrowedBooksCount;
} User;
```

---

## Come compilare

Il progetto usa **CMake**:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Esegui il programma con:

```bash
./library-system
```

---

## Come usare il sistema

1. **Gestione libri**
   - Aggiungi libri con titolo, autore e numero copie
   - Modifica o rimuovi libri esistenti
   - Salva e carica lista libri da CSV

2. **Gestione utenti**
   - Aggiungi nuovi utenti
   - Modifica nome utente
   - Prestito libri (controlla disponibilità)
   - Restituzione libri
   - Salva e carica lista utenti da CSV

3. **Persistenza**
   - Tutti i dati possono essere salvati in CSV (`data/books.csv`, `data/users.csv`) e caricati all’avvio

---

## Esempio di output

```
Enter user name: Mario Rossi
User added successfully. Total users: 1

Enter book title: C Programming
Enter book author: Dennis Ritchie
Enter available copies: 5
Book added successfully! Total books: 1

Borrowing book BK001 by user USR001...
Book BK001 borrowed by user USR001
```

---

## Dipendenze

- **C standard library** (`stdio.h`, `stdlib.h`, `string.h`, `stdarg.h`)
- Compilatore compatibile con C99 o superiore

---

## Contributi

Questo progetto è aperto a modifiche e miglioramenti:
- Gestione grafica (GUI)
- Database reale invece di CSV
- Funzionalità di ricerca avanzata libri/utenti

---