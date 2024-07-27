//FILE 1
#include <iostream>
using namespace std;

//#define NULL 0 ///delete it


struct card{
    int value;
    struct card *next;
};

int CardInfo[4][13]; //contain which card is throw and which is not, card not thrown: 1, card thrown: 0

int CardArray[4][13]={
{114, 113, 112, 111, 110, 19, 18, 17, 16, 15, 14, 13, 12},
{214, 213, 212, 211, 210, 29, 28, 27, 26, 25, 24, 23, 22},
{314, 313, 312, 311, 310, 39, 38, 37, 36, 35, 34, 33, 32},
{414, 413, 412, 411, 410, 49, 48, 47, 46, 45, 44, 43, 42}};

struct card *CardList=NULL;
struct card *Players = NULL;

int Won[4]; 
int Board[6]; //all initialized with -1, board[0] will have first player id, board[5] will have player id having heighest
             //card and board[1], board[2], board[3] & board[4] will have card thrown by respective player
             //here index is the id of player
    
//FILE 2
//TESTED


class player{
    public:
    int playerid;//1, 2, 3 and 4
    card * Cards[4]; //spades diamond clubs hearts 1 2 3 4 //in decending order form left to rignt
    int availableCard[4]; //to number of cards available for respective set

    player(){
        for(int i=0; i<4; i++){
            Cards[i] = NULL;
            availableCard[i]=0;
        }
    }
}p[4];

//FILE 3
#include <cstdlib>
#include <ctime>

//cardSetValue = originalThrownCard
//temproray functions

int size(struct card *ptr){
    struct card *temp = ptr;
    int size=0;
    while(temp){
        size++;
        temp = temp->next;
    }
    return size;
}

void print(struct card *ptr){
    struct card *temp = ptr;
    while(temp){
        cout<<temp->value<<' ';
        temp = temp->next;
    }
    cout<<endl;
}




//temproray functions



int func6(player &p, int cardSetValue){ //throw maximum card
    cout<<"func6 ";
    struct card *ptr = p.Cards[cardSetValue-1];
    int cardValue = ptr->value;
    p.Cards[cardSetValue-1] = ptr->next;
    delete ptr;
    int x=(cardValue<100) ? cardValue/10 : cardValue/100 ,
    y=(cardValue<100) ? cardValue%10 : cardValue%100 ;
    CardInfo[x-1][14-y]=0;
    //cardValue = (cardValue<100) ? cardValue%10 : cardValue%100 ;
    p.availableCard[cardSetValue-1]-=1;
    return cardValue;
}

int func5(player &p, int cardSetValue){  //throw minimum card
    cout<<"func5 ";
    int cardValue;
    struct card *ptr = p.Cards[cardSetValue-1];
    if(ptr->next == NULL){
        cardValue = ptr->value;
        delete ptr;
        p.Cards[cardSetValue-1] = NULL;
    }
    else{
        while(ptr->next->next!=NULL) ptr = ptr->next;
        cardValue = ptr->next->value;
        struct card *tempptr = ptr->next;
        ptr->next = NULL;
        delete tempptr;
    }
    int x=(cardValue<100) ? cardValue/10 : cardValue/100 ,
    y=(cardValue<100) ? cardValue%10 : cardValue%100 ;
    CardInfo[x-1][14-y]=0;
    //cardValue = (cardValue<100) ? cardValue%10 : cardValue%100 ;
    p.availableCard[cardSetValue-1]-=1;
    return cardValue;
}

int func4(player &p, int cardSetValue){ //do you have card maximum to current maximum card
    cout<<"func4 ";
    int current_heighest_card, i=0;
    while(CardInfo[cardSetValue-1][i]==0  &&  i<12) i++;
    current_heighest_card = 14-i;
    int HighstCard = p.Cards[cardSetValue-1]->value;
    HighstCard = (HighstCard<100) ? HighstCard%10 : HighstCard%100 ;

    if(current_heighest_card <= HighstCard) return func6(p, cardSetValue);
    else return func5(p, cardSetValue);
}

