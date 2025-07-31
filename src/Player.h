using namespace std;

class Player{
    struct Position {
        int x;
        int y;
    } position;
    public: 
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
