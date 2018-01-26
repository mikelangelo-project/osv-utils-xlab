
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    char **ch;
    printf("Environment variables:\n");
    for (ch=environ; ch != nullptr && *ch != nullptr; ch++) {
        printf("  %s\n", *ch);
    }
    return 0;
}
