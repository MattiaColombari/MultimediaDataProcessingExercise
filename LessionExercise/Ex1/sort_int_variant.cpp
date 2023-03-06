//Solution for Ex1 made at home, but in C++.

// In questa variante modifichiamo la funzione per l'assegnamento.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

// Libreria standard.
#include <util.h>
#include <algorithm>
#include <iostream>

int cmpfunc(const void *a, const void *b)
{
    int32_t x = *(int32_t *)a;
    int32_t y = *(int32_t *)b;
    if (x < y) {
        return -1;
    }
    else if (x > y) {
        return 1;
    }
    else {
        return 0;
    }
}

typedef struct vector {
    //Per convenzione di usa "_" nel nome di una variabile di una classe, alla fine
    //per indicare che si tratta di una variabile della classe.
    int32_t *nums_;
    int n_;
    int capacity_; // capacity of nums_ array

    //Costruttore e Decostruttore non devono essere chiamato esplicitamente.
    //Struttura del Costruttore.
    vector() {
        //Come per Java se non c'è conflitto di nomi non serve specificare "this".
        //In altri punti useremo this, per rimasugli del programma.
        nums_ = NULL;
        n_ = 0;
        capacity_ = 0;
    }
    vector(int initial_size){
        nums_ = (int32_t*) calloc(initial_size, sizeof(int32_t));
        n_ = initial_size;
        capacity_ = initial_size;
    }
    /*
        Definiamo un nuovo cvostruttore che a partire da un0altro vettore ne crea una copia.
        In CPP non passare mai un vettore senza il riferimento altrimenti avremmo una shallow copy,
        Quindi usiamo un riferimento.
        Quando se passi un oggetto senza il riferimento metti un commento dicendo che lo stai
        facendo volontariemente.
    */
    vector(const vector& other){
        n_ = other.n_;
        capacity_ = other.capacity_;
        nums_ = (int32_t*) malloc(capacity_ * sizeof(int32_t));
        //Sarebbe più efficente usare 
        for(size_t i = 0; i < n_; i++){
            nums_[i] = other.nums_[i];
        }
    }
    // Funzione per l'assegnamento, deepcopy.
    // Copy and swap Idiom.
    // Questa è la versione caninica super specifica, adesso non sai cosa significa ma lo capirai.
    vector& operator=(vector other){
        /*
            Creiamo una variabile copia, da notare che è una deepcopy.
            vector copy = other; Questo comando non serve più perchè abbiamo giè una shallow copy
            quando la passiamo per parametro.

            In generale i guru di stackoverlow concordano con l'uso di un metodo esterno.
            Mostrato nella funzione successiva.
        */

        swap(*this, other);

        // I miei dati vendono disrtutti perchè non hanno più rifemento, dato che li abbiamo
        // scambiati con copy.
        return *this;
    }
    // Con friend indichiamo che è una funzione "amica" per accedere ai dati interni alla funzione
    // senza poi violare l'incapsulamento.
    friend void swap(vector& left, vector& right){
        // Comando per fede.
        using std::swap;
        swap(left.n_, right.n_);
        swap(left.capacity_, right.capacity_);
        swap(left.nums_, right.nums_);
    }

    //Struttura del Decostruttore, distruttore.
    ~vector(){
        free(nums_);
    }
    void destructor() {
        free(this->nums_);
    }
    void push_back(int32_t num) {
        if (this->n_ == this->capacity_) {
            this->capacity_ = (this->capacity_ == 0 ? 1 : this->capacity_ * 2);
            //Il casting a puntatore di "int32_t" deve essere esplicito, a differenza del C.
            this->nums_ = (int32_t*) realloc(this->nums_, this->capacity_ * sizeof(int32_t));
            if (this->nums_ == NULL) {
                printf("Error: failed to allocate memory.\n");
                exit(EXIT_FAILURE);
            }
        }
        this->nums_[this->n_] = num;
        this->n_++;
    }
    void sort() {
        qsort(this->nums_, this->n_, sizeof(int32_t), cmpfunc);
    }
    //La sintassi "*metodo_name* const" indica che è un metodo che non va a modificare l'oggetto.
    int size() const {
        return this->n_;
    }

    int32_t at(int i) const {
        assert(i >= 0 && i < this->n_);
        return this->nums_[i];
    }

    /*
        int32_t& operator[](int i) {
            return nums_[i];
        }

        Applichiamo l'overload degli operatori, in modo che possiamo accedere agli elementi di un
        oggetto nel segunete modo:
        v[i];

        Da notare che però non possiamo scrivere:
        v[2] = 5;
        Questo perchè la funzione ritora un valore, non un indirizzo, quindo non possiamo modificarlo.
        Quindi ritorniamo un riferimento, come mostrato nella funzione successiva.
        Da notare che abbiamo tolto const poché nonostante il compilatore me lo faccia passare
        in realtà andiamo a dare un riferimento che può essere modificato.

        Scriviamo due volte la funzione perché volgliamo in alcuni casi riscrivere l'oggetto in
        altri casi no, questo è una pratica molto frequente.
        Le due funzioni si distinguono dai parametri, in un caso abbiamo un int nell'altro un const int.
    */
   int32_t& operator[](int i) {
        return nums_[i];
    }
    const int32_t& operator[](int i) const{
        return nums_[i];
    }

    
};

