#include <stdio.h>
#include "c_from_cpp_encapsulation_defs.h"

extern const char* shelf_message;
extern const char* const shelf_DEF_MSG;

static Box largeBox;
static Box box99;
static Box box88;
static int num99=0;
static int num88=0;
void before_main(){
    box_ctor_ddd(&largeBox,10, 20, 30);
}

void g_thisFunc(){
    printf("\n--- thisFunc() ---\n\n");
    if(num99==0) {
        box_ctor_ddd(&box99, 99, 99, 99);
    }
    box_mul_eq_d(&box99 ,10);
    num99++;
}

void g_thatFunc() {
    printf("\n--- thatFunc() ---\n\n");
    if (num88 == 0) {
        box_ctor_ddd(&box88, 88, 88, 88);
    }
    box_mul_eq_d(&box88, 10);
    num88++;
}

void g_doBoxes()
{
    Box b1,b2,b3,b4;
    printf("\n--- Start doBoxes() ---\n\n");

    box_ctor_d(&b1,3);
    box_ctor_ddd(&b2,4, 5, 6);

    printf("b1 volume: %f\n", b1.length*b1.width*b1.height);
    printf("b2 volume: %f\n", b2.length*b2.width*b2.height);

    box_mul_eq_d(&b1, 1.5);
    box_mul_eq_d(&b2 , 0.5);

    printf("b1 volume: %f\n", b1.length*b1.width*b1.height);
    printf("b2 volume: %f\n", b2.length*b2.width*b2.height);

    b3 = b2;
    b4 =  b2;
    box_mul_eq_d(&b4,3);
    printf("b3 %s b4\n", b3.height== b4.height && b3.width==b4.width && b3.length==b4.length ? "equals" : "does not equal");

    box_mul_eq_d(&b3 ,1.5);
    box_mul_eq_d(&b4 , 0.5);
    printf("Now, b3 %s b4\n", b3.height== b4.height && b3.width==b4.width && b3.length==b4.length ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");
    box_dtor(&b4);
    box_dtor(&b3);
    box_dtor(&b2);
    box_dtor(&b1);
}

void g_doShelves(){
    Box aBox,tmp;
    Shelf aShelf;
    int i;

    printf("\n--- start doShelves() ---\n\n");

    box_ctor_d(&aBox, 5);
    for(i=0; i<3;i++){
        box_ctor_d(&(aShelf.boxes[i]),1);
    }

    shelf_print(&aShelf);
    shelf_setBox_iboxp(&aShelf, 1, &largeBox);
    shelf_setBox_iboxp(&aShelf, 0, &aBox);

    shelf_print(&aShelf);
    shelf_message="This is the total volume on the shelf:";
    shelf_print(&aShelf);
    shelf_message="Shelf's volume:";
    shelf_print(&aShelf);
    box_ctor_ddd(&tmp,2, 4, 6);
    shelf_setBox_iboxp(&aShelf, 1, &tmp);
    box_dtor(&tmp);
    box_ctor_d(&tmp, 2);
    shelf_setBox_iboxp(&aShelf,2,&tmp);
    box_dtor(&tmp);
    shelf_print(&aShelf);

    printf("\n--- end doShelves() ---\n\n");

    for(i=3-1; i>=0;i--){
        box_dtor(&(aShelf.boxes[i]));
    }
    box_dtor(&aBox);
}


void after_main(){
    if(num99)
        box_dtor(&box88);
    if(num88)
        box_dtor(&box99);
    box_dtor(&largeBox);
}

void __attribute__((constructor)) before_main();
void __attribute__((destructor)) after_main();

int main()
{
    printf("\n--- Start main() ---\n\n");

    g_doBoxes();

    g_thisFunc();
    g_thisFunc();
    g_thisFunc();
    g_thatFunc();
    g_thatFunc();

    g_doShelves();

    printf("\n--- End main() ---\n\n");
    return 0;
}
