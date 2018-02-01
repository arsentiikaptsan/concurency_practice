//
// Created by Arsentii Kaptsan on 28.01.2018.
//

#ifndef TASK4STRIPEDHASHSET_TESTFRIENDSHIP_H
#define TASK4STRIPEDHASHSET_TESTFRIENDSHIP_H

class A;

class TestFriendship {
    friend A;
private:
    int x;
};

class A {
public:
    int foo() {
        return TestFriendship().x;
    }
};


#endif //TASK4STRIPEDHASHSET_TESTFRIENDSHIP_H
