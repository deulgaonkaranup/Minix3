#include "topicTable.h"

void testMaxTopicCreation(){
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
     	printf("Max Topic Created. Failed \n");
   }
	
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"StartUps");
   createtopic(6,topic);
   if(errCode == MAX_TOPIC_REACHED){
      printf("Max Topic Created. Failed \n");
   }
}

void testMaxMessagesperTopic(){
	
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
		printf("MAX Messages reached for the topic\n");
	publishmessage(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		printf("MAX Messages reached for the topic\n");
	
	char rmsg[MAX_MESSAGE_LENGTH];
	getmessage(index,2,rmsg);
	printf("2:  ");
	printf("%s",rmsg);
	printf("\n\n");
	
	publishmessage(index,1,message[5]);
	if(errCode == MAX_MESSAGES_REACHED)
		printf("MAX Messages reached for the topic\n");
}

void testSubscribers(){
	
	char topic[MAX_TOPIC_LENGTH];
	memset(topic,0,MAX_TOPIC_LENGTH);
	strcpy(topic,"Technology");
	
	int index = topiclookup(topic);
	tpublisher(3,topic);	
	tsubscriber(4,topic);
	
	char message[MAX_MESSAGE_LENGTH];
	memset(message,0,MAX_MESSAGE_LENGTH);
	strcpy(message,"Why Facebook copied Snapchat Interface??");
	publishmessage(index,3,message);
	
	tsubscriber(5,topic);
	
	memset(message,0,MAX_MESSAGE_LENGTH);
	strcpy(message,"Deep Minds new VR INterface ?");

	publishmessage(index,3,message);
	
	char rmsg[MAX_MESSAGE_LENGTH];
	
	getmessage(index,4,rmsg);
	printf("4:  ");
	printf("%s",rmsg);
	printf("\n\n");
	
	getmessage(index,4,rmsg);
	printf("4:  ");
	printf("%s",rmsg);
	printf("\n\n");
	
	getmessage(index,5,rmsg);
	printf("5:  ");
	printf("%s",rmsg);
	printf("\n\n");

}

int main(){
	testMaxTopicCreation();
	testMaxMessagesperTopic();
	testSubscribers();
	return 0;
}
