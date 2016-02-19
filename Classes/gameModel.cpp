//
//  gameModel.cpp
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
#include "gameModel.h"

//this array is the solution of the puzzle 
int solution_array[7] = {RF,RF,RF,ES,GF,GF,GF};

//this function is going to init the node
Node * create_node()
{
	Node *n;
	n = new Node;
	n->parent = NULL;
	n->is_solution = NOT_A_SOLUION;
	
    for(int i = 0; i < MAX_CHILD_NUM; i++)
	{
		n->childs[i] = NULL;
	}
    
	return n;
}

//this constructor for user want to play the game
frog_jumping_game_model::frog_jumping_game_model(int user_mode)
{
    user_current_state [0]= ES;
}


int frog_jumping_game_model::user_move_frog(int index)
{
    //if the index is larger then the range return illegal move
    if(index > FROG_NUMBER || index < 0)
    {
        return ILLEGAL_MOVE;
    }
    
    //if the cuurent frog is green frog
    if(user_current_state[index] == GF)
    {
        //check the right hand side frog if empty strone then you can move
        if((user_current_state[index + 1] == ES ) && (index + 1 <= 6))
        {
            //change it in user_current_state_array
            swap(user_current_state[index],user_current_state[index + 1]);
            
            //return the index to the controller
            return index + 1;
        }
        else if((user_current_state[index + 2] == ES)&& (index + 2 <= 6))
        {
            //change it in user_current_state_array
            swap(user_current_state[index],user_current_state[index + 2]);
            
            return index + 2;
        }
        else
        {
            return ILLEGAL_MOVE;
        }
    }
    
    //if this frog is red frog 
    else if(user_current_state[index] == RF)
    {
        if((user_current_state[index - 1] == ES) && (index - 1 >= 0))
        {
            //change it in user_current_state_array
            swap(user_current_state[index],user_current_state[index - 1]);
            
            return index - 1;
        }
        else if((user_current_state[index - 2] == ES) && (index - 2 >= 0))
        {
            //change it in user_current_state_array
            swap(user_current_state[index],user_current_state[index - 2]);
            
            return index - 2;
        }
        else
        {
            return ILLEGAL_MOVE;
        }
    }
    else
    {
        return ILLEGAL_MOVE;
    }
}

//this user is going to check if the user win the game or not
int frog_jumping_game_model::check_user_win()
{
    int user_win = FAIL;
    for(int i = 0; i < FROG_NUMBER; i++)
    {
        if(this->user_current_state[i] == solution_array[i])
        {
            user_win = SUCESS;
            
        }
        else
        {
            user_win = FAIL;
            break;
        }
    }
    
    if(user_win == SUCESS)
    {
        return SUCESS;
    }
    else
    {
        return FAIL;
    }
}

//game constructor
frog_jumping_game_model::frog_jumping_game_model()
{
    //init user frog array
    int currnt [FROG_NUMBER] = {GF,GF,GF,ES,RF,RF,RF};
    
    for(int i = 0; i < FROG_NUMBER ;i++)
    {
        user_current_state [i] = currnt[i];
    }
}

