#include <iostream>
#include <string>
using namespace std;

struct node{
    string leksi;
    int f;
    node *arist, *deks;
};

node *insert_help(node* t, const string &s) {
    if (t == nullptr) {
        node *p = new node;
        p->leksi = s;
        p->f = 1;
        p->deks = p->arist = nullptr;
    }
    else if (t->leksi > s) {
        if (t->arist == nullptr) {
            node *p = new node;
            p->leksi = s;
            p->f = 1;
            t->arist = p;
            p->deks = p->arist = nullptr;
        } 
        else t->arist = insert_help (t->arist, s);
    }
    else if (t->leksi < s) {
        if (t->deks == nullptr) {
            node *p = new node;
            p->leksi = s;
            p->f = 1;
            t->deks = p;
            p->deks = p->arist = nullptr;
        } 
        else t->deks = insert_help(t->deks, s);
    }
    else if (t->leksi == s) t->f++;
    return t;
}

int lookup_help (node* t, const string &s) {
    if (t == nullptr) return 0;
    else if (t->leksi == s) return t->f;
    else if (t->leksi > s) lookup_help(t->arist, s);
    else if (t->leksi < s) lookup_help(t->deks, s);
}

int depth_help(node* t, const string &s, int &n) {
    if (t == nullptr) return -1;
    else if (t->leksi > s) {
        ++n;
        depth_help(t->arist, s, n);
    }
    else if (t->leksi < s) {
        ++n;
        depth_help(t->deks, s, n);
    }
    else if (t->leksi == s) {
        ++n;
        return n;
    }
}

void delete_dentro(node* t) {
    if (t == nullptr) return;
    delete_dentro(t->arist);
    delete_dentro(t->deks);
    delete t;
}

void inorder(ostream &out, node* t) {
    if (t != nullptr) {
        inorder(out, t->arist);
        out << t->leksi << " " << t->f << endl;
        inorder(out, t->deks);
    }
}

node *find_node(node* t, const string &s) {
    if (t == nullptr) return 0;
    else if (t->leksi > s) find_node(t->arist, s);
    else if (t->leksi < s) find_node(t->deks, s);
    else if (t->leksi == s) return t;
}

void delete_node(node* t, node* q, const string &s) {
    if (t == nullptr) ;
    else if (t->leksi > s) {
        q = t;
        delete_node(t->arist, q, s);
    }
    else if (t->leksi < s) {
        q = t;
        delete_node(t->deks, q, s);
    }
    else if (t->leksi == s) {
        node *w ;
        node *k;
        if (t->arist!=nullptr && t->deks!=nullptr) {
            w = t->arist;
            k = t;
            while (w->deks != nullptr) {
                k = w;
                w = w->deks;
            }
            t->leksi = w->leksi;
            t->f = w->f;
            if (k != t) k->deks = nullptr;
            else k->arist = nullptr;
            delete w;
            
        }
        else if (t->arist==nullptr && t->deks==nullptr) {
            if (q->deks == t) {
                q->deks = nullptr;
                delete t;
            }
            else if (q->arist = t) {
                q->arist = nullptr;
                delete t;
            }
        }
        else if (t->arist==nullptr && t->deks!=nullptr) {
            if (q->deks == t) {
                q->deks = t->deks;
                delete t;
            }
            else if (q->arist == t) {
                q->arist = t->deks;
                delete t;
            }
        }
        else if (t->arist!=nullptr && t->deks==nullptr) {
            if (q->deks == t) {
                q->deks = t->arist;
                delete t;
            }
            else if (q->arist == t) {
                q->arist = t->arist;
                delete t;
            }
        }
    }
}

class lexicon {
    public:
        lexicon() {
            riza = nullptr;
        }
        ~lexicon() {
            delete_dentro(riza);
        }
        void insert(const string &s) {
            node *p;
            if (riza == nullptr) {
                riza = new node;
                riza->leksi = s;
                riza->f = 1;
                riza->arist = riza->deks = nullptr;
            }
            else {
                p = riza;
                insert_help(p, s);
            }
        }
        int lookup(const string &s) const {
            node *p = riza;
            return lookup_help(p, s);
        }
        int depth(const string &s) const {
            int vathos = -1;
            node *p = riza;
            return depth_help(p, s, vathos);
        }
        void replace(const string &s1, const string &s2) {
            node *p = riza, *q;
            int f1 = lookup(s1), f2 = lookup(s2);
            if (f1 == 0) ;
            else if (f2 == 0) {
                p = riza;
                if (riza->leksi != s1) {
                    q = p;
                    if (p->leksi > s1) p = p->arist;
                    else p = p->deks;
                    delete_node(p, q, s1);
                    insert(s2);
                    q = riza;
                    node *r = find_node(q, s2);
                    r->f = f1;
                }
                else {
                    if (riza->arist!=nullptr && riza->deks!=nullptr) {
                        node *w, *k;
                        k = riza;
                        w = riza->arist;
                        while (w->deks != nullptr) {
                            k = w;
                            w = w->deks;
                        }
                        riza->leksi = w->leksi;
                        riza->f = w->f;
                        if (k == p) k->arist = nullptr;
                        else k->deks = nullptr;
                    }
                    else if (riza->arist==nullptr && riza->deks!=nullptr) {
                        riza = riza->deks;
                        delete p;
                    }
                    else if (riza->arist!=nullptr && riza->deks==nullptr) {
                        riza = riza->arist;
                        delete p;
                    }
                    else {
                        delete p;
                        riza = nullptr;
                    }
                    insert(s2);
                    q = riza;
                    node *r = find_node(q, s2);
                    r->f = f1;
                }
            }
            else if (f2 != 0) {
                p = riza;
                node *r = find_node(p, s2);
                r->f += f1;
                p = riza;
                if (riza->leksi != s1) {
                    q = p;
                    if (p->leksi > s1) p = p->arist;
                    else p = p->deks;
                    delete_node(p, q, s1);
                }
                else {
                    if (riza->arist!=nullptr && riza->deks!=nullptr) {
                        node *w, *k;
                        k = riza;
                        w = riza->arist;
                        while (w->deks != nullptr) {
                            k = w;
                            w = w->deks;
                        }
                        riza->leksi = w->leksi;
                        riza->f = w->f;
                        if (k == p) k->arist = nullptr;
                        else k->deks = nullptr;
                    }
                    else if (riza->arist==nullptr && riza->deks!=nullptr) {
                        riza = riza->deks;
                        delete p;
                    }
                    else if (riza->arist!=nullptr && riza->deks==nullptr) {
                        riza = riza->arist;
                        delete p;
                    }
                    else {
                        delete p;
                        riza = nullptr;
                    }
                }
            }
        }
        friend ostream & operator << (ostream &out, const lexicon &l) {
            node *p = l.riza;
            inorder(out, p);
            return out;
        }
    private:
        node *riza;
};




