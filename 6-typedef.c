

typedef int *intptr; // added type intptr

struct tag_mystruct {
    int i;
    double d;
};
typedef struct tag_mystruct mystruct;
//now instead of writing "struct tag_mystruct my_struct_instance"
// we can write: mystruct my_struct_instance;

//or, typedef likethat
typedef struct tag_mystruct1 {
    int i;
    double d;
} mystruct1;

mystruct s;
mystruct1 s1;


