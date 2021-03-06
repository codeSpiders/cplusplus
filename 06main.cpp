#include <iostream>

using namespace std;

//内联函数inline function
//在c中，经常把一些短而执行频繁的计算写成宏，而不是函数，这样做的理由是
//为了执行效率，宏可以避免函数调用的开销（出入栈的开销）。
//但是，在c++出现以后，使用预处理宏会出现两个问题：第一，在c中也会出现，
//宏看起来像一个函数调用，但是会有隐藏一些难以发现的错误。第二，是c++特
//有的，预处理器不允许访问类的成员，也就是说，预处理器宏不能作为类的成员函数。
//为了保持预处理宏的效率，又增加安全性，而且还能像一般成员函数那样可以在
//类里访问自如，c++引入了内联函数。
//内联函数继承了宏函数的效率，没有函数调用时的开销，又可以像普通函数那样，
//可以进行参数、返回值类型的安全检查，又可以作为成员函数。

//问题一：
/*#define ADD(x,y) x+y
inline int add(int x,int y){
    return x+y;
}

int main(int argc, char *argv[])
{
    int a=10;
    int b=20;
    int ret1=ADD(a,b)*10;//210
    int ret2=add(a,b)*10;//300
    cout<<"ret1="<<ret1<<endl;
    cout<<"ret2="<<ret2<<endl;
    return 0;
}*/

//问题二：
/*#define CMP(x,y)  ((x)>(y)?(x):(y))
int cmp(int x,int y){
    return x>y?x:y;
}
int main(int argc, char *argv[])
{
    int a=3;
    int b=1;
    cout<<"CMP="<<CMP(++a,b)<<endl;
    cout<<"cmp="<<cmp(++a,b)<<endl;//为什么这里会输出6？上一个语句
    //a已经等于5了，cmp内部用a=5计算，退出后，再a++
    return 0;
}*/

/*#define CMP(x,y)  ((x)<(y)?(x):(y))
inline int cmp(int x,int y){
    return x<y?x:y;
}
int main(int argc, char *argv[])
{
    int a=1;
    int b=3;
    cout<<"CMP="<<CMP(++a,b)<<endl;
    cout<<"cmp="<<cmp(++a,b)<<endl;
    return 0;
}*/

//内联函数是一个真正的函数。注意：函数体和申明要结合在一起，否则编译器
//把它当成普通函数来对待。也就是说，inline必须写在函数定义前。
//内联函数的替换发生在编译阶段，而宏的替换发生在预处理阶段。
//内联函数以空间换时间；
/*inline int mymul(int x,int y){//内联函数是函数，并不像宏那样直接
   //替换，而是替换成函数，在编译阶段进行，这样避免了函数调用。
    return x*y;
}
int main(int argc, char *argv[])
{
    cout<<"mymul="<<mymul(10+10,20+20)<<endl;
    return 0;
}*/

//在类内部定义的内联函数不需要加inline，事实上，类内部定义的所有函数，
//都自动成为了内联函数。目的是为了提高效率。

//内联函数和编译器：
/*内联函数并不是随时随地都有效。
  对于任何类型的函数（包括内联函数），编译器会将函数类型（包括函数名字、
参数类型、返回值类型）放入到符号表中。当调用一个内联函数的时候，编译器
首先确保传入参数类型是正确匹配的，或者如果类型不是完全匹配，但是可以将其
转换为目标类型，并且返回值在目标表达式里匹配正确类型，或者可以转换为目标
类型，内联函数就会直接替换函数调用，这就消除了函数调用的开销。假如内联函数
是成员函数，对象this指针也会被放入合适位置。类型检查和类型转换，包括在
合适位置放入对象this指针，这些都是预处理器不能完成的。由编译器完成？
但是，c++内联编译会有一些限制，以下情况编译器可能考虑不会将函数进行内联编译：
1、不能存在任何形式的循环语句；
2、不能存在过多的条件判断语句；
3、函数体不能过于庞大，不能对函数进行取址操作；
    内联仅仅只是给编译器一个建议，编译器不一定会接受这种建议，如果你没有
将函数声明为内联函数，那么编译器也可能将此函数做内联编译。一个好的编译器
将会内联小的、简单的函数。
*/


