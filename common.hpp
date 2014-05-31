#ifndef _common_hpp
#define _common_hpp

class partition {
public:
    int floor;
    int ceiling;
    partition(int floor, int ceiling): floor(floor), ceiling(ceiling) {}
    partition() {floor = -1; ceiling = 0;}
};

#endif
