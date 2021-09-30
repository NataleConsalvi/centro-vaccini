
# Esame Tecniche di Programmazione Avanzata 24 Giugno 2021 - Centro Vaccinazioni Drive-Through

Recentemente sono usciti diversi articoli sui giornali riguardo disservizi ed errori commessi in vari centri di vaccinazione Covid sul territorio: proveremo a sviluppare un sistema che prevenga errori.

## Modello dati

**Vaccini**: Un vaccino ha un codice numerico (0,1,2...), un nome (x,y,z...), un range d'età in cui può essere somministrato, un intervallo di giorni entro cui deve essere fatta una nuova somministrazione,  ed il numero di somministrazioni da effettuare (recall), da 1 (monodose) a n.

**Pazienti**: Un paziente ha un codice fiscale, nome, cognome, data di nascita, eventuali allergie a vaccini.

**Centro**: Un centro gestisce un sito online dove i pazienti devono prenotare una vaccinazione, potendo scegliere il nome del vaccino e la data di somministrazione. Il tipo del vaccino e la data potrebbero essere soggetti a vincoli in base all'età del paziente e se ha già effettuato una somministrazione in passato di un vaccino. La prenotazione genera un Appointment, che i pazienti portano con se quando si recano al centro. 

Un Vaccination Drive-Through è un sistema di code di due tipi: le generiche code checkin, dove arrivano i pazienti con la prenotazione in mano, e le code Injectionpoints, dove vengono somministrati i vaccini. 

- tutte le code hanno un nome
- Ogni injection point può somministrare un solo tipo di vaccino (x,y,z,..). Lo stesso tipo di vaccino non può essere somministrato in più injection points
- Gli injection point hanno anche un magazzino con segnanta la quantità di dosi disponibili

Il sistema procede a stati discreti con macro step di 5 minuti. Ad ogni macro step tutti i pazienti in fronte agli injection points viene somministrato il vaccino ed escono dal centro, e tutti i pazienti in fronte alla coda dei checkin vengono transitati in coda agli opportuni injection points. 


NOTA: nei checkin mostriamo più dati perchè sono i punti con maggiori controlli, ma inizialmente basterà considerare solo i codici fiscali e i nomi dei vaccini

```
Data: 2021,2,18   10:30

          Injection points      Check-in

          0 x: a  e               0: h   o   r             <----- direzione ingresso
vaccino        x  x                  x   x   y 
tempo                                t7  t11 t14   
recall                               1   1   2

          1 y: c                  1: i   p
vaccino        y                     z   w
tempo                                t8  t12
                                     2   1

          2 z: b  d  g             2: m   q   s   t
vaccino        z  z  z                z   x   z   y  
tempo                                 t9  t13 t15 t16
recall                                1   1   3   1  

                                   3: n  
                                      y
                                      t10
                                      2
```

Dopo un macro step (chiamata a Center::dequeue):

```
Pazienti usciti dal centro: a,c,b
Data: 2021,2,18   10:35

          Injection points      Check-in

          0 x: e  h               0: o   r             <----- direzione ingresso
vaccino        x  x                  x   y 
tempo                                t11 t14   
recall                               1   2

          1 y: n                  1: p
vaccino        y                      w
tempo                                 t12
                                      1

          2 z: d  g  i  m         2: q   s   t
vaccino        z  z  z  z            x   z   y  
tempo                                t13 t15 t16
recall                               1   3   1  

                                  3:                                   
```                                   
                                   

## Metodologia:

- **IMPORTANTE**: TUTTO il codice può essere implementato negli header .h come inline, **NON** perdere tempo a creare cpp e/o separare il corpo dei metodi
- Si suppone che l'utente sviluppatore interagisca col software solo attraverso la classe Center: non dovrebbe essergli possibile manomettere le classi interne, quindi se esponete qualcosa usate opportuni meccanismi di protezione (incapsulamento / const)
- Detto ciò, **NON** perdete tempo a creare classi super incapsulate con getter / setter, se vi serve qualche struttura di appoggio semplicemente usate una struct che di default ha già tutto public
- vi vengono forniti un abbozzo di main.cpp e la libreria vaxlib.h con qualche struttura e funzione di utilità
- la data e ora attuale sono artificialmente impostate con il metodo Center::open(Date, Time) che implementerete, **NON** mettere l'ora attuale con funzioni di libreria, testare diventerebbe impossibile!
- l'uso di puntatori e allocazione dinamica verrà opportunamente premiato in fase di valutazione
- il focus sarà sulla correttezza, comunque chi userà strutture efficienti (mappe, indici con puntatori, etc) sarà opportunamente premiato

