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
      cout << "Max Topic Created. Failed" << endl;
   }
   _createTopic_(6,"StartUps");
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl;
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
		cout << "MAX Messages reached for the topic" << endl;
	_publishMessage_(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl;
	
	string rmsg;
	_getMessage_(index,2,rmsg);
	cout << rmsg << endl;
	
	_publishMessage_(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl;
}

int main(){
	__initialize__();
	testMaxTopicCreation();
	testMaxMessagesperTopic();
	return 0;
}
