#include "topicTable.h"

int errCode;

_sys_topic_list tList;
_sys_subscribers_list subscribers;
_sys_publishers_list publishers;
_sys_message_list msgList;

void _initialize_(){
	
	errCode = -1;

	tList.index = -1;
	tList.topics = (_sys_topic *)calloc(sizeof(_sys_topic), MAX_TOPICS);
	
	subscribers.sList = (_sys_subscribers *)calloc(sizeof(_sys_subscribers), MAX_TOPICS);	
	subscribers.index = -1;
	
	publishers.index = -1;
	publishers.pList = (_sys_publishers *)calloc(sizeof(_sys_publishers), MAX_TOPICS);
	
	msgList.mList = (_sys_message *)calloc(sizeof(_sys_message), MAX_TOPICS);
	msgList.index = -1;
}

int isValidTopic(const char *name){
	for(int i=0;i<=tList.index;i++){
		if(strcmp(name, tList.topics[i].name))
			return i;
	}
	return -1;
}

int topiclookup(char *name){
	int index = -1;
	if((index = isValidTopic(name)) != -1)
		return index;
	return TOPIC_NOT_FOUND;
}

void createtopic(int id,const char *tName){
	errCode = -1;
	if((tList.index+1) < MAX_TOPICS){
		tList.index++;
		strcpy(tList.topics[tList.index].name,tName);
		tList.topics[tList.index].owner_id = id;
	}else{
		errCode = MAX_TOPIC_REACHED;
	}
}

bool isRegisteredPub(int id,int tIndex,int &topic_index){

   if(publishers.pList == NULL)
      return false;

   for(int i = 0; i <= publishers.index; i++){
      if(publishers.pList[i].topic_index == tIndex){
			topic_index = i;
         for(int j = 0; j <= publishers.pList[i].index; j++){
            if(publishers.pList[i].users[j] == id){
               return true;
            }
         }
         return false;
      }
   }
   return false;
}

bool isRegisteredSubs(int id,int tIndex,int &topic_index){

	if(subscribers.sList == NULL)
		return false;
	
	for(int i = 0; i <= subscribers.index; i++){
		if(subscribers.sList[i].topic_index == tIndex){
			topic_index = i;
			for(int j = 0; j <= subscribers.sList[i].index; j++){
				if(subscribers.sList[i].users[j] == id){
					return true;
				}
			}
			return false;
		}		
	}
	return false;
}

void tsubscriber(int id,const char *name){
	errCode = -1;
	int index = isValidTopic(name);
	if(index == -1)
		return;
	
	int tIndex = -1;
	if(isRegisteredSubs(id,index,tIndex)) //if user not part of subscriber but others exists then return tIndex else -1
		return;
	
	if(tIndex == -1){
		subscribers.sList[++subscribers.index].topic_index = index;
		subscribers.sList[subscribers.index].users = (int *)calloc(sizeof(int), MAX_SUBSCRIBERS_PER_TOPIC);
		subscribers.sList[subscribers.index].index = -1;
		tIndex = subscribers.index;
	}
	
	if(subscribers.sList[tIndex].index == MAX_SUBSCRIBERS_PER_TOPIC)
		return;
	
	subscribers.sList[tIndex].users[++subscribers.sList[tIndex].index] = id;
}

void copyArray(int *&dest,int *source, int length){
	dest = (int *)calloc(sizeof(int),length);
   for(int i = 0; i < length; i++)
      dest[i] = source[i];
}

void getSubscriberIDs(int tindex,int *&subs_ids,int &count){
	for(int i = 0; i <= subscribers.index; i++){
		if(subscribers.sList[i].topic_index == tindex){
			copyArray(subs_ids,subscribers.sList[i].users,subscribers.sList[i].index+1);
			count = subscribers.sList[i].index+1;
			return;
		}
	}
}

int getTopicIndexMessageList(int index){
	for(int i = 0; i <= msgList.index; i++){
		if(msgList.mList[i].topic_index == index)
			return i;
	}
	return -1;
}

void publishmessage(int topic_index,int id,char *message){
	errCode = -1;	

	int publisher_index = -1;
	if(!isRegisteredPub(id,topic_index,publisher_index))		//This checks both valid publisher and topic
		return;
		
	int index = getTopicIndexMessageList(topic_index);
	_sys_message msg;
	_sys_message_internal msgInternal;
	int msgCount = 0;
	if(index == -1){
		if(msgList.index == MAX_TOPICS) 															// Publishing for the first time
			return;
		msg.topic_index = topic_index;
		msg.messages = new linkedList<_sys_message_internal>();
		strcpy(msgInternal.message,message);
		getSubscriberIDs(topic_index,msgInternal.subscb_users,msgInternal.count);
		msg.messages->getCount(msgCount);
		if(msgCount == MAX_MESSAGES_PER_TOPIC){
			errCode = MAX_MESSAGES_REACHED;
		}else{
			msg.messages->insert(msgInternal);
			msgList.mList[++msgList.index] = msg;
		}
	}else{
		msgList.mList[index].messages->getCount(msgCount);
		if(msgCount == MAX_MESSAGES_PER_TOPIC){
			errCode = MAX_MESSAGES_REACHED;
		}else{
			strcpy(msgInternal.message,message);
			getSubscriberIDs(topic_index,msgInternal.subscb_users,msgInternal.count);
			msgList.mList[index].messages->insert(msgInternal);
		}
	}
}

bool _getMessage_(int index,int id,char *rmessage){
	
	int mIndex = -1;
	for(int i = 0; i <= msgList.index; i++){
		if(msgList.mList[i].topic_index == index){
			mIndex = i;
			break;
		}
	}
	int count;
	msgList.mList[mIndex].messages->getCount(count);
	if(count == 0)
		return false;
	
	_sys_message_internal *msgInternal;
	msgList.mList[mIndex].messages->resetCurrent();
	for(int i = 0; i < count; i++){
		msgList.mList[mIndex].messages->getNode(&msgInternal);
		for(int j = 0; j < msgInternal->count; j++){
			if(id == msgInternal->subscb_users[j]){
				strcpy(rmessage, msgInternal->message);
				msgInternal->subscb_users[j] = -1;
				bool flag = false;
				for(int k = 0; k < msgInternal->count;k++){
					if(msgInternal->subscb_users[k] != -1){
						flag = true;
						break;
					}
				}
				if(!flag)
					msgList.mList[mIndex].messages->removeCurrent();
				return true;
			}
		}
		msgList.mList[mIndex].messages->increment();
	}
	return false;
}

void getmessage(int topic_index,int id,char *message){
	memset(message,0,MAX_MESSAGE_LENGTH);
	errCode = -1;
	int subs_index = -1;
	if(!isRegisteredSubs(id,topic_index,subs_index))
		return;
	_getMessage_(topic_index,id,message);
}

void tpublisher(int id,char *name){
	errCode = -1;
	int index = isValidTopic(name);
	if(index == -1)
		return;
	
	int tIndex = -1; 					//if user is not registered but topic exists in publishers
	if(isRegisteredPub(id,index,tIndex))
		return;
	
	if(tIndex == -1){ 					/* Topic doesnot exists Create one*/
		publishers.pList[++publishers.index].topic_index = index;
		publishers.pList[publishers.index].users = (int *)calloc(sizeof(int), MAX_PUBLISHERS_PER_TOPIC);
		publishers.pList[publishers.index].index = -1;
		tIndex = publishers.index;
	}
	if(publishers.pList[tIndex].index == MAX_PUBLISHERS_PER_TOPIC)
		return;
	publishers.pList[tIndex].users[++publishers.pList[tIndex].index] = id;
}
