//
//  gameModel.h
//  FrogJumpingModel
//
//  Created by Hafiz on 3/29/14.
//  Copyright (c) 2014 Hafiz. All rights reserved.
//
/*
 This code is written by Hafiz K.Irshaid
 Date 12/3/2013
 Computer engineering department at Najah National University
 Artificial Intelligence
 Frog Jumping Game
 Description :
 this class contans all functions needs to the game model that will generate
 the solution and move the frog.
 */


#ifndef __FrogJumpingModel__gameModel__
#define __FrogJumpingModel__gameModel__
#include <iostream>
#include <vector.h>

using namespace std;

//program codes 
#define MAX_SOLUTION_NUMBER 50
#define LEGAL_MOVE 100  //if the move is legal
#define ILLEGAL_MOVE 101// if the move is illegal
#define FROG_NUMBER 7
#define MAX_CHILD_NUM 4
#define NULL_PTR 200
#define GF 1	//green frog
#define RF 2	//red frog
#define ES 0	//empty stone
#define SUCESS 10
#define FAIL 20
#define SOLUION 50
#define NOT_A_SOLUION 55
#define MAX_CHILD_NUM 4

/*
 * the node that holds the game node values
 */
struct Node
{
	//the parent
	Node *parent;
    
	//the current state frogs locations
	int current_state[FROG_NUMBER];
    
	//the clilds of this node, next states
	Node * childs[MAX_CHILD_NUM];
    
	//if this node is the solution this variable will hode SOLUTION, else hold NOT_A_SOLUTION
	int is_solution;
};

struct game_state_node
{
    int state[FROG_NUMBER];
};

/*
 * this class is the frog jumping game model.
 */
class frog_jumping_game_model
{
public :
	//game constructor
	frog_jumping_game_model();
    
    //game constructor
    frog_jumping_game_model(int user_mode);
    
    //this variable will hold the number of moves to solve the puzzles
    int number_of_moves_to_solve_puzzle;
    
    //this vector contains all solution states
    vector<game_state_node> solution_states;
    
    //this vector contain the solution sequance, the indexes of solution
    vector <int> solution_sequance;
    
    //this function is going to solve the puzzle and store the solution sequance in indexes_for_sollution_array
    void solve_puzzle();
    
    //this function is going to generate all possible states in the game tree
    void generate_all_states();
    
    //this method will bring the solution
    void generate_solution();
    
    //this array holds the user mode play
    int user_current_state[7];
    
    //this functions will move a frog to the given index
    int user_move_frog(int index);
    
    //this function is going to check if the user win or not
    int check_user_win();
    
    //game distructior
    ~frog_jumping_game_model();

private:
    
    //game tree root node
	Node * Root;
    
    //solution pointer to point to the solution on game tree
	Node * solution_node_ptr;
    
    //this array holds all solutions found in the tree
	Node ** game_solutions;
    
    //the number of solutions
	int number_of_solutions ;
    
    //this function will move the frog in the given state to the index i
	int move_frog(Node* state, int i);
    
    //this function will assign the child pointer to state node
	int store_node_on_state_node_child(Node * node, Node *state);
    
    //this function is auxiluary function to generate all state
	void generate_state(Node *state);
	
    //print the given node
	void print_node(Node *n);
    
    //this function will traverse all the tree to find the solution
	void search_for_solution(Node * root);
    
    //this functions will count all nodes in the tree
	void count_all_nodes(Node * nd);
    
    //this variable hold the number of nodes in the tree
	int node_counter ;
};

#endif /* defined(__FrogJumpingModel__gameModel__) */