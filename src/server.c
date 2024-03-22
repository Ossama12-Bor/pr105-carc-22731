#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  void *handle = dlopen("../install/libplayer1.so",RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "Error: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  const char * (*p)() = dlsym(handle, "get_player_name");
  if (!p) {
    fprintf(stderr, "Error: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  printf("%s\n",(*p)());
  return 0;
}
