#include <stdio.h>
#include "c_from_cpp_inheritance_defs.h"


void doMaterials()
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    struct MatTest { Materials mat; Material_t mat_t; };
    Materials mat;
    Material_t mat1,mat2;

    printf("\n--- Start doMaterials() ---\n\n");

    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n",sizeof(mat));
    printf("Size of Materials::Types: %lu\n", sizeof(enum Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));

    printf("Size of Materials + Material_t: %lu\n",sizeof(struct MatTest));

    mat1.material=OTHER;
    printf("Material created, set to %s\n", names[mat1.material]);
    mat2.material=METAL;
    printf("Material created, set to %s\n", names[mat2.material]);

    printf("\n--- End doMaterials() ---\n\n");
}

void doPhysicalBox()
{
    PhysicalBox pb1, pb2,pb3,pb4;
    printf("\n--- Start doPhysicalBox() ---\n\n");

    physicalBox_ctor_dddmattype(&pb1, 8, 6, 4,PLASTIC);
    physicalBox_ctor_mattype(&pb2,WOOD);
    physicalBox_ctor_ddd(&pb3, 7, 7, 7);

    printf("\npb4 is copy-constructed from pb1\n");
    pb4 = pb1;
    physicalBox_printp(&pb4);
    physicalBox_printp(&pb1);
    printf("pb4 %s pb1\n", pb4.b.height == pb1.b.height && pb4.b.length==pb1.b.length && pb4.b.width==pb1.b.width && pb4.material.material==pb1.material.material ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    physicalBox_printp(&pb4);
    physicalBox_printp(&pb3);
    printf("pb4 %s pb3\n", pb4.b.height == pb3.b.height && pb4.b.length==pb3.b.length && pb4.b.width==pb3.b.width && pb4.material.material==pb3.material.material? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");
    physicalBox_dtor(&pb4);
    physicalBox_dtor(&pb3);
    physicalBox_dtor(&pb2);
    physicalBox_dtor(&pb1);
}

void doWeightBox()
{
    WeightBox pw1, pw2, pw3,pw4;
    printf("\n--- Start doWeightBox() ---\n\n");

    weightBox_ctor_dddd(&pw1, 8, 6, 4, 25);
    weightBox_ctor_dddd(&pw2, 1, 2, 3, 0.0);
    weightBox_ctor_dddd(&pw3, 10, 20, 30, 15);

    printf("\npw4 is copy-constructed from pw1\n");
    weightBox_copyctor(&pw4, &pw1);
    weightBox_printw(&pw4);
    weightBox_printw(&pw1);
    printf("pw4 %s pw1\n", pw4.b.width== pw1.b.width && pw4.b.length==pw1.b.length && pw4.b.height==pw1.b.height && pw4.weight==pw1.weight ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    weightBox_op_eq(&pw4, &pw3);
    weightBox_printw(&pw4);
    weightBox_printw(&pw3);
    printf("pw4 %s pw3\n",  pw4.b.width== pw3.b.width && pw4.b.length==pw3.b.length && pw4.b.height==pw3.b.height && pw4.weight==pw3.weight ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");
    weightBox_dtor(&pw4);
    weightBox_dtor(&pw3);
    weightBox_dtor(&pw2);
    weightBox_dtor(&pw1);
}





int main()
{
    printf("\n--- Start main() ---\n\n");

    doMaterials();

    doPhysicalBox();

    doWeightBox();

    printf("\n--- End main() ---\n\n");
    return 0;

}