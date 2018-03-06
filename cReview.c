#include<stdio.h>

int main(){
  int x;
  x = 1;

  while(x != 0){
    scanf("%d",&x);
    switch (x) {
      case 0:
        break;
      case 1:
        printf("Oi\n");
    }
  }
  return 0;
}
