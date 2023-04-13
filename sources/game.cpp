#include "game.hpp"
#include "card.hpp"
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using namespace ariel;

    Game::Game(Player &playerT1,Player &playerT2): player1(playerT1), player2(playerT2)
    {
        //create new packets of 52 cards
        for(int i=1;i<=52;i++){
            //cout<<"hi";
            if(i<=13)
            {
                Card card(i,"Hearts");
                packet.push_back(card);
            }
            if(i>13&&i<=26)
            {
                Card card(i-13,"Spades");
                packet.push_back(card);
            }
             if(i>26&&i<=39)
            {
                Card card(i-26,"Clubs");
                packet.push_back(card);
            }
             if(i>39&&i<=52)
            {
                Card card(i-39,"Diamonds");
                packet.push_back(card);
            }
            
        }
        //use the shuffle function to mix the packet.
        random_device randCard;
        mt19937 rand(randCard());
        shuffle(begin(packet),end(packet),rand);
    //      for(auto it : packet)
    //     {
    //   cout<< it.getshape()<<it.getvalue()<<endl;
    //     }

        // division the packets of 52 cards to twe equal packets of 26 cards for each player.
        for (int i=1;i<=52;i++)
        {
            if (i%2==1)
            {
                packetp1.push(packet.back());
            }
            else
            {
                packetp2.push(packet.back());
            }
            packet.erase(packet.end());
        }
        player1.setsizestack(26);
        player2.setsizestack(26);
        wins1=0;
        wins2=0;
        num_turns=0;
        count_draws=0;
        log="";
        lastTurn="";
    }
    //Game::Game(){}


    void Game::playTurn(){
        if (&player1==&player2)
            throw exception();
        if(player1.stacksize()>0 && player2.stacksize()>0){
            draw_in_a_row=0;
            Card card1=packetp1.top();
            Card card2=packetp2.top();
            int valuec1= card1.getvalue();
            int valuec2=card2.getvalue();
            packetp1.pop();
            packetp2.pop();
            if(valuec1==valuec2)
            {
                //draw
                lastTurn= stringLastTurn(3,card1,card2,valuec1,valuec2);
                count_draws++;
                drawturn();
                return;
            }
            if(valuec1==1&&valuec2!=2){
                //ass vs >2
                player1.setcardstaken(player1.cardesTaken()+2) ;
                player1.setsizestack(player1.stacksize()-1);
                player2.setsizestack(player2.stacksize()-1);
                lastTurn=stringLastTurn(1,card1,card2,valuec1,valuec2);

            }else if(valuec2==1&&valuec1!=2){
                //>2 vs ass
                player2.setcardstaken(player2.cardesTaken()+2) ;
                player1.setsizestack(player1.stacksize()-1);
                player2.setsizestack(player2.stacksize()-1);
                lastTurn=stringLastTurn(2,card1,card2,valuec1,valuec2);
            }else if(valuec1>valuec2){
                   // 1>2
                player1.setcardstaken(player1.cardesTaken()+2) ;
                player1.setsizestack(player1.stacksize()-1);
                player2.setsizestack(player2.stacksize()-1);
                lastTurn=stringLastTurn(1,card1,card2,valuec1,valuec2);
            }else if(valuec1<valuec2){
                   // 1<2
                player2.setcardstaken(player2.cardesTaken()+2) ;
                player1.setsizestack(player1.stacksize()-1);
                player2.setsizestack(player2.stacksize()-1);
                lastTurn=stringLastTurn(2,card1,card2,valuec1,valuec2);
            }
            log+=lastTurn+"\n";
        }
        else
        {
            throw exception();
        }
    }
        
    

    
    void Game::printLastTurn(){cout<<lastTurn<<endl;}

    void Game::playAll(){
        while(player1.stacksize()!=0 && player2.stacksize()!=0)
        {
            playTurn();
        }
    }
    void Game::printWiner(){
        if(player1.stacksize()!=0 && player2.stacksize()!=0)
            cout<<"the game not over"<<endl;
        else
            if(player1.cardesTaken()>player2.cardesTaken())
                cout<<player1.getname()<<" won"<<endl;  
        else 
            if(player1.cardesTaken()<player2.cardesTaken())
                cout<<player2.getname()<<" won"<<endl;
            else
                cout<<"draw"<<endl;
        }
    void Game::printLog(){cout<<log;}

    void Game::printStats(){
        cout<<"the number of turns are played: "<<num_turns <<endl;
        cout<<"the win rate of "<< player1.getname()<<":"<<(wins1/num_turns)*100<<"%"<<endl;
        cout<<"the win rate of "<< player2.getname()<<":"<<(wins2/num_turns)*100<<"%"<<endl;
        cout<<"the number of cards that "<< player1.getname()<<" won is: "<<player1.cardesTaken()<<endl;
        cout<<"the number of cards that "<< player2.getname()<<" won is: "<<player2.cardesTaken()<<endl;
        cout<<"the number of draws that happand is: "<<count_draws<<endl;
        cout<<"the draw rate is: "<<(count_draws/num_turns)*100<<"%"<<endl;
    }
    
    void Game::drawturn(){
        draw_in_a_row++;
        if(player1.stacksize()==1&& player2.stacksize()==1)
            {
                player1.setsizestack(player1.stacksize()-1);
                player2.setsizestack(player2.stacksize()-1);
                player1.setcardstaken(player1.cardesTaken()+(draw_in_a_row-1)*2 +1);
                player2.setcardstaken(player2.cardesTaken()+(draw_in_a_row-1)*2 +1);
                lastTurn+=" the cards are over";
            }
        else if(player1.stacksize()==2 && player2.stacksize()==2)
            {
                player1.setsizestack(player1.stacksize()-2);
                player2.setsizestack(player2.stacksize()-2);
                packetp1.pop();
                packetp2.pop();
                player1.setcardstaken(player1.cardesTaken()+(draw_in_a_row-1)*2+2);
                player2.setcardstaken(player2.cardesTaken()+(draw_in_a_row-1)*2+2);
                lastTurn+=" the cards are over";
            }
        else {
            packetp1.pop();
            packetp2.pop();
            Card card1=packetp1.top();
            Card card2=packetp2.top();
            int valuec1=card1.getvalue();
            int valuec2=card2.getvalue();
            packetp1.pop();
            packetp2.pop();
            if(valuec1==valuec2)
            {
                //draw
                lastTurn+=stringLastTurn(3,card1,card2,valuec1,valuec2);
                drawturn();
                return; // finish the func and not add to the log more turns;
            }
            else if(valuec1==1&&valuec2!=2){
                //ass vs >2
                player1.setcardstaken(player1.cardesTaken()+(draw_in_a_row)*4+2);
                player1.setsizestack(player1.stacksize()-((2*draw_in_a_row)+1)) ;
                player2.setsizestack(player2.stacksize()-((2*draw_in_a_row)+1)) ;
                lastTurn+=stringLastTurn(1,card1,card2,valuec1,valuec2);
            }else if(valuec2==1&&valuec1!=2){
                //>2 vs ass
                player2.setcardstaken(player2.cardesTaken()+(draw_in_a_row)*4+2);
                player1.setsizestack(player1.stacksize()-((2*draw_in_a_row)+1)) ;
                player2.setsizestack(player2.stacksize()-((2*draw_in_a_row)+1)) ;
                lastTurn+=stringLastTurn(2,card1,card2,valuec1,valuec2);   
            }else if(valuec1>valuec2){
                   // 1>2
                player1.setcardstaken(player1.cardesTaken()+(draw_in_a_row)*4+2);
                player1.setsizestack(player1.stacksize()-((2*draw_in_a_row)+1)) ;
                player2.setsizestack(player2.stacksize()-((2*draw_in_a_row)+1)) ;
                lastTurn+=stringLastTurn(1,card1,card2,valuec1,valuec2);
            }else if(valuec1<valuec2){
                   // 1<2
                player2.setcardstaken(player2.cardesTaken()+(draw_in_a_row)*4+2);
                player1.setsizestack(player1.stacksize()-((2*draw_in_a_row)+1)) ;
                player2.setsizestack(player2.stacksize()-((2*draw_in_a_row)+1)) ;
                lastTurn+=stringLastTurn(2,card1,card2,valuec1,valuec2);
            }
            log=log+lastTurn+"\n"; // add the turn to the log
            
        }
        
    }
    string Game::valuec(int index){
        if (index==1)
            return "Ace";
        if(index<11)
            return to_string(index);
        if(index==11)
            return "Jack";
        if(index==12)
            return "Queen";
        if(index==13)
            return "King";
        else
            return "";
    }
    string Game::stringLastTurn(int index,Card card_1,Card card_2,int val1,int val2)
    {
        if(index==1){
            num_turns++;
            wins1++;
            return (player1.getname()+" played "+valuec(val1)+" of "+ 
                card_1.getshape()+" "+player2.getname()+" played "+valuec(val2)+" of "+ 
                card_2.getshape()+". "+player1.getname()+" wins.");}
        if(index==2){
            num_turns++;
            wins2++;
            return (player1.getname()+" played "+valuec(val1)+" of "+ 
                card_1.getshape()+" "+player2.getname()+" played "+valuec(val2)+" of "+ 
                card_2.getshape()+". "+player2.getname()+" wins.");
        }
        if(index==3){
                return (player1.getname()+" played "+valuec(val1)+" of "+ 
                card_1.getshape()+" "+player2.getname()+" played "+valuec(val2)+" of "+ 
                card_2.getshape()+". Draw.");}
        else
            return "";

    }

    



   