//Nuova funzione fatta per dimostrazione.
void raddoppia(int val){
    val *= 2;
}

void raddoppia_sol_C(int* val){
    *val = *val * 2;
}

void raddoppia_sol_CPP(int &val){
    //Con '&' andiamo a speficiare che stiamo usando un riferimento alla varibile passata.
    val = val * 2;
}

void scrivi_vettore(FILE *f, const vector& v){
    for (int i = 0; i < v.size(); i++) {
        fprintf(f, "%" PRId32 "\n", v[i]);
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        printf("Usage: sort_int <filein.txt> <fileout.txt>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL) {
        printf("Error opening output file.\n");
        fclose(fin);
        return 1;
    }

    //Non serve invocare il costruttore esplicitamente.
    vector v;

    //Importante se non passi parametri NON mettere le tonde.
    //Se scrivessi "vector v();" avrei definito la dichiarazione a una funzione
    //che ritorna un vecotor.

    //Modo per chaimare il sortuttore che vuole un int come parametro.
    vector t(10);

    //Notazione alternativa, così possiamo passare un solo valore.
    vector s = 10;

    //Notazione più moderna ma equivalente.
    //vector r{10};

    int y = 7;
    raddoppia(7);
    printf("Es1:\t%d\n", y);
    //Restituisce sempre 7, il passaggio è per COPIA.

    //Con il C avremmo passato il puntatore.
    raddoppia_sol_C(&y);
    printf("Es2:\t%d\n", y);

    //Soluzione in C.
    raddoppia_sol_CPP(y);
    printf("Es2:\t%d\n", y);

    int &k = y;
    k = 80;
    printf("k:\t%d\ny:\t%d\n", k, y);

    //Esempi inizializzazione
    int x[20] = { 1,2,3 };
    // x = { 1,2,3, }; Non va bene, l'inizializzazione può essere fatta sono nella definizione.

    //L'assegnamento fra due struct diverso copia elemento per elemento.
    //Non va bene scrivere vector j = v; poichè j e v condivideranno gli stessi dati,
    //e quando andiamo a liberare i primi quando proviamo a liberarli abbiamo un errore,
    //questa è una shallow copy.

    while (1) {
        int32_t num;
        if (fscanf(fin, "%" SCNd32, &num) == 1) {
            v.push_back(num);
        }
        else if (feof(fin)) {
            break;
        }
        else {
            printf("Warning: incorrect data in input file.\n");
            break;
        }
    }

    /*
        Dato che abbiamo implementato il costruttore che prende un'altro vettore come input,
        allora abbiamo una deep copy.
        Questa è un'operazione di Inizializzazione.
    */
    vector h = v;

    /*
        Questa è un'oprazione di assegnamento.
        E senza il metodo prediscposto è una shallow copy.
    */
    vector v_deepcopy;
    v_deepcopy = v;     // Questo è un'expression statement.

    int a, b, c, d;
    a = b = c = d = 5;  // Questo assegnamento è lecito in CPP, come in C.
    (a = b) = 8; //Dopo questo "b" rimarrebbe inviato e "a" sarebbe 8, la valutazione dell'espressione ritorna "a", come variabile propio.

    // Se non ritornassimo niente come ritorno della funzione di assegnamento questo non funzionerebbe.
    h = v_deepcopy = v;

    v.sort();

    scrivi_vettore(fout, v);

    //Non serve neanche invocare il decostruttore.
    fclose(fin);
    fclose(fout);

    return 0;
}