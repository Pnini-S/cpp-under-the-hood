#ifndef C_UTH_ENCAPSULATION_P_S_MBY_C_FROM_CPP_ENCAPSULATION_DEFS_H
#define C_UTH_ENCAPSULATION_P_S_MBY_C_FROM_CPP_ENCAPSULATION_DEFS_H

typedef struct box{
    double length;
    double width;
    double height;
}Box;

void box_ctor_d(Box *const this, double dim);
void box_ctor_ddd(Box *const this, double l, double w, double h);
void box_dtor(Box  *const this);

Box *box_mul_eq_d(Box *const this,double mult);

void box_print(const Box *const this);

typedef struct shelf{
    Box boxes[3];
}Shelf;

void shelf_setBox_iboxp(Shelf *const this,int index, const Box *dims);

double shelf_getVolume(const Shelf *const this);

void shelf_print(const Shelf *const this);

#endif
