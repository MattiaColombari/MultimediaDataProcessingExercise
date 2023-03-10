//Solution for Ex1 made at home, fatto bene sta volta, con funzioni della libreria standard.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#include <util.h>
#include <iostream>

// Librerie standard
#include <utility>
#include <vector>
#include <iostream> // Gestione degli stream, I/O per file e stdinput e stdoutput.
#include <fstream> // Stream per file.
#include <algorithm> // Per algoritmi standard, come la sort.
#include <iterator> // Iteratori per gli output.

// Per il move constructor bisogna scriverci vicino 'noexcept'.

struct mio_int{
    int val_;

    // 'explicit' indica che la chiamata del costruttore deve essere esplicita.
    // quindi non possiamo fare una conversione automatica.
    explicit mio_int(int val) : val_(val){}

    // operatore di casting da 'mio_int' a 'int'.
    // anche quì se mettiamo 'explicit' deve essere chiamato in modo esplicito.
    explicit operator int() {
        return val_;
    }
};

int main(int argc, char *argv[]) {
    int x = 4;
    mio_int a(5);

    // Dato che abbiamo il costruttuttore che accetta int possiamo associare a 'a' 'x'.
    // a = x;  // Se abbiamo exiplit non possiamo scrivere così.
    a = mio_int(x);

    // Funziona grazie all'operatore di casting.
    // x = a; // senza 'explicit'.
    x = int(a);


    if (argc != 3) {
        /*
            In CPP non abbimao più file, abbiamo un cocetto più in alto, cioè gli stream.
            opreazione equivalente dalla printf ma con gli stream.
            l'opreatore "<<" è definito inserter quando usato su unostream chiama la
            printf su di esso.
            Possiamo passagli qualunque dato standard e lui lo co vertità.
            Si possono usare manipolatori standard per modificare il testo,
            anche se nelle ultime versioni del CPP abbiamo la sintassi stile Python.
        */
        std::cout << "Usage: sort_int <filein.txt> <fileout.txt>\n";
        return 1;
    }

    /*
        Apertura file in input.
        Al costruttore si passa la stringa del nome del file,
        in laternativa si potrebbe passargli un puntatore a FILE.
    */
    std::ifstream is(argv[1]);
    // Controllo apertura file.
    if (is.fail()) {        // anche la condizione '!is' va bene.
        std::cout << "Error opening input file.\n";
        return 1;
    }

    std::ofstream os(argv[2]);
    if (os.fail()) {        // anche la condizione '!os' va bene.
        std::cout << "Error opening output file.\n";
        return 1;
    }

    // A differenza del C tutte le volte che usimao gli estrattorei '>>' saltiamo
    // SEMPRE i white space, anche se leggiamo un carattere alla volta.

    std::vector<double> v;

    // Lettura da file con inputstream iterator.
    /*
    std::istream_iterator<double> start(is);
    std::istream_iterator<double> stop; // Senza parametri nel costruttore ritorna il termine.
    for(auto it = start; it != stop; it++){
        v.push_back(*it);
    }
    */

    // Versione alternativa.
    /*
    std::istream_iterator<double> start(is);
    std::istream_iterator<double> stop;
    std::copy(start, stop, std::back_inserter(v));
    */

    // Un'altra versione alternativa.
    /*
    std::istream_iterator<double> start(is);
    std::istream_iterator<double> stop;
    std::vector<double> v(start, stop);
    */

    while (1) {         // while (!is.eof()) è sbagliato perchè non abbiamo ancora letto.
                        // Sempre: Leggi -> Controlla -> Usa.
        double num;

        // Lettura double da stream, identica alla fscanf ma identifica automaticamente il tipo
        // della variabile che deve leggere.
        // A differenza di fscanf non abbiamo un valore di ritorno, ma dobbiamo verificare
        // lo stato dello stream.
        is >> num;

        if (is.good()) {            // 'is' è equivamnete come condizione.
            // Lettura avvenuta con successo.
            v.push_back(num);
        }
        else if (is.eof()) {
            // Siamo alla fine del file.
            break;
        }
        else {
            // Se lo stream non è good e non siamo alla fine del file allora abbaimo avuto un
            // problema nella lettura.
            std::cout << "Warning: incorrect data in input file.\n";
            break;
        }

        /*
            Versione equivalente.

            if(!is){
                if(!is.eof()){
                    std::cout << "Warning: incorrect data in input file.\n";
                }
                break;
            }
            v.push_back(num);
        */
    }

    /*
        Sort è un template che funziona in modo generico, e richiede due iteratori,
        Nella sort per mentenere tutto generico sono stati deifiniti due elementi.
        Contenitori: oggetti che mantengono i dati.
        Iteratori: sono alberi oggetti, strutture che contengono i contenitori, hanno
            i seguenti funzioni:
                - Dammi il primo elemento.
                - Passa al prossimo elemento.
                - Verifica se siamo arrivati alla fine.
        
        Per il confronto fra essi si chiama l'operatore '<', minore, fra essi,
        quindi possimo ordianre qualunque elemento che supporti l'operatore '<'.
    */
    // inizio |          | fine         del contenitore.
    std::sort(v.begin(), v.end());
    // In future versioni del CPP la cosa è più facile.

    /* Versione classica senza iteratori, che va anche bene.
    for (size_t i = 0; i < v.size(); i++){
        os << v[i];
        os << '\n';
        // Si potrebbe anche fare così dato che l'operatore '<<' ritorna a sua volta lo stream.
        // os << v[i] << '\n'; // Chain degli operatori.
    }
    */

    /* Versione con iteratori, 1 */
    /* Questa è una versione poco usata, e se usata si usano i typedef. */
    /*
    // v.begin();      // Ritorna un iteratore.
    std::vector<double>::iterator start = v.begin();    // Iteratore definito all'interno
                                                        // di vector<double>.
    std::vector<double>::iterator stop = v.end();
    std::vector<double>::iterator it;

    // Se incermento un 'iteratore mi muove nel prossimo valore.
    for (it = start; it != stop; it++){
        os << *it << '\n';  // con '*' otteniamo l'elemento attuale.
    }
    */

    /* Versione con iteratori, 2 */
    /* Versione in po più carina. */
    /*
    auto start = v.begin();
    auto stop = v.end();

    for (auto it = start; it != stop; it++){
        double &x = *it;    // Predniamo il riferimento di 'it'.
        os << x << '\n';
    }
    */

    /* Versione con iteratori, 3, Range-based for loop.*/
    /* Versione migliore. */
    /*
    for (const auto &x : v){    // Al posto di 
        os << x << '\n';
    }
    */

    // Dato un intervallo di elementi leggete tutti gli elementi e li scrive in un'altro iteraore.
    // Assume siano grandi uguali.
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<double>(os, "\n")
        /*
            Itearore su un output, bisogna fornirgli il tipo di dato tra trasmettere, dove
            deve essere scritto e qual'è il carattere con il quale volgiamo terminare dopo ogni
            elemento.
        */
        );

    // Da notare che non serve più chiudere i file, il CPP lo gestisce automaticamente.

    return 0;
}