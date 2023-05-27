//Archivo:main.cpp
//Autor: Salvador Rodriguez A01704562
//Alejandra Cabrera A01704463
//Lexer Paralelo
//To compile: g++ main.cpp -pthread
//To execute: ./a test1.cpp test2.cpp test3.cpp test4.cpp

#include <iostream>
#include <cmath>
#include <fstream>
#include <regex>
#include <ctime>

using namespace std;
#define N					10

string html_top = R"(<!DOCTYPE html> <html> <head><link rel='stylesheet' href='./colors.css' type='text/css' /></head><body><style>
body{
background-color:#000000;
}
.string{
color: #f44f4f;
}
.float{
color: #c37ed5;
}
.operator{
color: #fafa8a;
font-weight: 900;
}
.variable{
color: #46f6b0;
}
.delimiter{
color: #3dd1f3;
}
.comment{
color: #63ff01;
}
.undefinded{
color: #dec7c7;
}
.reserved{
color: #7d42b0;
}
.int{
color: #a6ffeb;
}
</style>)";
string html_bot =
        "</body>"
        "</html>";
string seqName(int num_file){

    string name_file = "sequential";
    string s = to_string(num_file);
    name_file += s;
    name_file += ".html";
    return name_file;

}

string parallelName(int num_file){
    string name_file = "concurrente";
    string s = to_string(num_file);
    name_file += s;
    name_file += ".html";

    return name_file;
}

void create_html(string html_lexer, string name_file) {
    const string &filename(name_file);
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open()) {
        cout << "Failed to open" << filename << '\n';
    } else {
        file_out << html_top << html_lexer << html_bot << endl;
    }
}

void lexer(string file, string name_file) {
    ifstream input;
    string results, response;

    input.open(file);
    if (!input.is_open()) {
        cout << "Failed to open";
    }

    while (getline(input, results)) {
        string comment = "\\/\\/.*";
        string str = "\".*\"";
        string space =  "\\s+";
        string flt = "[+-]?(?=\\d*[.eE])(?=\\.?\\d)\\d*\\.?\\d*(?:[eE][+-]?\\d+)?";
        string inte = "\\-?[0-9]+";
        string delimiter = "[\\(|\\)|\\#|\\;|\\<|\\>|\\,\\[|\\]|\\{|\\}\\.|\\!]";
        string reserved = "auto|const|double|int|float|short|struct|unsigned|break|continue|else|for|long|signed|switch|void|case|default|enum|goto|register|sizeof|typedef|volatile|char|do|extern|if|return|static|union|while|asm|dynamic_cast|namespace|reinterpret_cast|try|bool|explicit|new|static_cast|typeid|catch|false|operator|template|typename|class|friend|string|private|this|using|const_cast|inline|public|throw|virtual|delete|mutable|protected|true|wchar_t";
        string var = "[a-zA-Z][a-zA-Z0-9_]*";
        string oper = "[\\-|\\+|\\^|\\=|\\/|\\*]";
        regex regex_tokens(
                comment + "|" + str + "|" + space + "|" + flt + "|" + inte + "|" + delimiter + "|" + reserved + "|" +
                var + "|" + oper);
        auto start_file = sregex_iterator(results.begin(), results.end(), regex_tokens);
        auto end_file = sregex_iterator();
        for (sregex_iterator i = start_file; i != end_file; i++) {
            smatch match = *i;
            string character = match.str();

            if (regex_match(character, regex(inte))) {
                response += "<span class= int>" + character + "</span>";
            } else if (regex_match(character, regex(comment))) {
                response += "<span class= comment>" + character + "</span>";
            } else if (regex_match(character, regex(str))) {
                response += "<span class= string>" + character + "</span>";
            } else if (regex_match(character, regex(space))) {
                response += "<span class= space>" + character + "</span>";
            } else if (regex_match(character, regex(flt))) {
                response += "<span class= float>" + character + "</span>";
            } else if (regex_match(character, regex(delimiter))) {
                response += "<span class= delimiter>" + character + "</span>";
            } else if (regex_match(character, regex(reserved))) {
                response += "<span class= reserved>" + character + "</span>";
            } else if (regex_match(character, regex(var))) {
                response += "<span class= variable>" + character + "</span>";
            } else if (regex_match(character, regex(oper))) {
                response += "<span class= operator>" + character + "</span>";
            }
        }
        response += "<br>";
    }
    create_html(response, name_file);
}

typedef struct {
    string filepath, nom_arch;
} Block;


void* taskLexer(void* param) {
    Block *block;
    block = (Block*) param;


    lexer(block->filepath, block->nom_arch);
    pthread_exit(0);
    return 0;
}

int main(int argc, char* argv[]) {

    int THREADS = argc;
    unsigned t0, t1, t2, t3;

    pthread_t tids[THREADS];
    Block blocks[THREADS];


    for (int i = 0; i < N; i++) {
        t0 = clock();
        for (int j = 1; j < THREADS; j++) {
            lexer(argv[j],seqName(j));
        }
        t1 = clock();
    }
    float time = (t1 - t0) / float(CLOCKS_PER_SEC);
    cout << "Tiempo transcurrido en secuencial: " << time << " s" << endl;


    for (int i = 1; i < THREADS; i++) {

        blocks[i-1].filepath = argv[i];
        blocks[i-1].nom_arch = parallelName(i);

    }


    for (int i = 0; i < N; i++) {
        t2 = clock();

        for (int j = 1; j < THREADS; j++) {
            pthread_create(&tids[j-1], NULL, taskLexer, (void*) &blocks[j-1]);
        }


        for (int j = 1; j < argc; j++) {
            pthread_join(tids[j-1], NULL);
        }
        t3 = clock();
    }
    float timeP = (t3 - t2) / float(CLOCKS_PER_SEC);
    cout << "Tiempo transcurrido en paralelo: " << timeP << " s" << endl;

    cout << "Speedup: " << time / timeP << endl;

    return 0;
}
