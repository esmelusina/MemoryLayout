#pragma once

class System
{
    bool condition(struct entity *);

    bool procedure(struct entity *);

    bool update(struct entity *)
    {
        for each entity e:
            if condition(e) :
                procedure(e);
    }
};

class System
{
    bool condition(struct entity *);

    bool procedure(struct entity *);

    bool update()
    {
        for each entity e :
            if condition(e) :
                procedure(e);
    }
};

class PairWiseSystem
{
    bool condition(struct entity *, struct entity *);

    bool procedure(struct entity *, struct entity *);

    bool update()
    {
        for each entity pair <a,b> :
        if condition(e) :
            procedure(e);
    }
};
