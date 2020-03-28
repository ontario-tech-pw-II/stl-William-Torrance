// Student class is implemented based on string and do not need any change

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <random> // used to create random names if no file is given
#include <fstream> // used to import from a given file
#include <regex> // used to split the grade from the name in the file, it also verifies the lines of the file are using the correct format

using namespace std;

// ----------------------------- Base class

class Person{
	protected:
		string name;
	    
	public:
		void setname(char const *);
		string getname();


		Person(); 				// default constructor
		Person(const char *);
		Person(const Person &); 		// copy constructor

		Person(const string &);

		virtual ~Person();

};

void Person::setname(char const *n)
{
	name = n;
}

string Person::getname()
{
	return name;
}


Person::Person()
{
	name = "";
}

Person::Person(char const *n)
{
	setname(n);
}

Person::Person(const string & n)
{
	name = n;
}

Person::~Person()
{
}

Person::Person(const Person &t):name(t.name)
{
}

// -----------------------------  Student class

class Student : public Person{
	private:
		double grade;

	public:
      	
      	void setgrade(double);
      	double getgrade();

      	Student();    // default constructor
		Student(char const *, double);
		Student(const Student &);  // copy constructor

		~Student();

	friend ostream & operator<<(ostream &, const Student &);

};

void Student::setgrade(double g)
{
	grade =g;
}

double Student::getgrade()
{
	return grade;
}

ostream & operator<<(ostream & out, const Student & s)
{
		out << s.name << "," << s.grade;
		return out;

}

Student::Student(): grade(0)
{
}

Student::Student(char const *n, double g): Person(n)
{
	setgrade(g);
}

Student::Student(const Student &t):Person(t.name)
{
	grade = t.grade;
}

Student::~Student()
{
}

char const *randomNames[50] = { // some random names for the case where a user doesn't input a file
    "Lucie Bonnell", "Mindy Eide", "Elinor Rushin", "Temple Markee", "Amee Buntin",
    "Jeffrey Mackinnon", "Kerstin Oros", "Jefferson Tyree", "Yahaira Greenburg", "Eulalia Rockett",
    "Ava Rodrick", "Toi Michalowski", "Fumiko Mcwhorter", "Ivory Daniels", "Antonio Wison",
    "Rosann Braverman", "Renata Hungate", "Guillermo Marine", "Kenneth Morlock", "Shavonne Pyper",
    "Hermina Galentine", "Jenniffer Endo", "Vernie Milbourne", "Nannette Cogdill", "Tiara Hereford",
    "Victoria Marlow", "Felecia Stephenson", "Cherilyn Sibrian", "Leanne Shepler", "Necole Teller",
    "Mao Marcella", "Wava Palin", "Lacresha Thomure", "Tangela Kitchen", "Leena Dewalt",
    "Billie Salguero", "Trina Hage", "Margurite Bianchi", "Eleanore Saylor", "Brittny Adolphsen",
    "Dannielle Mayweather", "Samatha Shoultz", "Sima Gorrell", "Rob Mckenzie", "Jacquelyn Levey",
    "Alejandrina Lundgreen", "Rogelio Wren", "Williams Gillispie", "Dean Houge", "Shandi Tyler"
};
int task1(int argc, char** argv);
int task2(int argc, char** argv);
int task3(int argc, char** argv);

