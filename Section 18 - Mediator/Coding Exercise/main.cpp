#include <vector>

struct IParticipant {
    virtual void notify(IParticipant* sender, int value) = 0;
};

struct Mediator {
    std::vector<IParticipant*> participants;

    void say(IParticipant* sender, int value) {
        for (auto participant : participants)
            participant->notify(sender, value);
    };
};

struct Participant : IParticipant
{
    int value{ 0 };
    Mediator& mediator;

    Participant(Mediator& mediator) : mediator(mediator)
    {
        mediator.participants.push_back(this);
    }

    void notify(IParticipant* sender, int value) {
        if (sender != this)
            this->value += value;
    };

    void say(int value)
    {
        mediator.say(this, value);
    }
};


int main() {
    Mediator m;
    Participant p1{ m };
    Participant p2{ m };

    p1.say(2);
    p2.say(4);
    return 0;
}