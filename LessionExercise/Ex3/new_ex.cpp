#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#include <util.h>
#include <algorithm>
#include <iostream>

// Studio performance con struct vecchia.
// Queste cose all'esame forse non la chiede.

// Da errori di compilazione, confronta con soluzione professore.


template<typename T>
struct vector {
    T *nums_;
    int n_;
    int capacity_;

    vector() {
        printf("Vector\tDefault constructor\n");
        nums_ = NULL;
        n_ = 0;
        capacity_ = 0;
    }
    vector(int initial_size){
        printf("Vector\tint constructor\n");
        nums_ = new T[initial_size];
        n_ = initial_size;
        capacity_ = initial_size;
    }
    vector(vector&& other){
        printf("Vector\tMove constructor\n");
        n_ = other.n_;
        capacity_ = other.capacity_;
        nums_ = other.nums_;
        other.nums_ = nullptr;
    }
    vector(const vector& other){
        printf("Vector\tCopy constructor\n");
        n_ = other.n_;
        capacity_ = other.capacity_;
        nums_ = new T[capacity_];
        //Sarebbe più efficente usare 
        for(size_t i = 0; i < n_; i++){
            nums_[i] = other.nums_[i];
        }
    }
    
    vector& operator=(vector other){
        printf("Vector\tCopy Assignement\n");

        swap(*this, other);

        return *this;
    }

    // other è una "r-value reference" ,cioè un oggetto che morirà presto, quinid non c'è
    // bisogno di preservalo.
    //                             ** Da notare la sintassi.
    vector& operator=(const vector &&other){
        /*
            Non serve all'esame ma è molto utile.
            Quanod siamo certi che l'oggetto verrà subito distrutto lo tratta come un tipo
            particolare, dato che sta per morire, 
        */
        printf("Vector\tMove Assignement\n");

        n_ = other.n_;
        capacity_ = other.capacity_;
        nums_ = other.nums_;    // Puntiamo ai dati di other, tanto tra poco verrà distrutto.
        other.nums_ = NULL;     // Lo facciamo perchè quando other verrà distrutto, non vogliamo
                                // che vada a distruggerci i dati nella distructor.

        return *this;
    }
    
    friend void swap(vector& left, vector& right){
        // Comando per fede.
        using std::swap;
        swap(left.n_, right.n_);
        swap(left.capacity_, right.capacity_);
        swap(left.nums_, right.nums_);
    }

    //Struttura del Decostruttore, distruttore.
    ~vector(){
        printf("Vector\tDestructor\n");
        free(nums_);
    }
    void destructor() {
        free(this->nums_);
    }
    void push_back(const T& num) {
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
            /*
                Non è un tipo generico, ma a tempo di compilazione viene sostituito,
                quindi DEVE anche essere riconosciuto a tempo di compilazione, questo è usato
                così da non dover riscrivere il tipo ogni volta, soprattutto se molto lungo.
            */

            auto* tmp = new T[capacity_];
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


struct esempio {
    int val_;
    esempio() : val_(0) {}
    esempio(int val) : val_(val) {}
};


// "void" è implicito se non inidcato come ritorno.

vector<esempio> crea_mio(){
    vector<esempio> out;
    out.push_back(6);
    out.push_back(-9);
    out.push_back(23);
    return out;
}


int main(int argc, char *argv[]){
    vector<esempio> mio;

    /*
        Quando ritoniamo i dati di una funzione se ne fa una copia, quindi i dati di "out"
        verranno distrutti, chiamato il distruttore, solo dopo l'assegnamento.
    */

    mio = crea_mio();   // Soluzione non ideale perchè dopo l'assegnamento distruggo subito
                        // il vettore temporaneo.

    /*
        Usare l'inizializzazione rispetto l'assegnamento e meglio perchè i compilatori
        ottimizzano l'inizializzazione senza creare una copia dei dati, questo è chiamato
        RVO: Return Value Optimization.
    */

    // printf("\n\n\tRVO:\n");
    // vector<esempio> mio = crea_mio(); RVO.

    /*
        In questo caso non si può fare perchè provo a aggiungere dati senza aver prima creato
        l'oggetto, dato che provo a sfruttare l'RVO.
    */
   
    /*
        Inevec che fare la copia dei dati, mi conviene fare una shallow copy, dato che 
        questo viene fatto in molti linguaggi in CPP prende il nome di "move".
    */


    // vector<esempio> mio = crea_mio();



    return 0;
}