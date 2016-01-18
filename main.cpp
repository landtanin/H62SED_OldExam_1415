#include <MATH.H>
#include <IOSTREAM.H>
#include <FSTREAM.H>
#include <STDLIB.H>

// #include "1415Header.h" no need header file. The instruction didn't ask to create header file

using namespace std;

using namespace std;


class module_record{

    public:

    module_record(int _module_ID = 0, int _module_score = 0) // constructor

    virtual ~module_record(); // destructor

    module_record(istream& in);

    module_record(const module_record& m); // declaration of copy constructor

    const module_record& operator=(const module_record& m); // equal operator


    void set_module_ID(const int module); // set1

    int get_module_ID(); // get1

    void set_module_mark(const int mark); // set2

    int get_module_mark(); // get2


    friend istream& operator>>(istream& in, module_record& m); // stream input file

    friend ostream& operator<<(ostream& out, const module_record& m); // stream output file


    virtual bool is_passed();

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

    void set_student_modules(); // set2

    int get_module_mark(const int module_id);

    void set_module_mark(const module_record& m); // look like copy constructor


    friend istream& operator>>(istream& in, student_record& s); // stream input file

    friend ostream& operator<<(ostream& out, const student_record& s); // stream output file


    bool pass_all();

    int number_of_failed();


    private:

        int id_number;

        int number_of_module;

        module_record** modules;


}; // class student_record

//----------------------------------task 5--------------------------------------

class module_with_project_record:public module_record{

public:

    module_with_project_record(int _module_ID = 0, int _module_score = 0, int _project_mark);

    virtual ~module_with_project_record();

    // does it need to have the 4 fundamental member function of good class?
    // yes

   //module_with_project_record(istream& in); // but don't need this

    module_with_project_record(const module_with_project_record& mj); // declaration of copy constructor

    const module_with_project_record& operator=(const module_with_project_record& mj); // equal operator

    int get_project_mark();

    void set_project_mark(const int _project_mark);


    virtual bool is_passed();

private:

    int project_mark;

}

module_with_project_record::module_with_project_record(int _module_ID, int _module_score, int _project_mark):

    module_score(_module_ID,module_score), // call the constructor of the base class

    project_mark(_project_mark){

    }

module_with_project_record::~module_with_project_record(){} // derived class's destructor

// module_with_project_record(istream& in);

module_with_project_record(const module_with_project_record& mj) // copy constructor

    :module_record(mj.get_module_ID(),mj.get_module_mark()),project_mark(mj.project_mark){ // again the base constructor is called

}

const module_with_project_record& operator=(const module_with_project_record& mj){ // equal operator

    if(this==&mj) return(*this);

    //module_ID = mj.module_ID;
    set_module_ID(mj.get_module_ID());

    //module_score = m.module_score;
    set_module_mark(mj.get_module_mark());

    project_mark = mj.project_mark;

    return(*this);

}

int get_project_mark(){

    return project_mark;

}

void set_project_mark(const int _project_mark){

    if(0<=_project_mark&&_project_mark<=100){

        project_mark = _project_mark;

    }

}

bool module_with_project_record::is_passed(){

    return(module_record::is_passed()&&project_mark>=40); // how to call base member function in derived class

}


//----------------------------------task 1 -------------------------------------

module_record::module_record(int _module_ID = 0, int _module_score = 0):module_ID(_module_ID),module_score(_module_score){

} // definition of constructor

module_record::~module_record(){} // definition of destructor

module_record::module_record(istream& in);{

    in>>*this;
}

module_record::module_record(const module_record& m){ // copy constructor

    module_ID = m.module_ID;

    module_score = m.module_score;

}

const module_record& module_record::operator=(const module_record& m){ // operator equal

    if(this==&m) return(*this);

    module_ID = m.module_ID;

    module_score = m.module_score;

    return(*this);

}

void module_record::set_module_ID(const int module){ // set1

        module_ID = module;

}

