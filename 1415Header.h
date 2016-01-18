#ifndef 1415HEADER_H_INCLUDED
#define 1415HEADER_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;


class module_record{

    public:

    module_record(int _module_ID = 0, int _module_score = 0) // constructor

    ~module_record(); // destructor

    module_record(istream& in);

    module_record(const module_record& m); // declaration of copy constructor

    const module_record& operator=(const module_record& m); // equal operator


    void set_module_ID(const int module);

    int get_module_ID();

    void set_module_mark(const int mark); // set2

    int get_module_mark(); // get2



    friend istream& operator>>(istream& in, module_record& m); // stream input file

    friend ostream& operator<<(ostream& out, module_record& m); // stream output file

    friend class student_record;

    private:

        int module_ID;

        int module_score;

}; // class module_record

class student_record{

    public:

    student_record(int _id_number=0, int _number_of_module=0, module_record** _modules=NULL);
                                                          // two pointers, one is for being an array
                                                          // another is to point to the module_record
                                                          // because module_record is not like float or
                                                          // int that only have one variable.
                                                          // module_record have 2 arguments

    ~student_record(); // destructor

    student_record(istream& in);

    student_record(const student_record& s); // declaration of copy constructor

    const student_record& operator=(const student_record& s); // equal operator

    int get_student_id(); // get1

    void set_student_id(const int id); // set1

    int get_student_modules(); // get2

    void set_student_modules(const int no_modules); // set2

    int get_module_mark(const int module_id);

    void set_module_mark(const module_record& m); // look like copy constructor


    bool pass_all();

    int number_of_failed();


    friend istream& operator>>(istream& in, student_record& s); // stream input file

    friend ostream& operator<<(ostream& out, student_record& s); // stream output file


    private:

        int id_number;

        int number_of_module;

        module_record** modules;


}; // class student_record





#endif // 1415HEADER_H_INCLUDED
