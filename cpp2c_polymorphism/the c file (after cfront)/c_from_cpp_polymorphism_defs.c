#include <stdio.h>
#include "c_from_polymorphism_defs.h"



VirtTable textFormaterTable={(dtorFunc)textFormatter_dtor, NULL};

void textFormatter_ctor(TextFormatter *this){
    this->vptr=(void *) &textFormaterTable;
}
void textFormatter_dtor(TextFormatter *this) {
    this->vptr=NULL;
}

VirtTable defaultTextFormatterTable={ (dtorFunc)defaultTextFormatter_dtor, (print_pcFunc)defaultTextFormatter_print_pc};
int next_id=0;

void defaultTextFormatter_ctor(DefaultTextFormatter *const this){
    textFormatter_ctor((TextFormatter*)this);
    this->tf.vptr=(void *)&defaultTextFormatterTable;
    this->id=next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}

void defaultTextFormatter_copyctor(DefaultTextFormatter *const this, const DefaultTextFormatter *const other){
    this->tf.vptr=(void *)&defaultTextFormatterTable;
    this->id=next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, this->id);
}

DefaultTextFormatter* defaultTextFormatter_op_eq_dtf(DefaultTextFormatter *const this, const DefaultTextFormatter *const other){
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id, this->id);
    return this;
}

void defaultTextFormatter_dtor(DefaultTextFormatter *const this){
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->id);
    this->tf.vptr=(void *)&textFormaterTable;
    textFormatter_dtor((TextFormatter *) this);
}

void defaultTextFormatter_print_pc(const DefaultTextFormatter *const this, const char* text){
    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray(){
    int i;
    DefaultTextFormatter* d=malloc(sizeof(DefaultTextFormatter)*3);
    for(i=0;i<3;i++){
        defaultTextFormatter_ctor(d+i);
    }
    return d;
}

VirtTable1 prePostFixerTable={{(dtorFunc)prePostFixer_dtor,(print_pcFunc)prePostFixer_print_pc },(print_lcFunc)prePostFixer_print_lc,(getDefaultSymbolFunc)prePostFixer_getDefaultSymbol};

void prePostFixer_ctor_pcpc(PrePostFixer *const this,const char* prefix, const char* postfix) {
    defaultTextFormatter_ctor((DefaultTextFormatter *)this);
    this->dtf.tf.vptr=(void *)&prePostFixerTable;
    this->pre=prefix;
    this->post=postfix;
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre,this->post);
}

void prePostFixer_dtor(PrePostFixer *const this){
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
    this->dtf.tf.vptr=(void *)&defaultTextFormatterTable;
    defaultTextFormatter_dtor((DefaultTextFormatter *)this);
}

void prePostFixer_print_pc(const PrePostFixer *const this, const char* text){
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", this->pre, text,this->post);
}

void prePostFixer_print_lc(const PrePostFixer *const this, long num, char symbol ){
    printf("%-60s | ","[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol) {
        printf("%-60s | ","[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", this->pre, symbol, num, this->post);
    }
    else {
        printf("%-60s | ","[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", this->pre, num, this->post);
    }
}

char prePostFixer_getDefaultSymbol(const PrePostFixer *const this){
    return '\0';
}

VirtTable1 prePostDollarFixerTable={{(dtorFunc)prePostDollarFixer_dtor,(print_pcFunc)prePostFixer_print_pc }, (print_lcFunc)prePostDollarFixer_print_lc,(getDefaultSymbolFunc)prePostDollarFixer_getDefaultSymbol};
const char DEFAULT_SYMBOL_ppdf = '$';

void prePostDollarFixer_ctor_pcpc(PrePostDollarFixer *const this, const char* prefix, const char* postfix){
    prePostFixer_ctor_pcpc((PrePostFixer *)this, prefix, postfix);
    this->ppf.dtf.tf.vptr=(void *)&prePostDollarFixerTable;
    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
}

