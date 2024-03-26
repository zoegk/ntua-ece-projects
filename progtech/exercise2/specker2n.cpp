using namespace std;  
  
class Player {
public:
    Player(const string &n);
    virtual ~Player();
    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player);

protected:
    string player_name;
};

class GreedyPlayer : public Player {
public:
    GreedyPlayer(const string &n) : Player(n){
        player_type = "Greedy";
    }
    virtual const string&getType() const override{
        return player_type;
    }
    virtual Move play(const State &s) override {
        int source_heap = 0;
        int source_coins = 0;
        for (int i=0; i<s.getHeaps(); i++){
            if (s.getCoins(i) > source_coins){
                source_heap = i;
                source_coins = s.getCoins(i);
            }
        }
        Move GreedyObject(source_heap, source_coins, 0, 0);
        return GreedyObject;
    }
private:
string player_type;
};

class SpartanPlayer : public Player {
    public:
    SpartanPlayer(const string &n) : Player(n) {
        player_type = "Spartan";
    }
    virtual const string &getType() const override{
        return player_type;
    }
    virtual Move play(const State &s) override{
        int source_heap = 0;
        int source_coins = 0;
        for (int i=0; i<s.getHeaps(); i++){
            if (s.getCoins(i) > source_coins) {
                source_heap = i;
                source_coins = s.getCoins(i);
            }
        }
        Move SpartanObject(source_heap, 1, 0, 0);
        return SpartanObject;
    }
    private:
    string player_type;
};

class SneakyPlayer : public Player {
    public:
    SneakyPlayer(const string &n) : Player(n){
        player_type = "Sneaky";
    }
    virtual const string &getType() const override{
        return player_type;
    }
    virtual Move play(const State &s) override{
        int j = 0;
        while (s.getCoins(j) == 0) j++;
        int source_heap = j;
        int source_coins = s.getCoins(j);
        for (int i=j+1; i<s.getHeaps(); i++) {
            if ((s.getCoins(i) < source_coins) && (s.getCoins(i) > 0)){
                source_heap = i;
                source_coins = s.getCoins(i);
            }
        }
        Move SneakyObject(source_heap, source_coins, 0, 0);
        return SneakyObject;
    }
    private:
    string player_type;
};

class RighteousPlayer : public Player {
    public:
    RighteousPlayer(const string &n) : Player(n){
        player_type = "Righteous";
    }
    virtual const string &getType() const override{
        return player_type;
    }
    virtual Move play(const State &s) override{
        int target_heap = 0;
		int source_heap = 0;
		int source_coins = s.getCoins(0);
		int target_coins = source_coins;

		for (int i = 1; i < s.getHeaps(); i++) {
			if (s.getCoins(i) > source_coins) {
				source_heap = i;
				source_coins = s.getCoins(i);
			} else if (s.getCoins(i) < target_coins) {
				target_heap = i;
				target_coins = s.getCoins(i);
			}
		}
        source_coins -= source_coins / 2;
		Move RighteousObject(
			source_heap, source_coins, target_heap, source_coins - 1);
		return RighteousObject;
    }
    private:
    string player_type;
};

Player::Player(const string &n){
    player_name = n;
};

Player:: ~Player(){
    player_name.clear();
};

ostream &operator<<(ostream &out, const Player &player){
    out << player.getType() << " player " << player.player_name;
    return out;
};
