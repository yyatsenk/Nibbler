
#ifndef LIBABSTRACT_HPP
#define LIBABSTRACT_HPP

class LibAbstract
{
    public:
    virtual int WindowCreate(int width = 512, int height = 512){};
    virtual int GetEvents(){printf("DEBUG::LibAbstract: Events\n"); return 0;}
    virtual void WindowDestroy(){};
    LibAbstract(){}
    //virtual void Destroy(){printf("DEBUG::LibAbstract: Destroy\n");}
    virtual ~LibAbstract(){}
};

#endif