void prePostDollarFixer_copyctor(PrePostDollarFixer *const this, const PrePostDollarFixer *other){

    defaultTextFormatter_copyctor((DefaultTextFormatter  *)this,(DefaultTextFormatter *)other);
    this->ppf.dtf.tf.vptr=(void *)&prePostFixerTable;
    this->ppf.pre=other->ppf.pre;
    this->ppf.post=other->ppf.post;
    this->ppf.dtf.tf.vptr=(void *)&prePostDollarFixerTable;
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
}

void prePostDollarFixer_dtor(PrePostDollarFixer *const this){
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
    this->ppf.dtf.tf.vptr=(void *) &prePostFixerTable;
    prePostFixer_dtor((PrePostFixer *)this);
}

void prePostDollarFixer_print_ic(const PrePostDollarFixer *const this, int num, char symbol){
    VirtTable1 *tmp=(VirtTable1 *)this->ppf.dtf.tf.vptr;
    printf("%-60s | ","[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");
    tmp->print_lc((void *)this, (long)(num), symbol);
}

void prePostDollarFixer_print_lc(const PrePostDollarFixer *const this, long num, char symbol){
    printf("%-60s | ","[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");
    prePostFixer_print_lc((PrePostFixer *)this, num, symbol);
}

void prePostDollarFixer_print_dc(const PrePostDollarFixer *const this, double num, char symbol){
    printf("%-60s | ","[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", this->ppf.pre, symbol, num, this->ppf.post);
}

char prePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer *const this ){
    return DEFAULT_SYMBOL_ppdf;
}

VirtTable1 prePostHashFixerTable={{(dtorFunc)prePostHashFixer_dtor,(print_pcFunc)prePostFixer_print_pc },(print_lcFunc)prePostHashFixer_print_lc,(getDefaultSymbolFunc)prePostHashFixer_getDefaultSymbol};
const char DEFAULT_SYMBOL_pphf = '#';

void prePostHashFixer_ctor_i(PrePostHashFixer *const this, int prc){
    prePostDollarFixer_ctor_pcpc((PrePostDollarFixer *)this,"===> ", " <===");
    this->ppdf.ppf.dtf.tf.vptr=(void *)&prePostHashFixerTable;
    this->precision=prc;
    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->ppdf.ppf.pre, this->ppdf.ppf.post, this->precision);

    printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n",this->ppdf.ppf.pre, DEFAULT_SYMBOL_pphf, this->precision, 9999.9999, this->ppdf.ppf.post);
}

void prePostHashFixer_dtor(PrePostHashFixer *const this){
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this->ppdf.ppf.pre, this->ppdf.ppf.post);
    this->ppdf.ppf.dtf.tf.vptr=(void *)&prePostDollarFixerTable;
    prePostDollarFixer_dtor((PrePostDollarFixer *)this);
}

void prePostHashFixer_print_ic(const PrePostHashFixer *const this, int num, char symbol){
    printf("%-60s | ","[PrePostHashFixer::print(int, char)]");
    printf("-->\n");


    printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n",this->ppdf.ppf.pre,symbol, this->precision,(double)num, this->ppdf.ppf.post);

}

void prePostHashFixer_print_lc(const PrePostHashFixer *const this, long num, char symbol){
    printf("%-60s | ","[PrePostHashFixer::print(long, char)]");
    printf("-->\n");


    printf("%-60s | ","[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n",this->ppdf.ppf.pre,symbol, this->precision,(double)num, this->ppdf.ppf.post);
}

char prePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this){
    return DEFAULT_SYMBOL_pphf;
}

VirtTable1 prePostFloatDollarFixerTable={{(dtorFunc)prePostFloatDollarFixer_dtor,(print_pcFunc)prePostFixer_print_pc },(print_lcFunc)prePostDollarFixer_print_lc,(getDefaultSymbolFunc)prePostFloatDollarFixer_getDefaultSymbol};

const char DEFAULT_SYMBOL_ppfdf='@';

