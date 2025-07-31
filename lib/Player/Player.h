#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

#define LINE1 142
#define LINE2 168
#define LINE3 195
#define COLUMN1 17
#define COLUMN2 70
#define COLUMN3 123
#define COLUMN4 175  // A partir daqui é para o player 2
#define COLUMN5 229
#define COLUMN6 282

class Player{
    struct Position {
        int x;
        int y;
    } position;
    public: 
        char hit_points = 100;
        Player(int xPosition, int yPosition){
            this->position.x = xPosition;
            this->position.y = yPosition;
        };  
        Position getPositionPlayer(){
            Position aux;
            aux.x = this->position.x;
            aux.y = this->position.y;
            return aux;    
        };

        void setPositionPlayer(int xPosition,int yPosition){
            this->position.x = xPosition;
            this->position.y = yPosition; 
        };
};

#endif