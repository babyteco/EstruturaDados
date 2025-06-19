#include <stdio.h>
#include <stdlib.h>
#include "booked.h"

int main(){
    Booked *b = criaBooked();
    leLivrosTxt(b);
    leLeitoresTxt(b);
    comandosTxt(b);
    liberaBooked(b);
    return 0;
}