# opengl-computer-graphics-
```c
void UserFunc(){
    printf("A");
}

void SystemFunc(void (*fp)()){
    if(event) fp();
}

int main(){
    SystemFunc(UserFunc);
}

```
callback 함수가 어떻게 동작하는가?
