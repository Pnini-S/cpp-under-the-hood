#include <stdio.h>
#include "c_from_polymorphism_defs.h"

extern VirtTable multiplierTable;

void doPrePostFixer()
{
    PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");

    prePostFixer_ctor_pcpc(&angleBrackets,"<<< ", " >>>");
    prePostFixer_print_pc(&angleBrackets,"Hello World!");
    prePostFixer_print_lc(&angleBrackets,-777,'\0');
    prePostFixer_print_lc(&angleBrackets,350, '#');
    prePostFixer_print_lc(&angleBrackets,(long int)(3.14),'\0');

    printf("\n--- end doPrePostFixer() ---\n\n");
    prePostFixer_dtor(&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    prePostDollarFixer_ctor_pcpc(&asterisks,"***** ", " *****");
    prePostDollarFixer_print_ic(&asterisks,-777,'$');
    prePostDollarFixer_print_ic(&asterisks,350, '#');
    prePostDollarFixer_print_dc(&asterisks,3.14f,'$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    prePostDollarFixer_dtor(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;
    printf("\n--- start doPrePostChecker() ---\n\n");

    prePostChecker_ctor(&check);
    prePostChecker_printThisSymbolUsingFunc(&check);
    prePostChecker_printThisSymbolDirectly(&check);
    prePostChecker_printDollarSymbolByCastDirectly(&check);
    prePostChecker_printDollarSymbolByScopeDirectly(&check);
    prePostChecker_printDollarSymbolByCastUsingFunc(&check);
    prePostChecker_printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");
    prePostChecker_dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    prePostFloatDollarFixer_ctor_pcpc(&hashes,"### ", " ###");
    prePostFloatDollarFixer_print_f(&hashes,-777);
    prePostFloatDollarFixer_print_fc(&hashes,350,'#');
    prePostFloatDollarFixer_print_f(&hashes,3.14f);

    prePostDollarFixer_copyctor(&hashes2,(PrePostDollarFixer *)&hashes);
    prePostDollarFixer_print_dc(&hashes2,7.5, '$');
    prePostDollarFixer_print_ic(&hashes2,100, '$');

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    prePostDollarFixer_dtor(&hashes2);
    prePostFloatDollarFixer_dtor(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* const pp)
{
    VirtTable1 *tmp=(VirtTable1 *)pp->dtf.tf.vptr;
    void (*tmpFunc)(const void *const this,long,char);
    tmpFunc=(void (*)(const void *const this,long,char))tmp->print_lc;
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");
    tmpFunc(pp,123,'\0');
    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer* pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");
    prePostDollarFixer_print_ic(pp,123,'$');

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");
    prePostDollarFixer_print_ic(&pp,123,'$');

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(const PrePostHashFixer* pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");
    prePostHashFixer_print_ic(pp,123,'#');
    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    Multiplier m1, m2, m3, m4;
    printf("\n--- start doMultiplier() ---\n\n");

    defaultTextFormatter_ctor((DefaultTextFormatter *)&m1);
    m1.dtf.tf.vptr=(void *)&multiplierTable;
    m1.times=3;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    defaultTextFormatter_ctor((DefaultTextFormatter *)&m2);
    m2.dtf.tf.vptr=(void *)&multiplierTable;
    m2.times=5;
    printf("--- Multiplier CTOR: times = %d\n", m2.times);
    defaultTextFormatter_copyctor((DefaultTextFormatter *)&m3, (DefaultTextFormatter*)&m1);
    m3.dtf.tf.vptr=(void *)&multiplierTable;
    m3.times = m1.times;
    defaultTextFormatter_copyctor((DefaultTextFormatter *)&m4, (DefaultTextFormatter*)&m2);
    m4.dtf.tf.vptr=(void *)&multiplierTable;
    m4.times = m2.times;

    multiplier_print(&m1,"abc ");
    multiplier_print(&m2,"abc ");
    multiplier_print(&m3,"abc ");
    multiplier_print(&m4,"abc ");

    printf("\n--- start doMultiplier() ---\n\n");
    multiplier_dtor(&m4);
    multiplier_dtor(&m3);
    multiplier_dtor(&m2);
    multiplier_dtor(&m1);
}

void doFormatterArray()
{
    int i;
    PrePostDollarFixer p1;
    Multiplier m1;
    PrePostChecker p2;
    DefaultTextFormatter formatters[3];
    printf("\n--- start doFormatterArray() ---\n\n");

    prePostDollarFixer_ctor_pcpc(&p1,"!!! ", " !!!");
    defaultTextFormatter_copyctor(formatters,(DefaultTextFormatter *)&p1);
    prePostDollarFixer_dtor(&p1);
    defaultTextFormatter_ctor((DefaultTextFormatter *)&m1);
    m1.dtf.tf.vptr=(void *)&multiplierTable;
    m1.times=4;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    defaultTextFormatter_copyctor(formatters+1,(DefaultTextFormatter *)&m1);
    multiplier_dtor(&m1);
    prePostChecker_ctor(&p2);
    defaultTextFormatter_copyctor(formatters+2,(DefaultTextFormatter *)&p2);
    prePostChecker_dtor(&p2);

    for (i = 0; i < 3; ++i) {
        defaultTextFormatter_print_pc(formatters+i, "Hello World!");
    }

    printf("\n--- end doFormatterArray() ---\n\n");
    for (i = 2; i>=0 ; --i) {
        defaultTextFormatter_dtor(formatters+i);
    }
}

void doFormatterPtrs()
{
    int i;
    DefaultTextFormatter* pfmt[3];
    printf("\n--- start doFormatterPtrs() ---\n\n");

    pfmt[0]=malloc(sizeof(PrePostDollarFixer));
    if(pfmt[0]==NULL){
        printf("error in malloc\n");
        return;
    }
    prePostDollarFixer_ctor_pcpc((PrePostDollarFixer *)pfmt[0],"!!! "," !!!" );
    pfmt[1]=malloc(sizeof(Multiplier));
    if(pfmt[0]==NULL){
        printf("error in malloc\n");
        return;
    }
    defaultTextFormatter_ctor((DefaultTextFormatter *)pfmt[1]);
    ((Multiplier *)pfmt[1])->dtf.tf.vptr=(void *)&multiplierTable;
    ((Multiplier *)pfmt[1])->times=4;
    printf("--- Multiplier CTOR: times = %d\n", ((Multiplier *)pfmt[1])->times);
    pfmt[2]=malloc(sizeof(PrePostChecker));
    if(pfmt[0]==NULL){
        printf("error in malloc\n");
        return;
    }
    prePostChecker_ctor((PrePostChecker *)pfmt[2]);

    for (i = 0; i < 3; ++i){
        VirtTable *tmp=pfmt[i]->tf.vptr;
        tmp->print_pc(pfmt[i],"Hello World!");
    }
    for (i = 2; i >= 0; --i) {
        VirtTable *tmp=pfmt[i]->tf.vptr;
        tmp->dtor(pfmt[i]);
        free( pfmt[i]);
    }

    printf("\n--- end doFormatterPtrs() ---\n\n");

}

void doFormatterDynamicArray()
{
    int i;
    DefaultTextFormatter* formatters;
    printf("\n--- start doFormatterDynamicArray() ---\n\n");

     formatters= generateFormatterArray();

    for (i = 0; i < 3; ++i) {
        VirtTable *tmp=formatters[i].tf.vptr;
        tmp->print_pc(formatters+i,"Hello World!");
    }
    for (i = 2; i >= 0; --i) {
        VirtTable *tmp=formatters[i].tf.vptr;
        tmp->dtor(formatters+i);
    }
    free(formatters);

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}

int main()
{
    PrePostDollarFixer copy;
    PrePostHashFixer hfix;
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();

    prePostHashFixer_ctor_i(&hfix,4);
    runAsPrePostFixerRef((PrePostFixer *)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer *)&hfix);
    prePostDollarFixer_copyctor(&copy,(PrePostDollarFixer *)&hfix);
    runAsPrePostDollarFixerObj(copy);
    prePostDollarFixer_dtor(&copy);
    runAsPrePostHashFixerRef(&hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");
    prePostHashFixer_dtor(&hfix);
    return 0;
}


