#include <iostream>
#include "time.h"
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

using namespace std;

class zegar
{
    public:

    unsigned int siz;
    unsigned int x,y;
    unsigned int state;

    zegar(int _x,int _y,int _size,int _state):x(_x),y(_y),siz(_size), state(_state) {};


    void draw()
    {
        switch(state)
        {
        case 1:
        {
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            break;
        } 
        
        
        case 2:
        {
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            hor(y,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x);
            
            break;
        }
        
        case 3:
        {  
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            
            break;
        }
        
        case 4:
        {
            ver(y+1,x);
            hor(y+siz+1,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            break;
        }
        
        case 5:
        {  
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            ver(y+siz+2,x+siz+1);
            ver(y+1,x);
            
            break;
        }
        
        case 6:
        {  
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            ver(y+siz+2,x+siz+1);
            ver(y+1,x);
            ver(y+siz+2,x);
            
            break;
        }
        
        case 7:
        {
            hor(y,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            break;
        }
        
        case 8:
        {  
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            ver(y+1,x);
            ver(y+siz+2,x);
            
            break;
        }
        
        case 9:
        {  
            hor(y,x+1);
            hor(y+siz+1,x+1);
            hor(y+2*siz+2,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            ver(y+1,x);
            
            break;
        }
        
        case 0:
        {   
            hor(y,x+1);
            ver(y+1,x+siz+1);
            ver(y+siz+2,x+siz+1);
            hor(y+2*siz+2,x+1);
            ver(y+1,x);
            ver(y+siz+2,x);

            break;
        } 
            
        }

    }

    void hor(unsigned int ty, unsigned int tx)
    { 
        for(int i = 0;i<siz;i++)
        {
            mvaddch(ty,tx+i,'#');
        }
    }

    void ver(unsigned int ty, unsigned int tx)
    {
        for(int i = 0;i<siz; i++)
        {
            mvaddch(ty+i,tx,'#');
        }
    }

    void setState(unsigned int temp) 
    {
        state = temp;

    }

}
;

int main()
{
    initscr();
    curs_set(0);
    nodelay(stdscr,1);
    noecho();
    

    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);

    zegar h1(5,5,5,(ptr->tm_hour/10));
    zegar h2(15,5,5,(ptr->tm_hour%10));

    zegar m1(31,5,5,(ptr->tm_min/10));
    zegar m2(41,5,5,(ptr->tm_min%10));

    zegar s1(56,5,5,(ptr->tm_sec/10));
    zegar s2(66,5,5,(ptr->tm_sec%10));

    int temp;
    bool dots = true;
    temp=ptr->tm_sec;

    while(getch()!='q')
    {

        
    t = time(NULL);
    ptr = localtime(&t);
    
    clear();

    h1.setState(ptr->tm_hour/10);
    h2.setState(ptr->tm_hour%10);
    
    m1.setState(ptr->tm_min/10);
    m2.setState(ptr->tm_min%10);
    
    s1.setState(ptr->tm_sec/10);
    s2.setState(ptr->tm_sec%10);

    h1.draw();
    h2.draw();
    
    m1.draw();
    m2.draw();
    
    s1.draw();
    s2.draw();

    usleep(1000000);

    if(dots)
    {   
        mvaddch(9,26,'#');
        mvaddch(14,26,'#');

        mvaddch(9,51,'#');
        mvaddch(14,51,'#');
        dots = false;
    }
    else
    {
        dots = true;
    }


    }
    
    curs_set(1);
    endwin();
}