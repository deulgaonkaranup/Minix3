#include "topicTable.h"
#include "errorMsg.h"

using namespace std;

void testMaxTopicCreation(){
   _createTopic_(1,"Sports");
   _createTopic_(2,"Technology");
   _createTopic_(3,"Business");
   _createTopic_(4,"Politics");
   _createTopic_(5,"Affaris");
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl << endl;
   }
   _createTopic_(6,"StartUps");
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl << endl;
   }
}

void testMaxMessagesperTopic(){
	
	string message[6];
	message[0] = "India vs Aus tie the test tournament 1 - 1";
	message[1] = "Real Madrid vs FC Bayern UEFA";
	message[2] = "India vs Aus series. India wins";
	message[3] = "Has Bhubeneshwar given enough ooportunities??";
	message[4] = "Is Zidane the best mid-fielder for Real??";
	message[5] = "who will win world cup russia??";

	int index = _topicLookup_("Sports");
	
	_topicPublisher_(1,"Sports");
	_topicSubscriber_(2,"Sports");
	
	_publishMessage_(index,1,message[0]);
	_publishMessage_(index,1,message[1]);
	_publishMessage_(index,1,message[2]);
	_publishMessage_(index,1,message[3]);
	_publishMessage_(index,1,message[4]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
	_publishMessage_(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
	
	string rmsg;
	_getMessage_(index,2,rmsg);
	cout << "2:  " << rmsg << endl << endl;
	
	_publishMessage_(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
}

void testSubscribers(){

	int index = _topicLookup_("Technology");
	
	_topicPublisher_(3,"Technology");	
	
	_topicSubscriber_(4,"Technology");
	
	_publishMessage_(index,3,"Why Facebook copied Snapchat Interface??");
	
	_topicSubscriber_(5,"Technology");

	_publishMessage_(index,3,"DeepMinds new VR Interface??");
	
	string rmsg;
	
	_getMessage_(index,4,rmsg);
	cout << "4:  " << rmsg << endl << endl;
	
	_getMessage_(index,4,rmsg);
	cout << "4:  " << rmsg << endl << endl;
	
	_getMessage_(index,5,rmsg);
	cout << "5:  " << rmsg << endl << endl;

}

int main(){
	__initialize__();
	testMaxTopicCreation();
	testMaxMessagesperTopic();
	testSubscribers();
	return 0;
}
