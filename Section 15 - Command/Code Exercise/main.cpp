struct Command
{
    enum Action { deposit, withdraw } action;
    int amount{ 0 };
    bool success{ false };
};

struct Account
{
    int balance{ 0 };

    void process(Command& cmd)
    {
        // todo
        switch (cmd.action) {
        case Command::Action::deposit:
            balance += cmd.amount;
            cmd.success = true;
            break;
        case Command::Action::withdraw:
            if (cmd.amount > balance)
                break;

            balance -= cmd.amount;
            cmd.success = true;
            break;
        }
    }
};