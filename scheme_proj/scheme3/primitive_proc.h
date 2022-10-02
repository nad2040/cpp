#pragma once
#include "Expression.h"

Expression* isNullProc(Expression *args); 
Expression* isBoolProc(Expression *args); 
Expression* isSymbolProc(Expression *args); 
Expression* isIntegerProc(Expression *args); 
Expression* isCharProc(Expression *args); 
Expression* isStringProc(Expression *args); 
Expression* isPairProc(Expression *args); 
Expression* isProcedureProc(Expression *args); 

Expression* charToIntProc(Expression *args); 
Expression* intToCharProc(Expression *args); 
Expression* numToStrProc(Expression *args); 
Expression* strToNumProc(Expression *args); 
Expression* symbolToStrProc(Expression *args); 
Expression* strToSymbolProc(Expression *args); 

Expression* addProc(Expression *args); 
Expression* subProc(Expression *args); 
Expression* multProc(Expression *args); 
Expression* quotientProc(Expression *args); 
Expression* remainderProc(Expression *args); 
Expression* isNumberEqualProc(Expression *args); 
Expression* isLessThanProc(Expression *args); 
Expression* isGreaterThanProc(Expression *args); 

Expression* consProc(Expression *args); 
Expression* carProc(Expression *args); 
Expression* cdrProc(Expression *args); 
Expression* setcarProc(Expression *args); 
Expression* setcdrProc(Expression *args); 
Expression* listProc(Expression *args); 

Expression* isEqProc(Expression *args); 

Expression* applyProc(Expression *args);

Expression* interactionEnvProc(Expression *args);
Expression* nullEnvProc(Expression *args);
Expression* envProc(Expression *args);
Expression* evalProc(Expression *args);

Expression *loadProc(Expression *args);

Expression *openInputPortProc(Expression *args);
Expression *closeInputPortProc(Expression *args);
Expression *isInputPortProc(Expression *args);

Expression *readProc(Expression *args);
Expression *readCharProc(Expression *args);
Expression *peekCharProc(Expression *args);

Expression *isEOFObjProc(Expression *args);

Expression *openOutputPortProc(Expression *args);
Expression *closeOutputPortProc(Expression *args);
Expression *isOutputPortProc(Expression *args);

Expression *writeCharProc(Expression *args);
Expression *writeProc(Expression *args);

Expression *errorProc(Expression *args);