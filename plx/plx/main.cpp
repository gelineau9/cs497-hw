#include <cassert>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <plx/data/HashTable.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/lexer/Lexer.hpp>
#include <plx/literal/InputStream.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/HashCode.hpp>
#include <plx/object/Object.hpp>

#include <plx/parser/P_Primitive.hpp>

PLX::HashTable* parseOptions(int argc, char** argv) {
    PLX::HashTable* argMap = new PLX::HashTable();
    PLX::HashTable* bindings = new PLX::HashTable();
    PLX::Queue* switches = new PLX::Queue();
    PLX::Queue* positional = new PLX::Queue();
    PLX::Queue* extra = new PLX::Queue();
    argMap->put(PLX::Symbol::create("ProgName"), new PLX::String(argv[0]));
    int state = 0;
    PLX::String* key = nullptr;
    for (int n=1; n<argc; n++) {
        PLX::String* argString = new PLX::String(argv[n]);
        switch (state) {
            case 0:
                if (argString->startsWith("-") || argString->startsWith("--")) {
                    int argLen;
                    assert(argString->length(argLen));
                    if (argLen == 2) {
                        state = 2;
                    }
                    else {
                        key = argString->stripLeft('-');
                        state = 1;
                    }
                }
                else {
                    positional->enq(argString);
                }
                break;
            case 1:
                if (argString->startsWith("-") || argString->startsWith("--")) {
                    switches->enq(key);
                    key = argString->stripLeft('-');
                }
                else {
                    bindings->put(key, argString);
                    key = nullptr;
                    state = 0;
                }
                break;
            case 2:
                extra->enq(argString);
                break;
            default:
                assert(false);
        }
    }
    if (key != nullptr) {
        switches->enq(key);
        key = nullptr;
    }
    argMap->put(PLX::Symbol::create("Bindings"), bindings);
    argMap->put(PLX::Symbol::create("Extra"), extra->asList());
    argMap->put(PLX::Symbol::create("Positional"), positional->asList());
    argMap->put(PLX::Symbol::create("Switches"), switches->asList());
    return argMap;
}

void setup() {
    PLX::GLOBALS = new PLX::Globals();
    PLX::GLOBALS->initializeAll();
}

void shutdown() {
    delete PLX::GLOBALS;
}

namespace PLX{
    void readEvalPrint() {
        std::cout << "PLX> ";
        std::string line;
        getline(std::cin, line);
        PLX::Lexer* lexer = new PLX::Lexer();
        PLX::InputStream* is = new InputStream(line);
        PLX::List* tokenList = new List();
        PLX::Object* saveVal = new Object();
        PLX::Object* returnVal = new Object();
        PLX::Evaluator* etor = new Evaluator();
        bool boolLexer = lexer->tokenize(is,tokenList,saveVal);
        if(boolLexer){
            if(!pAny(tokenList,saveVal)){
                std::cout << "error:" << saveVal << "\n";
            }
            else{
                returnVal = etor->evalExpr(saveVal);
                std::cout << returnVal << "\n";
            }
            
        }
        else{
            std::cout << "error" << saveVal << "\n";
        }
    }
}
void repLoop(){
    while(true){
        PLX::readEvalPrint();
    }
}

int main(int argc, char** argv) {
    setup();
    PLX::HashTable* argMap = parseOptions(argc, argv);
    PLX::GLOBALS->SetArgMap(argMap);
    // std::cout << "ArgMap = " << argMap << "\n";
    repLoop();
    shutdown();
    return 0;
}
