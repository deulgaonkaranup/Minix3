#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minix_ipc.h"

char *string_return[]={
	"SUCCESS_MESSAGING"
	"MAX_TOPIC_REACHED"
	"TOPIC_NOT_FOUND"
	"MAX_MESSAGES_REACHED"
	"NULL_TOPICNAME_ERR"
	"DUPLICATE_PUBLISHER"
	"DUPLICATE_SUBSCRIBER"
	"BUFFER_OVERFLOW"
	"NOT_SUBSCRIBER_OF_TOPIC"
	"BUFFER_UNDERFLOW"
	"DUPLICATE_TOPIC"
	"TOPICS_FULL"
};


void displayErrorCode(int code){
	switch(code){
		case 101: printf("\n Maximum Limit Reached. \n");
					 break;
		case 102: printf("\n Topic entered is not found. \n");
					 break;
		case 103: printf("\n User is not registered. \n");
					 break;
		case 104: printf("\n No Messages to retrieve. \n");
					 break;
		default: break;
	}
}

int main(int argc, char** argv)
{
    int status,PublisherID,SubscriberID,string_return;
	 char choice,topic[MAX_TOPIC_LENGTH],topicToPublish[MAX_TOPIC_LENGTH],list_of_topics[MAX_TOPIC_LENGTH];
	 char topicToSubscribe[MAX_TOPIC_LENGTH],publishMessage[MAX_TOPIC_LENGTH],msg[MAX_MESSAGE_LENGTH],msg1[MAX_MESSAGE_LENGTH];
    int usr_input = -1;
    
    printf("\n\n-----CS551: Project 2-----\n\n");
    
    while(1)
    {
		  printf("\n-------Available Operations-------\n");
        printf("\n1. Create new TOPIC (TopicCreate) \n");
        printf("\n2. Topic Publisher Initiation (TopicPublisher) \n");
        printf("\n3. Topic Subscriber Initiation (TopicSubscriber) \n");
        printf("\n4. Publish a message (Publish) \n");
        printf("\n5. Retrieve a message (Retrieve) \n");
        printf("\n6. Show Topics Available (TopicLookup) \n");
        
        printf("\n0. Execution of Program Ending \n\n");
        
        printf("\n Make your choice : ");
        scanf(" %d",&usr_input);
        
        switch(usr_input)
        {
            case 1:
               printf("\n--Creating New TOPIC (TopicCreate)--\n");
					printf("\nEnter a topic :");
					scanf (" %[^\n]%*c", topic);
					int id;
					printf("\nEnter ID: ");
					scanf("%d",&id);
					displayErrorCode(createtopic(id,topic));
               break;
            case 2:
               printf("\n--Topic Publisher Initiation (TopicPublisher)--\n");
					printf("\nEnter publisher ID :");
					scanf("%d",&PublisherID);
					printf("\nEnter a topic :");
					scanf (" %[^\n]%*c", topicToPublish);
					displayErrorCode(tpublisher(PublisherID,topicToPublish));
               break;
            case 3:
               printf("\n--Topic Subscriber Initiation (TopicSubscriber)--\n");
					printf("\nEnter subscriber ID :");
					scanf("%d",&SubscriberID);
					printf("\nEnter a topic :");
					scanf (" %[^\n]%*c", topicToSubscribe);
					displayErrorCode(tsubscriber(SubscriberID,topicToSubscribe));
               break;
            case 4:
               printf("\n--Publish a message (Publish)--\n");
					printf("\nEnter publisher ID :");
					scanf("%d",&PublisherID);
					printf("\nEnter a topic :");
					scanf (" %[^\n]%*c", topic);
					printf("\nEnter a message :");
					scanf (" %[^\n]%*c", msg);
					int tindex = topiclookup(topic);
					if(tindex == -1)
						displayErrorCode(tindex);
					displayErrorCode(publishmessage(tindex,PublisherID,msg));
               break;
            case 5:
               printf("\n--Retrieve a message (Retrieve)--\n");
					printf("\nEnter subscriber ID :");
					scanf("%d",&SubscriberID);
					printf("\nEnter a topic :");
					scanf (" %[^\n]%*c", topic);
					int index = topiclookup(topic);
					char msg[MAX_MESSAGE_LENGTH];
					displayErrorCode(getmessage(index,SubscriberID,msg));
					printf("\nMessage : %s\n", msg);
               break;
            /*case 6:
              	printf("\n--Show Topics Available (TopicLookup)--\n");
					status = topiclookup(list_of_topics);
    				printf("\nRetrieved topics : \n");
					char *token = strtok(list_of_topics, ";");
					while(token) {
						printf("%s\n", token);
						token = strtok(NULL, ";");
					}
               break;*/
            case 0:
               exit(0);
               break;
            default :
               printf("\Error in input. Please Try again... \n");
               break;
        }
    }
}
