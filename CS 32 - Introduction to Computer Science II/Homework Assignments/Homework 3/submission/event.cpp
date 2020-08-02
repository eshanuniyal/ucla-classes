class Event {
    public: 
        // member functions
        Event(string name) : m_name(name) {}        // initialize m_name to name
        string name() const { return m_name; }      // return name
        virtual bool isSport() const = 0;           // pure virtual function   
        virtual string need() const = 0;            // pure virtual function
        virtual ~Event() {}                         // virtual destructor
    private:
        // member variables
        string m_name;
};

class BasketballGame : public Event {
    public:
        // constructor
    BasketballGame(string name) : Event(name) {}
    virtual bool isSport() const { return true; }
    virtual string need() const { return "hoops"; }
    virtual ~BasketballGame() { 
        cout << "Destroying the " << Event::name() << " basketball game" << endl; 
    }
};

class Concert : public Event {
    public:
        Concert(string name, string type) : Event(name), m_type(type) {}
        virtual bool isSport() const { return false; }
        virtual string need() const { return "a stage"; }
        virtual ~Concert() { 
            cout << "Destroying the " << Event::name() << " " << m_type << " concert"<< endl; 
        }
    private:
        string m_type;  // stores type of concert (e.g. banda or hard rock)
};

class HockeyGame : public Event {
    public:
        // constructor
        HockeyGame(string name) : Event(name) {}
        virtual bool isSport() const { return true; }
        virtual string need() const { return "ice"; }
        virtual ~HockeyGame() { 
            cout << "Destroying the " << Event::name() << " hockey game" << endl; 
        }
};