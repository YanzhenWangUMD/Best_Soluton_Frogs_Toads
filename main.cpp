
/*
 
Created by : Yanzhen Wang
Created at : 5/5/2017
 
Description: This program is to examine the effectiveness of the A* search algorithm compared to that of Branch&Bound search
             and to slove the Frogs and Toads puzzle.



*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

vector<string> initialList_2()// intialize the 2X2 games
{
    vector<string> temp;
    
    temp.push_back("F");
    temp.push_back("F");
    temp.push_back(" ");
    temp.push_back("T");
    temp.push_back("T");
    return temp;
}

vector<string> initialList_3() // intialize the 3X3 games
{
    vector<string> temp;
    
    temp.push_back("F");
    temp.push_back("F");
    temp.push_back("F");
    temp.push_back(" ");
    temp.push_back("T");
    temp.push_back("T");
    temp.push_back("T");
    return temp;
}

void swap (vector<string> &temp,int x, int y) // simply swap two element of the vector
{
    string temp1;
    temp1 = temp[x];
    temp[x]= temp[y];
    temp[y] = temp1;
}

void move_right(vector<string> &temp, int& gap) // move right by swaping the gap position and either can be frog or toad in the positon-1
{
    swap(temp,gap,(gap-1));
    gap--;
}

void move_left(vector<string> &temp , int &gap) // move left by swaping the gap position and either can be frog or toad in the positon+1
{
    swap(temp,gap,(gap+1));
    gap++;
}

void jump_right(vector<string>& temp , int &gap)// jump right by swaping the gap position and either can be frog or toad in the positon-2
{
    swap(temp,gap,(gap-2));
    gap = gap-2;
}
void jump_left(vector<string> &temp , int & gap)// jump left by swaping the gap position and either can be frog or toad in the positon+2
{
    swap(temp,gap,(gap+2));
    gap = gap+2;
}

bool moveable_right(vector<string> &temp , int gap) // check if the position is moveable to right
{
    if(gap==0)
        return false;
    return true;
}
bool moveable_left(vector<string> &temp , int gap)// check if the position is moveable to left
{
    unsigned long int length= temp.size();
    if(gap==(length-1))
        return false;
    return true;
}
bool can_jump_right(vector<string> &temp , int gap)// check if the position is moveable to jump right
{
    if(gap <=1 || temp[gap-1] ==temp[gap-2]) // second condition is to make sure that
        return false;
    return true;
}
bool can_jump_left(vector<string> &temp , int gap)// check if the position is moveable to jump left
{
    unsigned long int length= temp.size();
    if(gap >= (length-2)|| temp[gap+1] ==temp[gap+2])
        return false;
    return true;
}

struct State_data {
    int underestimate = 0;// how many frogs/toads are not in place
    int distance_travelled = 1; // how much steps has it travelled
    int total_path = 0; // total path equal underestimate plus distance_travelled.
    int gapPosition = 0; // where the space is located
    
    vector<string> frogs_toads;
    vector<vector<string>> solution; // the elements of the vector are string vectores. data structure-- doulbe vectore
    
public:
    
    int get_underestimate()
    {
        vector<string> intial;
        
        if(frogs_toads.size() == 5)// check if it is 2X2 game or 3X3 game
        {
            intial= initialList_2();
        }
        
        else
        {
            intial = initialList_3();
        }
        
        for(int i =0 ; i< frogs_toads.size();i++)// count how many element of frogs_toads and intial list matchecd
        {
            if(frogs_toads[i] == intial[i])
                underestimate ++;
        }
        return underestimate;
    }
    
    void updateDistanceTraveled(){ distance_travelled++;}
    
    void update_total_path(){total_path = underestimate + distance_travelled;} // This is for A* algorithm
   
    int get_total_path()
        {
            return underestimate + distance_travelled;
        }
    
    void printSolution()
        {
            for(int i = 0; i < solution.size(); i++)
            {
                for(int j = 0; j < solution[i].size(); j++)
                {
                    cout << "[";
                    cout << solution[i][j];
                    cout << "]";
                }
            cout << endl;
        }
    }
    // this is the overload function. Since the priority queue is sorted, but it does not know how to
    // sort a structure, so this function is to make sure the priority queue with state works
    bool operator < (const State_data& other) const
    {
        return this->total_path > other.total_path;
    }
    // overloading function equal to deep copy data
    State_data& operator = (const State_data& rhs)
    {
        if (this != &rhs)
        {
            this->underestimate = rhs.underestimate;
            this->distance_travelled = rhs.distance_travelled;
            this->total_path = rhs.total_path;
            this->frogs_toads = rhs.frogs_toads;
            this->solution = rhs.solution;
            this->gapPosition = rhs.gapPosition;
        }
        return *this;
    }
    //operator overloading to allow using = true
    bool operator == (const State_data& rhs)
    {
        bool same = true;
        
        for(int i = 0; i < rhs.frogs_toads.size(); i++)
        {
            if (this->frogs_toads[i] != rhs.frogs_toads[i])
            {
                same = false;
            }
        }
        
        return same;
    }
    // check if the game is over in this state 
    bool isSolution()
    {
        bool solutionFound = true;
        vector<string> final;
        int length;
        
        if(frogs_toads.size() == 5)
        {
            length = 5;
        }
        else
        {
            length = 7;
        }
        
        for (int i = 0; i < length/2; ++i)
        {
            if (this->frogs_toads[i] == "F" || this->frogs_toads[i] == " ")
            {
                solutionFound = false;
            }
        }
        
        for (int i = (length/2) + 1; i < length; ++i)
        {
            if (this->frogs_toads[i] == "T" || this->frogs_toads[i] == " ")
            {
                solutionFound = false;
            }
        }
        
        return solutionFound;
    }
    
};

// This function is to check if the state or the vector is already visited. This is particularly useful for A* algorithm, since this algorithm reduces the redundant path.
bool isAlreadyVisited(State_data &partial, vector<State_data> &list)
{
    bool alreadyVisited = false;
    
    for (int i = 0; i < list.size(); i++)
    {
        if (partial == list[i])
        {
            alreadyVisited = true;
        }
    }
    return alreadyVisited;
}

void Astar_algorithm (State_data startState, bool aStar)
{
    vector<State_data> alreadyVisited;// put all the state that generated by moves and jump in this vector
    priority_queue<State_data, vector<State_data>> pri_que;// the priority queue sort and store all the states and the vector contain states
    State_data partialPath; // create an object of state_data
    bool solutionFound = false;
    long numLoops = 0;// keep tracking how many steps that generated to get the final state
    
    pri_que.push(startState);
    
    
    // if a Star is true, then put the state in the vector
    if (aStar)
    {
        alreadyVisited.push_back(startState);
    }
    
    while (!solutionFound)
    {
        numLoops++;
        State_data currentState = pri_que.top();
        pri_que.pop();// the one poped up will be expand and generate more vectors.
        
        // check if can be moved to right
        if ( moveable_right(currentState.frogs_toads,currentState.gapPosition) == 1 )
        {
            // copy state
            partialPath = currentState;
            // do move
            move_right(partialPath.frogs_toads,partialPath.gapPosition);
            // update new distance
            partialPath.updateDistanceTraveled();
            
            if (aStar)
            {
                // update underestimate
                partialPath.get_underestimate();
            }
            //update total path
            partialPath.update_total_path();
            // Add previous move to solution vector
            partialPath.solution.push_back(currentState.frogs_toads);
            // check if state is solution
            if (partialPath.isSolution())
            {
                solutionFound = true;
                // add latest move to solution vector
                partialPath.solution.push_back(partialPath.frogs_toads);
                cout << "The shortest path solution has been found.\nIt took " << numLoops << " loop iterations. The solution is:\n";
                partialPath.printSolution();
                break;
            }
            
            if (aStar)
            {
                // check if state has already been visited
                if (!isAlreadyVisited(partialPath, alreadyVisited))
                {
                    pri_que.push(partialPath);
                    alreadyVisited.push_back(partialPath);
                }
            }
            else
            {
                pri_que.push(partialPath);
            }
            
             }
        if ( moveable_left(currentState.frogs_toads,currentState.gapPosition) == 1)
        {
            // copy state
            partialPath = currentState;
            // do move
            move_left(partialPath.frogs_toads,partialPath.gapPosition);
            // update new distance
            partialPath.updateDistanceTraveled();
            if (aStar)
            {
                // update underestimate
                partialPath.get_underestimate();
            }
            //update total path
            partialPath.update_total_path();
            // Add previous move to solution vector
            partialPath.solution.push_back(currentState.frogs_toads);
            // check if state is solution
            if (partialPath.isSolution())
            {
                solutionFound = true;
                // add latest move to solution vector
                partialPath.solution.push_back(partialPath.frogs_toads);
                cout << "The shortest path solution has been found.\nIt took " << numLoops << " loop iterations. The solution is:\n";
                partialPath.printSolution();
                break;
            }
            
            if (aStar)
            {
                // check if state has already been visited
                if (!isAlreadyVisited(partialPath, alreadyVisited))
                {
                    pri_que.push(partialPath);
                    alreadyVisited.push_back(partialPath);
                }
            }
            else
            {
                pri_que.push(partialPath);
            }
        }
        if ( can_jump_right(currentState.frogs_toads,currentState.gapPosition) == 1)
        {
            // copy state
            partialPath = currentState;
            // do move
            jump_right(partialPath.frogs_toads,partialPath.gapPosition);
            // update new distance
            partialPath.updateDistanceTraveled();
            if (aStar)
            {
                // update underestimate
                partialPath.get_underestimate();
            }
            //update total path
            partialPath.update_total_path();
            // Add previous move to solution vector
            partialPath.solution.push_back(currentState.frogs_toads);
            // check if state is solution
            if (partialPath.isSolution())
            {
                solutionFound = true;
                // add latest move to solution vector
                partialPath.solution.push_back(partialPath.frogs_toads);
                cout << "The shortest path solution has been found.\nIt took " << numLoops << " loop iterations. The solution is:\n";
                partialPath.printSolution();
                break;
            }
            
            if (aStar)
            {
                // check if state has already been visited
                if (!isAlreadyVisited(partialPath, alreadyVisited))
                {
                    pri_que.push(partialPath);
                    alreadyVisited.push_back(partialPath);
                }
            }
            else
            {
                pri_que.push(partialPath);
            }
        }
        if ( can_jump_left(currentState.frogs_toads,currentState.gapPosition) == 1)
        {
            // copy state
            partialPath = currentState;
            // do move
            jump_left(partialPath.frogs_toads,partialPath.gapPosition);
            // update new distance
            partialPath.updateDistanceTraveled();
            if (aStar)
            {
                // update underestimate
                partialPath.get_underestimate();
            }
            //update total path
            partialPath.update_total_path();
            // Add previous move to solution vector
            partialPath.solution.push_back(currentState.frogs_toads);
            // check if state is solution
            if (partialPath.isSolution())
            {
                solutionFound = true;
                // add latest move to solution vector
                partialPath.solution.push_back(partialPath.frogs_toads);
                cout << "The shortest path solution has been found.\nIt took " << numLoops << " loop iterations. The solution is:\n";
                partialPath.printSolution();
                break;
            }
            
            if (aStar)
            {
                // check if state has already been visited
                if (!isAlreadyVisited(partialPath, alreadyVisited))
                {
                    pri_que.push(partialPath);
                    alreadyVisited.push_back(partialPath);
                }
            }
            else
            {
                pri_que.push(partialPath);
            }
        }
    }
    
}
int main()
{
    State_data state;
    int size;
    
    cout<<"Please choose the version of Frogs and Toads 2 or 3 : ";
    cin>>size;
    
    if (size ==2)
    {
        state.frogs_toads = initialList_2();
        state.gapPosition = 2;
        
        cout << "\nDoing Branch and Bound search algorithm\n --------------------------------------" << endl;
        Astar_algorithm(state, false);
        
        state.frogs_toads = initialList_2();
        state.gapPosition = 2;
        
        cout << "\nDoing A* search algorithm\n ---------------------------" << endl;
        Astar_algorithm(state, true);
    }
    else if (size ==3)
    {
        state.frogs_toads = initialList_3();
        state.gapPosition = 3;
        
        
        cout << "\nDoing A* search algorithm\n ---------------------------" << endl;
        Astar_algorithm(state, true);
        
        
        cout << "\nDoing Branch and Bound search algorithm\n --------------------------------------" << endl;
        Astar_algorithm(state, false);
        
        state.frogs_toads = initialList_3();
        state.gapPosition = 3;
        
    }
    else
    {
        cout<<"Invalid input.";
    }
    
    
    return 0;
}
