void listAll(string path, const Class* c) {
    cout << path << c->name() << endl;
    for (vector<Class*>::const_iterator itr = c->subclasses().cbegin(); itr != c->subclasses().cend(); itr++)
        listAll(path + c->name() + "=>", *itr);
}