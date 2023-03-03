//Solution for Ex1 made at home, but in C++.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

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
    //Struttura del Decostruttore.
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
    int32_t at(int i) {
        assert(i >= 0 && i < this->n_);
        return this->nums_[i];
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

    v.sort();

    for (int i = 0; i < v.size(); i++) {
        fprintf(fout, "%" PRId32 "\n", v.at(i));
    }

    //Non serve neanche invocare il decostruttore.
    fclose(fin);
    fclose(fout);

    return 0;
}