int func3(player &p, int cardSetValue){  //throw the minimum of cards which is maximum in number
    cout<<"func3 ";
    int maxNoofCard=p.availableCard[0], maxIndex=0;
    int cardValue;
    for(int i=0; i<4; i++){
        if(p.availableCard[i] > maxNoofCard){
            maxNoofCard = p.availableCard[i];
            maxIndex=i;
        }
    }

    struct card *ptr = p.Cards[maxIndex];
    if(ptr->next == NULL){
        cardValue = ptr->value;
        delete ptr;
        p.Cards[maxIndex] = NULL;
    }
    else{
        while(ptr->next->next!=NULL) ptr = ptr->next;
        cardValue = ptr->next->value;
        struct card *tempptr = ptr->next;
        ptr->next = NULL;
        delete tempptr;
    }
    
    int x=(cardValue<100) ? cardValue/10 : cardValue/100 ,
    y=(cardValue<100) ? cardValue%10 : cardValue%100 ;
    CardInfo[x-1][14-y]=0;
    p.availableCard[x-1]-=1;
    //cardValue = (cardValue<100) ? cardValue%10 : cardValue%100 ;
    return cardValue;
}

int func2(player &p, int cardSetValue){  //do you have original thrown card
    cout<<"func2 ";
    if(p.availableCard[cardSetValue-1] > 0) return func4(p, cardSetValue);
    else return func3(p, cardSetValue);
}

int func7(player &p){ //check which cardset has cards highest than curren highest card
    cout<<"func7 ";
    int maxCardSetValue=-1;
    for(int i=0; i<4; i++){
        if(p.availableCard[i] == 0) continue;
        int j=0;
        while(CardInfo[i][j]==0 && j<13) j++;
        int maxCard = p.Cards[i]->value;
        //cout<<maxCard<<' '<<j<<' ';
        maxCard = (maxCard<100) ? maxCard%10: maxCard%100;
        if (maxCard >= (14-j)) {
            maxCardSetValue = i+1;
            break;
        }
    }
    if(maxCardSetValue == -1) return func3(p, maxCardSetValue);
    else return func6(p, maxCardSetValue);
}

int func1(player &p, int Board[]){  //TOP MOST FUNCTION
    cout<<"func1 ";
    int cardSetValue = Board[Board[0]];
    cardSetValue = (cardSetValue<100) ? cardSetValue/10 : cardSetValue/100;
    if(Board[0] == -1) return func7(p);
    else return func2(p, cardSetValue);
}


void fillPlayers(){  //fills player in Players Linked list
    Players = new card;
    struct card *player2 = new card;
    struct card *player3 = new card;
    struct card *player4 = new card;
    Players->value = 1; 
    Players->next = player2;
    player2->value = 2; 
    player2->next = player3;
    player3->value = 3; 
    player3->next = player4;
    player4->value = 4; 
    player4->next = Players;
}

int nextPlayer(int wonPlayer){  //return next player
    if(wonPlayer == -1){
        int temp = Players->value;
        Players = Players->next;
        return temp;
    }
    else{
        struct card *ptr = Players;
        while(Players->value != wonPlayer) Players = Players->next;
        int temp = Players->value;
        Players = Players->next;
        return temp;
    }
}

void fillCardsInLL(){ //fill all the cards in CardList ie all 52 cards
    struct card *ptr = CardList;
    for(int i=0; i<4; i++){
        for(int j=0; j<13; j++){
            if(ptr==NULL){
                ptr=new card;
                CardList = ptr;
            }
            else{
                ptr->next = new card;
                ptr = ptr->next;
            }
            ptr->value = CardArray[i][j];
        }
    }
    if(ptr!=NULL)
        ptr->next = NULL;
}

void addNode(player &p, int cardSetnValue){  //add a new node in the linked list of cards of given set of given player and fill its value
    int cardSet = (cardSetnValue<100) ? cardSetnValue/10 : cardSetnValue/100;
    struct card *newNode = new card;
    newNode->next = NULL; newNode->value = cardSetnValue;
    struct card *ptr = p.Cards[cardSet-1];
    if(ptr==NULL){
        p.Cards[cardSet-1] = newNode;
    }
    else{
        while(ptr->next!=NULL) ptr = ptr->next;
        ptr->next = newNode;
    }
}

