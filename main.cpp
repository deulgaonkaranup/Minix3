#include "topicTable.h"
#include "errorMsg.h"

using namespace std;

void testMaxTopicCreation(){
<<<<<<< HEAD
	char topic[MAX_TOPIC_LENGTH];
	strcpy(topic,"Sports");
   createtopic(1,topic);
	
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"Technology");
   createtopic(1,topic);
   
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"Business");
   createtopic(1,topic);

	
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"Politics");
   createtopic(1,topic);
	
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"Affairs");
   createtopic(1,topic);
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl << endl;
   }
	
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"StartUps");
   createtopic(6,topic);
=======
   _createTopic_(1,"Sports");
   _createTopic_(2,"Technology");
   _createTopic_(3,"Business");
   _createTopic_(4,"Politics");
   _createTopic_(5,"Affaris");
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl << endl;
   }
   _createTopic_(6,"StartUps");
>>>>>>> ddf0d68c194a5b6e7c126e6c35014c9d0a2d8832
   if(errCode == MAX_TOPIC_REACHED){
      cout << "Max Topic Created. Failed" << endl << endl;
   }
}

void testMaxMessagesperTopic(){
	
<<<<<<< HEAD
	char message[6][MAX_MESSAGE_LENGTH];
	strcpy(message[0],"India vs Aus tie the test tournament 1 - 1");
	strcpy(message[1],"Real Madrid vs FC Bayern UEFA");
	strcpy(message[2],"India vs Aus series. India wins");
	strcpy(message[3],"Has Bhubeneshwar given enough ooportunities??");
	strcpy(message[4],"Is Zidane the best mid-fielder for Real??");
	strcpy(message[5],"who will win world cup russia??");
	
	char topic[MAX_TOPIC_LENGTH];
	strcpy(topic,"Sports");
	int index = topiclookup(topic);
	
	tpublisher(1,topic);
	tsubscriber(2,topic);
	
	publishmessage(index,1,message[0]);
	publishmessage(index,1,message[1]);
	publishmessage(index,1,message[2]);
	publishmessage(index,1,message[3]);
	publishmessage(index,1,message[4]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
	publishmessage(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
	
	char rmsg[MAX_MESSAGE_LENGTH];
	getmessage(index,2,rmsg);
	cout << "2:  " << rmsg << endl << endl;
	
	publishmessage(index,1,message[5]);
=======
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
>>>>>>> ddf0d68c194a5b6e7c126e6c35014c9d0a2d8832
	if(errCode == MAX_MESSAGES_REACHED)
		cout << "MAX Messages reached for the topic" << endl << endl;
}

void testSubscribers(){
<<<<<<< HEAD
	
	char topic[MAX_TOPIC_LENGTH];
	strcpy(topic,"Technology");
	
	int index = topiclookup(topic);
	tpublisher(3,topic);	
	tsubscriber(4,topic);
	
	char message[MAX_MESSAGE_LENGTH];
	strcpy(message,"Why Facebook copied Snapchat Interface??");
	publishmessage(index,3,message);
	
	tsubscriber(5,topic);
	
	memset(message,0,MAX_MESSAGE_LENGTH);
	strcpy(message,"Deep Minds new VR INterface ?");

	publishmessage(index,3,message);
	
	char rmsg[MAX_MESSAGE_LENGTH];
	
	getmessage(index,4,rmsg);
	cout << "4:  " << rmsg << endl << endl;
	
	getmessage(index,4,rmsg);
	cout << "4:  " << rmsg << endl << endl;
	
	getmessage(index,5,rmsg);
=======

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
>>>>>>> ddf0d68c194a5b6e7c126e6c35014c9d0a2d8832
	cout << "5:  " << rmsg << endl << endl;

}

int main(){
<<<<<<< HEAD
	_initialize_();
=======
	__initialize__();
>>>>>>> ddf0d68c194a5b6e7c126e6c35014c9d0a2d8832
	testMaxTopicCreation();
	testMaxMessagesperTopic();
	testSubscribers();
	return 0;
}