int module_record::get_module_ID(){ // get1

        return module_ID;

}

void module_record::set_module_mark(const int mark){ // set2

    if(mark>=0&&mark<=100){

        module_score = mark;

    }

}

int module_record::get_module_mark(){ // get2

        return module_score;

}

bool module_record::is_passed(){

  return(module_score>=40);

}

//-------------------------------task 2-----------------------------------------

student_record::student_record(int _id_number, int _number_of_module, module_record** _modules):id_number(_id_number),number_of_module(_number_of_module){ // student_record constructor

    modules = new module_record*[number_of_module]; // modules is an array of type module_record

    for(int i=0;i<number_of_module;i++) modules[i] = new module_record(*_modules[i]); // not sure why it has to create new module_record

}

student_record::~student_record(){ // student_record destructor

    if(modules!=NULL) delete[] modules;

}

student_record::student_record(istream& in);{

    in>>*this;
}

student_record::student_record(const student_record& s):id_number(s.id_number),number_of_module(s.number_of_module){ // student copy constructor

    modules = new module_record*[number_of_module];

    for(int i = 0;i<number_of_module;i++)
    {
        modules[i] = new module_record(*(s.modules[i]));
    }

}

const student_record& student_record::operator=(const student_record& s){ // student operator =

    if(this==&s) return(*this);

    id_number = s.id_number;

    delete[] modules;

    number_of_module = s.number_of_module;

    modules = new module_record*[number_of_module];

    for(int i = 0;i<number_of_module;i++){

        modules[i] = new module_record(*(s.modules[i]))

    }

    return(*this);

}


int student_record::get_student_id(){ // get1

    return id_number;

}


void student_record::set_student_id(const int id){ // set1

    id_number=id;

}

int student_record::get_student_modules(){ // get2

    return number_of_module;

}

void student_record::set_student_modules(){ // set2

    number_of_module = no_modules;

}

int student_record::get_module_mark(const int module_id){

    for(int i = 0;i<number_of_module;i++){

        if(module_id==module[i]->get_module_ID()) return (module[i]->get_module_mark());

    }

    return (-1); // to denote didn't take the module

}

void student_record::set_module_mark(const module_record& m){

    for(int i = 0;i<number_of_module;i++){

        if(module[i]->get_module_ID()==m.get_module_ID()){

            return (modules[i]->set_module_mark(m.get_module_mark()));

        }

    }

    // So confuse even look at the solution

}

//---------------------------task 4---------------------------------------------

bool student_record::pass_all(){

    return(number_of_failed==0); // we can use the call another member function in member function

}

int student_record::number_of_failed(){

    int count_failed(0);

    for(int i = 0;i<number_of_module;i++){

        if(!module[i]->is_passed) count_failed++;

    }

    return count_failed;
  }
}

//------------------------------------------------------------------------------

//--------------Stream operator - task 3----------------------------------------

istream& operator>>(istream& in,module_record &m){

      in>>m.module_id>>m.module_score;

      return(in);

}

ostream& operator<<(ostream& out,module_record &m){

      out<<m.module_id<<" "<<m.module_score<<endl;

      return(out);

}

istream& operator>>(istream& in,student_record &s){

    // we need to know how many modules, how many subjects?

      in>>s.id_number;

      in>>s.number_of_module;

      delete[] s.modules; // clear array memory

      s.modules = new module_record*[s.number_of_module];

      for(int i = 0;i<s.number_of_module;i++) s.modules[i]=new module_record(in); // don't understand

      return(in);
}

ostream& operator<<(ostream& out,student_record &s){

    // we need to know how many modules, how many subjects?

    out<<s.id_number<<"\n";

    out<<s.number_of_module;

    for(int i = 0;i<s.number_of_module;i++){

        out<<"\n"<< *(s.modules[i]); // this line will recall to the output stream of module_record

    }

    return(out);

}
//------------------------------------------------------------------------------




int main()
{

}