//this function is going to solve the puzzle
void frog_jumping_game_model::solve_puzzle()
{
    game_solutions = (Node **) malloc(sizeof(Node *) * MAX_SOLUTION_NUMBER);
    
    number_of_solutions = 0;
    
    Root = create_node();
    
    int currnt [FROG_NUMBER] = {GF,GF,GF,ES,RF,RF,RF};
   
    for(int i = 0; i < FROG_NUMBER; i++)
    {
        Root->current_state[i] = currnt[i];
    }
    
    //generate solution tree
    generate_all_states();
    
    //find the solution
    generate_solution();
    
//    for(int i = 0; i < number_of_solutions; i++)
    {
        cout<<"***************************"<<endl;
        
        Node *ptr;
        ptr = game_solutions[0];
        
        while(ptr != NULL)
        {
            
            //stroe the current state in ptr pointer to the game state node
            game_state_node current_state;
            for(int i = 0; i < FROG_NUMBER; i++)
            {
                current_state.state[i] =  ptr->current_state[i];
            }
            
            //add current state node to the vector
            this->solution_states.push_back(current_state);
            
            //print the node
            print_node(ptr);
            
            //go to the parent
            ptr = ptr->parent;
        }
        
        cout<<endl;
    }
    
    
    //now generate indexes from the inexes array solution vector
    for(int i = 0; i < this->solution_states.size() - 1; i++)
    {
        int next_index = NULL_PTR;
        
        //game_state_node current_state = this->solution_states[i];
        game_state_node next_state = this->solution_states[i + 1];
        
        
        for(int i = 0 ; i < FROG_NUMBER; i++)
        {
            if(next_state.state[i] == ES)
            {
                next_index = i;
                break;
            }
        }
        
        if(next_index != NULL_PTR)
        {
            //add it to the vector
            this->solution_sequance.push_back(next_index);
        }
    }
    
    
    //print the solutuoin
    for(int i = 0; i < solution_sequance.size(); i++)
    {
        cout<<solution_sequance[i]<<endl;
    }
    
    this->count_all_nodes(this->Root);
    
    cout<<"Number of nodes in the tree is "<<this->node_counter<<endl;
}

//this function is going to generate the solutions of the game
void frog_jumping_game_model::generate_solution()
{
    search_for_solution(this->Root);
}

//this function is going to move the frog
int frog_jumping_game_model::move_frog(Node* state, int i)
{
	//if the state is NULL this may cause an error in the program so return
	if((state == NULL)||(i > 7)||(i < 0))
	{
		return NULL_PTR;
	}
    
	int move_flag = ILLEGAL_MOVE;
    
	//can jump or move to left only
	if(state->current_state[i] == RF)
	{
		//now check if the index zero because the frog cannot jump there
		if(i == 0)
		{
			move_flag = ILLEGAL_MOVE;
		}
		if((state->current_state[i - 1] == ES)&&(i - 1 >= 0))
		{
			//you can move
			int temp = state->current_state[i];
			state->current_state[i] = state->current_state[i - 1];
			state->current_state[i - 1] = temp;
			move_flag = LEGAL_MOVE;
		}
		else if((state->current_state[i - 2] == ES) &&(i - 2 >= 0))
		{
			//you can jump
			int temp = state->current_state[i];
			state->current_state[i] = state->current_state[i - 2];
			state->current_state[i - 2] = temp;
			move_flag = LEGAL_MOVE;
		}
	}
	//can jump or move to right only
	else if(state->current_state[i] == GF)
	{
		//now check if the index FROG_NUMBER - 1 because the frog cannot jump there
		if(i == FROG_NUMBER - 1)
		{
			move_flag = ILLEGAL_MOVE;
		}
		if((state->current_state[i + 1] == ES)&&(i + 1 <= (FROG_NUMBER - 1)))
		{
			//you can move
			int temp = state->current_state[i];
			state->current_state[i] = state->current_state[i + 1];
			state->current_state[i + 1] = temp;
			move_flag = LEGAL_MOVE;
		}
		else if((state->current_state[i + 2] == ES)&&(i + 2 <= (FROG_NUMBER - 1)))
		{
			//you can jump
			int temp = state->current_state[i];
			state->current_state[i] = state->current_state[i + 2];
			state->current_state[i + 2] = temp;
			move_flag = LEGAL_MOVE;
		}
	}
    
	//if the index is empty stone, do not jump
	else if(state->current_state[i] == ES)
	{
		move_flag = ILLEGAL_MOVE;
	}
	return move_flag;
}

//this function is going to store the Node 'node' on the child node of the node 'state'
int frog_jumping_game_model::store_node_on_state_node_child(Node * node, Node *state)
{
    
	//find the available child index and store on it
	int child_node_index = 0;
	for(int i = 0; i < MAX_CHILD_NUM; i++)
	{
		if(state->childs[i] == NULL)
		{
			break;
		}
		child_node_index++;
	}
    
	//now we have the child index
    
	state->childs[child_node_index] = node;
	node->parent = state;
    
	//return that index
	return child_node_index;
}

