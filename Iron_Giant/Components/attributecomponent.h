#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
    //leveling
    int level;
    int exp;
    int expNext;
    int attributePoints;

    //attributes
    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    //stats
    int hp;
    int hpMax;
    int dmgMin;
    int dmgMax;
    int accuracy;
    int defence;
    int luck;

    //constructors/destructors
    AttributeComponent(int level);
    virtual ~AttributeComponent();

    //functions
    void updateStats(const bool reset);
    void updateLevel();
    std::string debugPrint() const;
    void gainExp(const int exp);

    void update();
};

#endif // ATTRIBUTECOMPONENT_H
