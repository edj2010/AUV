#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>
#include <string>
int main(){
  bool flag = false;
  time_t timer=time(0);
  while(time(0)-timer<=30){
    flag = false;
    std::thread t([&]{
      std::this_thread::sleep_for(std::chrono::seconds(20));
      
      if(flag==false)
        std::terminate();
    });
    t.join();
    int a = 0;
    std::cin >> a;
    flag=true;
    t.detach();
  }
  
}