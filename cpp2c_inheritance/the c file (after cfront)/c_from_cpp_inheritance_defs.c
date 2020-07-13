#include <stdio.h>
#include "c_from_cpp_inheritance_defs.h"
#include "c_from_cpp_encapsulation_defs.h"

void physicalBox_ctor_ddd(PhysicalBox *const this,double l, double w, double h){
    box_ctor_ddd(&(this->b),l, w, h);
    this->material.material=OTHER;
    printf("Material created, set to Other");
    physicalBox_printp(this);
}

void physicalBox_ctor_dddmattype(PhysicalBox *const this,double l, double w, double h, enum Types t){
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    box_ctor_ddd(&(this->b),l, w, h);
    this->material.material=t;

    printf("Material created, set to %s\n", names[this->material.material]);
    physicalBox_printp(this);
}

void physicalBox_ctor_mattype(PhysicalBox *const this,enum Types t){
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    box_ctor_d(&(this->b),1);
    this->material.material=t;
    printf("Material created, set to %s\n", names[this->material.material]);
    physicalBox_printp(this);
}

void physicalBox_dtor(PhysicalBox *const this){
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", this->b.length, this->b.width,this->b.height, names[this->material.material]);
    box_dtor(&(this->b));
}

void physicalBox_printp(const PhysicalBox *const this){
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox, made of %s; ", names[this->material.material]);
    box_print(&(this->b));
}



void weightBox_ctor_dddd(WeightBox *const this, double l, double w, double h, double wgt){
     box_ctor_ddd(&(this->b),l, w, h);
     this->weight=wgt;
    weightBox_printw(this);
}

void weightBox_copyctor(WeightBox *const this, const WeightBox* const other) {
    this->weight=other->weight;
    box_ctor_d(&(this->b),1);
    weightBox_printw(this);
}

void weightBox_dtor(WeightBox *const this){
    printf("Destructing WeightBox; ");
    weightBox_printw(this);
    box_dtor(&(this->b));
}

WeightBox* weightBox_op_eq(WeightBox *const this,const WeightBox* const other){
    this->weight = other->weight;
    return this;
}

void weightBox_printw(const WeightBox *const this)
{
    printf("WeightBox, weight: %f; ",this->weight);
    box_print(&(this->b));
}
