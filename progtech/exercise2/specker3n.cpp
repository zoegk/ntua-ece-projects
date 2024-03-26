#include <iostream>
#include <stdexcept>
using namespace std;
class Game {
public:
    Game(int heaps, int players);
    ~Game();

    void addHeap(int coins) throw(logic_error);
    void addPlayer(Player *player) throw(logic_error);
    void play(ostream &out) throw(logic_error);

    int getPlayers() const;
    const Player *getPlayer(int p) const throw(logic_error);

private:
    int game_heaps, game_players, current_heap, current_player;
    int *heap_coins;
    Player **players_list;
};

Game:: Game(int heaps, int players){
    heap_coins = new int [heaps];
    game_heaps = heaps;
    game_players = players;
    current_heap = 0;
    current_player = 0;
    players_list = new Player*[players];
}

Game:: ~Game() {
    delete[] heap_coins;
    delete[] players_list;
}

void Game:: addHeap(int coins) throw(logic_error){
    if (current_player > game_players) throw logic_error("all heaps are full with coins");
    else if (coins<0) throw logic_error("coins must be a positive number");
    else{
        heap_coins[current_heap++] = coins;
    }
}

void Game:: addPlayer(Player *player) throw(logic_error){
    if (current_player > game_players) throw logic_error("all players are added");
    else{
        players_list[current_player++] = player;
    }
}

void Game:: play(ostream &out) throw(logic_error){
    if ((current_player != game_players) && (current_heap != game_heaps)){
        throw logic_error("add all heaps and players");
    }
    else{
        int i = 0;
        State currentState(game_heaps, heap_coins, game_players);
        while(!currentState.winning()){
            out << "State: " << currentState <<endl;
            out << *players_list[i%game_players] << " " << players_list[i%game_players]->play(currentState) <<endl;
            currentState.next(players_list[i%game_players]->play(currentState));

            i++;
        }
        out << "State: " << currentState << endl;
        i--;
        out << *players_list[i%game_players] << " wins" <<endl;
    }
}

int Game:: getPlayers() const{
    return game_players;
}

const Player* Game:: getPlayer(int p) const throw(logic_error){
        if (p < 0 || p>= game_players) throw logic_error("there are not that many players");
    else{
        return players_list[p];
    }
}
