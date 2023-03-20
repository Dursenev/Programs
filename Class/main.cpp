#include <iostream>
using namespace std;
class Time
{
public:
    int hours, minutes, seconds;
    Time(bool pr = true);
    void Show_time();
    void Show_daytime();
    ~Time();
    Time operator+(Time M);
    Time operator-(Time M);
    bool operator<(Time M);
    bool operator>(Time M);
};
Time::Time(bool pr)
{
    if (pr)
    {
        cout << "Enter:" << endl;
        cout << "Hours: ";
        cin >> hours;
        while (hours < 0 || hours >= 24)
            cin >> hours;
        cout << "Minutes: ";
        cin >> minutes;
        while (minutes < 0 || minutes >= 60)
            cin >> minutes;
        cout << "Seconds: ";
        cin >> seconds;
        while (seconds < 0 || seconds >= 60)
            cin >> seconds;
    }
    else
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}
Time::~Time() {}
void Time::Show_time()
{
    cout << "Time: " << hours << ":" << minutes << ":" << seconds << ".";
}
void Time::Show_daytime()
{
    if (hours >= 0 && hours < 6)
        cout << "Night";
    if (hours >= 6 && hours < 12)
        cout << "Morning";
    if (hours >= 12 && hours < 18)
        cout << "Afternoon";
    if (hours >= 18 && hours < 24)
        cout << "Evening";
}
Time Time::operator+(Time M)
{
    Time temp(false);
    temp.hours = hours + M.hours;
    if (temp.hours >= 24)
        temp.hours = temp.hours - 24;
    temp.minutes = minutes + M.minutes;
    if (temp.minutes >= 60)
    {
        temp.minutes = temp.minutes - 60;
        temp.hours = temp.hours + 1;
        if (temp.hours >= 24)
            temp.hours = temp.hours - 24;
    }
    temp.seconds = seconds + M.seconds;
    if (temp.seconds >= 60)
    {
        temp.seconds = temp.seconds - 60;
        temp.minutes = temp.minutes + 1;
        if (temp.minutes >= 60)
        {
            temp.minutes = temp.minutes - 60;
            temp.hours = temp.hours + 1;
            if (temp.hours >= 24)
                temp.hours = temp.hours - 24;
        }
    }
    return temp;
}
Time Time::operator-(Time M)
{
    Time temp(false);
    temp.hours = hours - M.hours;
    if (temp.hours < 0)
        temp.hours = temp.hours + 24;
    temp.minutes = minutes - M.minutes;
    if (temp.minutes < 0)
    {
        temp.minutes = temp.minutes + 60;
        temp.hours = temp.hours - 1;
        if (temp.hours < 0)
            temp.hours = temp.hours + 24;
    }
    temp.seconds = seconds - M.seconds;
    if (temp.seconds < 0)
    {
        temp.seconds = temp.seconds + 60;
        temp.minutes = temp.minutes - 1;
        if (temp.minutes < 0)
        {
            temp.minutes = temp.minutes + 60;
            temp.hours = temp.hours - 1;
            if (temp.hours < 0)
                temp.hours = temp.hours + 24;
        }
    }
    return temp;
}
bool Time::operator<(Time M)
{
    if (hours < M.hours)
        return 1;
    else
    {
        if (hours == M.hours)
        {
            if (minutes < M.minutes)
                return 1;
            else
            {
                if (minutes == M.minutes)
                {
                    if (seconds < M.seconds)
                        return 1;
                    else
                        return 0;
                }
                return 0;
            }
        }
        return 0;
    }
}
bool Time::operator>(Time M)
{
    if (hours > M.hours)
        return 1;
    else
    {
        if (hours == M.hours)
        {
            if (minutes > M.minutes)
                return 1;
            else
            {
                if (minutes == M.minutes)
                {
                    if (seconds > M.seconds)
                        return 1;
                    else
                        return 0;
                }
                return 0;
            }
        }
        return 0;
    }
}
int main()
{
    Time t1, t2, t3, t4, T1(false), T2(false);
    T1 = t1 + t3;
    T2 = t4 - t2;
    T1.Show_time();
    cout << endl;
    T2.Show_time();
    cout << endl;
    if (T1 < T2)
    {
        cout << "T1<T2";
    }
    if (T1 > T2)
    {
        cout << "T1>T2";
    }
    cout << endl;
    T1.Show_daytime();
    cout << endl;
    T2.Show_daytime();
}