void frog_jumping_game_model::generate_state(Node *state)
{
	//if this node is null return
	if(state == NULL)
	{
		return;
	}
    
	int win_flag = SOLUION;
    
	//  check if this node is a solution
	for(int i = 0; i < MAX_CHILD_NUM; i++)
	{
		if(state->current_state[i] != solution_array[i])
		{
			win_flag = NOT_A_SOLUION;
			break;
		}
	}
    
	//if this node is the solution, mark it and return
	if(win_flag == SOLUION)
	{
		state->is_solution = SOLUION;
		return ;
	}
    
	//fisrt of all, find empty stoen index to decide how many legal move we can move
	int empty_stone_index = 0;
	for(int i = 0; i < FROG_NUMBER; i++)
	{
		if(state->current_state[i] == ES)
		{
			empty_stone_index = i;
			break;
		}
	}
    
	//check all possible moves
	if(empty_stone_index == (FROG_NUMBER - 1))
	{
		//we have one move and one jump
		Node * move_node ;
		move_node = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			move_node->current_state [i] = state->current_state [i];
		}
        
		//note that at this index, we have one move and one jump, we need to move fisrt then check if it legal
		//or not, if if legal move, then you can connect it to the state(make the state it's parent;
        
		int legal_or_illegal_move_check_variable = ILLEGAL_MOVE;
        
		//now move to left
		legal_or_illegal_move_check_variable = move_frog(move_node, (FROG_NUMBER - 1) - 1);
        
		//now we can connect it to the parnnt
		if(legal_or_illegal_move_check_variable == LEGAL_MOVE)
		{
			//find the index of the fisrt available child of the node
			store_node_on_state_node_child(move_node, state);
            
			//call the function recursivelly
			generate_state(move_node);
		}
        
		//the same thing must be here, but this time jump
        
		Node * jump_node;
		jump_node = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			jump_node->current_state [i] = state->current_state[i];
		}
        
		int legal_or_illegal_jump_check_variable = ILLEGAL_MOVE;
        
		//now move to left
		legal_or_illegal_jump_check_variable = move_frog(jump_node, (FROG_NUMBER - 1) - 2);
        
		if(legal_or_illegal_jump_check_variable == LEGAL_MOVE)
		{
			store_node_on_state_node_child(jump_node, state);
            
			//call the function recussively
			generate_state(jump_node);
		}
	}
	else if(empty_stone_index == 0)
	{
		//we have one move and one jump
		Node * move_node ;
		move_node = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			move_node->current_state [i] = state->current_state [i];
		}
        
		//note that at this index, we have one move and one jump, we need to move fisrt then check if it legal
		//or not, if if legal move, then you can connect it to the state(make the state it's parent;
        
		int legal_or_illegal_move_check_variable = ILLEGAL_MOVE;
        
		//now move to left
		legal_or_illegal_move_check_variable = move_frog(move_node, 1);
        
		//now we can connect it to the parnnt
		if(legal_or_illegal_move_check_variable == LEGAL_MOVE)
		{
			//find the index of the fisrt available child of the node
			store_node_on_state_node_child(move_node, state);
            
			//call the function recursivelly
			generate_state(move_node);
		}
        
		//the same thing must be here, but this time jump
        
		Node * jump_node;
		jump_node = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			jump_node->current_state [i] = state->current_state[i];
		}
        
		int legal_or_illegal_jump_check_variable = ILLEGAL_MOVE;
        
		//now move to left
		legal_or_illegal_jump_check_variable = move_frog(jump_node, 2);
        
		if(legal_or_illegal_jump_check_variable == LEGAL_MOVE)
		{
			store_node_on_state_node_child(jump_node, state);
            
			//call the function recussively
			generate_state(jump_node);
		}
        
	}
	else
	{
		Node * first_move;
		first_move = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			first_move->current_state [i] = state->current_state[i];
		}
        
		int legal_or_illegal_move_flag = ILLEGAL_MOVE;
		legal_or_illegal_move_flag = move_frog(first_move, empty_stone_index - 1);
        
		if(legal_or_illegal_move_flag == LEGAL_MOVE)
		{
			store_node_on_state_node_child(first_move, state);
            
			generate_state(first_move);
		}
		else
		{
			//free(fisrt_move);
		}
        
        
		Node * second_move;
		second_move = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			second_move->current_state [i] = state->current_state[i];
		}
        
		legal_or_illegal_move_flag = ILLEGAL_MOVE;
		legal_or_illegal_move_flag = move_frog(second_move, empty_stone_index + 1);
        
		if(legal_or_illegal_move_flag == LEGAL_MOVE)
		{
			store_node_on_state_node_child(second_move, state);
            
			generate_state(second_move);
		}
        
		Node * fisrt_jump;
		fisrt_jump = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			fisrt_jump->current_state [i] = state->current_state[i];
		}
        
		legal_or_illegal_move_flag = ILLEGAL_MOVE;
		legal_or_illegal_move_flag = move_frog(fisrt_jump, empty_stone_index - 2);
        
		if(legal_or_illegal_move_flag == LEGAL_MOVE)
		{
			store_node_on_state_node_child(fisrt_jump, state);
            
			generate_state(fisrt_jump);
		}
        
		Node * second_jump;
		second_jump = create_node();
        
		//copy all frogs from the above state to the new state then make the move
		for(int i = 0; i < FROG_NUMBER; i++)
		{
			second_jump->current_state [i] = state->current_state[i];
		}
        
		legal_or_illegal_move_flag = ILLEGAL_MOVE;
		legal_or_illegal_move_flag = move_frog(second_jump, empty_stone_index + 2);
        
		if(legal_or_illegal_move_flag == LEGAL_MOVE)
		{
			store_node_on_state_node_child(second_jump, state);
            
			generate_state(second_jump);
		}
        
		//we have two moves and two jumps
		return;
	}
}

