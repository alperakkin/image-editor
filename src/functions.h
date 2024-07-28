
struct Function {
    char* argument;
    void (*name)(char* argument);

};

typedef struct {
    struct Function *functions;
    int length;
}FunctionList;

void cleanup(FunctionList *function_list)
{
    for(int i=0; i<function_list->length; i++)
    {
        free(&function_list->functions[i]);
    }
}

void process_functions(FunctionList *function_list)
{
    for(int i=0; i<function_list->length; i++)
    {
        struct Function func = function_list->functions[i];

        func.name(func.argument);

    }

    cleanup(function_list);


}