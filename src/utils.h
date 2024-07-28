void split_factors(char* args, double* factors, char seperator)
{
    char *token;
    int ind = 0;

    token = strtok(args, &seperator);

    while (token != NULL)
    {
        factors[ind++] = atof(token);
        token = strtok(NULL, &seperator);
    }

}