## Che fare:

1. Cominciare a implementare Center.h:

1.1. scegliere in che struttura dati mettere i checkin e gli injection_points, la scomposizione in più classi sarà premiata
1.2. implementare add_checkin, add_injection_point, add_patient, book, open, enqueue, dequeue in modo semplice solo per poter riempire la struttura dati, **senza fare controlli**. Si suppone che i pazienti si accodino sempre alla coda più breve e arrivino in orario.
1.3. implementare l'override del `<<` per center (*mettendo le code fianco a fianco come negli esempi sotto), fare delle prove di stampa

2. Una volta fatto quanto sopra, porsi il problema di preservare l'integrità dei dati, anche aggiungendo/modificando  attributi dove opportuno (**in particolare puntatori**). 

NOTA: il metodo `book` per come è impostato offre al paziente diversi modi di fare prenotazioni sbagliate: per quanto un sistema ideale offrirebbe al paziente una rosa di possibilità sempre corrette tra cui scegliere, nel nostro caso invece basta limitarsi a individuare e segnalare eventuali richieste errate.

Esempi:

Non si dovrebbero poter inserire persone / vaccini duplicati

Non dovrebbe essere possibile prenotare:

- un vaccino per fascia di età sbagliata
- una recall maggiore di quelle previste
- un vaccino secondo recall se non si è già fatta la prima iniezione
- una recall n+1 prima dei giorni previsti dalla n
- una recall di un vaccino diverso dal primo       

Nel centro si potrebbero gestire questi casi:

- non dovrebbe essere possibile avere più di n pazienti contemporaneamente nel centro
- pazienti non prenotati / sconosciuti dovrebbero essere rigettati
- se un paziente arriva più di 30 min in ritardo, viene rifiutato
- paziente arriva a injection point e non ci sono dosi a sufficienza (perchè magari dopo la prenotazione il Ministero ne ha ordinato la distruzione ...)
- Un paziente ha dimenticato il foglio della prenotazione e comunica oralmente dati sbagliati della prenotazione, da confrontare con quelli registrati nel sistema
- un paziente riesce a superare la prima fascia di checkin senza averne titolo (perchè magari era a piedi..)
- viene chiuso temporaneamente un checkin, con conseguente spostamento dei pazienti nelle altre

**IMPORTANTE 1**: molto probabilmente non avrete il tempo di implementare a dovere tutto quanto, piuttosto scegliete alcuni aspetti e aggiungete dei test che dimostrino l'efficacia della vostra soluzione. Preferenzialmente mettete i controlli ai checkin, e solo poi eventualmente duplicateli negli injection points.

**IMPORTANTE 2**: ai fini dell'esame quando viene incontrata una condizione d'errore è sufficiente che che il programma termini (i.e. sollevando eccezioni), non perdete tempo a fare gestione accurata degli errory (blocchi try) che vi porterebbero via troppo tempo.



## Esempio di esecuzione (NOTA: è **solo** un abbozzo di display del main, ogni cosa va opportunamente valutata)

