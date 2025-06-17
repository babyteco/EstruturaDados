//
//  booked.h
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#ifndef booked_h
#define booked_h
#include <stdio.h>
#include "livro.h"

#define MAX_TAM_STRING 50

typedef struct booked Booked;

Booked *criaBooked();

void leLivrosTxt(Booked *b);

void leLeitoresTxt(Booked *b);

void comandosTxt(Booked *b);

#endif
