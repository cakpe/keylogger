#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer{
    std::thread Thread; //this is the thread for asynchronous execution without blocking the main thread
    bool Alive = false;
    long CallNumber = -1L;//we use long instead of int to ensure overflow doesn't occur
    long repeat_count = -1L; //the amount of times func has been called while the above is the above is the no of times you want the func to be called
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr; //this is akin to a pointer to a function

    void SleepAndRun(){
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();//the 1st parenthesis calls Function and the second one calls the second function it returns
    }
    void ThreadFunc(){
        if(CallNumber == Infinite)//Infinite will be defined below
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
            SleepAndRun();
    }

public:
    static const long Infinite = -1L;
    Timer(){
    }
    Timer(const std::function<void(void)> &f): funct (f) {
    }
    Timer(const std::function<void(void)> &f, const unsigned long &i, const long repeat = Timer::Infinite): funct(f),
                                                                                                            interval(std::chrono::milliseconds(i)),
                                                                                                            CallNumber(repeat){}
    // this method is to start the timer
    void Start(bool Async = true){
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }
    void Stop(){
        Alive = false;
        Thread.join();
    }


    void SetFunction(const std::function<void(void)> &f){
        funct = f;
    }
    bool IsAlive() const{return Alive;}
    void RepeatCount(const long r){
        if(Alive)
            return;
        CallNumber = r;
    }

    long GetleftCount() const {return repeat_count;}
    long RepeatCount() const {return CallNumber;}

    void setInterval(const unsigned long &i){
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }

    unsigned long Interval() const{
        return interval.count();//.count helps us convert the interval to a type long because it is originally type chrono::millisecinds
    }
    const std::function<void(void)> &Function(){
        return funct; //remember Function()()
    }
};

#endif // TIMER_H
