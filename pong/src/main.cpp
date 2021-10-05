#include "program.h"

int main(void)
{
    Program* program = new Program();

    program->Play();

    delete program;

    return 0;
}