//Solution for Ex1 made at home, but in C++.

// In questa variante modifichiamo la creazione dei vettori.
// Inoltre ora vogliamo leggere da file dei double.

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
    double x = *(double *)a;
    double y = *(double *)b;
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

/*
    I template sono molto sofisticati, si possini usare linguaggi template per scrivere codice
    che produce risultati anche solo a tempo di compilazione.
    Non approfondiremo molto sui template.
*/

/*
    In questo esmepio abbiamo raggiunto il limite, dato che abbiamo troppa roba di C,
    quindi non possiamo uteriormente generalozzare, dovremmo riscrivere il cofronto e altro.
*/

// Usiamo questo comando per creare un tamplate, così da creare un vettore di tipi diversi.
// In visual studio devi fornire un'esempio di che tipo sarà T.
// "typename" specifica che 'T' è un tipo.
template<typename T>
struct vector {
    T *nums_;
    int n_;
    int capacity_;

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
        nums_ = new T[initial_size];
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
        nums_ = new T[capacity_];
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
    void push_back(T num) {
        if (this->n_ == this->capacity_) {
            this->capacity_ = (this->capacity_ == 0 ? 1 : this->capacity_ * 2);
            //Il casting a puntatore di "int32_t" deve essere esplicito, a differenza del C.
            /*
                Usiamo un vettore temporaneo, perchè non possaimo fare una realloc sul vettore
                creato con la new, quindi spostiamo i dati su tmp e poi li rimettiamo su nums_.
            */
            /*
                Cosa molto importante, non modificare una variabile nella stessa espressione,
                questo porta un comportamento diverso sulla base del compilatore scelto.
            */
            T* tmp = new T[capacity_];
            if (tmp == NULL){
                printf("Error\n");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < n_; i++){
                tmp[i] = nums_[i];
            }
            nums_ = tmp;
        }
        this->nums_[this->n_] = num;
        this->n_++;
    }
    //La sintassi "*metodo_name* const" indica che è un metodo che non va a modificare l'oggetto.
    int size() const {
        return this->n_;
    }

    T at(int i) const {
        assert(i >= 0 && i < this->n_);
        return this->nums_[i];
    }

    T& operator[](int i) {
        return nums_[i];
    }
    const T& operator[](int i) const{
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

void scrivi_vettore(FILE *f, const vector<double>& v){
    for (int i = 0; i < v.size(); i++) {
        fprintf(f, "%f\n", v[i]);
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

    // Quando istanziamo v il compilatore da il "copia incolla" del tipo specificato in vector.
    vector<double> v;
    vector<int> x;

    while (1) {
        double num;
        if (fscanf(fin, "%lf" SCNd32, &num) == 1) {
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
    
    qsort(&v[0], v.size(), sizeof(double), cmpfunc);

    scrivi_vettore(fout, v);

    //Non serve neanche invocare il decostruttore.
    fclose(fin);
    fclose(fout);

    return 0;
}