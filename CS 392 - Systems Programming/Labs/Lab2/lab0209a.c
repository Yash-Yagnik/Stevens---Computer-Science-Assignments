/***************************************************************************
 * 
 * Copyright (c) 2024 shudong All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file lab0209a.c
 * @author shudong(shudong)
 * @date 2024/02/09 15:32:02
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <stdio.h>


struct ArrayList {
    void* array;
    void (*init_arr)(struct ArrayList* parr, int len, int type);
    void (*destroy)(struct ArrayList* parr);
};

void intitalize(struct ArrayList* parr, int len, int type) {
    if (type == 1) parr->array = malloc(len * sizeof(int));
    else parr->array = malloc(len * sizeof(float));
}

int main() {
    struct ArrayList p;
    intitalize(&p, 10, 1);

}


