void prePostFloatDollarFixer_ctor_pcpc(PrePostFloatDollarFixer *const this, const char* prefix, const char* postfix)
{
    prePostDollarFixer_ctor_pcpc((PrePostDollarFixer *)this,prefix,postfix);
    this->ppdf.ppf.dtf.tf.vptr=(void *)&prePostFloatDollarFixerTable;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->ppdf.ppf.pre, this->ppdf.ppf.post);
}

void prePostFloatDollarFixer_dtor(PrePostFloatDollarFixer *const this){
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", this->ppdf.ppf.pre, this->ppdf.ppf.post);
    this->ppdf.ppf.dtf.tf.vptr=(void *)&prePostDollarFixerTable;
    prePostDollarFixer_dtor((PrePostDollarFixer *)this);
}

void prePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer *const this, float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    prePostFloatDollarFixer_print_fc(this, num, DEFAULT_SYMBOL_ppfdf);
}

void prePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer *const this,float num, char symbol) {
    printf("%-60s | ","[PrePostFloatDollarFixer::print(float, char)]");

    printf("%s%c%.2f%s\n", this->ppdf.ppf.pre, symbol, num, this->ppdf.ppf.post);
}

char prePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this){
    return DEFAULT_SYMBOL_ppfdf;
}

VirtTable1 prePostCheckerTable={{(dtorFunc)prePostChecker_dtor,(print_pcFunc)prePostFixer_print_pc }, (print_lcFunc)prePostDollarFixer_print_lc,(getDefaultSymbolFunc)prePostFloatDollarFixer_getDefaultSymbol};

void  prePostChecker_ctor(PrePostChecker *const this){
    prePostFloatDollarFixer_ctor_pcpc((PrePostFloatDollarFixer *)this,"[[[[ ", " ]]]]");
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=(void *)&prePostCheckerTable;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->ppfdf.ppdf.ppf.pre, this->ppfdf.ppdf.ppf.post);
}

void prePostChecker_dtor(PrePostChecker *const this){
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->ppfdf.ppdf.ppf.pre, this->ppfdf.ppdf.ppf.post);
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=(void *)&prePostFloatDollarFixerTable;
    prePostFloatDollarFixer_dtor((PrePostFloatDollarFixer *)this);
}

void prePostChecker_printThisSymbolUsingFunc(const PrePostChecker *const this) {
    VirtTable1 *tmp=(VirtTable1 *)this->ppfdf.ppdf.ppf.dtf.tf.vptr;
    printf("%-60s | ","[PrePostChecker::printThisSymbolUsingFunc()]");

    printf("Default symbol is %c\n", tmp->getDefaultSymbol(this));
}

void prePostChecker_printThisSymbolDirectly(const PrePostChecker *const this) {
    printf("%-60s | ","[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", DEFAULT_SYMBOL_ppfdf);
}

void prePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker *const this) {
    VirtTable1 *tmp=(VirtTable1 *)((PrePostDollarFixer*)(this))->ppf.dtf.tf.vptr;
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", tmp->getDefaultSymbol(this));
}

void prePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker *const this) {
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", prePostDollarFixer_getDefaultSymbol((PrePostDollarFixer *)this));
}

void prePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker *const this) {
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n",DEFAULT_SYMBOL_ppdf);
}

void prePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker *const this) {
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", DEFAULT_SYMBOL_ppdf);
}

VirtTable multiplierTable={(dtorFunc)multiplier_dtor,(print_pcFunc)multiplier_print};

void multiplier_dtor(Multiplier *const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->times);
    this->dtf.tf.vptr=(void *)&defaultTextFormatterTable;
    defaultTextFormatter_dtor((DefaultTextFormatter *)this);
}

void multiplier_print(const Multiplier *const this, const char* text)
{
    int i;
    printf("%-60s | ","[Multiplier::print(const char*)]");

    for (i = 0; i < this->times; ++i)
        printf("%s", text);
    printf("\n");
}