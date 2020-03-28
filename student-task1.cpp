#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char** argv){
    if(argc < 3){ // we need 3 arguments at least
        cout << "You have not used the correct arguments" << endl;
        cout << "try " << argv[0] << " \"filename.filetype\" \"search term\"" << endl << "To allow both upper case and lower case answers, you can add -nocaps to the end" << endl;
    }
    bool icase = false;
    if(argc > 3){
        for(int i = 0; i < argc; i++){
            if(argv[i] == "-nocaps"){ // if we have nocaps, remove it and shift the rest to the left so the filename is still the first argument and the second is the search term
                icase = true;
                for(int q = i; q < argc; q++){
                    argv[q-1] = argv[q];
                }
                i = argc;
            }
        }
    }
    ifstream fin;
    fin.open(argv[1]); // open the fie
    string fullstring = "";
    while(!fin.eof()){
        string get;
        getline(fin,get); // get all the lines and concat them with \n
        fullstring += get;
        if(!fin.eof()){
            fullstring += "\n";
        }
    }
    regex houdini("[\\.\\\\\\+\\*\\?\\[\\^\\]\\$\\(\\)\\{\\}\\=\\!\\<\\>\\|\\:\\-]"); // this escapes all characters (houdini the escape artist)
    string replaced = regex_replace(argv[2],houdini,"\\$0"); // add a \ before the special character to escape it
    regex searchterm;
    if(icase){
        searchterm = regex(replaced,regex::ECMAScript|regex::icase); // add icase if it's supposed to ignore case
    } else {
        searchterm = regex(replaced); // if it doesn't ignore case it can keep the default flags
    }
    auto start = sregex_iterator(fullstring.begin(), fullstring.end(), searchterm); // search through the fill file
    auto end = sregex_iterator();
    cout << "There are \033[1m" << distance(start,end) << "\033[0m instances of \033[1m'" << argv[2] << "'\033[0m in this file" << endl; // count the instances
    fin.close();
    return 0;
}
