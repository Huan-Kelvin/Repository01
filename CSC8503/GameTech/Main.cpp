#include "../../Common/Window.h"
#include "../CSC8503Common/IntroScreen.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"

#include "../CSC8503Common/NavigationGrid.h"
#include "BehaviourAction.h"
#include "TutorialGame.h"
#include "BehaviourSequence.h"
#include "BehaviourSelector.h"
#include "../CSC8503Common/PushdownMachine.h"

using namespace NCL;
using namespace CSC8503;

/*

The main function should look pretty familar to you!
We make a window, and then go into a while loop that repeatedly
runs our 'game' until we press escape. Instead of making a 'renderer'
and updating it, we instead make a whole game, and repeatedly update that,
instead. 

This time, we've added some extra functionality to the window class - we can
hide or show the 

三个部分：  物理  AI  网络链接
*/
/*ector <Vector3 > testNodes;
void TestStateMachine() {
	StateMachine* testMachine = new StateMachine();
	int data = 0;
	State* A = new State([&](float dt)->void
		{
		std::cout << "I’m in state A!\n";
		data++;
		}
	);
	
	State* B = new State([&](float dt)->void
		{
			std::cout << "I’m in state B!\n";
			data--;
		}
	);
	StateTransition * stateAB = new CSC8599::StateTransition(A, B, [&](void)->bool
		{
		return data > 10;
		}
	);
	StateTransition * stateBA = new CSC8599::StateTransition(B, A, [&](void)->bool
		 {
		return data < 0;
		}
	);
	testMachine->AddState(A);
	testMachine->AddState(B);
	testMachine->AddTransition(stateAB);
	testMachine->AddTransition(stateBA);
	
	for(int i = 0; i < 100; ++i) {
		testMachine->Update(1.0f);	
	}
}*/
//void TestPathfinding() {
//	NavigationGrid grid("TestGrid1.txt");
//	
//	NavigationPath outPath;
//
//	Vector3 startPos(80, 0, 10);
//	Vector3 endPos(80, 0, 80);
//	
//	bool found = grid.FindPath(startPos, endPos, outPath);
//	
//	Vector3 pos;
//	while (outPath.PopWaypoint(pos)) {
//		testNodes.push_back(pos);
//		
//	}
//}
//void DisplayPathfinding() {
//	for (int i = 1; i < testNodes.size(); ++i) {
//		Vector3 a = testNodes[i - 1];
//		Vector3 b = testNodes[i];
//		
//		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
//	}
//}
//void TestBehaviourTree() {
//	float behaviourTimer;
//	float distanceToTarget;
//	BehaviourAction* findKey = new BehaviourAction(" Find Key ",
//		[&](float dt, BehaviourState state)-> BehaviourState {
//			if (state == Initialise) {
//				std::cout << " Looking for a key !\n";
//				behaviourTimer = rand() % 100;
//				state = Ongoing;
//			}
//			else if (state == Ongoing) {
//				behaviourTimer -= dt;
//				if (behaviourTimer <= 0.0f) {
//					std::cout << " Found a key !\n";
//					return Success;
//				}
//			}
//			return state; // will be ’ongoing ’ until success
//		}
//	);
//
//
//	BehaviourAction * goToRoom = new BehaviourAction("Go To Room ",
//		[&](float dt, BehaviourState state)-> BehaviourState{
//			if (state == Initialise) {
//				std::cout << " Going to the loot room !\n";
//				state = Ongoing;
//			}
//			else if (state == Ongoing) {
//				distanceToTarget -= dt;
//				if (distanceToTarget <= 0.0f) {
//					std::cout << " Reached room !\n";
//					return Success;
//		  }
//	   }
//			return state; // will be ’ongoing ’ until success
//		}
//	);
//
//	BehaviourAction * openDoor = new BehaviourAction(" Open Door ",
//		[&](float dt, BehaviourState state)-> BehaviourState{
//			if (state == Initialise) {
//				std::cout << " Opening Door !\n";
//				return Success;
//			 }
//			return state;
//		}
//	);
//
//
//	BehaviourAction * lookForTreasure = new BehaviourAction(
//		" Look For Treasure ",
//		[&](float dt, BehaviourState state)-> BehaviourState{
//			if (state == Initialise) {
//				std::cout << " Looking for treasure !\n";
//				return Ongoing;
//			 }
//			else if (state == Ongoing) {
//				bool found = rand() % 2;
//				if (found) {
//					std::cout << "I found some treasure !\n";
//					return Success;
//				  }
//				std::cout << "No treasure in here ...\ n";
//				return Failure;
//			}
//			return state;
//		}
//	);
//
//	BehaviourAction * lookForItems = new BehaviourAction(
//		" Look For Items ",
//		[&](float dt, BehaviourState state)-> BehaviourState{
//			if (state == Initialise) {
//				std::cout << " Looking for items !\n";
//				return Ongoing;
//			 }
//			else if (state == Ongoing) {
//				 bool found = rand() % 2;
//				 if (found) {
//					 std::cout << "I found some items !\n";
//					 return Success;
//				 }
//				std::cout << "No items in here ...\ n";
//				return Failure;
//			}
//			return state;
//		}
//	);
//
//	BehaviourSequence* sequence = new BehaviourSequence(" Room Sequence ");
//	sequence-> AddChild(findKey);
//	sequence-> AddChild(goToRoom);
//	sequence-> AddChild(openDoor);
//
//	BehaviourSelector * selection =
//	new BehaviourSelector(" Loot Selection ");
//	selection-> AddChild(lookForTreasure);
//	selection-> AddChild(lookForItems);
//
//	BehaviourSequence * rootSequence =
//	new BehaviourSequence(" Root Sequence ");
//	rootSequence-> AddChild(sequence);
//	rootSequence-> AddChild(selection);
//
//	for (int i = 0; i < 5; ++i) {
//		rootSequence-> Reset();
//		behaviourTimer = 0.0f;
//		distanceToTarget = rand() % 250;
//		BehaviourState state = Ongoing;
//		std::cout << "We ’re going on an adventure !\n";
//		while (state == Ongoing) {
//			state = rootSequence-> Execute(1.0f); // fake dt
//		}
//		if (state == Success) {
//		std::cout << " What a successful adventure !\n";
//		}
//		else if (state == Failure) {
//			std::cout << " What a waste of time !\n";
//			
//		}
//	
//	}
//	std::cout << "All done !\n";
//}
//void TestPushdownAutomata(Window * w) {
//	PushdownMachine machine(new IntroScreen());
//	while (w-> UpdateWindow()) {
//		float dt = w-> GetTimer()->GetTimeDeltaSeconds();
//		if (!machine.Update(dt)) {
//			return;
//		}
//	}
//}

bool isLock = false;
void LockMouseToWindow(Window* w) {
	w->ShowOSPointer(isLock);
	w->LockMouseToWindow(!isLock);
	isLock = !isLock;
}

int main() {
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);

	if (!w->HasInitialised()) {
		return -1;
	}	
	srand(time(0));
	LockMouseToWindow(w);

	TutorialGame* g = new TutorialGame();
	w->GetTimer()->GetTimeDeltaSeconds(); //Clear the timer so we don't get a larget first dt!
	//TestStateMachine();
	//TestPathfinding();
	//TestBehaviourTree();
	//TestPushdownAutomata(w);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		float dt = w->GetTimer()->GetTimeDeltaSeconds();
		if (dt > 0.1f) {
			std::cout << "Skipping large time delta" << std::endl;
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::T)) {
			w->SetWindowPosition(0, 0);
		}

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::TAB)) {
			LockMouseToWindow(w);
		}

		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		g->UpdateGame(dt);
		
		//DisplayPathfinding();
	}
	Window::DestroyGameWindow();
}