//this function is gonna generate a solution of the puzzle
void frog_jumping_game_model::generate_all_states()
{
	generate_state(Root);
}

void frog_jumping_game_model::print_node(Node *n)
{
	if(n == NULL)
	{
		cout<<"NULL"<<endl;
		return;
	}
    
	//print the node
	for(int i = 0; i <FROG_NUMBER; i++)
	{
        if(n->current_state[i] == ES)
        {
            cout<<"ES ";
        }
        else if(n->current_state[i] == GF)
        {
            cout<<"GF ";
        }
        else if(n->current_state[i] == RF)
        {
            cout<<"RF ";
        }
        
    }
    cout<<endl;
}

//this function is going to search for the solutions on the game tree
void frog_jumping_game_model::search_for_solution(Node * root)
{
	if(root == NULL)
	{
		return;
	}
    
	//print if it a good node or not
    /*
	int count_red_frog = 0;
	int count_green_frog = 0;
	int count_empty_stone = 0;
    
	for(int i = 0; i < FROG_NUMBER; i++)
	{
		if(root->current_state[i] == GF)
		{
			count_green_frog++;
		}
		else if(root->current_state[i] == ES)
		{
			count_empty_stone++;
		}
		else if(root->current_state[i] == RF)
		{
			count_red_frog++;
		}
	}
    
	if(count_empty_stone == 1 && count_green_frog == 3 && count_red_frog == 3)
	{
        int win_flag = SOLUION;
        for(int i = 0; i < FROG_NUMBER; i++)
        {
            if(root->current_state[i] != solution_array[i])
            {
			win_flag = NOT_A_SOLUION;
			break;
            
		}
	}
    
	if(win_flag == SOLUION)
	{
		game_solutions[number_of_solutions++] = root;
	}
     }
*/
    if(root->is_solution == SOLUION)
    {
        game_solutions[number_of_solutions++] = root;   
    }

	search_for_solution(root->childs[0]);
	search_for_solution(root->childs[1]);
	search_for_solution(root->childs[2]);
	search_for_solution(root->childs[3]);
}


//this function si going to count all nodes in the game tree
void frog_jumping_game_model::count_all_nodes(Node * nd)
{
	if(nd == NULL)
	{
		return;
	}
	
    node_counter++;
    
	count_all_nodes(nd->childs[0]);
	count_all_nodes(nd->childs[1]);
	count_all_nodes(nd->childs[2]);
	count_all_nodes(nd->childs[3]);
}

//game destructor , you have to deallocate all memory locations that you have reserved them 
frog_jumping_game_model::~frog_jumping_game_model()
{
    
}