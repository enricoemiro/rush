# Rush
Gioco Top-Down Platform based scritto in C++.

## Installazione
Scaricare la cartella di gioco e posizionarsi all'interno di essa.
Per compilare i file sorgenti usare il comando `make` e `./game` per avviare il gioco.

## Descrizione

### Comandi
Arrow keys per muovere il personaggio e WASD per sparare.

### Il gioco
Lo scopo del gioco è superare quanti più livelli possibile.
Il gioco termina quando si perdono tutte le vite.

### Mappa
Nella mappa sono presenti i seguenti caratteri:
* &: Rappresenta il Player;
* B: Rappresenta un Bonus;
* L: Rappresenta una Vita;
* T: Rappresenta un TEnemy;
* M: Rappresenta un MEnemy;
* S: Rappresenta la porta di entrata;
* E: Rappresenta la porta di uscita;
* *: Rappresenta uno sparo;

### Punteggio
Il punteggio viene incrementato se:
* si raccoglie un Bonus (+10);
* si uccide un TEnemy (+5);
* si uccide un MEnemy (+10);

### Vite
Le vite incrementano se si raccoglie una Vita. Le vite decrementano se ci si scontra con un TEnemy o con un MEnemy.

### Livelli
Per passare al livello successivo bisogna riuscire a raggiungere la porta di uscita 'E' e cliccando il tasto 'E'.
Si può tornare al livello precedente ritornando sulla porta di entrata 'S' e cliccando il tasto 'Q'.
