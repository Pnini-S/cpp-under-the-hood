#ifndef CPP_UTH_INHERITANCE_P_S_MBY_C_FROM_CPP_INHERITANCE_DEFS_H
#define CPP_UTH_INHERITANCE_P_S_MBY_C_FROM_CPP_INHERITANCE_DEFS_H

#include "c_from_cpp_encapsulation_defs.h"
enum Types{
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
};

typedef struct materials{
    char help;
}Materials;

typedef struct material_t{
    enum Types material;
}Material_t;

typedef struct physicalBox
{
    Box b;
    Material_t material;
}PhysicalBox;

void physicalBox_ctor_ddd(PhysicalBox *const this,double l, double w, double h);
void physicalBox_ctor_dddmattype(PhysicalBox *const this,double l, double w, double h, enum Types t);
void physicalBox_ctor_mattype(PhysicalBox *const this,enum Types t);
void physicalBox_dtor(PhysicalBox *const this);
void physicalBox_printp(const PhysicalBox *const this);


typedef struct weightBox{
    Box b;
    double weight;
}WeightBox;

void weightBox_ctor_dddd(WeightBox *const this, double l, double w, double h, double wgt);
void weightBox_copyctor(WeightBox *const this, const WeightBox* const other);
void weightBox_dtor(WeightBox *const this);
WeightBox* weightBox_op_eq(WeightBox *const this,const WeightBox* const other);
void weightBox_printw(const WeightBox *const this);

#endif
