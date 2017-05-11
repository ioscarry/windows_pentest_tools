#include <stdio.h>

int main(int argc,char *argv[]){

setuid(0);

setgid(0);

system(argv[1]);

return (0);

}

