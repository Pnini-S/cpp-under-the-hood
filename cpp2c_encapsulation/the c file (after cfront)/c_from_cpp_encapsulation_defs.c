#include <stdio.h>
#include "c_from_cpp_encapsulation_defs.h"

void box_ctor_d(Box *const this, double dim){
    this->length=dim;
    this->width=dim;
    this->height= dim;
    box_print(this);
}

void box_ctor_ddd(Box *const this, double l, double w, double h){
    this->length=l;
    this->width=w;
    this->height= h;
    box_print(this);
}

void box_dtor(Box  *const this)
{
    printf("Box destructor, %f x %f x %f\n", this->width, this->height,this->length);
}

Box *box_mul_eq_d(Box *const this,double mult){
    this->width*=mult;
    this->length*=mult;
    this->height*=mult;
    return this;
}

void box_print(const Box *this) {
    printf("Box: %f x %f x %f\n", this->length, this->width, this->height);
}

const char* const shelf_DEF_MSG ="The total volume held on the shelf is";
const char* shelf_message="The total volume held on the shelf is";

void shelf_setBox_iboxp(Shelf *const this,int index,  const Box *dims){
    this->boxes[index] = *dims;
}

double shelf_getVolume(const Shelf *const this){
    double vol = 0;
    size_t i;
    for ( i= 0; i < 3; ++i)
        vol += this->boxes[i].height*this->boxes[i].width*this->boxes[i].length;

    return vol;
}

void shelf_print(const Shelf *const this){
    printf("%s %f\n", shelf_message, shelf_getVolume(this));
}