```
Adding checkin 0
Adding checkin 1
Adding checkin 2
Adding checkin 3
Opening injection point for Vaccine(0,x,pair(60,100),1,0)
Opening injection point for Vaccine(1,y,pair(20,40),2,15)
Opening injection point for Vaccine(2,z,pair(18,35),2,21)
Center:
0 x:        0: 
               
1 y:        1: 
               
2 z:        2: 
               
            3: 
               

Adding patient a
Adding patient b
Adding patient c
Adding patient d
Adding patient e
Adding patient f
Adding patient g
Adding patient h
Adding patient i
Adding patient l
Adding patient m
Adding patient n
 booking a at Date(2021,7,1) Time(9,30) for vaccine x
 booking b at Date(2021,7,1) Time(9,30) for vaccine y
 booking c at Date(2021,7,1) Time(9,30) for vaccine z
 booking d at Date(2021,7,1) Time(9,35) for vaccine x
 booking e at Date(2021,7,1) Time(9,35) for vaccine y
 booking f at Date(2021,7,1) Time(9,35) for vaccine z
 booking g at Date(2021,7,1) Time(9,40) for vaccine x
 booking h at Date(2021,7,1) Time(9,40) for vaccine y
 booking i at Date(2021,7,1) Time(9,40) for vaccine z
 booking l at Date(2021,7,1) Time(9,45) for vaccine x
 booking m at Date(2021,7,1) Time(9,45) for vaccine y
 booking n at Date(2021,7,1) Time(9,45) for vaccine z
**** Opening at Date(2021,7,1),Time(9,30)****
enqueing Appointment(a,0,x,Date(2021,7,1),Time(9,30),1,0) at checkin 0
enqueing Appointment(b,1,y,Date(2021,7,1),Time(9,30),1,0) at checkin 1
enqueing Appointment(c,2,z,Date(2021,7,1),Time(9,30),1,0) at checkin 2
enqueing Appointment(d,0,x,Date(2021,7,1),Time(9,35),1,0) at checkin 3
enqueing Appointment(e,1,y,Date(2021,7,1),Time(9,35),1,0) at checkin 0
enqueing Appointment(f,2,z,Date(2021,7,1),Time(9,35),1,0) at checkin 1
enqueing Appointment(g,0,x,Date(2021,7,1),Time(9,40),1,0) at checkin 2
enqueing Appointment(h,1,y,Date(2021,7,1),Time(9,40),1,0) at checkin 3
enqueing Appointment(i,2,z,Date(2021,7,1),Time(9,40),1,0) at checkin 0
enqueing Appointment(l,0,x,Date(2021,7,1),Time(9,45),1,0) at checkin 1
enqueing Appointment(m,1,y,Date(2021,7,1),Time(9,45),1,0) at checkin 2
enqueing Appointment(n,2,z,Date(2021,7,1),Time(9,45),1,0) at checkin 3
Center:
0 x:        0: a,e,i
               x,y,z
1 y:        1: b,f,l
               y,z,x
2 z:        2: c,g,m
               z,x,y
            3: d,h,n
               x,y,z

DEBUG dequeue: Date(2021,7,1) Time(9,30)
- dequeuing injections
- dequeuing checkins
Checkpoint 0: dequeuing a
Checkpoint 1: dequeuing b
Checkpoint 2: dequeuing c
Checkpoint 3: dequeuing d
Exiting center: 
Center:
0 x: a,d    0: e,i
     x,x       y,z
1 y: b      1: f,l
     y         z,x
2 z: c      2: g,m
     z         x,y
            3: h,n
               y,z

DEBUG dequeue: Date(2021,7,1) Time(9,35)
- dequeuing injections
Checkpoint 0 x: dequeuing a
Injected a with x
Checkpoint 1 y: dequeuing b
Injected b with y
Checkpoint 2 z: dequeuing c
Injected c with z
- dequeuing checkins
Checkpoint 0: dequeuing e
Checkpoint 1: dequeuing f
Checkpoint 2: dequeuing g
Checkpoint 3: dequeuing h
Exiting center: a, b, c
Center:
0 x: d,g    0: i
     x,x       z
1 y: e,h    1: l
     y,y       x
2 z: f      2: m
     z         y
            3: n
               z

DEBUG dequeue: Date(2021,7,1) Time(9,40)
- dequeuing injections
Checkpoint 0 x: dequeuing d
Injected d with x
Checkpoint 1 y: dequeuing e
Injected e with y
Checkpoint 2 z: dequeuing f
Injected f with z
- dequeuing checkins
Checkpoint 0: dequeuing i
Checkpoint 1: dequeuing l
Checkpoint 2: dequeuing m
Checkpoint 3: dequeuing n
Exiting center: d, e, f
Center:
0 x: g,l    0: 
     x,x       
1 y: h,m    1: 
     y,y       
2 z: i,n    2: 
     z,z       
            3: 
               

DEBUG dequeue: Date(2021,7,1) Time(9,45)
- dequeuing injections
Checkpoint 0 x: dequeuing g
Injected g with x
Checkpoint 1 y: dequeuing h
Injected h with y
Checkpoint 2 z: dequeuing i
Injected i with z
- dequeuing checkins
Exiting center: g, h, i
Center:
0 x: l      0: 
     x         
1 y: m      1: 
     y         
2 z: n      2: 
     z         
            3: 
               

DEBUG dequeue: Date(2021,7,1) Time(9,50)
- dequeuing injections
Checkpoint 0 x: dequeuing l
Injected l with x
Checkpoint 1 y: dequeuing m
Injected m with y
Checkpoint 2 z: dequeuing n
Injected n with z
- dequeuing checkins
Exiting center: l, m, n
Center:
0 x:        0: 
               
1 y:        1: 
               
2 z:        2: 
               
            3: 
               

 booking a at Date(2021,7,22) Time(9,0) for vaccine x
 booking b at Date(2021,7,22) Time(9,0) for vaccine y
 booking c at Date(2021,7,22) Time(9,0) for vaccine z
 booking d at Date(2021,7,22) Time(9,10) for vaccine x
 booking e at Date(2021,7,22) Time(9,10) for vaccine y
 booking f at Date(2021,7,22) Time(9,10) for vaccine z
**** Closing, everybody leaves
**** Opening at Date(2021,7,22),Time(9,0)****
enqueing Appointment(a,0,x,Date(2021,7,22),Time(9,0),2,0) at checkin 0
enqueing Appointment(b,1,y,Date(2021,7,22),Time(9,0),2,0) at checkin 1
enqueing Appointment(c,2,z,Date(2021,7,22),Time(9,0),2,0) at checkin 2
enqueing Appointment(d,0,x,Date(2021,7,22),Time(9,10),2,0) at checkin 3
enqueing Appointment(e,1,y,Date(2021,7,22),Time(9,10),2,0) at checkin 0
enqueing Appointment(f,2,z,Date(2021,7,22),Time(9,10),2,0) at checkin 1
Center:
0 x:        0: a,e
               x,y
1 y:        1: b,f
               y,z
2 z:        2: c
               z
            3: d
               x

DEBUG dequeue: Date(2021,7,22) Time(9,0)
- dequeuing injections
- dequeuing checkins
Checkpoint 0: dequeuing a
Checkpoint 1: dequeuing b
Checkpoint 2: dequeuing c
Checkpoint 3: dequeuing d
Exiting center: 
Center:
0 x: a,d    0: e
     x,x       y
1 y: b      1: f
     y         z
2 z: c      2: 
     z         
            3: 
               

DEBUG dequeue: Date(2021,7,22) Time(9,5)
- dequeuing injections
Checkpoint 0 x: dequeuing a
Injected a with x
Checkpoint 1 y: dequeuing b
Injected b with y
Checkpoint 2 z: dequeuing c
Injected c with z
- dequeuing checkins
Checkpoint 0: dequeuing e
Checkpoint 1: dequeuing f
Exiting center: a, b, c
Center:
0 x: d      0: 
     x         
1 y: e      1: 
     y         
2 z: f      2: 
     z         
            3: 
               

destroying Center..
DEBUG: Destroying Patient n
DEBUG: Destroying Patient m
DEBUG: Destroying Patient b
DEBUG: Destroying Patient e
DEBUG: Destroying Patient l
DEBUG: Destroying Patient c
DEBUG: Destroying Patient a
DEBUG: Destroying Patient f
DEBUG: Destroying Patient g
DEBUG: Destroying Patient d
DEBUG: Destroying Patient h
DEBUG: Destroying Patient i
DEBUG: Destroying Checkpoint 0 x
DEBUG: Destroying Checkpoint 1 y
DEBUG: Destroying Checkpoint 2 z
DEBUG: Destroying Checkpoint 0
DEBUG: Destroying Checkpoint 1
DEBUG: Destroying Checkpoint 2
DEBUG: Destroying Checkpoint 3
```