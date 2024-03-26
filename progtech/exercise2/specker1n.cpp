#include <iostream>
#include <stdexcept>
using namespace std;

class Move {
    public: 
    // Take sc coins from heap sh and put tc coins to heap th
    Move(int sh, int sc, int th, int tc);
    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream & operator << (ostream &out, const Move &move);
    
    private:
    int source_heap, source_coins, target_heap, target_coins;
};

Move:: Move(int sh, int sc, int th, int tc) {
    source_heap = sh;
    source_coins = sc;
    target_heap = th;
    target_coins = tc;
};

int Move:: getSource() const {
    return source_heap;
};

int Move:: getSourceCoins() const {
    return source_coins;
};

int Move:: getTarget() const {
    return target_heap;
};

int Move:: getTargetCoins() const {
    return target_coins;
};

ostream& operator << (ostream &out, const Move &move){
    if (move.getTargetCoins()) {
    	out << "takes " << move.getSourceCoins() << " coins from heap "
        				<< move.getSource() << " and puts " << move.getTargetCoins()
    	    			<< " coins to heap " << move.getTarget();
    
	} 
    else {
    	out << "takes " << move.getSourceCoins() << " coins from heap "
    		<< move.getSource() << " and puts nothing";
    }
};

class State{
    public:
    //State with h heaps, where the i-th heap starts with c[i] coins.
    //A total of n players are in the game, numbered from 0 to n-1,
    //and play 0 is the first to play.

    State(int h, const int c[], int n);
    ~State();

    void next(const Move &move) throw (logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const throw (logic_error);

    int getPlayers() const;
    int getPlaying() const;

    friend ostream & operator << (ostream &out, const State &state);

    private: 
    int heaps, *heap_coins, players, playing;
};

State:: State(int h, const int c[], int n){
    players = n;
    playing = 0;
    heaps = h;
    heap_coins = new int [heaps];
    for (int i = 0; i<heaps; i++) heap_coins[i] = c[i];
};

State:: ~State(){
    delete[] heap_coins;
    return;
};

int State:: getCoins(int h) const throw(logic_error){
    if (h <0 || h >=heaps){
        throw logic_error("invalid heap number, enter a number between 1 and heaps");
        return 1;
    }
    else {
        return heap_coins[h];
    }
};

void State:: next(const Move &move) throw(logic_error) {
    if ((move.getSource() < 0) || (move.getSource() > heaps) || (move.getTarget() < 0) || (move.getTarget() > heaps)){
        throw logic_error("invalid heap");
        return;
    }
    else if ((move.getSourceCoins()<1 || move.getTargetCoins() < 0) || move.getSourceCoins() <= move.getTargetCoins() ||move.getSourceCoins() > getCoins(move.getSource())){
        throw logic_error("invalid coin number");
    }
    else {
        heap_coins[move.getSource()] -= move.getSourceCoins();
        heap_coins[move.getTarget()] += move.getTargetCoins();
        playing = (playing +1)% players;
    }
};

bool State:: winning() const {
    int s = 0;
    for (int i = 0; i<heaps; i++) s+=getCoins(i);
    return not s;
};

int State:: getHeaps() const{
    return heaps;
};

int State:: getPlayers() const{
    return players;
};

int State:: getPlaying() const{
    return playing;
};

ostream &operator<<(ostream &out, const State &state) {
   	for (int i = 0; i < state.getHeaps(); i++) {
        out << state.heap_coins[i];
    	if (i != state.getHeaps() - 1)
    	out << ", ";
    }
    
    out << " with " << state.playing << "/" << state.players << " playing next" ;
		return out;
};



