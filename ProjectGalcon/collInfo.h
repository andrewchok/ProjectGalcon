#ifndef COLL_INFO_H
#define COLL_INFO_H

class CollInfoC
{
public:
    typedef enum 
    {
        SHAPE_INVALID,
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_MAX
    }CollisionShapes;
    
    CollisionShapes shape;
    float param1;
    float param2;
};

#endif // !COLL_INFO_H