void showCards(){
    for(int i=0; i<4; i++) cout<<Won[i]<<' ';
    cout<<endl<<endl;
    for(int i=0; i<13; i++){
        for(int j=0; j<4; j++){
            cout<<CardInfo[j][i]<<' ';
        }
        cout<<endl;
    }
    for(int i=0; i<4; i++){
        cout<<"P"<<i+1<<endl;
        for(int j=0; j<4; j++){
            struct card *ptr = p[i].Cards[j];
            while(ptr) {
                cout<<ptr->value<<' ';
                ptr = ptr->next;
            }
            cout<<' '<<p[i].availableCard[j]<<endl;
        }
        cout<<endl;
    }
}

void distribute(){  //distribute card randomly among all four players
    srand(static_cast<unsigned>(time(0)));
    for(int i=0; i<52;){
        for(int j=0; j<4 && i<52; j++){
            int random_number = rand() % (52-i);
            struct card *ptr = CardList;
            int temp;
            if(random_number == 0){
                addNode(p[j], CardList->value);
                temp = CardList->value;
                CardList = CardList->next;
                delete(ptr);
            }
            else{
                random_number-=1;
                while(random_number>0) {
                    ptr = ptr->next;
                    random_number--;
                }
                addNode(p[j], ptr->next->value);
                temp = ptr->next->value;
                struct card *tempptr = ptr->next;
                ptr->next = ptr->next->next;
                delete(tempptr);

            }
            temp = temp<100 ? temp/10 : temp/100;
            p[j].availableCard[temp-1] +=1 ;
            i++;
        }
    }
    
    
    // cout<<"SUCCESSFUL";
}

void sortCards(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            struct card *start = p[i].Cards[j];
            if(start==NULL || start->next==NULL) continue;
            int swapped;
            struct card *ptr1;
            do {
                swapped = 0;
                ptr1 = start;
                while (ptr1->next != NULL) {
                    if (ptr1->value < ptr1->next->value) { 
                        int temp = ptr1->value;
                        ptr1->value = ptr1->next->value;
                        ptr1->next->value = temp;
                        swapped = 1;
                    }
                    ptr1 = ptr1->next;
                }
            }
            while (swapped);
        }
    }
}

void initialize(){
    for(int i=0; i<4; i++){
        for(int j=0; j<13; j++){
            CardInfo[i][j]=1;
        }
    }
    fillPlayers();
    fillCardsInLL();
    distribute();
    sortCards();
    //showCards();
}


//FILE 4

void control(){
    int N=13;
    while(N){
        cout<<N<<endl;
        //showCards();
        N--;
        for(int i=0; i<6; i++) Board[i]=-1;
        int nextPlyr=nextPlayer(-1);
        int cardThrown=func1(p[nextPlyr-1], Board);
        Board[0]=nextPlyr;
        Board[nextPlyr]=cardThrown;
        Board[5]=nextPlyr;
        // for(int i=0; i<6; i++) cout<<Board[i]<<' '; cout<<' ';/////////////delete
        // for(int i=0; i<4; i++) cout<<p[Board[0]-1].availableCard[i]<<' ';
        //     cout<<endl;
        int OriginalSet = Board[Board[5]]<100 ? Board[Board[5]]/10 : Board[Board[5]]/100;


        for(int i=0; i<3; i++){
            int j = nextPlayer(-1);
            Board[j]=func1(p[j-1], Board);
            int CardValue = Board[j];
            int CardSet = CardValue<100 ? CardValue/10 : CardValue/100;
            if(CardSet == OriginalSet){
                if(CardValue > Board[Board[5]]){
                    Board[5] = j;
                }
            }
            // for(int i=0; i<6; i++) cout<<Board[i]<<' ';cout<<' ';/////////////delete
            // for(int i=0; i<4; i++) cout<<p[j-1].availableCard[i]<<' ';
            // cout<<endl;
        }

        int plyr = Board[5];
        Won[--plyr]+=1;
        nextPlayer(Board[5]);
    }
    cout<<endl;
    for(int i=0; i<4; i++) cout<<Won[i]<<' ';
}

int main(){
    initialize();
    showCards();
    // for(int i=0; i<6; i++) Board[i]=-1;
    // cout<<func1(p[1], Board)<<endl;
    // showCards();
    control();
}
