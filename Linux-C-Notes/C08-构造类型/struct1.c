#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32

struct
{
    int   i;
    char  ch;
    float f;
} a =
    {
        1,
        'a',
},
  b, c, *p, *q;

struct simp_st
{
    int   i;
    char  ch;
    float f;
    // char ch1;
};   // __attribute__((packed));


struct student_st
{
    int  id;
    char name[NAMESIZE];
    // struct birthday_st birth;
    struct birthday_st
    {
        int year;
        int month;
        int day;
    } birth;
    int math;
    int chinese;
};


void func(struct simp_st *b)
{
    printf("%d\n", sizeof(b));
}

int main( )
{
    // TYPE NAME = VALUE;


    struct simp_st  a;
    struct simp_st *p = &a;

    // func(a);

    func(p);




    // printf("sizeof(point) = %d\n", sizeof(p));
    // printf("sizeof(struct) = %d\n", sizeof(a));
    // out:
    // sizeof(point) = 8
    // sizeof(struct) = 12



#if 0
    struct student_st  stu    = {10011, "Alan", {2011, 11, 11}, 98, 97};
    struct student_st *p      = &stu;
    struct student_st  arr[2] = {{.name = "Alan"}, {.name = "John"}};

    p = &arr[0];

    // struct student_st stu = {.math = 98, .chinese = 97};

    // printf("%d %s %d-%d-%d %d %d\n",
    //        stu.id,
    //        stu.name,
    //        stu.birth.year,
    //        stu.birth.month,
    //        stu.birth.day,
    //        stu.math,
    //        stu.chinese);

    // printf("%d %s %d-%d-%d %d %d\n",
    //        p->id,
    //        p->name,
    //        p->birth.year,
    //        p->birth.month,
    //        p->birth.day,
    //        p->math,
    //        p->chinese);

    for (int i = 0; i < 2; i++, p++)
    {
        printf("%s ", p->name);
    }
    printf("\n");

#endif

#if 0
    struct simp_st a = {123, 456.789, 'a'};
    a.i = 112233;
    printf("%d %f %c", a.i, a.f, a.ch);
#endif

    exit(0);
}