int main(int argc, char** argv){
    task1(argc, argv);
    task2(argc, argv);
    task3(argc, argv);
}
int task1(int argc, char** argv){
    cout << "\033[1mTASK ONE\033[0m" << endl;
    list<Student> studentsByGrade; // the list of students
    int count = 0;
    int i = 0;
    ifstream fin; // the file input
    string input; // the current line to get the student grade out of
    regex r("^\\s*([a-zA-Z ]*?)\\s*([0-9]+(\\.[0-9]+)?)\\s*$"); // regex to find a name and a number
    //| ^\\s*([a-zA-Z ]*?)\\s*([0-9]+(\\.[0-9]+)?)\\s*$
    //| ^\\s*                Starts with any amount of white spaces
    //| ([a-zA-Z ]*?)        Any amount of letters and spaces, this is group 1 and it is not greedy (so if it ends in a space, it won't care)
    //| \\s*                 Any amount of white spaces
    //| ([0-9]+(\\.[0-9]+)?) At least one number, can have a decimal point if it also has numbers after
    //| \\s*$                Ends with any amount of white spaces
    smatch m;
    string *studentArray; // an array of unsorted students for the random names, I was going to make a class inheriting from ifstream to give random names
    if(argc == 1){ // if we only have one argument then there is no file name
        srand(time(0));
        cout << "How many random students do you want to add? ";
        cin >> count;
        studentArray = new string[count];
        for(int i = 0;i < count;i++){ // creates an array of random names and grades to place into student list later
            studentArray[i] = randomNames[rand()%50];
            studentArray[i] += " ";
            studentArray[i] += to_string(rand()%101);
        }
    } else {
        fin.open(argv[1]); // open the file to read from
        if(!fin.is_open()){ // if it didn't open, it doesn't exist so we should exit now
            cerr << "File '" << argv[1] << "' not found" << endl;
            return 0;
        }
    }

    while((argc != 1 && !fin.eof()) || (argc == 1 && i < count)){ // either a for loop of i < count or till the end of the file (depending on weather we have a file or not)
        if(argc == 1){ // get the input string from the file or the array, we could get a random name and grade each time
            input = studentArray[i];
        } else {
            getline(fin,input);
        }
        if(regex_match(input,m,r)){ // check for a name followed by a number for name and grade
            bool wasInserted = false;
            Student temp;
            temp.setname(m[1].str().data()); // .str().data() gets the character array out of the string out of the match
            temp.setgrade(stod(m[2].str())); // the double of the string of the number mark
            for(list<Student>::iterator itter = studentsByGrade.begin();itter != studentsByGrade.end() && !wasInserted;itter++){ // itterate through all the ones in the list
                if((*itter).getgrade() > temp.getgrade()){
                    studentsByGrade.insert(itter, temp); // insert before the grade which is larger
                    itter = studentsByGrade.end();
                    wasInserted = true;
                }
            }
            if(!wasInserted){ // if it's the largest grade it goes at the end
                studentsByGrade.push_back(temp);
            }
        } else {
            cerr << "Skipping \033[1m" << input << "\033[0m" << endl;
        }
        i++;
    }

    if(argc != 1){ // close the opened file OR delete the student array
        fin.close();
    } else {
        delete[] studentArray;
    }

    for(list<Student>::iterator itter = studentsByGrade.begin();itter != studentsByGrade.end();itter++){ // print all students
        cout << *itter << endl;
    }
}
int task2(int argc, char** argv){
    cout << "\033[1mTASK TWO\033[0m" << endl;
    set<string> naughtylist;
    int count = 0;
    int i = 0;
    ifstream fin;
    string input;
    regex r("^\\s*([a-zA-Z ]*?)\\s*([0-9]+(\\.[0-9]+)?)\\s*$");
    smatch m;
    string *studentArray;
    if(argc == 1){
        srand(time(0));
        cout << "How many random students do you want to add? ";
        cin >> count;
        studentArray = new string[count];
        for(int i = 0;i < count;i++){
            studentArray[i] = randomNames[rand()%50];
            studentArray[i] += " ";
            studentArray[i] += to_string(rand()%101);
        }
    } else {
        fin.open(argv[1]);
        if(!fin.is_open()){
            cerr << "File '" << argv[1] << "' not found" << endl;
            return 0;
        }
    }

    while((argc != 1 && !fin.eof()) || (argc == 1 && i < count)){
        if(argc == 1){
            input = studentArray[i];
        } else {
            getline(fin,input);
        }
        if(regex_match(input,m,r)){
            bool wasInserted = false;
            if(stod(m[2].str()) < 50){
                naughtylist.insert(m[1]);
            }
        } else {
            cerr << "Skipping \033[1m" << input << "\033[0m" << endl;
        }
        i++;
    }

    if(argc != 1){
        fin.close();
    } else {
        delete[] studentArray;
    }

    cout << "\033[91mNaught List:\033[0m" << endl;
    for(set<string>::iterator itter = naughtylist.begin();itter != naughtylist.end();itter++){
        cout << "\t\t" << *itter << endl;
    }
}
int task3(int argc, char** argv){
    cout << "\033[1mTASK THREE\033[0m" << endl;
    map<string, int> naughtylist;
    int count = 0;
    int i = 0;
    ifstream fin;
    string input;
    regex r("^\\s*([a-zA-Z ]*?)\\s*([0-9]+(\\.[0-9]+)?)\\s*$");
    smatch m;
    string *studentArray;
    if(argc == 1){
        srand(time(0));
        cout << "How many random students do you want to add? ";
        cin >> count;
        studentArray = new string[count];
        for(int i = 0;i < count;i++){
            studentArray[i] = randomNames[rand()%50];
            studentArray[i] += " ";
            studentArray[i] += to_string(rand()%101);
        }
    } else {
        fin.open(argv[1]);
        if(!fin.is_open()){
            cerr << "File '" << argv[1] << "' not found" << endl;
            return 0;
        }
    }

    while((argc != 1 && !fin.eof()) || (argc == 1 && i < count)){
        if(argc == 1){
            input = studentArray[i];
        } else {
            getline(fin,input);
        }
        if(regex_match(input,m,r)){
            bool wasInserted = false;
            if(stod(m[2].str()) < 50){
                naughtylist.insert(m[1].str(),{m[1].str(),stod(m[2].str())});
            }
        } else {
            cerr << "Skipping \033[1m" << input << "\033[0m" << endl;
        }
        i++;
    }

    if(argc != 1){
        fin.close();
    } else {
        delete[] studentArray;
    }

    cout << "\033[91mNaught List:\033[0m" << endl;
    for(map<string, int>::iterator itter = naughtylist.begin();itter != naughtylist.end();itter++){
        cout << "\t\t" << itter->first << " " << itter->second << endl;
    }
}
