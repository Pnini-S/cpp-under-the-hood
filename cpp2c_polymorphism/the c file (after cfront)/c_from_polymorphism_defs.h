#ifndef CPP_UTH_POLYMORPHISM_P_S_MBY_C_FROM_POLYMORPHISM_DEFS_H
#define CPP_UTH_POLYMORPHISM_P_S_MBY_C_FROM_POLYMORPHISM_DEFS_H


#include <stddef.h>
#include <malloc.h>

typedef  void (*dtorFunc)(void *const);
typedef  void (*print_pcFunc)(const void* const, const char *);
typedef  void (*print_lcFunc)(const void *const ,long ,char );
typedef  char(*getDefaultSymbolFunc)(const void *const );
typedef struct virtTable{
    dtorFunc dtor;
    print_pcFunc print_pc;
}VirtTable;
typedef struct virtTable1{
    VirtTable vt;
    print_lcFunc print_lc;
    getDefaultSymbolFunc getDefaultSymbol;
}VirtTable1;

typedef struct textFormater{
    void* vptr;
}TextFormatter;

void textFormatter_ctor(TextFormatter *this);
void textFormatter_dtor(TextFormatter *this);

typedef struct defaultTextFormatter{
    TextFormatter tf;
    int id;
}DefaultTextFormatter;

void defaultTextFormatter_ctor(DefaultTextFormatter *const this);
void defaultTextFormatter_copyctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
DefaultTextFormatter* defaultTextFormatter_op_eq_dtf(DefaultTextFormatter *const this, const DefaultTextFormatter *const other);
void defaultTextFormatter_dtor(DefaultTextFormatter *const this);
void defaultTextFormatter_print_pc(const DefaultTextFormatter *const this, const char* text);

DefaultTextFormatter* generateFormatterArray();

typedef struct prePostFixer{
    DefaultTextFormatter dtf;
    const char* pre;
    const char* post;
}PrePostFixer;

void prePostFixer_ctor_pcpc(PrePostFixer *const this,const char* prefix, const char* postfix);
void prePostFixer_dtor(PrePostFixer *const this);
void prePostFixer_print_pc(const PrePostFixer *const this, const char* text);
void prePostFixer_print_lc(const PrePostFixer *const this, long num, char symbol);
char prePostFixer_getDefaultSymbol(const PrePostFixer *const this);

typedef struct prePostDollarFixer{
    PrePostFixer ppf;
}PrePostDollarFixer;

void prePostDollarFixer_ctor_pcpc(PrePostDollarFixer *const this, const char* prefix, const char* postfix);
void prePostDollarFixer_copyctor(PrePostDollarFixer *const this, const PrePostDollarFixer *other);
void prePostDollarFixer_dtor(PrePostDollarFixer *const this);
void prePostDollarFixer_print_ic(const PrePostDollarFixer *const this, int num, char symbol);
void prePostDollarFixer_print_lc(const PrePostDollarFixer *const this, long num, char symbol);
void prePostDollarFixer_print_dc(const PrePostDollarFixer *const this, double num, char symbol);
char prePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer *const this);

typedef struct  prePostHashFixer{
    PrePostDollarFixer ppdf;
    int precision;
}PrePostHashFixer;

void prePostHashFixer_ctor_i(PrePostHashFixer *const this, int prc);
void prePostHashFixer_dtor(PrePostHashFixer *const this);
void prePostHashFixer_print_ic(const PrePostHashFixer *const this, int num, char symbol);
void prePostHashFixer_print_lc(const PrePostHashFixer *const this, long num, char symbol);
char prePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this);

typedef struct prePostFloatDollarFixer{
    PrePostDollarFixer ppdf;
}PrePostFloatDollarFixer;


void prePostFloatDollarFixer_ctor_pcpc(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix);
void prePostFloatDollarFixer_dtor(PrePostFloatDollarFixer *const this);
void prePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num);
void prePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer *const this,float num, char symbol);
char prePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this);


typedef struct prePostChecker{
    PrePostFloatDollarFixer ppfdf;
}PrePostChecker;


void  prePostChecker_ctor(PrePostChecker *const this);
void prePostChecker_dtor(PrePostChecker *const this);
void prePostChecker_printThisSymbolUsingFunc(const PrePostChecker *const this);
void prePostChecker_printThisSymbolDirectly(const PrePostChecker *const this) ;
void prePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker *const this);
void prePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this) ;
void prePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker *const this) ;
void prePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker *const this) ;

typedef struct multiplier{
    DefaultTextFormatter dtf;
    int times;
}Multiplier;

void multiplier_dtor(Multiplier *const this);
void multiplier_print(const Multiplier *const this, const char* text);
#endif
