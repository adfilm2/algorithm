#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Slot {
    int id;
    int num;
    int state;
    Slot* blue_link;
    Slot* red_link;

    Slot(int id, int num, int state, Slot* blue_link, Slot* red_link) {
        this->id = id;
        this->num = num;
        this->state = state;
        this->blue_link = blue_link;
        this->red_link = red_link;
    }

    bool isBlueSlot() { return state==2; }
    bool isStartSlot() { return state==0; }
    bool isBlackSlot() { return state==1; }
    bool isEndSlot() { return state==3; }
};

struct Player {
    Slot* current;
    
    Player(Slot* start) {
        this->current = start;
    }

    int getScore() {
        return current->num;
    }
};

int moves[10];
enum SlotColor {
    START, BLACK, BLUE, END
};

struct Game {
    const int SLOTNUM = 33;
    Player* players[4];
    Slot* start;

    Game(Slot* start) {
        this->start = start;
        for(int i=0; i<4; i++) {
            players[i] = new Player(start);
        }
    }

    bool moveCheck(int move_idx, int player_idx) {
        
        if (players[player_idx]->current->isEndSlot()) return 0;

        int move_num = moves[move_idx];
        Slot* next = players[player_idx]->current;
        move_impl(move_num, &next);
        if (next->isEndSlot()) return 1;
        if (isOtherPlayerThatSlot(player_idx, next)) return 0;
        return 1;
    }

    void movePlayer(int move_idx, int player_idx) {
        int move_num = moves[move_idx];
        move_impl(move_num, &players[player_idx]->current);
    }

private:
    void move_impl(int move_num, Slot** next) {
        for (int i=0; i<move_num; i++) {
            if (i==0 && (*next)->isBlueSlot()) {
                *next = (*next)->blue_link;
            }
            else {
                *next = (*next)->red_link;
                if ((*next)->isEndSlot()) break;
            }
        }
    }

    bool isOtherPlayerThatSlot(int player, Slot* slot) {
        
        for (int i=0; i<4; i++) {
            if (i == player) continue;
            if (players[i]->current->id == slot->id) return true;
        }
        return false;
    }

};

Game* game;


void init() {
    
    Slot* end = new Slot(32,0, END, nullptr, nullptr);
    Slot* slot40 = new Slot(31,40, BLACK, nullptr, end);
    Slot* slot38 = new Slot(30,38, BLACK, nullptr, slot40);
    Slot* slot35 = new Slot(29,35, BLACK, nullptr, slot40);
    Slot* slot36 = new Slot(28,36, BLACK, nullptr, slot38);
    Slot* slot34 = new Slot(27,34, BLACK, nullptr, slot36);
    Slot* slot32 = new Slot(26,32, BLACK, nullptr, slot34);
    Slot* slot30_in = new Slot(25,30, BLACK, nullptr, slot35);
    Slot* slot25 = new Slot(24,25, BLACK, nullptr, slot30_in);
    Slot* slot26_in = new Slot(23,26, BLACK, nullptr, slot25);
    Slot* slot27 = new Slot(22,27, BLACK, nullptr, slot26_in);
    Slot* slot28_in = new Slot(21,28, BLACK, nullptr, slot27);
    Slot* slot30_out = new Slot(20,30, BLUE, slot28_in, slot32);
    Slot* slot28_out = new Slot(19,28, BLACK, nullptr, slot30_out);
    Slot* slot26_out = new Slot(18,26, BLACK, nullptr, slot28_out);
    Slot* slot24_out = new Slot(17,24, BLACK, nullptr, slot26_out);
    Slot* slot22_out = new Slot(16,22, BLACK, nullptr, slot24_out);
    Slot* slot24_in = new Slot(15,24, BLACK, nullptr, slot25);
    Slot* slot22_in = new Slot(14,22, BLACK, nullptr, slot24_in);
    Slot* slot20 = new Slot(13,20, BLUE, slot22_in, slot22_out);
    Slot* slot18 = new Slot(12,18, BLACK, nullptr, slot20);
    Slot* slot16_out = new Slot(11,16, BLACK, nullptr, slot18);
    Slot* slot14 = new Slot(10,14, BLACK, nullptr, slot16_out);
    Slot* slot12 = new Slot(9,12, BLACK, nullptr, slot14);
    Slot* slot19 = new Slot(8,19, BLACK, nullptr, slot25);
    Slot* slot16_in = new Slot(7,16, BLACK, nullptr, slot19);
    Slot* slot13 = new Slot(6,13, BLACK, nullptr, slot16_in);
    Slot* slot10 = new Slot(5,10, BLUE, slot13, slot12);
    Slot* slot8 = new Slot(4,8, BLACK, nullptr, slot10);
    Slot* slot6 = new Slot(3,6, BLACK, nullptr, slot8);
    Slot* slot4 = new Slot(2,4, BLACK, nullptr, slot6);
    Slot* slot2 = new Slot(1,2, BLACK, nullptr, slot4);
    Slot* start = new Slot(0,0, START, nullptr, slot2);

    game = new Game(start);
    for (int i=0; i<10; i++) {
        cin >> moves[i];
    }
}

void dfs(int m, int p, int accscore, int& max) {

    if (m==10) {
        if (accscore > max) {
            max = accscore;
            return ;
        }
    }
    else {

        bool canGo = game->moveCheck(m, p);
        if (!canGo) {
            return ;
        }
        else {
            
            game->movePlayer(m, p);
            accscore += game->players[p]->getScore();

            Slot* cpy_player_pos[4];
            for (int i=0; i<4; i++) {
                cpy_player_pos[i] = game->players[i]->current;
            }

            for (int i=0; i<4; i++) {
                dfs(m+1, i, accscore, max);
                for (int i=0; i<4; i++) {
                    game->players[i]->current = cpy_player_pos[i];
                }
            }
        }
    }
}

int main() {

    int max_score = 0;
    init();

    Slot* cpy_player_pos[4];
    for (int i=0; i<4; i++) {
        cpy_player_pos[i] = game->players[i]->current;
    }

    for (int p=0; p<4; p++) {
        dfs(0, p, 0, max_score);
        for (int i=0; i<4; i++) {
            game->players[i]->current = cpy_player_pos[i];
        }
    }

    printf("%d", max_score);
    return 0;
}