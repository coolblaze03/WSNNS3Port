
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__
#include <vector>
using namespace std;

#define ALL -1
static const int MAX_NODE_ID = 1000;
static const int NETWORK_CYCLE = 20;
static const int NODE_INITIAL_ENERGY = 100; //joules
static const double NODE_RECEIVING_POWER = 0.048; //16ma x 3v = 48mw = .048 w
static double NODE_SETUP_TIME = 0.0001;//?
static const double NODE_TRANSMITTING_POWER = 0.051; //17ma * 3v = 51mw = .051w
static double SHIFT_RATE = 0.50;
static const int SINK_SETUP_TIME = -1;
static int TREE_ADJUST_TIME; //2 x MaxLevel x NETWORK_CYCLE
#define NODE_ID int
#define NUMBER_OF_NODES 100
#define NUMBER_OF_SINKS 4
//static int nodeID = 0;
static int tempdeadcounter = 0;
#define SINK_START_ID NUMBER_OF_NODES;
static int sinkID = SINK_START_ID;
static bool seedset = false;
#define RADIO_RANGE 15
#define FIELD_WIDTH 100
#define FIELD_HEIGHT 100
#define WAKEUP_ENERY_CONSUMED	(0.016 * 3 * 0.01)
#define ENERGY_SENDING_A_DATA_MESSAGE 0.00008671875 // Unit: joule. That is (0.017 + 0.008)(Amp) * 3 (Volt) * (37 * 8 / (250 * 1024)) (second). 
#define ENERGY_SENDING_A_DEAD_BROADCAST_MESSAGE 0.00002109375 // Unit: joule. That is (0.017 + 0.008)(Amp) * 3 (Volt) * (9 * 8 / (250 * 1024)) (second).
#define ENERGY_SENDING_A_BROADCAST_MESSAGE 0.00002109375 // Unit: joule. That is (0.017 + 0.008)(Amp) * 3 (Volt) * (9 * 8 / (250 * 1024)) (second).
#define ENERGY_RECEIVING_A_DATA_MESSAGE 0.00008325 // Unit: joule. That is (0.016 + 0.008) (Amp) * 3 (Volt) * (37 * 8 / (250 * 1024)) (second). 
#define ENERGY_RECEIVING_A_DEAD_BROADCAST_MESSAGE 0.00002025 // Unit: joule. That is (0.016+ 0.008) (Amp) * 3 (Volt) * (9 * 8 / (250 * 1024)) (second).
#define ENERGY_ACTIVE_LISTENING_AT_RECEIVING 0.000072 // Unit: joule. That is (0.016 +0.008) (Amp) * 3 (Volt) * 0.001 (second).
#define ENERGY_SLEEP_PROCESSOR_PER_SECOND 0.000024 // Unit: joule. That is 0.000008 (Amp) * 3 (Volt) * 1 (second).
#define MESSAGE_GENERATION_PERCENTAGE 10 //PERCENTAGE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BATTERY_RATIO 181.44



enum SHIFT_METHOD{
	SHIFT_SINK_CIRCLE = 0,
	SHIFT_SINK_CLUSTER = 1,
	SHIFT_SINK_NO_SHIFT = 2
};

class customTreeNode{
public:
	int ID;
	bool active;
	int x;
	int y;
	int num_nodes_below;
	customTreeNode(int val, int x, int y){
		ID = val;
		active = true;
		this->x = x;
		this->y = y;
		this->num_nodes_below = 0;
	}
	customTreeNode(){
		ID = -1;
		active = false;
		this->x = -1;
		this->y = -1;
		num_nodes_below = 0;
	}
	customTreeNode& operator=(const customTreeNode &rhs){
		this->ID = rhs.ID;
		this->active = rhs.active;
		this->x = rhs.x;
		this->y = rhs.y;
		this->num_nodes_below = rhs.num_nodes_below;
		return *this;
	}
	inline bool operator == (const customTreeNode &rhs){
		return (this->ID == rhs.ID);
	}
};

class cluster{
public:
	cluster(){
		active = true;
	}
	vector<int> values;
	bool contains(int val){
		vector<int>::iterator it = values.begin();
		while(it != values.end()){
			if ( (*it) == val)
				return true;
			it++;
		}
		return false;
	}
	cluster combine(cluster val){
		vector<int>::iterator it = val.values.begin();
		while(it != val.values.end()){
			if (!this->contains((*it)))
				values.push_back(*it);
			it++;
		}
		return *this;
	}
	bool isActive(){
		return active;
	}
	void setActive(bool val){
		active = val;
	}

private:
		bool active;
};

#endif
